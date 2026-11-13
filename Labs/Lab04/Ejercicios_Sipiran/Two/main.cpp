#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
//n es el numero de datos de mi arreglo
int primerCero(int arr[], int inicio, int final, int n) {
    if (inicio > final) return n;                            // no hay ceros: el primer cero estaria en n
    int medio = (inicio + final) / 2;
    if (arr[medio] == 1)                                     //zona de 1's -> frontera a la derecha
        return primerCero(arr, medio + 1, final, n);
    if (medio == 0 or arr[medio - 1] == 1)                   //arr[med] es cero y a su izquierda hay un 1 -> frontera
        return medio;
    return primerCero(arr, inicio, medio - 1, medio); //hay más ceros a la izquierda
}

int main() {
    int arr[] = {1, 1, 1, 1, 1, 1, 0};
    int ceros = 7 - primerCero(arr, 0, 7 - 1, 7);
    cout << ceros;
    return 0;
}
