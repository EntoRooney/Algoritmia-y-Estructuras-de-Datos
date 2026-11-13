#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int buscar(int arr[], int inicio, int fin) {
    if (inicio == fin) return arr[inicio];
    int medio = (inicio + fin) / 2;
    if (medio % 2 == 1) medio--;
    if (arr[medio] == arr[medio + 1]) return buscar(arr, medio + 2, fin);
    return buscar(arr, inicio, medio);
}

int main() {
    int arr[] = {1, 1, 3, 3, 4, 5, 5, 7, 7, 8, 8};

    int indice = buscar(arr, 0, 11);
    cout << arr[indice];
    return 0;
}
