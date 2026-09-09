#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

#define NUM_DIENTES 8

using namespace std;
#include "Diente.h"

int main() {
    struct Diente diente[NUM_DIENTES]{};
    //hardcodeamos los datos del enunciado
    diente[0] = {1, 3};
    diente[1] = {1, 1};
    diente[2] = {2, 0};
    diente[3] = {3, 1};
    diente[4] = {3, 2};
    diente[5] = {4, 1};
    diente[6] = {4, 2};
    diente[7] = {4, 3};
    //completamos los arreglos
    for (int i = 0; i < NUM_DIENTES; i++) {
        if (diente[i].tipo == 1) {
            diente[i].duracion = 5 * diente[i].cantidadCaries;
            diente[i].ganancia = 20 * diente[i].cantidadCaries;
        } else if (diente[i].tipo == 2) {
            diente[i].duracion = 7 * diente[i].cantidadCaries;
            diente[i].ganancia = 30 * diente[i].cantidadCaries;
        } else if (diente[i].tipo == 3) {
            diente[i].duracion = 10 * diente[i].cantidadCaries;
            diente[i].ganancia = 35 * diente[i].cantidadCaries;
        } else {
            diente[i].duracion = 12 * diente[i].cantidadCaries;
            diente[i].ganancia = 42 * diente[i].cantidadCaries;
        }
    }
    //como sabemos que solo pueden estar en 3 citas o en niguna
    //entonces tenemos 4 opciones para 8 variables
    int totalCombinaciones = pow(4, 8);
    //definimos la ganancia maxima
    int gananciaMaxima = -1;
    int maxCitaOne = 0, maxCitaTwo = 0, maxCitaThree = 0, arrMejorCombi[NUM_DIENTES]{};
    for (int j = 0; j < totalCombinaciones; j++) {
        //definimos las citas y la ganancia
        int citaOne = 0, citaTwo = 0, citaThree = 0, gananciaDeCombi = 0;
        //ahora convertimos el numero de la combinacion
        //a un numero en base 4 porque solo tenemos 4 opciones
        //donde 0 sea que no fue a ninguna cita para el diente
        //y 1 -> cita 1 y asi sucesivamente
        int aux = j;
        int arrEnBaseFour[NUM_DIENTES]{};
        for (int d = 0; d < NUM_DIENTES; d++) {
            arrEnBaseFour[d] = aux % 4;
            aux /= 4;
        }
        //ahora diente por diente separamos y sumamos respectivamente
        for (int e = 0; e < NUM_DIENTES; e++) {
            if (arrEnBaseFour[e] == 1) {
                citaOne += diente[e].duracion;
                gananciaDeCombi += diente[e].ganancia;
            } else if (arrEnBaseFour[e] == 2) {
                citaTwo += diente[e].duracion;
                gananciaDeCombi += diente[e].ganancia;
            } else if (arrEnBaseFour[e] == 3) {
                citaThree += diente[e].duracion;
                gananciaDeCombi += diente[e].ganancia;
            }
        }

        if (citaOne <= 60 and citaTwo <= 45 and citaThree <= 50) {
            if (gananciaDeCombi > gananciaMaxima) {
                gananciaMaxima = gananciaDeCombi;
                maxCitaOne = citaOne;
                maxCitaTwo = citaTwo;
                maxCitaThree = citaThree;
                for (int x = 0; x < NUM_DIENTES; x++)
                    arrMejorCombi[x] = arrEnBaseFour[x];
            }
        }
    }
    cout << "La ruta mas eficiente seria" << endl;
    for (int l = 0; l < NUM_DIENTES; l++) {
        if (arrMejorCombi[l] == 1) {
            cout << "Cita 1: Diente: " << l + 1 << endl;
        } else if (arrMejorCombi[l] == 2) {
            cout << "Cita 2: Diente: " << l + 1 << endl;
        } else if (arrMejorCombi[l] == 3) {
            cout << "Cita 3: Diente: " << l + 1 << endl;
        }
    }
    cout << "Tiempo total: " << endl;
    cout << "Cita Uno: " << maxCitaOne << endl;
    cout << "Cita Dos: " << maxCitaTwo << endl;
    cout << "Cita Tres: " << maxCitaThree << endl;
    cout << "La ganancia maxima seria: " << gananciaMaxima << endl;
    return 0;
}
