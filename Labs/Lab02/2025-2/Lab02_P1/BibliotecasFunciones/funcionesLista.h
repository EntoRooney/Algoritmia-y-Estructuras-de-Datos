//Fecha:  sábado 30 Agosto 2025 
//Autor: Ana Roncal 

#ifndef LISTASIMPLEMENTEENLAZADA_FUNCIONESLISTA_H
#define LISTASIMPLEMENTEENLAZADA_FUNCIONESLISTA_H

void construir(struct Lista & listaTAD);
void insertarAlFinal(struct Lista & listaTAD, const struct ElementoLista & elemento);
struct NodoLista * obtenerUltimoNodo(const struct Lista & listaTAD);
void imprimirLista(const struct Lista &lista) ;

#endif //LISTASIMPLEMENTEENLAZADA_FUNCIONESLISTA_H