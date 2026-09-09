#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#define M 11
#define N 6

bool moverRobot(int x, int y, int numGaleria, char matriz[N][M]) {
    //casos base
    if (y >= M) return true; //la galeria se completo
    if (x < 0 or x >= N) return false; //mi x esta fuera del rango
    if (matriz[x][y] != '0')return false; // la celda esta ocupada
    //marco la celda con el numero de la galeria
    matriz[x][y] = numGaleria + '0';
    //ahora hago en orden los movimientos
    if (moverRobot(x + 1, y, numGaleria, matriz)) {
        //abajo
    } else if (moverRobot(x, y + 1, numGaleria, matriz)) {
        //derecha
    } else if (moverRobot(x - 1, y, numGaleria, matriz)) {
        //arriba
    }else {
        //en caso los 3 movimientos me devuelvan false
        //se deshace todo y retorno falso
        matriz[x][y] = '0';
        return false;
    }
    return true;
}

void imprimirMapa(char matriz[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    char mapa[N][M]{};
    //lenamos el mapa de 0's
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            mapa[i][j] = '0';
        }
    }
    mapa[3][5] = '*';
    mapa[4][5] = '*';
    mapa[5][5] = '*';
    imprimirMapa(mapa);
    cout<<endl;
    int galeria = 1;
    int filaActual = N - 1;
    //tiene dos condiciones de para
    //1. la fila de inicio existe?
    //2. la celdad de inicio sigue libre?
    while (filaActual >= 0 and mapa[filaActual][0] == '0') {
        moverRobot(filaActual, 0, galeria, mapa);
        //subo una fila
        filaActual = filaActual - 1;
        //aumento una galeria
        galeria = galeria + 1;
    }
    imprimirMapa(mapa);
    return 0;
}
