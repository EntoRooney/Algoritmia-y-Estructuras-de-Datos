#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void contarFrecuencias(char almacen[], int inicio, int final, int frecuencias[]) {
    const int TAM = 256; //una casilla por cada caracter posible

    if (inicio == final) {
        //caso base: un solo polo
        for (int c = 0; c < TAM; c++)
            frecuencias[c] = 0; //empiezo la tabla en ceros

        frecuencias[almacen[inicio]] = 1;
        return;
    }

    int medio = (inicio + final) / 2;
    int frecIzquierda[TAM];
    int frecDerecha[TAM];

    contarFrecuencias(almacen, inicio, medio, frecIzquierda); //conquisto la mitad izquierda
    contarFrecuencias(almacen, medio + 1, final, frecDerecha); //conquisto la mitad derecha

    for (int c = 0; c < TAM; c++) //combino: sumo casilla por casilla
        frecuencias[c] = frecIzquierda[c] + frecDerecha[c];
}

int main() {
    char almacen[] = {'A', 'F', 'B', 'F', 'F', 'C', 'C', 'F'};
    int n = sizeof(almacen) / sizeof(almacen[0]);
    int frecuencias[256];

    contarFrecuencias(almacen, 0, n - 1, frecuencias);

    int mejor = 0; //posiciones de la casilla con mas polos
    for (int c = 1; c < 256; c++) {
        if (frecuencias[c] > frecuencias[mejor])
            mejor = c;
    }

    cout << "Polos con mas unidades: " << (char) mejor << endl;
    cout << "Cantidad de polos: " << frecuencias[mejor] << endl;
    return 0;
}
