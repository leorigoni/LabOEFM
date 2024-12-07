#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    // Definizione del numero originale
    double numero_originale = 8.9273e+08;

    // Conversione in formato 892.73e+06
    double numero_convertito = numero_originale / pow(10, 7); // Dividiamo per 10^3

    // Stampa del risultato
    std::cout << numero_convertito << std::endl;

    return 0;
}
