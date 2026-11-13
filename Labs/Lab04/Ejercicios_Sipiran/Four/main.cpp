#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int mejorSumaCruzada(int arr[], int inicio, int medio, int final) {
    int sumaActual = arr[medio];
    int mejorSumaIzquierda = sumaActual; //empiezo con arr[medio] que es obligatorio
    for (int i = medio - 1; i >= inicio; i--) {
        //avanzo hacia la izquierda
        sumaActual += arr[i];
        if (sumaActual > mejorSumaIzquierda)
            mejorSumaIzquierda = sumaActual;
    }

    sumaActual = arr[medio + 1];
    int mejorSumaDerecha = sumaActual; //empiezo con arr[medio +1]
    for (int i = medio + 2; i <= final; i++) {
        //avanzo hacia la derecha
        sumaActual += arr[i];
        if (sumaActual > mejorSumaDerecha)
            mejorSumaDerecha = sumaActual;
    }

    return mejorSumaIzquierda + mejorSumaDerecha;
}

int sumaMaxima(int arr[], int inicio, int final) {
    if (inicio == final) return arr[inicio]; //caso base: un solo elemento

    int medio = (inicio + final) / 2;

    int maxIzquierda = sumaMaxima(arr, inicio, medio);
    int maxDerecha = sumaMaxima(arr, medio + 1, final);
    int maxCruce = mejorSumaCruzada(arr, inicio, medio, final);

    int maxTotal = maxIzquierda;
    if (maxDerecha > maxTotal) maxTotal = maxDerecha;
    if (maxCruce > maxTotal) maxTotal = maxCruce;

    return maxTotal;
}

int main() {
    int arr[] = {-2, -5, 6, -2, -3, 1, 5, -6};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << sumaMaxima(arr, 0, n - 1) << endl;
    return 0;
}
