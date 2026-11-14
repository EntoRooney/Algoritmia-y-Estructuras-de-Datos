#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void ordenarSort(int *arr, int inicio, int medio, int final, int &adela, int &adelaFuerte) {
    int size = final - inicio + 1;
    int aux[size];
    for (int i = 0; i < size; i++) aux[i] = arr[i + inicio];
    int k = inicio;
    int izq = 0, der = medio - inicio + 1,
            izqMax = medio - inicio, derMax = final - inicio;
    //caso fuerte
    int izq2 = izq, der2 = der;
    while (izq2 <= izqMax and der2 <= derMax) {
        if (aux[der2] * 2 < aux[izq2]) der2++;
        else {
            adelaFuerte = adelaFuerte + (der2 - der);
            izq2++;
        }
    }
    while (izq2 <= izqMax) {
        adelaFuerte = adelaFuerte + (der2 - der);
        izq2++;
    }

    //caso normal
    while (izq <= izqMax and der <= derMax) {
        if (aux[izq] <= aux[der])arr[k++] = aux[izq++];
        else {
            arr[k++] = aux[der++];
            adela = adela + (izqMax - izq) + 1;
        }
    }
    while (izq <= izqMax) arr[k++] = aux[izq++];
    while (der <= derMax) arr[k++] = aux[der++];
}

void ordenar(int *arr, int inicio, int final, int &adela, int &adelaFuerte) {
    if (inicio == final)return;
    int medio = (inicio + final) / 2;
    ordenar(arr, inicio, medio, adela, adelaFuerte);
    ordenar(arr, medio + 1, final, adela, adelaFuerte);
    ordenarSort(arr, inicio, medio, final, adela, adelaFuerte);
}

int main() {
    int arr[] = {5, 4, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int adela = 0, adelaFuerte = 0;

    ordenar(arr, 0, size - 1, adela, adelaFuerte);
    cout << "Adelantamientos: " << adela << endl;
    cout << "Adelantamientos fuertes: " << adelaFuerte << endl;
    cout << "Dorsales ordenados: ";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    return 0;
}
