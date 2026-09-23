#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/ElementoLista.h"
#include "Bibliotecas/NodoLista.h"
#include "Bibliotecas/Lista.h"
#include "Bibliotecas/funcionesLista.h"

void crear_baraja(struct Lista &baraja) {
    construir(baraja);
    char palos[] = {'C', 'D', 'T', 'E'};
    struct ElementoLista elemento;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 13; j++) {
            elemento.numeros = j;
            elemento.palos = palos[i];
            insertarAlFinal(baraja, elemento);
        }
    }
}

NodoLista *extraerEnPosicion(struct Lista &baraja, int posicion) {
    if (esListaVacia(baraja))return nullptr;
    struct NodoLista *nodoExtraido;
    //caso donde sea el primer nodo
    if (posicion == 0) {
        nodoExtraido = baraja.inicio;
        baraja.inicio = baraja.inicio->siguiente;
    } else {
        struct NodoLista *nodoAnterior = nullptr;
        struct NodoLista *nodoActual = baraja.inicio;

        int i = 0;
        while (i < posicion) {
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->siguiente;
            i++;
        }
        //desconectamos el nodo
        nodoAnterior->siguiente = nodoActual->siguiente;
        nodoExtraido = nodoActual;
    }
    //desconectamos completamnete del nodo
    nodoExtraido->siguiente = nullptr;

    baraja.longitud--;
    return nodoExtraido;
}

void barajando(struct Lista &baraja) {
    srand(time(nullptr));

    int pendientes = baraja.longitud;

    while (pendientes > 0) {
        //generamos una posiion aleatoria dentro de la zona de pendientes
        int posiciones = rand() % pendientes;
        //extraemos el nodo
        struct NodoLista *nodoExtraido=extraerEnPosicion(baraja,posiciones);

        if (esListaVacia(baraja)) {
            baraja.inicio=nodoExtraido;
        }else {
            struct NodoLista *recorrido=baraja.inicio;
            while (recorrido->siguiente!=nullptr) {
                recorrido=recorrido->siguiente;
            }
            recorrido->siguiente=nodoExtraido;
        }
        baraja.longitud++;
        pendientes--;
    }
}


int main() {
    struct Lista baraja;
    //PARTE 1
    crear_baraja(baraja);
    cout<<"BARAJA ORIGINAL"<<endl;
    imprimir(baraja);
    cout<<"BARAJADO"<<endl;
    barajando(baraja);
    imprimir(baraja);
    cout<<"LIBERAR MEMORIA"<<endl;
    destruir(baraja);
    imprimir(baraja);
    return 0;
}
