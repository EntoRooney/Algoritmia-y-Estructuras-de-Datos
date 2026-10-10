//Fecha:  sábado 30 Agosto 2025 
//Autor: Ana Roncal

#include <iostream>
#include <iomanip>
#include "Lista.h"
#include "funcionesLista.h"
using namespace std;

void construir(struct Lista &listaTAD) {
    listaTAD.inicio = nullptr;
    listaTAD.longitud = 0;
}

bool esListaVacia(const struct Lista &listaTAD) {
    return listaTAD.inicio == nullptr;
}

/*Inserta los elementos al inicio de la lista*/
void insertarAlInicio(struct Lista &listaTAD, const struct ElementoLista &elemento) {
    struct NodoLista *nuevo;
    nuevo = new struct NodoLista;
    nuevo->elemento = elemento;
    nuevo->siguiente = listaTAD.inicio;
    listaTAD.inicio = nuevo;
    listaTAD.longitud++;
}

/*Inserta un elemento siempre al final de la lista*/
void insertarAlFinal(struct Lista &listaTAD, const struct ElementoLista &elemento) {
    struct NodoLista *ultimoNodoLista = obtenerUltimoNodo(listaTAD);
    struct NodoLista *nuevo;
    nuevo = new struct NodoLista;
    nuevo->elemento = elemento;
    nuevo->siguiente = nullptr;

    if (ultimoNodoLista == nullptr) /*Si la lista está vacía*/
        listaTAD.inicio = nuevo; /*se inserta en la cabeza de la lista*/
    else //La lista ya tiene NodoListas
        ultimoNodoLista->siguiente = nuevo;
    listaTAD.longitud++;
}

/*Obtiene el último NodoLista de la lista*/
struct NodoLista *obtenerUltimoNodo(const struct Lista &listaTAD) {
    struct NodoLista *ultimo = nullptr;
    struct NodoLista *recorrido = listaTAD.inicio;

    while (recorrido != nullptr) {
        ultimo = recorrido;
        recorrido = recorrido->siguiente;
    }
    return ultimo;
}

void destruir(struct Lista &listaTAD) {
    /*recorrido apunta al inicio del tad*/
    struct NodoLista *recorrido = listaTAD.inicio;

    while (recorrido != nullptr) {
        /*NodoLista auxiliar que va servir para eliminar los NodoListas*/
        struct NodoLista *NodoListaAEliminar = recorrido;
        recorrido = recorrido->siguiente;
        delete NodoListaAEliminar;
    }
    /*la lista queda vacia*/
    listaTAD.inicio = nullptr;
    listaTAD.longitud = 0;
}

/*con const aquello que pasas no va cambiar, el compilador se da cuenta que es constante*/
void imprimir(const struct Lista &listaTAD) {
    if (esListaVacia(listaTAD)) {
        cout << "La lista esta vacia no se puede mostrar" << endl;
    } else {
        struct NodoLista *recorrido = listaTAD.inicio;
        int estaImprimiendoLaCabeza = 1;
        cout << "[";

        while (recorrido != nullptr) {
            cout << recorrido->elemento.numero << recorrido->elemento.palo << ' ';
            recorrido = recorrido->siguiente;
        }
        cout << "]" << endl;
    }
}
