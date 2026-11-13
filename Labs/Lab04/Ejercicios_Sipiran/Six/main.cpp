#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
int mezclarYContar(int arr[], int aux[], int inicio, int medio, int final) {
    for (int k = inicio; k <= final; k++)
        aux[k] = arr[k];                         // copio el rango completo al auxiliar

    int inversiones = 0;
    int i = inicio;                              // recorre la mitad izquierda: inicio..medio
    int j = medio + 1;                           // recorre la mitad derecha: medio+1..final
    int k = inicio;                              // posición donde escribo en arr

    while (i <= medio and j <= final) {
        if (aux[i] <= aux[j]) {
            arr[k++] = aux[i++];                 // sin inversión
        } else {
            arr[k++] = aux[j++];
            inversiones += medio - i + 1;        // lo que queda de la mitad izquierda
        }
    }
    while (i <= medio) arr[k++] = aux[i++];      // copio lo que sobre de la izquierda
    while (j <= final) arr[k++] = aux[j++];      // copio lo que sobre de la derecha
    return inversiones;
}

int contarInversiones(int arr[], int aux[],int inicio, int final) {
    if (inicio >= final) return 0;

    int medio = (inicio + final) / 2;

    int invIzquierda = contarInversiones(arr, aux,inicio, medio);
    int invDerecha = contarInversiones(arr, aux,medio+1,final);
    int invCruzadas = mezclarYContar(arr,aux,inicio,medio,final);

    return invIzquierda+invDerecha+invCruzadas;
}

int main() {
    int arr[] = {31, 5, 14, 7, 12, 1, 21, 18};
    int n = sizeof(arr) / sizeof(arr[0]);
    int aux[100];                                // auxiliar: su tamaño debe ser >= n
    cout << contarInversiones(arr, aux, 0, n - 1) << endl;
    return 0;
}