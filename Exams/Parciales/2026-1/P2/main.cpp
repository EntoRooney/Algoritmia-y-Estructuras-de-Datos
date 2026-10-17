#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void contarPalabras(char texto[], char palabra[], int posTexto, int posPalabra, int &contador) {
    //caso base> terminamos de recorrer el texto
    if (texto[posTexto] == '\0') return;

    //verificamos que estemos al inicio de la palabra
    if (posPalabra == 0 and posTexto > 0 and texto[posTexto - 1] != ' ') {
        contarPalabras(texto, palabra, posTexto + 1, 0, contador);
        return;
    }

    //si las letras son diferentes, descargamos esa palabra
    if (texto[posTexto] != palabra[posPalabra]) {
        contarPalabras(texto, palabra, posTexto + 1, 0, contador);
        return;
    }

    //si encontramos la palabra completa
    if (palabra[posPalabra + 1] == '\0' and (texto[posTexto + 1] == ' ' or texto[posTexto + 1] == '\0')) {
        contador++;
    }

    //seguimos comparando las sgts letras
    contarPalabras(texto, palabra, posTexto + 1, posPalabra + 1, contador);
}

int main() {
    char texto[] = "ahola";
    char palabra[] = "hola";
    int contador = 0;
    contarPalabras(texto, palabra, 0, 0, contador);
    cout << contador;
    return 0;
}
