#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
//Ento Rooney Lazaro Trujillo
//20222032
using namespace std;

int encontrarBeneficioMaximo(int proyectoActual, int presupuestoActual, int nroProyectos, int arrCosto[],
                             int arrGanancia[]) {
    //casos base
    //1. cuando me quede sin presupuesto
    if (presupuestoActual < 0) return 0;
    //2. cuando llegue al final
    if (proyectoActual >= nroProyectos) return 0;
    //tengo unicamente dos opciones
    //tomo el proyecto o no lo tomo
    int tomar;
    int noTomar = encontrarBeneficioMaximo(proyectoActual + 1, presupuestoActual, nroProyectos, arrCosto, arrGanancia);
	//el >= es para que si puedo saber si mi presupuesto puede ser 0 o mas y asi seguir avanzando
    if (presupuestoActual - arrCosto[proyectoActual] >= 0) {
        tomar = arrGanancia[proyectoActual] +
                encontrarBeneficioMaximo(proyectoActual + 1, presupuestoActual - arrCosto[proyectoActual], nroProyectos,
                                         arrCosto, arrGanancia);
    } else {
        tomar = 0;
    }
    if (noTomar > tomar) {
        return noTomar;
    } else {
        return tomar;
    }
}

int beneficioMaximo(int nroProyectos, int presupuesto, int arrCosto[], int arrGanancia[]) {
    return encontrarBeneficioMaximo(0, presupuesto, nroProyectos, arrCosto, arrGanancia);
}

int main() {
    //para este ejercicio usaremos arrays
    int nroProyectos = 7;
    //array para el costo
    int arrCosto[nroProyectos] = {100, 50, 150, 50, 50, 150, 100};
    int arrGanancia[nroProyectos] = {200, 300, 300, 400, 200, 800, 250};
    //declaramos el presupuesto
    int presupuesto = 400;
    cout << "Beneficio total: " << beneficioMaximo(nroProyectos, presupuesto, arrCosto, arrGanancia)
            << " (Millones de $)" << endl;
    return 0;
}
