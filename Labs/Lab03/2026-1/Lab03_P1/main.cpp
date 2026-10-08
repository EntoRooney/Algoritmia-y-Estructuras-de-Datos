#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "BibliotecaLista/funcionesLista.h"
#include "BibliotecaLista/ElementoLista.h"
#include "BibliotecaLista/NodoLista.h"
#include "BibliotecaLista/Lista.h"

void depuracion(struct Lista &listaDepurada, struct Lista &listaSospechosos) {
    //tenemos que recorrer la lista depurada(la original)
    struct NodoLista *actual = listaDepurada.inicio;
    struct NodoLista *anterior = nullptr;

    while (actual != nullptr) {
        //el bool nos va a ayudar a saber si los hemos eliminado el nodo ono
        //en caso que no, avanzamos con normalidad
        bool eliminado = false;

        //vamos a avanzar con la lista depurada tambien
        struct NodoLista *actualSospechoso = listaSospechosos.inicio;

        while (actualSospechoso != nullptr) {
            //en caso de que coincidan, tendremos dos casos
            if (actual->elemento.usuario == actualSospechoso->elemento.usuario) {
                //guardamos el siguiente
                struct NodoLista *siguiente = actual->siguiente;
                //el primer caso es si es el primero de la listaOg
                //simplemente el inicio lo ponemos al que le sigue
                if (anterior == nullptr) {
                    listaDepurada.inicio = siguiente;
                } else {
                    //en caso no sea el primero, solo lo desconectamos
                    anterior->siguiente = siguiente;
                }
                //avanzamos y ponemos el eliminado en true para saber que ya avanzamos
                actual = siguiente;
                eliminado = true;
                break;
            }
            actualSospechoso = actualSospechoso->siguiente;
        }
        //en caso hayamos eliminado, lo saltamos porque no vamos a modificar el anterior
        if (!eliminado) {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

void sospechosos(struct Lista &listaOg, struct Lista &listaSospechosos) {
    //primero vamos contando las ocurrencias
    //para ello vamos recorriendo la lista
    struct NodoLista *actual = listaOg.inicio;


    while (actual != nullptr) {
        //para poder recorrer la lista de nuevo tenemos que
        struct NodoLista *actualFor = listaOg.inicio;

        int contador = 0; //nos servira para contar las ocurrencias que tiene cada elemento

        //ahora abrimos otro recorrido de la lista principal
        while (actualFor != nullptr) {
            //en caso coincida incrementamos el contador
            if (actual->elemento.usuario == actualFor->elemento.usuario) {
                contador++;
            }
            actualFor = actualFor->siguiente;
        }
        //si son 3 o mas, lo agregamos a la lista de sospechosos
        if (contador >= 3) {
            //invocamos un aux para que recorra la lista de sospechosos
            struct NodoLista *aux = listaSospechosos.inicio;
            //nos ayudara a ver si existe o no existe el usuario en la lista de sospechosos
            bool existe = false;
            //recorremos la lista
            while (aux != nullptr) {
                if (actual->elemento.usuario == aux->elemento.usuario) {
                    //en caso exista, cambiamos el bool y nos salimos del while
                    existe = true;
                    break;
                }
                aux = aux->siguiente;
            }
            //en caso sea la primera vez del sospechoso, lo insertamos
            if (!existe) {
                insertarAlFinal(listaSospechosos, actual->elemento);
            }
        }
        actual = actual->siguiente;
    }
}

int main() {
    //invocamos la lista original que pasara a ser la lista depurada
    struct Lista listaOg;
    construir(listaOg);
    //ademas invocamos la lista de sospechosos
    struct Lista listaSospechosos;
    construir(listaSospechosos);
    //y los elementos para guardarlos
    struct ElementoLista elemento;

    //ahora primero leemos los datos y lo colocamos en la lista original
    ifstream arch("../ArchivosDeDatos/Usuarios.txt", ios::in);
    if (not arch.is_open()) {
        cout << "ERROR, el archivo no se pudo abrir correctamente" << endl;
        exit(1);
    }

    while (true) {
        arch >> elemento.usuario;
        if (arch.eof()) break;
        insertarAlFinal(listaOg, elemento);
    }
    arch.close();
    cout << "Lista de intentos fallidos: ";
    imprimir(listaOg);

    //primero generamos la lista de sospechosos
    sospechosos(listaOg, listaSospechosos);
    //despues generamos la lista ya depurada
    depuracion(listaOg, listaSospechosos);

    cout << "Lista de usuarios sospechosos: ";
    imprimir(listaSospechosos);

    cout << "Lista depurada: ";
    imprimir(listaOg);
    return 0;
}
