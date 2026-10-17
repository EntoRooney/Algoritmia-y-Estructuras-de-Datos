#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "BibliotecaCola/funcionesCola.h"
#include "BibliotecaCola/ElementoCola.h"
#include "BibliotecaCola/NodoCola.h"
#include "BibliotecaCola/Cola.h"

int main() {
    struct Cola cola;
    construir(cola);
    int n = 6;

    encolar(cola, {1});
    for (int i = 0; i < n; i++) {
        struct ElementoCola e = desencolar(cola);
        int numero = e.codigo;
        cout << numero << ' ';
        if (i + 1 < n) {
            encolar(cola, {numero * 10});
            encolar(cola, {numero * 10 + 1});
        }
    }
    return 0;
}
