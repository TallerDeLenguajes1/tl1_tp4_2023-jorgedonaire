#include <stdio.h>
#include <stdlib.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef Tarea;

int main(){
    int cantidadTareas;
    puts("Ingrese cantidad de tareas a realizar: ");
    scanf("%d", &cantidadTareas);

    Tarea* arreglo = (Tarea**) malloc(sizeof(Tarea*)*cantidadTareas);


    return 0;
}
