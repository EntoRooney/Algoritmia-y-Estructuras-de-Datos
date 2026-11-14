#include <iostream>
#include <fstream>
#include <iomanip>
#define N 6

using namespace std;

int buscarSolitario(int *fila, int inicio, int final) {
    //caso base encontramos el unico elemento
    if (inicio == final) return fila[inicio];

    //calculamos la posicion del medio
    int medio = (inicio + final) / 2;

    //si el medio es par, las parejas estan alineadas empezando desde
    //la posicion cero
    if (medio % 2 == 0) {
        if (fila[medio] == fila[medio + 1]) {
            return buscarSolitario(fila, medio + 2, final);
        } else {
            return buscarSolitario(fila, inicio, medio);
        }
    } else {
        //si el medio es impar, revisamos la alineacion contraria
        if (fila[medio] == fila[medio + 1]) {
            return buscarSolitario(fila, inicio, medio - 1);
        } else {
            return buscarSolitario(fila, medio + 1, final);
        }
    }
}

void mostrarMutacion(int mutacion) {
    switch (mutacion) {
        case 1: cout << "Amarillo";
            break;
        case 2: cout << "Rojo";
            break;
        case 3: cout << "Blanco";
            break;
        case 4: cout << "Negro";
            break;
        case 5: cout << "Bruno";
            break;
        case 6: cout << "Agata";
            break;
        case 7: cout << "Isabel";
            break;
    }
}

void buscarFaltantes(int canarios[N][N]) {
    for (int fila = 0; fila < N; fila++) {
        cout << "Fila " << fila + 1 << ": ";

        //si la ultima posicicion tiene INT_MAX
        //existe una casilla vacia y un canario sin pareja

        if (canarios[fila][N - 1] == INT_MAX) {
            int mutacion = buscarSolitario(canarios[fila], 0,N - 2);
            mostrarMutacion(mutacion);
        } else {
            cout << "Sin faltantes";
        }
        cout << endl;
    }
}

void mezclar(int *fila, int inicio, int medio, int final) {
    //calculamos cuantos elementos tiene cada mitad
    int cantidadIzquierda = medio - inicio + 1;
    int cantidadDerecha = final - medio;

    //creamos arreglos aux para guardar las dos mitades
    int izquierda[N + 1], derecha[N + 1];

    //copiamos la primera mitad
    for (int i = 0; i < cantidadIzquierda; i++) {
        izquierda[i] = fila[inicio + i];
    }
    //agregamos el centinela al final
    izquierda[cantidadIzquierda] = INT_MAX;

    //copaimos la segunda mitad
    for (int i = 0; i < cantidadDerecha; i++) {
        derecha[i] = fila[medio + 1 + i];
    }
    //agregamos el centinela al final
    derecha[cantidadDerecha] = INT_MAX;

    //indices para recorrer las dos mitades
    int indiceIzquierda = 0;
    int indiceDerecha = 0;

    //mezclamos ambaas mitades en el array og
    for (int i = inicio; i <= final; i++) {
        if (izquierda[indiceIzquierda] < derecha[indiceDerecha]) {
            fila[i] = izquierda[indiceIzquierda++];
        } else {
            fila[i] = derecha[indiceDerecha++];
        }
    }
}

void mergeSort(int *fila, int inicio, int final) {
    //caso base: ya no podemos dividir mas
    if (inicio >= final) return;

    //encontramos la mitad de la fila
    int medio = (inicio + final) / 2;

    //ordenamos la mitad izquierda
    mergeSort(fila, inicio, medio);
    //ordenamos la mitad derecha
    mergeSort(fila, medio + 1, final);
    //unimos las dos mitades ordenadas
    mezclar(fila, inicio, medio, final);
}


void ordenarMatriz(int canarios[N][N]) {
    for (int fila = 0; fila < N; fila++) {
        mergeSort(canarios[fila], 0,N - 1);
    }
}

void imprimirCanarios(int canarios[N][N]) {
    for (int fila = 0; fila < N; fila++) {
        for (int columna = 0; columna < N; columna++) {
            if (canarios[fila][columna] == INT_MAX)
                cout << "INT_MAX ";
            else
                cout << canarios[fila][columna] << ' ';
        }
        cout << endl;
    }
}

int main() {
    //matriz de seis filas y seis columnas
    //INT_MAX representa una casilla vacia
    int canarios[N][N] = {
        {INT_MAX, 3, 7, 2, 2, 7},
        {5,INT_MAX, 3, 1, 5, 3},
        {7, 7, 3, 6, 6, 3},
        {7, 4,INT_MAX, 7, 2, 4},
        {5, 1, 2, 5, 1, 2},
        {6,INT_MAX, 7, 4, 7, 4}
    };
    cout << endl << "Matriz" << endl;
    imprimirCanarios(canarios);

    //primero ordenamos todas las filas
    ordenarMatriz(canarios);
    //mostramos la matriz ordenada
    cout << endl << "Matriz Ordenado" << endl;
    imprimirCanarios(canarios);

    //despues buscamos las mutaciones faltantes
    cout << endl << "Faltantes:" << endl;
    buscarFaltantes(canarios);


    return 0;
}
