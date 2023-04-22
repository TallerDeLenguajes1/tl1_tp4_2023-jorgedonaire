#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef Tarea;

void cargarTareas(Tarea **tareasPendientes, int cantidad);
void mostrarTareas(Tarea **tareasPendientes, Tarea **tareasRealizadas,int cantidad);
void listarTareas(Tarea **tareasPendientes,Tarea **tareasRealizadas,int cantidad);
Tarea* buscarTarea(Tarea **tareasPendientes, Tarea **tareasRealizadas, int cantidad, int idBuscado);

int main(){
    int cantidadTareas,id;
    puts("Ingrese cantidad de tareas a realizar: ");
    scanf("%d", &cantidadTareas);

    Tarea** tareasPendientes = (Tarea**) malloc(sizeof(Tarea*)*cantidadTareas);
    Tarea** tareasRealizadas = (Tarea**) malloc(sizeof(Tarea*)*cantidadTareas);
    Tarea* tareaAux;
    //inicializo en null todos los elementos del vector
    for (int i = 0; i < cantidadTareas; i++)
    {
        tareasPendientes[i] = NULL;
        tareasRealizadas[i] = NULL;
    }

    cargarTareas(tareasPendientes, cantidadTareas);
    listarTareas(tareasPendientes,tareasRealizadas,cantidadTareas);
    mostrarTareas(tareasPendientes, tareasRealizadas, cantidadTareas);

    puts("Ingrese el ID ");
    scanf("%d", &id);
    tareaAux=buscarTarea(tareasPendientes,tareasRealizadas,cantidadTareas,id);
    printf("Tarea encontrada: %s", tareaAux->Descripcion);

    //liberar memoria
    for (int i = 0; i < cantidadTareas; i++)
    {
        free (tareasPendientes);
        free (tareasPendientes[i]);
        free (tareasPendientes[i]->Descripcion);
    }
    
    return 0;
}

void cargarTareas(Tarea **tareasPendientes, int cantidad){
    srand(time(NULL));
    for (int i = 0; i < cantidad; i++)
    {
        tareasPendientes[i]= malloc(sizeof(Tarea)); //reservo memoria para el elemento puntero a la estructura
        tareasPendientes[i]->TareaID=i+1;
        tareasPendientes[i]->Duracion=10+rand()%101;
        printf("Ingrese la descripcion de la tarea Nro %d: ", tareasPendientes[i]->TareaID);
        char buff[500];
        scanf("%s",buff);
        tareasPendientes[i]->Descripcion = malloc((sizeof(char) * strlen(buff+1))); // reservo memoria para la descripcion antes de cargarla
        strcpy(tareasPendientes[i]->Descripcion,buff);
    }
}

void listarTareas(Tarea **tareasPendientes,Tarea **tareasRealizadas,int cantidad){
    // char respuesta[3];
    int respuesta;

    for (int i = 0; i < cantidad; i++)
    {
        printf("Se realizo la siguiente tarea? - %s (1/0): ", tareasPendientes[i]->Descripcion);
        scanf("%d", &respuesta);

        if (respuesta == 1)
        {
            tareasRealizadas[i] = tareasPendientes[i];
            tareasPendientes[i]=NULL;
        }
        
    }
}

void mostrarTareas(Tarea **tareasPendientes, Tarea **tareasRealizadas, int cantidad){
    puts("////////////////////////////////////");
    puts("***********TAREAS REALIZADAS*************");

    for (int i = 0; i < cantidad; i++)
    {
        if (tareasRealizadas[i] != NULL)
        {        
            printf("Tarea Nro: %d\n", tareasRealizadas[i]->TareaID);
            printf("Duracion: %d\n", tareasRealizadas[i]->Duracion);
            printf("La descripcion de la tarea %d es: %s\n", tareasRealizadas[i]->TareaID ,tareasRealizadas[i]->Descripcion);
            puts("----------------------------");

        }
    }

    puts("////////////////////////////////////");
    puts("***********TAREAS PENDIENTES*************");

    for (int j = 0; j < cantidad; j++)
    {
        if (tareasPendientes[j] != NULL)
        {
            printf("Tarea Nro: %d\n", tareasPendientes[j]->TareaID);
            printf("Duracion: %d\n", tareasPendientes[j]->Duracion);
            printf("La descripcion de la tarea %d es: %s\n", tareasPendientes[j]->TareaID ,tareasPendientes[j]->Descripcion);
            puts("----------------------------");

        }
    } 
}

Tarea* buscarTarea(Tarea **tareasPendientes, Tarea **tareasRealizadas, int cantidad, int idBuscado){
    for (int i = 0; i < cantidad; i++)
    {
        if (tareasRealizadas[i]!= NULL && tareasRealizadas[i]->TareaID == idBuscado)
        {
            return tareasRealizadas[i];
            break;
        }

        if (tareasPendientes[i]!= NULL && tareasPendientes[i]->TareaID == idBuscado)
        {
            return tareasPendientes[i];
            break;
        }
    }
    return NULL;
    
}