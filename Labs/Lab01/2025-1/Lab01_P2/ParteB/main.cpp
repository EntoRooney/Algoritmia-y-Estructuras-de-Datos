#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;
#include "Recurso.h"
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
//esta parte es lo mismo solo se agrega una condicion uu
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
    //ademas pedimos el nivel de Seguridad minimo
    int presupuesto = 200;
    int nivelSeguridad = 400;
    // cout<<"Ingrese el presupuesto (en miles de soles): ";
    // cin>>presupuesto;
    // cout<<"Ingrese el nivel de seguridad minimo requerido: ";
    // cin>>presupuesto;
    int limiteInferior = presupuesto * 0.8;
    bool imprimio = false; //es para en caso no encuentre solucion
    cout << "Combinaciones validas(Costo entre " << limiteInferior << " y " << presupuesto << " miles ";
    cout << "y Nivel de seguridad >= " << nivelSeguridad << "):" << endl;
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
            int costoTotal = 0;
            //nueva variable para la condicion del siguiente if
            int nivelSeguridadTotal = 0;
            for (int v = 0; v < NUM_RECURSOS; v++) {
                if (arrNumBaseTwo[v] == 1) {
                    costoTotal += recurso[v].costo;
                    nivelSeguridadTotal += recurso[v].nivelSeguridad;
                }
            }
            //simplemente agregamos una condicion más y ya xd
            if (costoTotal >= limiteInferior and costoTotal <= presupuesto and nivelSeguridadTotal >= nivelSeguridad) {
                imprimio = true;
                cout << "Combinacion " << i << ": Recursos ";
                for (int v = 0; v < NUM_RECURSOS; v++) {
                    if (arrNumBaseTwo[v] == 1) {
                        cout << "R" << v+1 << " ";
                    }
                }
                cout << "| Costo: " << costoTotal << " miles " ;
                cout << "| Nivel de Seguridad: " << nivelSeguridadTotal << endl;
            }
        }
        //sino salteamos al otro
    }
    if (not imprimio) {
        cout << "No se encontraron soluciones que cumplan con lo solicitado" << endl;
    }

    return 0;
}
