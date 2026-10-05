#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "BibliotecaLista/funcionesLista.h"
#include "BibliotecaLista/ElementoLista.h"
#include "BibliotecaLista/Lista.h"
#include "BibliotecaLista/NodoLista.h"

void preparacionPostres(struct Lista &postres, ifstream &archStock) {
    //leemos los ingredientes que estan en el almacen
    int arrCodigoStock[20]{}, arrCantidadStock[20]{}, cantStock = 0;
    char basura[20]; //lo usamos para descartar el nombre

    while (true) {
        archStock.getline(basura, 20, '*');
        if (archStock.eof()) break;
        archStock >> arrCodigoStock[cantStock] >> arrCantidadStock[cantStock];
        cantStock++;
    }

    //comenzamos con el recorrido de la lista
    struct NodoLista *actual = postres.inicio;
    struct NodoLista *anterior = nullptr; //es null porque estamos empezando del comienzo

    int cantidadPreparados = 0; //nos detenemos si son 3 || restriccion del problema

    while (actual != nullptr and cantidadPreparados < 3) {
        //estamos suponiendo que inicialmente el postre si se puede preparar
        //si encontramos al menos UNO, le ponemos false
        bool sePuedePreparar = true;

        //comenzamos a revisar todos los ingredientes del postre actual
        for (int i = 0; i < actual->elemento.cantidadIngredientes; i++) {
            //para cada ingrediente debemos saber si existe en el stock
            bool encontrado = false;

            //buscamos el ingrediente i dentro del stock
            for (int j = 0; j < cantStock; j++) {
                //el codigo requerido por el postre coincide con alguno del stock?
                if (actual->elemento.ingrediente[i] == arrCodigoStock[j]) {
                    encontrado = true;

                    //el ingrediente existe
                    //ahora vamos a comprobar si alcanza la cantidad
                    if (arrCantidadStock[j] < actual->elemento.cantidad[i]) {
                        //existe pero no hay suficiente
                        sePuedePreparar = false;
                    }

                    //hemos encontrado el codigo, no necesitamos seguir buscando en el stock
                    break;
                }
            }
            //si recorrimos todo el stock y nunca encontramos el ingrediente
            if (!encontrado) {
                sePuedePreparar = false;
            }

            //si ya sabemos que el postre no se puede preparar, safamos
            if (!sePuedePreparar) {
                break;
            }
        }

        if (sePuedePreparar) {
            //descontamos los ingredientes del stock
            for (int i = 0; i < actual->elemento.cantidadIngredientes; i++) {
                //nuevamente buscamos cada ingrediente dentro del stock
                for (int j = 0; j < cantStock; j++) {
                    if (actual->elemento.ingrediente[i] == arrCodigoStock[j]) {
                        //restamos lo utilizado para agregar este postre
                        arrCantidadStock[j] -= actual->elemento.cantidad[i];

                        //ya encontramos el ingrediente
                        break;
                    }
                }
            }


            //guardamos el siguiente nodo porque vamos a modificar actual->sgt
            struct NodoLista *siguiente = actual->siguiente;

            //solo debemos mover si NO esta en el inicio
            if (actual != postres.inicio) {
                //desenlazamos el actual de su posicion
                anterior->siguiente = actual->siguiente;
                //actual ahora apunta al inicio
                actual->siguiente = postres.inicio;
                postres.inicio = actual;
                actual = siguiente;
            } else {
                //aca solo avanzamos porque no es necesario traerlo al inicio
                anterior = actual;
                actual = actual->siguiente;
            }
            //encontramos un postre preparable
            cantidadPreparados++;
        } else {
            //si no se puede preparar, entonces avanzamos normalmente
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

int main() {
    //invocamos a la lista
    struct Lista postres;
    construir(postres);
    //y tambien invocamos a la struct elementos para poder guardalo dentro de la lista
    struct ElementoLista elemento;

    //abrimos el archivo de postres para la lectura de datos
    ifstream archPostres("../ArchivosDeDatos/Postres.txt", ios::in);
    if (not archPostres.is_open()) {
        cout << "Error al abrir el archivo Postres.txt" << endl;
        exit(1);
    }

    while (true) {
        archPostres.getline(elemento.codigo, 5, ' ');
        if (archPostres.eof()) break;
        archPostres.getline(elemento.descripcion, 20, '*');
        archPostres >> ws;
        int i = 0; //para la cantidad de ingredientes que necesita
        while (archPostres.peek() != '\n') {
            archPostres >> elemento.ingrediente[i] >> elemento.cantidad[i];
            i++;
        }
        elemento.cantidadIngredientes = i;
        archPostres.get();
        insertarEnOrden(postres, elemento);
    }
    archPostres.close();

    cout << "Listado Inicial" << endl;
    imprimir(postres);
    cout << endl;
    //abrirmos el archivo del almacen para invocar la funcion
    ifstream archStock("../ArchivosDeDatos/Ingredientes.txt", ios::in);
    if (not archStock.is_open()) {
        cout << "Error al abrir el archivo Ingredientes.txt" << endl;
        exit(1);
    }

    preparacionPostres(postres, archStock);

    cout << "Listado Final:" << endl;
    imprimir(postres);
    return 0;
}
