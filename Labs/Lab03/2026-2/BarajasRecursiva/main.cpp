#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "BibliotecaLista/ElementoLista.h"
#include "BibliotecaLista/NodoLista.h"
#include "BibliotecaLista/Lista.h"
#include "BibliotecaLista/funcionesLista.h"

struct NodoLista *extraerNodo(struct Lista &baraja, int posicion) {
    if (esListaVacia(baraja)) return nullptr;

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

void insertarNodoAlFinal(struct Lista &baraja, struct NodoLista *nodo) {
    if (nodo == nullptr) return;

    if (esListaVacia(baraja)) {
        baraja.inicio = nodo;
    } else {
        struct NodoLista *rec = baraja.inicio;
        while (rec->siguiente != nullptr) {
            rec = rec->siguiente;
        }
        rec->siguiente = nodo;
    }

    baraja.longitud++;
}

void barajearRecursivo(struct Lista &baraja, int pendientes) {
    // caso base
    if (pendientes == 0) return;

    // posición dentro de la zona pendiente
    int pos = pendientes / 2 + 1;

    // extraemos el nodo de esa posición
    struct NodoLista *nodoExtraido = extraerNodo(baraja, pos);

    // lo mandamos al final
    insertarNodoAlFinal(baraja, nodoExtraido);

    // llamada recursiva
    barajearRecursivo(baraja, pendientes - 1);
}


void barajear(struct Lista &baraja) {
    barajearRecursivo(baraja, baraja.longitud);
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

    cout << "Baraja barajeada: " << endl;
    imprimir(baraja);
    cout << endl;
    return 0;
}
