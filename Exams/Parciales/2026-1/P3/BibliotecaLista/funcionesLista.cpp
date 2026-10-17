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
    nuevo->next = listaTAD.inicio;
    listaTAD.inicio = nuevo;
    listaTAD.longitud++;
}

/*Inserta un elemento siempre al final de la lista*/
void insertarAlFinal(struct Lista &listaTAD, const struct ElementoLista &elemento) {
    struct NodoLista *ultimoNodoLista = obtenerUltimoNodo(listaTAD);
    struct NodoLista *nuevo;
    nuevo = new struct NodoLista;
    nuevo->elemento = elemento;
    nuevo->next = nullptr;

    if (ultimoNodoLista == nullptr) /*Si la lista está vacía*/
        listaTAD.inicio = nuevo; /*se inserta en la cabeza de la lista*/
    else //La lista ya tiene NodoListas
        ultimoNodoLista->next = nuevo;
    listaTAD.longitud++;
}

/*Obtiene el último NodoLista de la lista*/
struct NodoLista *obtenerUltimoNodo(const struct Lista &listaTAD) {
    struct NodoLista *recorrido = listaTAD.inicio;
    if (esListaVacia(listaTAD)) return recorrido;
    while (recorrido->next != listaTAD.inicio) {
        recorrido = recorrido->next;
    }
    return recorrido;
}

// void insertarEnOrden(struct Lista &listaTAD, const struct ElementoLista &elemento) {
//     struct NodoLista *nuevo, *recorrido = listaTAD.inicio, *anterior = nullptr;
//     nuevo = new struct NodoLista;
//     nuevo->elemento = elemento;
//     while (recorrido) {
//         if (recorrido->elemento.codigo > elemento.codigo) break;
//         anterior = recorrido;
//         recorrido = recorrido->next;
//     }
//     nuevo->next = recorrido;
//     if (anterior == nullptr) listaTAD.inicio = nuevo;
//     else anterior->next = nuevo;
//     listaTAD.longitud++;
// }

// void eliminaNodo(struct Lista &listaTAD, const struct ElementoLista &elemento) {
//     struct NodoLista *ultimo = nullptr;
//     struct NodoLista *recorrido = listaTAD.inicio;
//     /*Avanzo hasta encontrar el elemento*/
//     /*Si no lo encuentra no elimina nada*/
//     while ((recorrido != nullptr) and (recorrido->elemento.codigo != elemento.codigo)) {
//         ultimo = recorrido;
//         recorrido = recorrido->next;
//     }
//
//     if (recorrido != nullptr) {
//         if (ultimo == nullptr) /*Estoy al inicio de la lista*/
//             listaTAD.inicio = recorrido->next;
//         else
//             ultimo->next = recorrido->next;
//         delete recorrido; /*libera la memoria*/
//     }
//     listaTAD.longitud--;
// }

void destruir(struct Lista &listaTAD) {
    /*recorrido apunta al inicio del tad*/
    struct NodoLista *recorrido = listaTAD.inicio;

    while (recorrido != nullptr) {
        /*NodoLista auxiliar que va servir para eliminar los NodoListas*/
        struct NodoLista *NodoListaAEliminar = recorrido;
        recorrido = recorrido->next;
        delete NodoListaAEliminar;
    }
    /*la lista queda vacia*/
    listaTAD.inicio = nullptr;
    listaTAD.longitud = 0;
}

//*con const aquello que pasas no va cambiar, el compilador se da cuenta que es constante*/
void imprimir(const struct Lista &listaTAD) {
    if (esListaVacia(listaTAD)) {
        cout << "La lista esta vacia no se puede mostrar" << endl;
    } else {
        struct NodoLista *recorrido = listaTAD.inicio;

        int cantidad=listaTAD.longitud;

        for (int i=0;i<cantidad;i++) {
            cout << "Nodo ";
            cout << recorrido->elemento.node_id;
            if (recorrido->elemento.is_active) {
                cout << " [ACTIVO] ";
            } else {
                cout << " [CAIDO] ";
            }
            cout << "siguiente: " << recorrido->next->elemento.node_id
                    << " skip_next: " << recorrido->skip_next->elemento.node_id;
            cout << endl;
            recorrido = recorrido->next;
        }

    }
}
