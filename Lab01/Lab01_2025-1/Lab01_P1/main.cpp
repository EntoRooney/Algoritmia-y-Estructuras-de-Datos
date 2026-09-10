#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

#define NUM_TABLAS 6

using namespace std;
#include "Tabla.h"

int main() {
    struct Tabla tabla[NUM_TABLAS]{};
    //insertamos las variables del enunciado
    tabla[0] = {150};
    tabla[1] = {100};
    tabla[2] = {80};
    tabla[3] = {50};
    tabla[4] = {120};
    tabla[5] = {10};

    //como sabemos tendremos solo 3 discos(mochilas)
    //y tenemos 6 tablas, entonces el numero de combinaciones
    //sera 3^6
    int numCombinaciones = pow(3, 6);
    //definimos una variable para guardar la mejor optimizacion
    int mejorRestante = -999; //sera minima para que a la primera guarde el primer dato
    int arrMejorCombinacion[NUM_TABLAS]{}; //combinacion mas optima
    int mejorDiscoMenor = 0; //para saber cual es menor disco global
    for (int i = 0; i < numCombinaciones; i++) {
        int arrNumBaseTree[NUM_TABLAS]{};
        int aux = i;

        //convertimos el numero de la combinacion actual en base 3
        for (int j = 0; j < NUM_TABLAS; j++) {
            arrNumBaseTree[j] = aux % 3;
            aux /= 3;
        }
        //definimos los discos
        int discoOne = 250, discoTwo = 200, discoTree = 200;
        for (int z = 0; z < NUM_TABLAS; z++) {
            if (arrNumBaseTree[z] == 0) {
                discoOne -= tabla[z].velocidad;
            } else if (arrNumBaseTree[z] == 1) {
                discoTwo -= tabla[z].velocidad;
            } else {
                discoTree -= tabla[z].velocidad;
            }
        }
        //vemos que todos los discos sean positivos
        if (discoOne >= 0 and discoTwo >= 0 and discoTree >= 0) {
            //jugamos para encontrar el minimo
            int velocidadMinina = discoOne;
            int discoMenorActual = 1;
            if (discoTwo < velocidadMinina) {
                velocidadMinina = discoTwo;
                discoMenorActual = 2;
            }
            if (discoTree < velocidadMinina) {
                velocidadMinina = discoTree;
                discoMenorActual = 3;
            }

            if (velocidadMinina > mejorRestante) {
                mejorRestante = velocidadMinina;
                mejorDiscoMenor = discoMenorActual;
                for (int d = 0; d < NUM_TABLAS; d++) {
                    arrMejorCombinacion[d] = arrNumBaseTree[d];
                }
            }
        } else {
            continue;
        }
    }

    //formato de impresion pedido
    for (int d = 0; d < NUM_TABLAS; d++) {
        if (arrMejorCombinacion[d] == 0) {
            cout << "Para el Disco 1: La tabla " << d + 1 << endl;
        }
    }
    for (int d = 0; d < NUM_TABLAS; d++) {
        if (arrMejorCombinacion[d] == 1) {
            cout << "Para el Disco 2: La tabla " << d + 1 << endl;
        }
    }
    for (int d = 0; d < NUM_TABLAS; d++) {
        if (arrMejorCombinacion[d] == 2) {
            cout << "Para el Disco 3: La tabla " << d + 1 << endl;
        }
    }
    cout << "La solucion tiene una velocidad minima grupo de " << mejorRestante << endl;
    cout << "IOPS que se da en el disco " << mejorDiscoMenor;
    return 0;
}
