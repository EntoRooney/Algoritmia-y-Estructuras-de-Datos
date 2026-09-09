#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;
#define N 10
#define M 10

int contadorArtefactos(int x, int y, int alcance, int direccion, char matriz[N][M]) {
    int cont = 0;
    if (alcance < 0) return 0;

    if (matriz[x][y] == 'A') cont = 1;
    matriz[x][y] = '*';

    if (direccion <= 0) {
        cont += contadorArtefactos(x - 1, y - 1, alcance - 1, -1, matriz); //diagonal superior izquierda
        cont += contadorArtefactos(x - 1, y, alcance - 1, -1, matriz); //arriba
        cont += contadorArtefactos(x - 1, y + 1, alcance - 1, -1, matriz); //diagonal superior derecha
    }

    if (direccion >= 0) {
        cont += contadorArtefactos(x + 1, y - 1, alcance - 1, 1, matriz); //diagonal inferior izquierda
        cont += contadorArtefactos(x + 1, y, alcance - 1, 1, matriz); //abajo
        cont += contadorArtefactos(x + 1, y + 1, alcance - 1, 1, matriz); //diagonal inferior derecha
    }
    return cont;
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

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            mapa[i][j] = '-';
        }
    }

    mapa[4][4] = 'A';
    mapa[5][5] = 'A';
    mapa[6][5] = 'A';
    mapa[5][6] = 'A';
    mapa[6][8] = 'A';
    mapa[8][6] = 'A';
    imprimirMapa(mapa);
    int numArtefactos = contadorArtefactos(5, 5, 3, 0, mapa);
    cout << "Se encontro " << numArtefactos << " numero de artefactos" << endl;
    imprimirMapa(mapa);

    return 0;
}
