#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "BibliotecasFunciones/funcionesLista.h"
#include "BibliotecasFunciones/ElementoLista.h"
#include "BibliotecasFunciones/NodoLista.h"
#include "BibliotecasFunciones/Lista.h"

void moverBloques(struct Lista &lista, struct NodoLista *&head, struct NodoLista *&tail,  char *posicionPedida) {
    struct NodoLista *jugadorActual = lista.inicio;
    struct NodoLista *jugadorAnterior = nullptr;

    while (jugadorActual != nullptr) {

        if (strcmp(jugadorActual->elemento.posiciones, posicionPedida) == 0) {

            struct NodoLista *jugadorSiguiente = jugadorActual->siguiente;

            if (jugadorAnterior == nullptr) {
                lista.inicio=jugadorSiguiente;
            } else {
                jugadorAnterior->siguiente = jugadorSiguiente;
            }

            jugadorActual->siguiente = nullptr;

            if (head == nullptr) {
                head = tail = jugadorActual;
            } else {
                tail->siguiente = jugadorActual;
                tail = jugadorActual;
            }

            jugadorActual = jugadorSiguiente;

        } else {
            jugadorAnterior = jugadorActual;
            jugadorActual = jugadorActual->siguiente;
        }
    }
}

void ordernarPosiciones(struct Lista &lista,  char formaciones[][50], int numPosi) {
    struct NodoLista *head = nullptr;
    struct NodoLista *tail = nullptr;

    for (int i = 0; i < numPosi; i++) {
        moverBloques(lista, head, tail, formaciones[i]);
    }

    if (head != nullptr) {
        lista.inicio = head;
    }
}

int main() {
    //apertura de archivos
    ifstream archJugadores;
    archJugadores.open("ArchivosDeDatos/Nombres.txt", ios::in);
    if (not archJugadores.is_open()) {
        cout << "ERROR al abrir el archivo Nombres.txt" << endl;
        exit(1);
    }

    ifstream archPosiciones;
    archPosiciones.open("ArchivosDeDatos/Posiciones.txt", ios::in);
    if (not archPosiciones.is_open()) {
        cout << "ERROR al abrir el archivo Posiciones.txt" << endl;
        exit(1);
    }

    struct Lista lista;
    construir(lista);

    struct ElementoLista elemento;

    char c;


    while (true) {
        archJugadores >> c >> elemento.numCamiseta;
        if (archJugadores.eof()) break;
        archJugadores.get();
        archJugadores.getline(elemento.nombre, 50, ',');
        archJugadores.get();
        archJugadores.get();
        archJugadores.getline(elemento.posiciones, 50, '"');
        archJugadores.get();
        archJugadores.get();
        insertarAlFinal(lista, elemento);
    }

    cout << "ANTES DE ORDENAR " << endl;
    imprimirLista(lista);

    char formaciones[10][50];
    int numPosi = 0;

    while (archPosiciones.getline(formaciones[numPosi], 50)) {
        if (strlen(formaciones[numPosi]) > 0) {
            numPosi++;
        }
    }

    ordernarPosiciones(lista, formaciones, numPosi);

    cout << "DESPUES DE ORDENAR " << endl;
    imprimirLista(lista);
    return 0;
}
