#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int maximo(int arr[], int inicio, int final) {
    if (inicio == final) return arr[inicio]; //caso base: queda 1 elemento, esa es la cima
    int medio = (inicio + final) / 2;
    if (arr[medio] < arr[medio + 1]) //subida -> la cima esta a la derecha
        return maximo(arr, medio + 1, final);
    return maximo(arr, inicio, medio); //bajada -> la cuma esta en medio o a la izquierda
}

int main() {
    int arr[] = {8, 10, 20, 80, 100, 200, 400, 500, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << maximo(arr, 0, n - 1) << endl;
    return 0;
}
