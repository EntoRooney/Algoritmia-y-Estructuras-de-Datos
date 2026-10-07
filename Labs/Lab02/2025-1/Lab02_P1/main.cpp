#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "BibliotecaLista/funcionesLista.h"
#include "BibliotecaLista/ElementoLista.h"
#include "BibliotecaLista/NodoLista.h"
#include "BibliotecaLista/Lista.h"

void ordenarLista(struct Lista &participantes) {
    //el problema nos pide que los pares esten al principio de la lista
    //y despues los impares

    //comenzamos definiendo los nodos para recorrer la lista

    struct NodoLista *actual = participantes.inicio;
    struct NodoLista *anterior = nullptr;

    //vamos a hacer con un nodo de FinOrdenado para respetar el orden de llegada
    struct NodoLista *finOrdenado = nullptr;

    while (actual != nullptr) {
        //definimos otro puntero que nos ayudara mas adelante
        struct NodoLista *siguiente = actual->siguiente;

        //hacemos la validacion de la condicion
        if (actual->elemento.id % 2 == 0) {
            //ahora tenemos dos casos
            //caso 1:Si nuestra zona de ordenados aun no esta definida
            if (finOrdenado == nullptr) {
                //aqui tenemos dos casos
                //si el primero de la fila es el que tenemos que ordenar
                //simplemente le ponemos el puntero y avanzamos
                if (anterior == nullptr) {
                    finOrdenado = actual;

                    anterior = actual;
                    actual = siguiente;
                } else {
                    //pero si esta mas adelante
                    //lo movemos al inicio y le ponemos el puntero
                    anterior->siguiente = siguiente;

                    actual->siguiente = participantes.inicio;
                    participantes.inicio = actual;
                    finOrdenado = actual;

                    actual = siguiente;
                }
            } else {
                //si nuestra zona ordenada ya esta definida

                //aqui tambien tenemos dos casos
                //si el anterior es el fin ordenado
                if (anterior == finOrdenado) {
                    //simplemente ampliamos la zona
                    finOrdenado = actual;

                    anterior = actual;
                    actual = siguiente;
                } else {
                    //cuando esta lejos del fin ordenado
                    anterior->siguiente = siguiente;
                    //hacemos que el actual apunte a lo que apuntaba el fin Ordenado
                    actual->siguiente = finOrdenado->siguiente;
                    //y ponemos el actual despues del fin Ordenado
                    finOrdenado->siguiente = actual;
                    //y ahora el fin Ordenado es el actual
                    finOrdenado = actual;

                    actual = siguiente;
                }
            }
        } else {
            //en caso no cumpla, simplemente avanzamos
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

int main() {
    //invocamos la lista para el llenado de datos
    struct Lista participantes;
    //la construimos
    construir(participantes);
    //tambien invocamos a los elementos para guardalos
    struct ElementoLista elemento;

    cout << "Lista sin llenar: " << endl;
    imprimir(participantes);
    cout << endl;

    //abrimos el archivo
    ifstream arch("../ArchivosDeDatos/Participantes.txt", ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo no se pudo abrir correctamente" << endl;
        exit(1);
    }

    //comenzamos con el llenado de datos
    while (true) {
        arch >> elemento.id;
        if (arch.eof()) break;
        arch >> ws;
        arch.getline(elemento.nombre, 20, ' ');
        arch.getline(elemento.equipo, 20, '\n');
        insertarAlFinal(participantes, elemento);
    }
    arch.close();

    cout << "Lista inicial: " << endl;
    imprimir(participantes);
    cout << endl;

    ordenarLista(participantes);

    cout << "Lista final: " << endl;
    imprimir(participantes);
    cout << endl;

    return 0;
}
