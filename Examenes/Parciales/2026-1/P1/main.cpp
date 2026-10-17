#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    //programa que suma bloques de una matriz y lo compara con U
    int const F = 4, C = 4; //fila y columna
    int matriz[F][C] = {
        {1, 2, 3, 4},
        {5, 20, 1, 2},
        {3, 25, 4, 1},
        {1, 2, 30, 3}
    };
    int H = 2, W = 2, U = 50;

    cout << "Matriz evaluada: " << endl;
    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            cout << matriz[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Altura maxima del bloque: " << H << endl;
    cout << "Ancho maximo del bloque: " << W << endl;
    cout << "Umbral sospechoso: " << U << endl;
    cout << endl;
    bool encontro = false;
    int e = 1;
    //recorremos la matriz para tener poder agarrar todos los bloques posibles
    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            for (int a = 1; a <= H; a++) {
                if (i + a > F) break;
                for (int b = 1; b <= W; b++) {
                    if (j + b > C) break;
                    int sum = 0;
                    int filaFinal = 0;
                    int columnaFinal = 0;
                    for (int x = i; x < a + i; x++) {
                        for (int y = j; y < b + j; y++) {
                            sum += matriz[x][y];
                        }
                    }
                    filaFinal = a + i - 1;
                    columnaFinal = b + j - 1;
                    if (sum > U) {
                        encontro = true;
                        cout << "Bloque sospechoso " << e << ":" << endl;
                        cout << "Fila inicial: " << i << endl;
                        cout << "Columna inicial: " << j << endl;
                        cout << "Fila final: " << filaFinal << endl;
                        cout << "Columna final: " << columnaFinal << endl;
                        cout << "Suma del bloque: " << sum << endl;
                        cout << endl;
                        e++;
                    }
                }
            }
        }
    }

    if (!encontro) {
        cout << "No se encontraron patrones sospechosos" << endl;
    }
    return 0;
}
