#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;
#include "Objeto.h"
#define NUM_OBJETOS 10
#define DOSIS_FENIX 7

int main() {
    //creamos los arreglos para poder llenarlos
    struct Objeto objeto[NUM_OBJETOS]{};
    objeto[0] = {1, 2};
    objeto[1] = {2, 3};
    objeto[2] = {1, 1};
    objeto[3] = {4, 2};
    objeto[4] = {3, 1};
    objeto[5] = {4, 3};
    objeto[6] = {2, 2};
    objeto[7] = {3, 2};
    objeto[8] = {1, 4};
    objeto[9] = {4, 1};
    //ahora llenamos sus duraciones y ganancia por hechizo
    for (int i = 0; i < NUM_OBJETOS; i++) {
        if (objeto[i].tipo == 1) {
            objeto[i].duracion = 6 * objeto[i].cantHechizos;
            objeto[i].ganancia = 25 * objeto[i].cantHechizos;
        } else if (objeto[i].tipo == 2) {
            objeto[i].duracion = 8 * objeto[i].cantHechizos;
            objeto[i].ganancia = 32 * objeto[i].cantHechizos;
        } else if (objeto[i].tipo == 3) {
            objeto[i].duracion = 11 * objeto[i].cantHechizos;
            objeto[i].ganancia = 38 * objeto[i].cantHechizos;
        } else {
            objeto[i].duracion = 13 * objeto[i].cantHechizos;
            objeto[i].ganancia = 45 * objeto[i].cantHechizos;
        }
    }
    //como sabemos tenemos 10 objetos que pueden estar repartidos
    //dentro de 4 mochilas
    //entonces podemos decir que el # de combinaciones es 4^10
    int numCombinaciones = pow(5,NUM_OBJETOS);
    //creamos una variable para almacenar la ganancia maxima
    int gananciaMax = -1, citaOneMax = 0, citaTwoMax = 0, citaTreeMax = 0,
            citaFourMax = 0, turnoMax[NUM_OBJETOS]{}, combinacionMax = 0;
    for (int j = 0; j < numCombinaciones; j++) {
        //debemos tener un arreglo de 10 espacios en
        //cuyo maximo numero debe ser 3, es decir convertir
        //el numero de combiacion en base 4
        int arrNumBaseFour[NUM_OBJETOS]{};
        int aux = j; //para convertir el numero
        for (int z = 0; z < NUM_OBJETOS; z++) {
            arrNumBaseFour[z] = aux % 5;
            aux /= 5;
        }
        //definimos la duracion de los turnos
        int turnoOne = 0, turnoTwo = 0, turnoTree = 0, turnoFour = 0;
        //definimos el costo
        int costoCombinacion = 0;
        //ademas creamos una variable para la dosis del fenix
        int cantDosisUsada = 0, cantDosisRestante = 0;
        //recorremos el arr para sumar el tiempo de cada turno
        for (int d = 0; d < NUM_OBJETOS; d++) {
            if (arrNumBaseFour[d] == 1) {
                turnoOne += objeto[d].duracion;
                costoCombinacion += objeto[d].ganancia;
            } else if (arrNumBaseFour[d] == 2) {
                turnoTwo += objeto[d].duracion;
                costoCombinacion += objeto[d].ganancia;
            } else if (arrNumBaseFour[d] == 3) {
                turnoTree += objeto[d].duracion;
                costoCombinacion += objeto[d].ganancia;
            } else if (arrNumBaseFour[d] == 4) {
                turnoFour += objeto[d].duracion;
                costoCombinacion += objeto[d].ganancia;
            }
            if (arrNumBaseFour[d] > 0) {
                //en el enunciado dice el tipo y que la suma es la cantidad de hechizos
                if (objeto[d].tipo == 3 or objeto[d].tipo == 4) {
                    cantDosisUsada += objeto[d].cantHechizos;
                }
            }
        }
        //restamos el cant de dosis usada
        cantDosisRestante = DOSIS_FENIX - cantDosisUsada;
        //hacemos el filtro del enunciado
        if (turnoOne <= 70 and turnoTwo <= 55 and
            turnoTree <= 65 and turnoFour <= 40 and cantDosisRestante >= 0) {
            if (costoCombinacion > gananciaMax) {
                gananciaMax = costoCombinacion;
                combinacionMax = j;
                citaOneMax = turnoOne;
                citaTwoMax = turnoTwo;
                citaTreeMax = turnoTree;
                citaFourMax = turnoFour;
                for (int v = 0; v < NUM_OBJETOS; v++) {
                    turnoMax[v] = arrNumBaseFour[v];
                }
            }
        }
    }

    cout << "El tiempo maximo de la cita uno fue : " << citaOneMax << endl;
    for (int i = 0; i < NUM_OBJETOS; i++) {
        if (turnoMax[i] == 1) {
            cout << "Turno 1 Objeto: " << i + 1 << endl;
        }
    }
    cout << "El tiempo maximo de la cita dos fue : " << citaTwoMax << endl;
    for (int i = 0; i < NUM_OBJETOS; i++) {
        if (turnoMax[i] == 2) {
            cout << "Turno 2 Objeto: " << i + 1 << endl;
        }
    }
    cout << "El tiempo maximo de la cita tres fue : " << citaTreeMax << endl;
    for (int i = 0; i < NUM_OBJETOS; i++) {
        if (turnoMax[i] == 3) {
            cout << "Turno 3 Objeto: " << i + 1 << endl;
        }
    }
    cout << "El tiempo maximo de la cita cuatro fue : " << citaFourMax << endl;
    for (int i = 0; i < NUM_OBJETOS; i++) {
        if (turnoMax[i] == 4) {
            cout << "Turno 4 Objeto: " << i + 1 << endl;
        }
    }
    cout << "La maxima ganancia es: " << gananciaMax << endl;
    cout << "Numero de la combinacion es: " << combinacionMax << endl;
    return 0;
}
