#include <stdio.h>

struct Tarea
{
    int TareaID;
    char *Descripcion;
    int Duracion;
}typedef Tarea;

struct Nodo
{
    Tarea T;
    Nodo *Siguiente;
}typedef Nodo;

Nodo *CrearNodo(Tarea nuevaTarea);
Nodo *CrearListaVacia();



int main(){
    Nodo * Start;
    Start = CrearListaVacia(); 


}

Nodo *CrearNodo(Tarea nuevaTarea){
    Nodo *NuevoNodo = (Nodo *) malloc(sizeof(Nodo));
    NuevoNodo->T.Descripcion = "DESCRIPCION";
    NuevoNodo->Siguiente=NULL;
    return NuevoNodo;
}

Nodo *CrearListaVacia(){
    return NULL;
}

void InsertarNodo(Nodo **Start, int valor){
    Nodo *NuevoNodo = CrearNodo(valor);
    NuevoNodo->Siguiente=*Start;
    *Start = NuevoNodo;
}

Nodo * buscarNodo(Nodo * Start, int idBuscado){
    Nodo * Aux = Start;
    while (Aux && Aux->t != idBuscado)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}

void EliminarNodo(Nodo * nodo){
    if (!nodo)
    {
        free(nodo);
    }
    
}