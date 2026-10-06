//Fecha:  sábado 30 Agosto 2025 
//Autor: Ana Roncal

#include <iostream>
#include <iomanip>
#include "Lista.h"
#include "funcionesLista.h"
using namespace std;

void construir(struct Lista & listaTAD) {
    listaTAD.inicio = nullptr;
    listaTAD.longitud=0;
}

/*Inserta un elemento siempre al final de la lista*/
void insertarAlFinal(struct Lista & listaTAD, const struct ElementoLista & elemento) {

    struct NodoLista * ultimoNodoLista = obtenerUltimoNodo(listaTAD);
    struct NodoLista * nuevo;
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
struct NodoLista * obtenerUltimoNodo(const struct Lista & listaTAD) {
    struct NodoLista * ultimo = nullptr;
    struct NodoLista* recorrido = listaTAD.inicio;

    while (recorrido != nullptr) {
        ultimo = recorrido;
        recorrido = recorrido->siguiente;
    }
    return ultimo;
}

void imprimirLista(const struct Lista &lista) {
    struct NodoLista *rec=lista.inicio;
    while (rec != nullptr) {
        cout<<"("<<rec->elemento.numCamiseta
        <<", "<<rec->elemento.nombre
        <<", "<<rec->elemento.posiciones<<")"<<endl;
        rec=rec->siguiente;
    }
}
