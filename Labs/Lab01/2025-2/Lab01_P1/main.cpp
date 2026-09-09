#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
#include "Control .h"
#define NUM_CONTROLES 8

int main() {
    struct Control control[NUM_CONTROLES]{};
    //insertamos los datos de los controles
    control[0] = {35000, 80, 1};
    control[1] = {24000, 60, 3};
    control[2] = {30000, 70, 2};
    control[3] = {27000, 48, 1};
    control[4] = {10000, 20, 1};
    control[5] = {7000, 35, 2};
    control[6] = {6000, 10, 1};
    control[7] = {40000, 40, 3};
    //uso el caso de prueba 2
    int P = 70000, B = 150, F = 5;
    // cout << "Por favor inserte los datos de P"<< endl;
    // cin >> P;
    // cout << "Por favor inserte los datos de B"<< endl;
    // cin >> B;
    // cout << "Por favor inserte los datos de F"<< endl;
    // cin >> F;
    //como sabemos el total de combinaciones seran 2^8 porque pueden entrar o no
    int numCombinaciones = pow(2, 8);
    bool imprimio = false;
    for (int i = 0; i < numCombinaciones; i++) {
        int arrNumBaseEight[NUM_CONTROLES]{};
        int aux = i;
        int presupuesto = 0, beneficio = 0, falsosNegativos = 0;

        //convertimos en base binaria al numero de la combinacion

        for (int j = 0; j < NUM_CONTROLES; j++) {
            arrNumBaseEight[j] = aux % 2;
            aux /= 2;
        }
        //simplemente verificamos digito por digito para ver si estan dentro o no
        //si lo estan sumamos sus datos
        for (int z = 0; z < NUM_CONTROLES; z++) {
            if (arrNumBaseEight[z] == 1) {
                presupuesto += control[z].costo;
                beneficio += control[z].beneficio;
                falsosNegativos += control[z].falsosNegativos;
            }
        }
        //vemos si cumplen la condicion, si lo hacen la variable boleana cambia y imprime
        if (presupuesto < P and beneficio >= B and falsosNegativos <= F) {
            bool primero = true; //sirve para imprimir en el formato que nos piden
            imprimio = true;
            cout << "Recursos: {";
            for (int z = 0; z < NUM_CONTROLES; z++) {
                if (arrNumBaseEight[z] == 1) {
                    if (!primero) cout << ",";
                    cout << z + 1;
                    primero = false;
                }
            }
            cout << "},";
            cout << "Costo total: " << presupuesto << ", ";
            cout << "Beneficio : " << beneficio << ", ";
            cout << "Falsos Negativos: " << falsosNegativos << endl;
        }
    }
    //en caso no haya encontrado alguna solucion
    if (not imprimio) {
        cout << "No se pueden seleccionar controles de seguridad que cumplan todas las restricciones" << endl;
    }
    return 0;
}
