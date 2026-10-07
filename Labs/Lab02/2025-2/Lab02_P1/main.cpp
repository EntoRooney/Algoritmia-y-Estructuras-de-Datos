#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;
#include "BibliotecaLista/funcionesLista.h"
#include "BibliotecaLista/ElementoLista.h"
#include  "BibliotecaLista/NodoLista.h"
#include "BibliotecaLista/Lista.h"

void reOrdenarPosiciones(struct Lista &jugadores, ifstream &archPosiciones) {
    //comenzamos a leer las posiciones
    char posicion[20]{};

    //declaro el nodo donde comenzara mi zona ordenada
    struct NodoLista *finOrdenado = nullptr;


    while (true) {
        archPosiciones >> posicion;
        if (archPosiciones.eof()) break;

        //definimos el nodos principales
        struct NodoLista *actual = jugadores.inicio;
        struct NodoLista *anterior = nullptr;


        while (actual != nullptr) {
            //chequeo si la posicion de mi actual coincide con la posicion leida
            if (strcmp(posicion, actual->elemento.posicion) == 0) {
                struct NodoLista *siguiente = actual->siguiente;
                //vamos a trabajarlo mediante zonas

                //caso 1: si aun no hay una zona ordenada
                if (finOrdenado == nullptr) {
                    //si nuestro jugador esta al inicio
                    if (anterior == nullptr) {
                        //simplemente colocamos el puntero y avanzamos
                        finOrdenado = actual;

                        anterior = actual;
                        actual = siguiente;
                    } else {
                        //si el jugador esta mas adelante y debemos
                        //llevarlo al inicio

                        //sacamos al actual de su posicion
                        anterior->siguiente = siguiente;
                        //lo ponemos antes del inicio
                        actual->siguiente = jugadores.inicio;
                        //ahora actual sera el nuevo inicio
                        jugadores.inicio = actual;
                        //y tambien el ultimo ordenado
                        finOrdenado = actual;
                        actual = siguiente;
                        //el anterior no cambia
                    }
                    //caso 2: cuando ya existe una zona ordenada
                } else {
                    //si el nodo actual esta despues de la zona ordenada
                    if (anterior == finOrdenado) {
                        //no lo movemos, solo ampliamos la zona
                        finOrdenado = actual;
                        //nos movemos
                        anterior = actual;
                        actual = siguiente;
                    } else {
                        //si el jugador esta mas adelante en la lista

                        //sacamos el actual de su posicion
                        anterior->siguiente = siguiente;
                        //ahora el actual apunta al que esta despues del finOrdenado
                        actual->siguiente = finOrdenado->siguiente;
                        //ponemos el actual despues del ordenado
                        finOrdenado->siguiente = actual;
                        //ahora el actual pasa a ser el nuevo finOrdenado
                        finOrdenado = actual;
                        actual = siguiente;
                    }
                }
            } else {
                //en caso el jugador no tiene la posicion buscada
                //simplemente avanzamos
                anterior = actual;
                actual = actual->siguiente;
            }
        }
    }
}

int main() {
    //primero creamos una lista para almacenar ahi los datos de los jugadores
    struct Lista jugadores;
    construir(jugadores);
    cout << "Lista de jugadores sin llenar: " << endl;
    imprimir(jugadores);

    //invocamos al elemento para guardarlo
    struct ElementoLista elemento;

    //abrimos el archivo de datos para insertar los datos en los jugadores
    ifstream archJugadores("../ArchivosDeDatos/Jugadores.txt", ios::in);
    if (not archJugadores.is_open()) {
        cout << "ERROR, al abrir el archivo Jugadores.txt" << endl;
        exit(1);
    }

    while (true) {
        archJugadores >> elemento.nroCamiseta;
        if (archJugadores.eof()) break;
        archJugadores >> ws;
        archJugadores.getline(elemento.nombre, 20, ' ');
        archJugadores.getline(elemento.posicion, 20, '\n');
        insertarAlFinal(jugadores, elemento);
    }
    archJugadores.close();

    cout << endl << "La lista de jugadores sin ordenar:" << endl;
    imprimir(jugadores);

    //abrimos el archivo para el orden pedido por le DT
    ifstream archPosiciones("../ArchivosDeDatos/PosicionesDT.txt", ios::in);
    if (not archPosiciones.is_open()) {
        cout << "ERROR, al abrir el archivo Posiciones.txt" << endl;
        exit(1);
    }

    reOrdenarPosiciones(jugadores, archPosiciones);

    archPosiciones.close();

    cout << endl << "La lista de jugadores ya ordenado:" << endl;
    imprimir(jugadores);
    return 0;
}
