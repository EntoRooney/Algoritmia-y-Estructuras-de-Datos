#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#define N 6
#define M 7

bool buscarOro(int mapa[N][M], int fila, int columna, int df, int dc, int &filaOro, int &columnaOro) {
    fila += df;
    columna += dc;

    while (fila >= 0 and fila < N and columna >= 0 and columna < M) {
        //si encontramos una roca, dejamos de buscar
        if (mapa[fila][columna] == 8) return false;

        //si encontramos oro
        if (mapa[fila][columna] == 0) {
            filaOro = fila;
            columnaOro = columna;
            return true;
        }

        fila += df;
        columna += dc;
    }
    return false;
}

void imprimirVetas(int mapa[N][M], int fila, int columna, int dx, int dy, int combustible) {
    //casos base
    //caso 1 cuando no haya combustble
    if (combustible < 0) return;
    //caso 2 cuando estemos fuera del mapa
    if (fila < 0 or fila >= N or columna < 0 or columna >= M) return;

    //si encuentro una roca
    if (mapa[fila][columna] == 8) {
        imprimirVetas(mapa, fila - dx, columna - dy, -dx, -dy, combustible - 1);
        return;
    }

    //si encuentro oro
    int filaOro, columnaOro;
    //si se mueve horizontalmente
    if (dx == 0) {
        //para abajo
        if (buscarOro(mapa, fila, columna, 1, 0, filaOro, columnaOro)) {
            cout << "Oro: " << filaOro << " " << columnaOro << endl;
        }
        //para arriba
        if (buscarOro(mapa, fila, columna, -1, 0, filaOro, columnaOro)) {
            cout << "Oro: " << filaOro << " " << columnaOro << endl;
        }
        //para atras
        if (buscarOro(mapa, fila, columna, 0, -dy, filaOro, columnaOro)) {
            cout << "Oro: " << filaOro << " " << columnaOro << endl;
        }
    } else {
        //si se mueve verticalmente
        //para derecha
        if (buscarOro(mapa, fila, columna, 0, 1, filaOro, columnaOro)) {
            cout << "Oro: " << filaOro << " " << columnaOro << endl;
        }
        //para izquierda
        if (buscarOro(mapa, fila, columna, 0, -1, filaOro, columnaOro)) {
            cout << "Oro: " << filaOro << " " << columnaOro << endl;
        }
        //para atras
        if (buscarOro(mapa, fila, columna, -dx, 0, filaOro, columnaOro)) {
            cout << "Oro: " << filaOro << " " << columnaOro << endl;
        }
    }
    imprimirVetas(mapa, fila + dx, columna + dy, dx, dy, combustible - 1);
}

int main() {
    int mapa[N][M] = {
        {1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 8, 1, 1},
        {0, 0, 1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0, 1, 1},
    };

    int combustible = 4;
    // cout<<"Inserte el combustible: ";
    // cin>>combustible;

    int x = 3, y = 2; //posicion enviada

    imprimirVetas(mapa, x, y, 0, 1, combustible);
    return 0;
}
