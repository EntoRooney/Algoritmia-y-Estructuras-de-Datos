#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;
#include "Recurso .h"
#define NUM_RECURSOS 10

bool esValida(int arrNumBaseTwo[], struct Recurso recurso[]) {
    for (int i = 0; i < NUM_RECURSOS; i++) {
        if (arrNumBaseTwo[i] == 1) {
            for (int d = 0; d < recurso[i].cantidadRecursos; d++) {
                int indiceReque = recurso[i].arrRecursosImplementados[d];
                if (arrNumBaseTwo[indiceReque - 1] == 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    struct Recurso recurso[NUM_RECURSOS]{};
    //insertamos los valores iniciales
    recurso[0] = {50, 120, {}, 0};
    recurso[1] = {40, 110, {}, 0};
    recurso[2] = {80, 140, {}, 0};
    recurso[3] = {70, 130, {1}, 1};
    recurso[4] = {85, 160, {1}, 1};
    recurso[5] = {140, 250, {1, 2}, 2};
    recurso[6] = {55, 100, {2}, 1};
    recurso[7] = {130, 240, {2, 3}, 2};
    recurso[8] = {30, 90, {}, 0};
    recurso[9] = {150, 300, {1, 2, 5}, 3};
    //pedimos el presupuesto inicial y sacamos el 80%
    int presupuesto = 100;
    // cout<<"Ingrese el presupuesto (en miles de soles): ";
    // cin>>presupuesto;
    int limiteInferior = presupuesto * 0.8;
    bool imprimio = false; //es para en caso no encuentre solucion
    cout << "Combinaciones validas(Costo entre " << limiteInferior << " y " << presupuesto << " miles):" << endl;
    //como sabemos que solo pueden estar o no estar, es una mochila simple
    int numCombinacions = pow(2, 10);
    for (int i = 0; i < numCombinacions; i++) {
        int arrNumBaseTwo[10]{};
        int aux = i;
        //convertimos el numero en base dos, porque solo tienen dos opciones
        for (int j = 0; j < NUM_RECURSOS; j++) {
            arrNumBaseTwo[j] = aux % 2;
            aux /= 2;
        }

        //chequeamos que todos los que entran, entren con sus requerimientos
        if (esValida(arrNumBaseTwo, recurso)) {
            //variable donde guarda la suma de los costos y asi poder verificar la condicion de la pregunta
            int costoTotal = 0;
            for (int v = 0; v < NUM_RECURSOS; v++) {
                if (arrNumBaseTwo[v] == 1) {
                    costoTotal += recurso[v].costo;
                }
            }
            if (costoTotal >= limiteInferior and costoTotal < presupuesto) {
                imprimio = true;
                cout << "Combinacion " << i << ": Recursos ";
                for (int v = 0; v < NUM_RECURSOS; v++) {
                    if (arrNumBaseTwo[v] == 1) {
                        //lo sumo uno porque el array comienza de 0
                        cout << "R" << v+1 << " ";
                    }
                }
                cout << "| Costo: " << costoTotal << " miles " << endl;
            }
        }
        //sino salteamos al otro
    }
    if (not imprimio) {
        cout << "No se encontraron soluciones dentro de ese rango" << endl;
    }

    return 0;
}
