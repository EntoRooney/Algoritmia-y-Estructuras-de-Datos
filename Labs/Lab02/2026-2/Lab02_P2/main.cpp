#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#define N 5

bool buscarCanario(int matriz[][N], int n, int codigo, int fila, int columna) {
    //CASOS BASE

    //si nos salimos de la matriz ya sea por abajo o por la izquierda
    if (fila >= N or columna < 0) return false;

    //cuando encontramos el codigo buscado
    if (matriz[fila][columna] == codigo) return true;

    //si el codigo buscado es menor que el actual
    //nos movemos una columna hacia la izquierda
    if (codigo < matriz[fila][columna]) {
        return buscarCanario(matriz, n, codigo, fila, columna - 1);
    }

    //si el codigo buscado es mayor que el actual
    //nos movemos una fila hacia abajo
    return buscarCanario(matriz, n, codigo, fila + 1, columna);
}

int main() {
    int nidos[N][N]{
        {1, 8, 17, 21, 36},
        {6, 14, 28, 33, 48},
        {9, 16, 29, 35, 41},
        {10, 20, 30, 37, 45},
        {13, 31, 32, 43, 50},
    };
    int codigo;
    cout << "Ingrese codigo de la anilla: ";
    cin >> codigo;
    if (buscarCanario(nidos,N, codigo, 0, N - 1)) {
        cout << "La anilla " << codigo << " si se encuentra en el avario" << endl;
    } else {
        cout << "La anilla " << codigo << " no se encuentra en el aviario" << endl;
    }
    return 0;
}
