#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "BibliotecaLista/ElementoLista.h"
#include "BibliotecaLista/NodoLista.h"
#include "BibliotecaLista/Lista.h"
#include "BibliotecaLista/funcionesLista.h"

struct NodoLista *extraerNodo(struct Lista &baraja, int posicion) {
    struct NodoLista *nodoExtraido;

    if (posicion == 1) {
        nodoExtraido = baraja.inicio;
        baraja.inicio = baraja.inicio->siguiente;
    } else {
        struct NodoLista *nodoAnterior = nullptr;
        struct NodoLista *nodoActual = baraja.inicio;

        int pos = 1;

        while (pos < posicion) {
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->siguiente;
            pos++;
        }
        nodoAnterior->siguiente = nodoActual->siguiente;
        nodoExtraido = nodoActual;
    }
    nodoExtraido->siguiente = nullptr;

    baraja.longitud--;
    return nodoExtraido;
}

void barajear(struct Lista &baraja) {
    int pendientes = baraja.longitud;

    while (pendientes > 0) {
        int pos = pendientes / 2 + 1;

        struct NodoLista *nodoExtraido = extraerNodo(baraja, pos);

        struct NodoLista *nodoActual = baraja.inicio;
        while (nodoActual->siguiente != nullptr) {
            nodoActual = nodoActual->siguiente;
        }
        nodoActual->siguiente = nodoExtraido;
        baraja.longitud++;
        pendientes--;
    }
}

void crear_baraja(struct Lista &baraja) {
    construir(baraja);
    struct ElementoLista elemento;

    char palos[] = {'C', 'D', 'T', 'E'};
    int n = sizeof(palos) / sizeof(palos[0]);

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= 13; j++) {
            elemento.palo = palos[i];
            elemento.numero = j;
            insertarAlFinal(baraja, elemento);
        }
    }
}

int main() {
    struct Lista baraja;

    crear_baraja(baraja);

    cout << "Baraja sin barajear: " << endl;
    imprimir(baraja);
    cout << endl;

    barajear(baraja);

    cout << "Baraja  barajeada: " << endl;
    imprimir(baraja);
    cout << endl;

    return 0;
}
