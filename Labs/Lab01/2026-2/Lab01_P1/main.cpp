#include <iostream>
#include <iomanip>
#include <cmath>
//Ento Rooney Lazaro Trujillo
//20222032
using namespace std;
#include "Estudiante.h"
#define NUM_ESTUDIANTE 8

int main() {
    //invocamos la estructura para que se haga más facil
    struct Estudiante estudiante[NUM_ESTUDIANTE]{};
    //hardcodeamos los datos
    estudiante[0] = {1, 3};
    estudiante[1] = {1, 1};
    estudiante[2] = {2, 0};
    estudiante[3] = {3, 1};
    estudiante[4] = {3, 2};
    estudiante[5] = {4, 1};
    estudiante[6] = {4, 2};
    estudiante[7] = {4, 3};
    //ahora calculamos la duracion para cada estudiante
    for (int i = 0; i < NUM_ESTUDIANTE; i++) {
        if (estudiante[i].casa == 1) {
            estudiante[i].duracion = 5 * estudiante[i].cantCualidadad;
            estudiante[i].puntajeAfinidad = 20 * estudiante[i].cantCualidadad;
        } else if (estudiante[i].casa == 2) {
            estudiante[i].duracion = 7 * estudiante[i].cantCualidadad;
            estudiante[i].puntajeAfinidad = 30 * estudiante[i].cantCualidadad;
        } else if (estudiante[i].casa == 3) {
            estudiante[i].duracion = 10 * estudiante[i].cantCualidadad;
            estudiante[i].puntajeAfinidad = 35 * estudiante[i].cantCualidadad;
        } else if (estudiante[i].casa == 4) {
            estudiante[i].duracion = 12 * estudiante[i].cantCualidadad;
            estudiante[i].puntajeAfinidad = 42 * estudiante[i].cantCualidadad;
        }
    }
    //sabemos que los estudiantes pueden pertenecer a 3 turnos o ninguno
    //entonces el numero de combinaciones seria un 4^numEstudiantes
    int numCombinaciones = pow(4,NUM_ESTUDIANTE);
    //declaramos las variables para el puntaje maximo y duracion maxima
    int puntajeMaximo = -1, arrMaximo[NUM_ESTUDIANTE]{};
    int citaOneMax = 0, citaTwoMax = 0, citaThreeMax = 0;
    //recorremos todas las combinaciones posibles
    for (int j = 0; j < numCombinaciones; j++) {
        //como tendremos 4 opciones lo más conveniente seria trabajarlo en un numero base 4
        int arrNumBaseFive[NUM_ESTUDIANTE]{};
        int aux = j; //juego para la conversion
        for (int z = 0; z < NUM_ESTUDIANTE; z++) {
            arrNumBaseFive[z] = aux % 4;
            aux /= 4;
        }
        //ahora calculamos los turnos de cada combinacion
        int turnoOne = 0, turnoTwo = 0, turnoThree = 0;
        //variable para el puntaje de afinidad
        int puntajeAfinidad = 0;
        for (int d = 0; d < NUM_ESTUDIANTE; d++) {
            if (arrNumBaseFive[d] == 1) {
                turnoOne += estudiante[d].duracion;
            } else if (arrNumBaseFive[d] == 2) {
                turnoTwo += estudiante[d].duracion;
            } else if (arrNumBaseFive[d] == 3) {
                turnoThree += estudiante[d].duracion;
            }
            if (arrNumBaseFive[d] > 0) {
                puntajeAfinidad += estudiante[d].puntajeAfinidad;
            }
        }
        //primer filtro
        if (turnoOne <= 35 and turnoTwo <= 30 and turnoThree <= 25) {
            //segundo filtro
            if (puntajeMaximo < puntajeAfinidad) {
                puntajeMaximo = puntajeAfinidad;
                for (int d = 0; d < NUM_ESTUDIANTE; d++) {
                    arrMaximo[d] = arrNumBaseFive[d];
                }
                citaOneMax = turnoOne;
                citaTwoMax = turnoTwo;
                citaThreeMax = turnoThree;
            }
        }
    }
    //es solo formato de impresion uu
    cout << "Resultado obtenido: Puntaje maximo = " << puntajeMaximo << endl;
    cout << "Una distribucion optima posible" << endl;

    bool primera = false;
    cout << "Turno 1: Estudiantes ";
    for (int d = 0; d < NUM_ESTUDIANTE; d++) {
        if (arrMaximo[d] == 1) {
            cout << d + 1;
            if (!primera) {
                cout << ",";
                primera = true;
            }
        }
    }
    cout << endl;

    bool primera2 = false;
    cout << "Turno 2: Estudiantes ";
    for (int d = 0; d < NUM_ESTUDIANTE; d++) {
        if (arrMaximo[d] == 2) {
            cout << d + 1;
            if (!primera2) {
                cout << ",";
                primera2 = true;
            }
        }
    }
    cout << endl;

    bool primera3 = false;
    cout << "Turno 3: Estudiantes ";
    for (int d = 0; d < NUM_ESTUDIANTE; d++) {
        if (arrMaximo[d] == 3) {
            cout << d + 1;
            if (!primera3) {
                cout << ",";
                primera3 = true;
            }
        }
    }
    return 0;
}
