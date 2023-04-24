#include <stdio.h>
#include <time.h>

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

Nodo *CrearListaVacia();
Nodo *CrearNodo(Tarea NuevaTarea);
void InsertarNodo(Nodo **Start, Tarea NuevaTarea);


int main(){
    Nodo * Start;
    Start = CrearListaVacia(); 


}

Nodo *CrearListaVacia(){
    return NULL;
}

Nodo *CrearNodo(Tarea NuevaTarea){
    srand(time(NULL));
    Nodo *NuevoNodo = (Nodo *) malloc(sizeof(Nodo));
    NuevoNodo->T.Descripcion = "DESCRIPCION";
    NuevoNodo->T.Duracion=10+rand()%101;
    NuevoNodo->Siguiente=NULL;
    return NuevoNodo;
}

void InsertarNodo(Nodo **Start, Tarea NuevaTarea){
    Nodo *NuevoNodo = CrearNodo(NuevaTarea);
    NuevoNodo->Siguiente=*Start;
    *Start = NuevoNodo;
}


void EliminarNodo(Nodo * nodo){
    if (!nodo)
    {
        free(nodo);
    }
    
}