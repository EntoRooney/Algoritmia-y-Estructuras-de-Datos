#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "BibliotecaLista/ElementoLista.h"
#include "BibliotecaLista/NodoLista.h"
#include "BibliotecaLista/Lista.h"
#include "BibliotecaLista/funcionesLista.h"

void intercambiar(struct Lista &libros, int posX, int posY) {
    //caso donde las posiciones sean iguales
    if (posX == posY) return;

    //ahora hacemos que siempre el nodoA este antes que el nodoB
    //para reducir casos
    if (posX > posY) {
        int aux = posX;
        posX = posY;
        posY = aux;
    }

    //definimos los nodos tanto para el nodoA y el nodoB
    struct NodoLista *anteriorA = nullptr;
    struct NodoLista *nodoA = nullptr;

    struct NodoLista *anteriorB = nullptr;
    struct NodoLista *nodoB = nullptr;

    //ahora hacemos el recorrido
    struct NodoLista *actual = libros.inicio;
    struct NodoLista *anterior = nullptr;

    //agregamos un contador
    int pos = 1;

    while (actual != nullptr) {
        //si lo encontramos, los asignamos
        if (posX == pos) {
            anteriorA = anterior;
            nodoA = actual;
        }
        if (posY == pos) {
            anteriorB = anterior;
            nodoB = actual;
        }
        //en caso ya hayan encontrado a los dos
        if (nodoA != nullptr and nodoB != nullptr) break;
        //solo avanzamos y guardamos el anterior
        anterior = actual;
        actual = actual->siguiente;
        pos++;
    }

    //en caso no existan los nodos
    if (nodoA == nullptr or nodoB == nullptr) return;

    //tendremos 3 casos
    //caso 1: si el nodoA y nodoB estan juntos
    if (nodoA->siguiente == nodoB) {
        //caso 1.1: si el nodoA es el inicio
        if (anteriorA == nullptr) {
            libros.inicio = nodoB;
            nodoA->siguiente = nodoB->siguiente;
            nodoB->siguiente = nodoA;
        } else {
            //caso 1.2 si el nodoA no esta en el inicio
            anteriorA->siguiente = nodoB;
            nodoA->siguiente = nodoB->siguiente;
            nodoB->siguiente = nodoA;
        }
    } else if (nodoA == libros.inicio) {
        //caso 2: si el nodoA esta en el inicio y estan separados

        //aqui nos conviene guardar los siguientes
        struct NodoLista *siguienteA = nodoA->siguiente;
        struct NodoLista *siguienteB = nodoB->siguiente;

        libros.inicio = nodoB;
        nodoB->siguiente = siguienteA;
        anteriorB->siguiente = nodoA;
        nodoA->siguiente = siguienteB;
    } else {
        //caso 3: si el nodoA y el nodoB estan separados, y nodoA no es el head

        //como el caso 2, tambien nos conviene guardar los sigueintes
        struct NodoLista *siguienteA = nodoA->siguiente;
        struct NodoLista *siguienteB = nodoB->siguiente;

        anteriorA->siguiente = nodoB;
        nodoB->siguiente = siguienteA;
        anteriorB->siguiente = nodoA;
        nodoA->siguiente = siguienteB;
    }
}

void buscarVentas(struct Lista &libros, int &posVentasMayor, int &posVentasMenor) {
    //definimos los nodos para el recorrido
    struct NodoLista *actual = libros.inicio;

    //definimos las variables globales para encontrar el mayor y el menor
    int ventasMayor = -1, ventasMenor = 1000000;

    //definimos la posicion que comienza en 1 por restriccion del problema
    int pos = 1;

    while (actual != nullptr) {
        if (actual->elemento.unidVendidas > ventasMayor) {
            ventasMayor = actual->elemento.unidVendidas;
            posVentasMayor = pos;
        }
        if (actual->elemento.unidVendidas < ventasMenor) {
            ventasMenor = actual->elemento.unidVendidas;
            posVentasMenor = pos;
        }
        actual = actual->siguiente;
        pos++;
    }
}

void buscarLikes(struct Lista &libros, int &posLikesMayor, int &posLikesMenor) {
    //definimos los nodos para el recorrido
    struct NodoLista *actual = libros.inicio;

    //definimos las variables globales para encontrar el mayor y el menor
    int likesMayor = -1, likesMenor = 1000000;

    //definimos la posicion que comienza en 1 por restriccion del problema
    int pos = 1;

    while (actual != nullptr) {
        if (actual->elemento.cantLikes > likesMayor) {
            likesMayor = actual->elemento.cantLikes;
            posLikesMayor = pos;
        }
        if (actual->elemento.cantLikes < likesMenor) {
            likesMenor = actual->elemento.cantLikes;
            posLikesMenor = pos;
        }
        actual = actual->siguiente;
        pos++;
    }
}

int main() {
    //invocamos la lista para poner los libros ahi
    struct Lista libros;
    //la inicializamos
    construir(libros);
    //invocamos las structs de elementos
    struct ElementoLista elemento;

    //abrimos el archivo para la lectura de datos
    ifstream arch("../ArchivosDeDatos/Libros.txt", ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo no se pudo abrir correctamente" << endl;
        exit(1);
    }

    //comenzamos la lectura de datos
    while (true) {
        arch.getline(elemento.codigo, 10, ' ');
        if (arch.eof()) break;
        arch.getline(elemento.nombre, 50, '*');
        arch >> elemento.unidVendidas >> elemento.cantLikes;
        arch >> ws;
        insertarAlFinal(libros, elemento);
    }
    arch.close();
    //imprimimos como estaba antes de ordenar
    cout << "Lista sin ordenar:" << endl;
    imprimir(libros);

    //ahora buscamos el indice de mayor y menor cantidad de likes
    int posLikesMayor, posLikesMenor;
    buscarLikes(libros, posLikesMayor, posLikesMenor);
    //ahora invocamos la funcion para intercambiar segun las reestricciones
    intercambiar(libros, posLikesMayor, posLikesMenor);

    //hacmeos lo mismo para el indice de mayor y menor de ventas
    int posVentasMayor, posVentasMenor;
    buscarVentas(libros, posVentasMayor, posVentasMenor);
    //ahora invocamos la funcion para intercambiar segun las reestricciones
    intercambiar(libros, posVentasMenor, posVentasMayor);

    //imprimimos como esta despues de ordenar
    cout << endl;
    cout << "Lista ordenada:" << endl;
    imprimir(libros);
    return 0;
}
