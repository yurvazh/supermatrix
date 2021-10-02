#include<iostream>
#include "supermatrix.h"

using namespace std;

int main() {
    int n, m, n1, m1;
    cout << "size of first matrix: \n";
    cin >> n >> m;
    cout << "\nsize of second matrix: \n";
    cin >> n1 >> m1;
    cout << "integers for multiplication and power: \n";
    int d, q;
    cin >> d >> q;
    supermatrix<int> a(n, m), b(n1, m1);
    cout << "\nfirst matrix is: \n";
    cin >> a;
    cout << "\nsecond matrix is: \n";
    cin >> b;

    cout << "\n\n\n RESULTS : \n";
    cout << "A + B = \n";

    try {
        cout << (a + b);
    } catch (const char *msg) {
        cerr << "ERROR: " << msg << endl;
    }
    cout << "A * B = \n";
    try {
        cout << (a * b);
    } catch (const char *msg) {
        cerr << "ERROR: " << msg << endl;
    }
    cout << "Transposed A: \n";
    cout << a.tr();
    cout << "Transposed B: \n";
    cout << b.tr();
    cout << "A * d = \n";
    cout << (a * d);
    cout << "A ^ q = \n";
    try {
        cout << (a ^ q);
    } catch (const char* msg) {
        cerr << "ERROR: " << msg << endl;
    }
    cout << "B * d = \n";
    cout << (b * d);
    cout << "B ^ q = \n";
    try {
        cout << (b ^ q);
    } catch (const char *msg) {
        cerr << "ERROR: " << msg << endl;
    }
    return 0;
}