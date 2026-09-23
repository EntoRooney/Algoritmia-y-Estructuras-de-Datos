#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
#define N 10

int buscarCandidato(int actual, int oponente, int n, int aporte[N][N]) {
    //caso base
    //si el oponente llega a n, significa que ya se comparo
    //al actual con todos los demas canarios
    //por eso se retorna actual como posible candidato
    if (oponente == n) return actual;
    //tenemos q tener en claro que el cuando el aporte de un canario
    //se le escribe asi aporte[actual][oponente] = a
    //esto se lee como el canario oponente aporta "a" genes al canario actual
    if (aporte[actual][oponente] != 0) {
        //si el valor es dif de 0, entonces el actual recibio de otro
        //entonces el actual queda descartado y el oponente queda a ser el nuevo candidato
        return buscarCandidato(oponente, oponente + 1, n, aporte);
    } else {
        //si el valor es 0, es decir que el actual no ha recibio genes del oponente
        //entonces actual sigue siendo el candidato y pasamos al sgt oponente
        return buscarCandidato(actual, oponente + 1, n, aporte);
    }
}

bool verificarCandidato(int candidato, int i, int n, int aporte[N][N]) {
    //caso base
    //si i llega a n, significa que ya se reviso al candidato con todos los demas canarios
    //si no se ha encontrado una condicion invalida entonces si cumple que es el ancestral
    if (i == n) return true;
    //si i es igual al candidado entonces solo se avanza al sigueinte
    if (i == candidato) {
        return verificarCandidato(candidato, i + 1, n, aporte);
    }
    //si el candidato ha sido aportado por i, queda descartado
    if (aporte[candidato][i] != 0)
        return false;

    //si el candidato no ha aportado a i, queda descartado
    if (aporte[i][candidato] == 0)
        return false;

    //si las demas condiciones se cumplen, entonces se sigue verificando con el sgt canario
    return verificarCandidato(candidato, i + 1, n, aporte);
}

int main() {
    //defino el registro de aportes
    int aporte[N][N] = {
        {100, 0, 50, 40, 30, 20, 30, 0, 80, 0},
        {50, 100, 0, 40, 30, 20, 20, 0, 10, 25},
        {80, 30, 100, 40, 30, 0, 30, 20, 10, 60},
        {50, 0, 0, 100, 30, 0, 50, 30, 30, 90},
        {50, 10, 10, 10, 100, 0, 10, 50, 10, 50},
        {20, 0, 0, 0, 0, 100, 90, 20, 40, 20},
        {0, 0, 0, 0, 0, 0, 100, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 50, 100, 50, 20},
        {20, 0, 0, 40, 0, 0, 90, 0, 100, 10},
        {0, 10, 0, 0, 0, 0, 10, 0, 60, 100}
    };
    //defino el candidato y lo mando a mi recursiva

    int candidato = buscarCandidato(0, 1,N, aporte);
    //ya teniendo al candidado tenemos que verificarlo
    if (verificarCandidato(candidato, 0,N, aporte)) {
        cout << "Canario Ancestral: " << candidato << endl;
    } else {
        cout << "No hay Canario Ancestral" << endl;
    }

    return 0;
}
