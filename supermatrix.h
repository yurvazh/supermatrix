//
// Created by Yury Vazhenin on 29.09.2021.
//

#ifndef MATRIX_SUPERMATRIX_H
#define MATRIX_SUPERMATRIX_H

#include<iostream>
#include<vector>

using namespace std;
using ii = pair<int, int>;

template <typename T>

class supermatrix {
    int n, m;
    vector<vector<T>> v;
public:
    supermatrix(vector<vector<T>> vec);
    supermatrix(int n_, int m_);
    ii size() const {return make_pair(n, m);}
    const supermatrix operator+(const supermatrix&) const;
    const supermatrix operator*(T) const;
    const supermatrix operator^(int p) const;
    supermatrix operator*(const supermatrix&) const;
    vector<T>& operator[](int i) {return v[i];} ;
    const vector<T>& operator[](int i) const {return v[i];} ;
    supermatrix tr();
    supermatrix obr();
    long long det();
    template<typename Type> friend istream& operator>>(istream&, supermatrix<Type>&);
    template<typename Type> friend ostream& operator<<(ostream&, supermatrix<Type>&);
};
template<typename T>
supermatrix<T>::supermatrix(vector<vector<T>> vec) {
    n = vec.size();
    m = 0;
    if (n > 0)
        m = vec[0].size();
    v = vec;
}
template<typename T>
supermatrix<T>::supermatrix(int n_, int m_) {
    n = n_;
    m = m_;
    v.resize(n);
    for (int i = 0; i < n; i++)
        v[i].assign(m, 0);
}

template<typename T>
const supermatrix<T> supermatrix<T>::operator*(T k) const{
    vector<vector<T>> res(n);
    for (int i = 0; i < n; i++) {
        res[i].resize(m);
        for (int j = 0; j < m; j++) {
            res[i][j] = v[i][j] * k;
        }
    }
    return supermatrix(res);
}

template<typename T>

supermatrix<T> supermatrix<T>::operator*(const supermatrix<T>& a) const {
    if (m != a.n) {
        throw "Multiplication is impossible";
    } else {
        vector<vector<T>> res(n);
        for (int i = 0; i < n; i++) {
            res[i].assign(a.m, 0);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < a.m; j++) {
                for (int k = 0; k < m; k++) {
                    res[i][j] += v[i][k] * (a.v)[k][j];
                }
            }
        }
        return supermatrix(res);
    }
}
template <typename T>
long long supermatrix<T>::det() {
    if (n != m) {
        throw "matrix is not square";
    } else if (n == 1) {
        return v[0][0];
    } else if (n == 2) {
        return v[0][0] * v[1][1] - v[0][1] * v[1][0];
    } else {
        vector<vector<T>> ap(n - 1);
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (k != i) {
                        ap[j - 1].push_back(v[j][k]);
                    }
                }
            }
            if (i % 2 == 0) {
                sum += v[0][i] * supermatrix(ap).det();
            } else {
                sum -= v[0][i] * supermatrix(ap).det();
            }
            for (int k = 0; k < n - 1; k++) {
                ap[k].resize(0);
            }
        }
        return sum;
    }
}
template<typename T>
const supermatrix<T> supermatrix<T>::operator^(int p) const {
    if (n != m) {
        throw "Power is impossible";
    } else {
        if (p == 1) {
            return *this;
        } else if (p % 2 == 0) {
            return (*this ^ (p / 2)) * (*this ^ (p / 2));
        } else {
            return (*this ^ (p - 1)) * (*this);
        }
    }
}

template <typename T>

const supermatrix<T> supermatrix<T>::operator+(const supermatrix<T>& a) const {
    if ((n != a.n) || (m != a.m)) {
        throw "Differnt matrix's sizes";
    } else {
        vector<vector<T>> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = v[i];
            for (int j = 0; j < m; j++) {
                res[i][j] += a[i][j];
            }
        }
        return supermatrix(res);
    }
}

template<typename T>
supermatrix<T> supermatrix<T>::tr() {
    vector<vector<T>> res(m);
    for (int i = 0; i < m; i++) {
        res[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res[j][i] = v[i][j];
        }
    }
    return supermatrix(res);
}

template<typename T>
supermatrix<T> supermatrix<T>::obr() {
    if (n != m) {
        throw "matrix is not square";
    } else {
        supermatrix<T> ed(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j)
                    ed[i][j] = 0.0;
                else
                    ed[i][j] = 1.0;
            }
        }
        supermatrix<T> matr = *this;
        for (int i = 0; i < n; i++) {
            bool x = false;
            for (int j = i; j < n; j++) {
                if (matr[j][i] != 0.0) {
                    if (i != j) {
                        swap(matr[i], matr[j]);
                        swap(ed[i], ed[j]);
                    }
                    x = true;
                    break;
                }
            }
            if (not x) {
                throw "impossible to find reverse matrix";
            }
            double k1 = matr[i][i];
            for (int j = 0; j < n; j++) {
                matr[i][j] /= k1;
                ed[i][j] /= k1;
            }
            for (int j = i + 1; j < n; j++) {
                double t = matr[j][i];
                for (int k = 0; k < n; k++) {
                    matr[j][k] -= matr[i][k] * (t / matr[i][i]);
                    ed[j][k] -= ed[i][k] * (t / matr[i][i]);
                }
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                double m1 = matr[i][j];
                for (int k = 0; k < n; k++) {
                    matr[i][k] -= matr[j][k] * (m1 / matr[j][j]);
                    ed[i][k] -= ed[j][k] * (m1 / matr[j][j]);
                }
            }
        }
        return ed;
    }
}

template<typename T>

istream& operator>>(istream& in, supermatrix<T>& a) {
    for (int i = 0; i < a.size().first; i++) {
        for (int j = 0; j < a.size().second; j++) {
            in >> a[i][j];
        }
    }
    return in;
}
template<typename T>
ostream& operator<<(ostream& out, supermatrix<T> a) {
    for (int i = 0; i < a.size().first; i++) {
        for (auto j : a[i]) {
            out << j << " ";
        }
        out << "\n";
    }
    return out;
}
#endif //MATRIX_SUPERMATRIX_H
