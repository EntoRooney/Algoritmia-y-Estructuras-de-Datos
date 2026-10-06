#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#include "Bibliotecas/ElementoPila.h"
#include "Bibliotecas/NodoPila.h"
#include "Bibliotecas/Pila.h"
#include "Bibliotecas/funcionesPila.h"
#include "Bibliotecas/Funciones.h"

int main() {
    struct Pila pilaA,pilaB,pilaC;
    //comenzamos a construir las pilas
    construir(pilaA);
    construir(pilaB);
    construir(pilaC);

    apilar(pilaA,{20});
    apilar(pilaA,{15});
    apilar(pilaA,{5});

    apilar(pilaB,{18});
    apilar(pilaB,{12});
    apilar(pilaB,{10});
    apilar(pilaB,{2});

    cout<<"INICIO"<<endl;
    cout<<"PILA A: ";imprimir(pilaA);
    cout<<"PILA B: ";imprimir(pilaB);
    cout<<"PILA C: ";imprimir(pilaC);

    fusionarPilas(pilaA,pilaB,pilaC);

    cout<<"FINAL"<<endl;
    cout<<"PILA A: ";imprimir(pilaA);
    cout<<"PILA B: ";imprimir(pilaB);
    cout<<"PILA C: ";imprimir(pilaC);

    return 0;
}