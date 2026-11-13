#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include "Ciudad.h"

int primerIndice(struct Ciudad *ciudades, int inicio, int final, int limite, int n) {
    if (inicio > final) return n;
    int medio = (inicio + final) / 2;
    if (ciudades[medio].distancia >= limite) {
        int izquierda = primerIndice(ciudades, inicio, medio - 1, limite, n);
        if (izquierda == n)
            return medio;
        else
            return izquierda;
    }
    return primerIndice(ciudades, medio + 1, final, limite, n);
}

int ultimoIndice(struct Ciudad *ciudades, int inicio, int final, int limite) {
    if (inicio > final) return -1;
    int medio = (inicio + final) / 2;
    if (ciudades[medio].distancia <= limite) {
        int derecha = ultimoIndice(ciudades, medio + 1, final, limite);
        if (derecha == -1)
            return medio;
        else
            return derecha;
    }
    return ultimoIndice(ciudades, inicio, medio - 1, limite);
}


void mezclar(struct Ciudad *ciudades, int inicio, int medio, int final) {
    Ciudad *aux = new Ciudad[final - inicio + 1];
    int i = inicio;
    int j = medio + 1;
    int z = 0;

    while (i <= medio and j <= final) {
        if (ciudades[i].distancia <= ciudades[j].distancia) {
            aux[z++] = ciudades[i++];
        } else {
            aux[z++] = ciudades[j++];
        }
    }
    while (i <= medio)
        aux[z++] = ciudades[i++];

    while (j <= final)
        aux[z++] = ciudades[j++];

    for (int e = 0; e < z; e++)
        ciudades[inicio + e] = aux[e];

    delete[] aux;
}

void mergeSort(struct Ciudad *ciudades, int inicio, int final) {
    if (inicio >= final) return; //caso base: 0 o 1 elemento
    int medio = (inicio + final) / 2;
    mergeSort(ciudades, inicio, medio);
    mergeSort(ciudades, medio + 1, final);
    mezclar(ciudades, inicio, medio, final);
}

void imprimir(struct Ciudad *ciudades, int inicio, int final) {
    for (int i = inicio; i <= final; i++)
        cout << left << setw(9) << ciudades[i].nombre << ": "
                << ciudades[i].distancia << " km." << endl;
}

int main() {
    //cargamos los datos
    struct Ciudad ciudades[] = {
        {"Lima", 34},
        {"Cusco", 12},
        {"Arequipa", 67},
        {"Trujillo", 8},
        {"Piura", 45},
        {"Iquitos", 23},
        {"Tacna", 89},
        {"Puno", 5}
    };

    int n = sizeof(ciudades) / sizeof(ciudades[0]);

    cout << "Ciudades al inicio" << endl;
    imprimir(ciudades, 0, n - 1);

    //un solo ordenamiento
    mergeSort(ciudades, 0, n - 1);

    cout << endl << "Ciudades ordenadas por distancia" << endl;
    imprimir(ciudades, 0, n - 1);

    int d1 = 10, d2 = 45;

    int primero = primerIndice(ciudades, 0, n - 1, d1, n);
    int ultimo = ultimoIndice(ciudades, 0, n - 1, d2);
    int total = ultimo - primero + 1;
    if (total < 0) total = 0;

    cout << endl;

    if (total == 0) {
        cout << "No hay ciudades en ese rango" << endl;
    } else {
        cout << "Ciudades entre " << d1 << " km. y " << d2 << " km." << endl;
        imprimir(ciudades, primero, ultimo);
        cout << "Total: " << total << " ciudades" << endl;
    }
    return 0;
}
