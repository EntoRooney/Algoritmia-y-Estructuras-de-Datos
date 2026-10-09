#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "BibliotecaPila/ElementoPila.h"
#include "BibliotecaPila/NodoPila.h"
#include "BibliotecaPila/Pila.h"
#include "BibliotecaPila/funcionesPila.h"

int main() {
    //invoco a la pila que nos ayudara a almacenar los niveles
    struct Pila pila;
    //inicializamos la pila
    construir(pila);
    char eventos[] = {'S', 'B', 'S', 'B', 'B', 'S', 'S'};
    //sacamos el tamaño del array
    int n = sizeof(eventos) / sizeof(eventos[0]);

    //para este problema, solo debemos entender 4 cosas
    //1. Siempre se genera el siguiente nivel y lo apilamos
    //2. Si la orden es una bajada, no se hace nada
    //3. Si la orden es una subida, desapilamos todo y imprimimos
    //4. al acabar las n órdenes, todavía falta generar el nivel n+1.
    //   lo apilamos y luego vaciamos la pila.

    //recorremos todos los eventos
    for (int i = 0; i < n; i++) {
        //apilamos siempre
        apilar(pila, {i + 1});
        //si el evento es una subida, vaciamos la pila
        //sino solamente lo apilamos
        if (eventos[i] == 'S') {
            while (not esPilaVacia(pila)) {
                struct ElementoPila elemento = desapilar(pila);
                cout << elemento.numero << " ";
            }
        }
    }
    //hay n órdenes, por lo tanto existen n+1 niveles.
    //apilamos el último nivel y vaciamos la pila.
    apilar(pila, {n + 1});
    while (not esPilaVacia(pila)) {
        struct ElementoPila elemento = desapilar(pila);
        cout << elemento.numero << " ";
    }

    return 0;
}
