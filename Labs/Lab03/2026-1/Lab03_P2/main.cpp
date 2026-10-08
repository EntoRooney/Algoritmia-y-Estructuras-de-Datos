#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "BibliotecaPila/ElementoPila.h"
#include "BibliotecaPila/NodoPila.h"
#include "BibliotecaPila/Pila.h"
#include "BibliotecaPila/funcionesPila.h"

int main() {
    //estoy tomando el primer caso donde si se puede
    //igual funciona pa tookioooo miauuuu
    int n = 4;
    int arrA[n] = {1, 2, 3, 4};
    int arrB[n] = {1, 3, 4, 2};

    int i = 0; //posicion en llegada
    int j = 0; //posicion en solicitado;

    //invocamos a la pila
    struct Pila pilaAux;
    construir(pilaAux);
    //tendremos 3 casos
    //1. cuando la pila no esta vacia y su cima sea lo que quiere el cliente j++
    //2. cuando tdv hay elementos en A y la pila no sirve
    //2.1 cuando el contenedor que llega es el que quiero i++ j++
    //2.2 cuando no es lo que quiero, solo lo apilo i++
    //3. cuando la cima no es lo que quiero y el i==n, es imposible

    while (j < n) {
        //caso 1: cuando la pila tiene elementos y el tope es justo lo q quiero
        if (not esPilaVacia(pilaAux) and cima(pilaAux).numero == arrB[j]) {
            desapilar(pilaAux);
            j++;
        } else if (i < n) {
            //caso 2: cuando todavia quedan contenedores por leer del arrA

            //el contenedor que llega es el solicitado
            if (arrA[i] == arrB[j]) {
                i++;
                j++;
            } else {
                //no es el solicitado y lo guardamos temporalmente en la pila
                apilar(pilaAux, {arrA[i]});
                i++;
            }
        } else {
            //caso 3: ya no quedan elementos en el arrA
            //y el tope de la pila tampoco era el solicitado
            break;
        }
    }
    //esto solo es impresion asfagdg
    cout << "Orden de llegada de los contenedores: ";
    i = j = 0;
    while (i < n) {
        cout << arrA[i];

        if (i < n - 1) {
            cout << ", ";
        }

        i++;
    }
    cout << endl;
    cout << "Orden solicitado por los clientes: ";
    while (j < n) {
        cout << arrB[j];

        if (j < n - 1) {
            cout << ", ";
        }

        j++;
    }
    cout << endl;
    //verificamos que si se pueda cumplir, es decir que se haya recorrido todo el arr pedido
    if (j == n) {
        cout << "Se puede cumplir con lo solicitado" << endl;
    } else {
        cout << "No se puede cumplir con lo solicitado" << endl;
    }


    return 0;
}
