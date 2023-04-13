#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef Tarea;

void cargarTareas(Tarea **arreglo, int cantidad);
void mostrarTareas(Tarea **arreglo, int cantidad);

int main(){
    int cantidadTareas;
    puts("Ingrese cantidad de tareas a realizar: ");
    scanf("%d", &cantidadTareas);

    Tarea** arreglo = (Tarea**) malloc(sizeof(Tarea*)*cantidadTareas);

    //inicializo en null todos los elementos del vector
    for (int i = 0; i < cantidadTareas; i++)
    {
        arreglo[i] = NULL;
    }
    
    cargarTareas(arreglo, cantidadTareas);
    mostrarTareas(arreglo, cantidadTareas);

    //liberar memoria
        for (int i = 0; i < cantidadTareas; i++)
    {
        free (arreglo);
        free (arreglo[i]);
        free (arreglo[i]->Descripcion);
    }
    
    return 0;
}

void cargarTareas(Tarea **arreglo, int cantidad){
    srand(time(NULL));
    for (int i = 0; i < cantidad; i++)
    {
        arreglo[i]= malloc(sizeof(Tarea)); //reservo memoria para el elemento puntero a la estructura
        arreglo[i]->TareaID=i+1;
        arreglo[i]->Duracion=10+rand()%101;
        printf("Ingrese la descripcion: ");
        char buff[500];
        scanf("%s",buff);
        arreglo[i]->Descripcion = malloc((sizeof(char) * strlen(buff+1)));
        strcpy(arreglo[i]->Descripcion,buff);
    }
}

void mostrarTareas(Tarea **arreglo, int cantidad){
    for (int i = 0; i < cantidad; i++)
    {
        printf("Numero de tarea: %d\n", arreglo[i]->TareaID);
        printf("Duracion: %d\n", arreglo[i]->Duracion);
        printf("La descripcion de la tarea %d es: %s\n", arreglo[i]->TareaID ,arreglo[i]->Descripcion);
    }
    
}