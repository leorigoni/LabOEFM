#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int n=0;
    cout << "N spostamenti: ";
    cin >> n;
    cout << endl;
    double numero_originale=4.56;
    double numero_convertito=numero_originale*pow(10, n);
    cout << numero_convertito << endl;
    return 0;
}
