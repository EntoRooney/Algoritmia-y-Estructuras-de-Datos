#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int mezclar(int *ordenDeLlegada, int inicio, int medio, int final, int &fuertes) {
    int p = medio + 1;
    for (int i = inicio; i <= medio; i++) {
        while (p <= final and ordenDeLlegada[i] > 2 * ordenDeLlegada[p])
            p++;
        fuertes += p - (medio + 1);
    }

    int *aux = new int[final - inicio + 1];
    int i = inicio, j = medio + 1, z = 0;
    int adelantamientos = 0;

    while (i <= medio and j <= final) {
        if (ordenDeLlegada[i] <= ordenDeLlegada[j]) {
            aux[z++] = ordenDeLlegada[i++];
        } else {
            aux[z++] = ordenDeLlegada[j++];
            adelantamientos += medio - i + 1;
        }
    }

    while (i <= medio) {
        aux[z++] = ordenDeLlegada[i++];
    }

    while (j <= final) {
        aux[z++] = ordenDeLlegada[j++];
    }

    for (int e = 0; e < z; e++) {
        ordenDeLlegada[inicio + e] = aux[e];
    }
    delete[] aux;
    return adelantamientos;
}

int contarAdelantamientos(int *ordenDeLlegada, int inicio, int final, int &fuertes) {
    if (inicio >= final) return 0;
    int medio = (inicio + final) / 2;
    int total = 0;
    total += contarAdelantamientos(ordenDeLlegada, inicio, medio, fuertes);
    total += contarAdelantamientos(ordenDeLlegada, medio + 1, final, fuertes);
    total += mezclar(ordenDeLlegada, inicio, medio, final, fuertes);
    return total;
}

void imprimir(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
}

int main() {
    int ordenLlegada[] = {3, 1, 4, 2};
    int n = sizeof(ordenLlegada) / sizeof(ordenLlegada[0]);

    cout << "Antes de ordenar: " << endl;
    imprimir(ordenLlegada, n);

    int fuertes = 0;

    int nroAdelantamientos = contarAdelantamientos(ordenLlegada, 0, n - 1, fuertes);
    cout << endl << "Despues de ordenar: " << endl;
    imprimir(ordenLlegada, n);
    cout << endl << "Adelantamientos: " << nroAdelantamientos << endl;
    cout << "Fuertes: " << fuertes << endl;
    return 0;
}
