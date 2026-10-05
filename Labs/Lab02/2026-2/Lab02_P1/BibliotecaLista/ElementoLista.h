//Fecha:  sábado 06 Setiembre 2025 
//Autor: Ana Roncal 

#ifndef LISTASIMPLEMENTEENLAZADA_ELEMENTOLISTA_H
#define LISTASIMPLEMENTEENLAZADA_ELEMENTOLISTA_H
struct ElementoLista {
    char codigo[5]{};
    char descripcion[20]{};
    int ingrediente[20]{};
    int cantidad[20]{};
    int cantidadIngredientes;
};
#endif //LISTASIMPLEMENTEENLAZADA_ELEMENTOLISTA_H