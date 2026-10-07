#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "BibliotecaPila/funcionesPila.h"
#include "BibliotecaPila/ElementoPila.h"
#include "BibliotecaPila/NodoPila.h"
#include "BibliotecaPila/Pila.h"

void hanoi(int n, struct Pila &desde, struct Pila &auxiliar, struct Pila &hacia) {
    if (n == 0) return; //si no hay elementos que mover, no hacemos nada
    //si solo hay un elemento, simplemente lo movemos
    //directamente desde la pila de origen hasta la pila de destino
    if (n == 1) {
        apilar(hacia, desapilar(desde));
        return;
    }
    //movemos los primeros n-1 elementos desde "desde" hacia aux
    hanoi(n - 1, desde, hacia, auxiliar);
    //ahora que hemos quitalo los n-1, solo movemos el elemento que queda abajo
    apilar(hacia, desapilar(desde));
    //movemos los n-1 elementos desde aux hasta hacia
    hanoi(n - 1, auxiliar, desde, hacia);
}

void fusionarPilas(struct Pila &pilaA, struct Pila &pilaB, struct Pila &pilaC) {
    //hasta que las dos esten vacias
    while (not esPilaVacia(pilaA) or not esPilaVacia(pilaB)) {
        //Si B esta vacia, entonces usamos A o ambas tienen elementos y A tiene el menor tope
        if (esPilaVacia(pilaB) or
            (not esPilaVacia(pilaA) and cima(pilaA).numero < cima(pilaB).numero)) {
            int n = longitud(pilaC);

            //movemos temporalmente C hacia B
            hanoi(n, pilaC, pilaA, pilaB);
            //colocamos el nuevo elemento a C
            apilar(pilaC, desapilar(pilaA));
            //devolvemos los elementos que estaban en C
            hanoi(n, pilaB, pilaA, pilaC);
        } else {
            //si no usamos A, usamos B
            int n = longitud(pilaC);

            //movemos temporalmente C hacia A
            hanoi(n, pilaC, pilaB, pilaA);
            //colocamos el nuevo elemento a C
            apilar(pilaC, desapilar(pilaB));
            //restauramos C
            hanoi(n, pilaA, pilaB, pilaC);
        }
    }
}

int main() {
    //invocamos a la primera pila
    struct Pila pilaA;
    construir(pilaA);

    apilar(pilaA, {20});
    apilar(pilaA, {15});
    apilar(pilaA, {5});

    //invocamos a la segunda pila
    struct Pila pilaB;
    construir(pilaB);

    apilar(pilaB, {18});
    apilar(pilaB, {12});
    apilar(pilaB, {10});
    apilar(pilaB, {2});

    //invocamos la tercera pila
    struct Pila pilaC;
    construir(pilaC);

    cout << "INICIO " << endl;
    cout << "Pila A: ";
    imprimir(pilaA);
    cout << "Pila B: ";
    imprimir(pilaB);
    cout << "Pila C: ";
    imprimir(pilaC);

    //invoco a la funcion donde vamos a fusionar las pilas
    //literal es hanoi xdafdaf
    fusionarPilas(pilaA, pilaB, pilaC);

    cout << "DESPUES " << endl;
    cout << "Pila A: ";
    imprimir(pilaA);
    cout << "Pila B: ";
    imprimir(pilaB);
    cout << "Pila C: ";
    imprimir(pilaC);


    return 0;
}
