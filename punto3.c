#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct Tarea
{
    int TareaID;
    char *Descripcion;
    int Duracion;
}Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo* Siguiente;
}Nodo;

Nodo *CrearListaVacia();
Nodo *CrearNodo();
void InsertarNodo(Nodo **Start);
void mostrarLista(Nodo *Start);
void EliminarNodo(Nodo * nodo);


int main(){
    Nodo * StartTareasPendientes;
    Nodo * StartTareasRealizadas;

    StartTareasPendientes = CrearListaVacia(); 
    StartTareasRealizadas = CrearListaVacia();

    InsertarNodo(&StartTareasPendientes);
    mostrarLista(StartTareasPendientes);
    

    return 0;
}

Nodo *CrearListaVacia(){
    return NULL;
}

Nodo *CrearNodo(){
    srand(time(NULL));
    Nodo *NuevoNodo = (Nodo *) malloc(sizeof(Nodo));
    NuevoNodo->T.Descripcion = "DESCRIPCION";
    NuevoNodo->T.Duracion=10+rand()%101;
    NuevoNodo->T.TareaID=69;
    NuevoNodo->Siguiente=NULL;
    return NuevoNodo;
}

void InsertarNodo(Nodo **Start){
    Nodo *NuevoNodo = CrearNodo();
    NuevoNodo->Siguiente=*Start;
    *Start = NuevoNodo;
}

void mostrarLista(Nodo *Start){
    Nodo *temp = Start;
    while (temp != NULL)
    {
        printf("Descripcion: %s\n", temp->T.Descripcion);
        printf("Duracion: %d\n", temp->T.Duracion);
        printf("Tarea ID: %d\n", temp->T.TareaID);

        temp=temp->Siguiente;
    }
    
}

void EliminarNodo(Nodo * nodo){
    if (!nodo)
    {
        free(nodo);
    }
    
}