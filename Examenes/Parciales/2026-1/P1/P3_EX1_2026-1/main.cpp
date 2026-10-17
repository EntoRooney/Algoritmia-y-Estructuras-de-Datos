#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "BibliotecaLista/funcionesLista.h"
#include "BibliotecaLista/ElementoLista.h"
#include "BibliotecaLista/NodoLista.h"
#include "BibliotecaLista/Lista.h"

void agregarNodo(struct Lista &listaCircular, struct NodoLista *nodoAagregar) {
    //caso 1: no hay nada en la lista
    if (esListaVacia(listaCircular)) {
        listaCircular.inicio = nodoAagregar;
        listaCircular.inicio->next = nodoAagregar;
    } else {
        //ya hay elementos en la lista
        struct NodoLista *nodoFinal = obtenerUltimoNodo(listaCircular);
        nodoFinal->next = nodoAagregar;
        nodoAagregar->next = listaCircular.inicio;
    }
    listaCircular.longitud++;
}

void calcularSkipNext(struct Lista &listaCircular) {
    //aqui calculamos los skip_next de los nodos
    struct NodoLista *recorrido = listaCircular.inicio;
    for (int i = 0; i < listaCircular.longitud; i++) {
        recorrido->skip_next = recorrido->next->next;
        recorrido = recorrido->next;
    }
}

void auto_healing(struct Lista &listaCircular) {
    if (listaCircular.inicio == nullptr)return;

    int cantidad = listaCircular.longitud;

    struct NodoLista *nodoAnterior = obtenerUltimoNodo(listaCircular);
    struct NodoLista *recorrido = listaCircular.inicio;

    for (int i = 0; i < cantidad; i++) {
        struct NodoLista *siguiente = recorrido->next;

        if (!recorrido->elemento.is_active) {
            nodoAnterior->next = siguiente;

            if (recorrido == listaCircular.inicio) {
                listaCircular.inicio = siguiente;
            }

            delete recorrido;
            listaCircular.longitud--;
        } else {
            nodoAnterior = recorrido;
        }
        recorrido = siguiente;
    }
    if (listaCircular.longitud == 0) {
        listaCircular.inicio = nullptr;
    } else {
        calcularSkipNext(listaCircular);
    }
}

void desactivarNodo(struct Lista &listaCircular, int id) {
    int cantidad = listaCircular.longitud;
    struct NodoLista *nodoActual = listaCircular.inicio;

    for (int i = 0; i < cantidad; i++) {
        if (nodoActual->elemento.node_id == id) {
            nodoActual->elemento.is_active = false;
            cout << ">>>>Nodo " << id << " cae<<<<" << endl;
            return;
        }
        nodoActual = nodoActual->next;
    }
}

int main() {
    struct Lista listaCircular;
    construir(listaCircular);
    agregarNodo(listaCircular, new NodoLista{{10, true}, nullptr, nullptr});
    agregarNodo(listaCircular, new NodoLista{{20, true}, nullptr, nullptr});
    agregarNodo(listaCircular, new NodoLista{{30, true}, nullptr, nullptr});
    agregarNodo(listaCircular, new NodoLista{{40, true}, nullptr, nullptr});
    agregarNodo(listaCircular, new NodoLista{{50, true}, nullptr, nullptr});
    calcularSkipNext(listaCircular);
    imprimir(listaCircular);
    desactivarNodo(listaCircular, 20);
    desactivarNodo(listaCircular, 30);
    cout << endl << "Estado antes de auto_healing" << endl;
    cout << "Anillo (" << listaCircular.longitud << " nodos): " << endl;
    imprimir(listaCircular);
    cout << endl << "Estado despues de auto_healing" << endl;
    auto_healing(listaCircular);
    cout << "Anillo (" << listaCircular.longitud << " nodos): " << endl;
    imprimir(listaCircular);

    return 0;
}
