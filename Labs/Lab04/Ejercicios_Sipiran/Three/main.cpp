#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int minimo(int arr[], int inicio, int final) {
    if (inicio == final) return arr[inicio]; //caso base: queda 1 elemento, ese es el minimo
    int medio = (inicio + final) / 2;
    if (arr[medio] > arr[final])             //medio esta en el bloque grande --> minimo a la derecha
        return minimo(arr, medio + 1, final);
    return minimo(arr, inicio, medio);  //medio esta en el bloque chico --> minimo en medio o a la izquierda
}

int main() {
    int arr[] = {4, 5, 6, 7, 8, 9, 1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << minimo(arr, 0, n - 1) << endl;
    return 0;
}
