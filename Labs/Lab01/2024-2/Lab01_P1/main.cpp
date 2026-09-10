#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstring>

#define NUM_LETRAS 10
#define NUM_PALABRAS 8

using namespace std;
#include "Letras.h"
#include "Palabras.h"
//con structs sale mas facil uu
int main() {
    struct Letras letra[NUM_LETRAS]{};
    //insertamos las letras del enunciado
    letra[0] = {'G'};
    letra[1] = {'A'};
    letra[2] = {'L'};
    letra[3] = {'A'};
    letra[4] = {'O'};
    letra[5] = {'G'};
    letra[6] = {'L'};
    letra[7] = {'M'};

    struct Palabras palabra[NUM_PALABRAS]{};
    //insertamos las palabras del enunciado
    palabra[0] = {'G', 'O', 'L'};
    palabra[1] = {'G', 'A', 'L', 'A'};
    palabra[2] = {'A', 'L', 'A'};
    palabra[3] = {'L', 'O', 'M', 'A'};
    //ahora tenemos que calcular el numero de combinaciones
    //como simplemente sera una mochila, tenemos dos opciones
    //es decir sera un 2^numLetras
    int numCombinaciones = pow(2, 8);

    //recorremos todas las palabras

    for (int p = 0; p < NUM_PALABRAS; p++) {
        int numLetrasPalabras = strlen(palabra[p].letras);
        //inicializamos para la impresion
        palabra[p].numCombi = 0;

        //recorremos todas las combinaciones
        for (int i = 0; i < numCombinaciones; i++) {
            int arrNumBaseTwo[NUM_LETRAS]{};
            int aux = i;

            //convertimos el numero de la combinacion actual en base dos
            for (int j = 0; j < NUM_LETRAS; j++) {
                arrNumBaseTwo[j] = aux % 2;
                aux /= 2;
            }

            //guardamos las letras que fueron seleccionadas
            char letrasSeleccionadas[NUM_LETRAS]{};
            int cantidadSelecciones = 0;

            for (int z = 0; z < NUM_LETRAS; z++) {
                if (arrNumBaseTwo[z] == 1) {
                    letrasSeleccionadas[cantidadSelecciones] = letra[z].letra;
                    cantidadSelecciones++;
                }
            }

            //si no tienen la misma cantidad de letras
            //entonces no pueden formar la palabra
            if (cantidadSelecciones != numLetrasPalabras) {
                continue;
            }

            //ahora vamos a verificar que una letra no se repita dos veces
            bool usadas[NUM_LETRAS]{};

            bool cumplePalabra = true;

            //recorremos cada letra de la palabra
            for (int e = 0; e < numLetrasPalabras; e++) {
                bool encontrada = false;

                //buscamos esa letra dentro de las seleccionadas
                for (int d = 0; d < cantidadSelecciones; d++) {
                    //el array de bool usadas es para que no se repita alguna letra
                    if (!usadas[d] and palabra[p].letras[e] == letrasSeleccionadas[d]) {
                        usadas[d] = true;
                        encontrada = true;
                        break;
                    }
                }
                //si no encontre la letra q necesitaba
                //esta combinacion no puede formar la palabra
                if (!encontrada) {
                    cumplePalabra = false;
                    break;
                }
            }
            if (cumplePalabra) {
                palabra[p].numCombi++;
            }
        }
    }
    //solo es impresion
    for (int v = 0; v < NUM_PALABRAS; v++) {
        if (strlen(palabra[v].letras) > 0) {
            cout << "La palabra: " << palabra[v].letras << " tiene " <<
                    palabra[v].numCombi << " combinaciones de Letras." << endl;
        }
    }

    return 0;
}
