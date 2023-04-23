#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef Tarea;

void inicializarTareas(Tarea **tareasPendientes, Tarea **tareasRealizadas, int cantidadTareas);
void cargarTareas(Tarea **tareasPendientes, int cantidad);
void mostrarTareas(Tarea **tareasPendientes, Tarea **tareasRealizadas,int cantidad);
void listarTareas(Tarea **tareasPendientes,Tarea **tareasRealizadas,int cantidad);
Tarea* BuscarTareaPorPalabra (Tarea **tareasPendientes,Tarea **tareasRealizadas, char *palabraBuscada,int cantidad);
Tarea* BuscarTareaPorId(Tarea **tareasPendientes, Tarea **tareasRealizadas, int cantidad, int idBuscado);
void BuscarTarea(Tarea ** tareasPendientes, Tarea ** tareasRealizadas, int cantidadTareas);
void liberarMemoria(Tarea ** tareasPendientes, Tarea **tareasRealizadas, int cantidadTareas);


int main(){
    int cantidadTareas,id;
    
    puts("Ingrese cantidad de tareas a realizar: ");
    scanf("%d", &cantidadTareas);

    //Reserva de Memoria para lista de Tareas Pendientes y Realizadas
    Tarea** tareasPendientes = (Tarea**) malloc(sizeof(Tarea*)*cantidadTareas);
    Tarea** tareasRealizadas = (Tarea**) malloc(sizeof(Tarea*)*cantidadTareas);
    Tarea* tareaAux;

    inicializarTareas(tareasPendientes,tareasRealizadas,cantidadTareas);
    cargarTareas(tareasPendientes, cantidadTareas);
    listarTareas(tareasPendientes,tareasRealizadas,cantidadTareas);
    mostrarTareas(tareasPendientes, tareasRealizadas, cantidadTareas);
    BuscarTarea(tareasPendientes,tareasRealizadas,cantidadTareas);
    liberarMemoria(tareasPendientes,tareasRealizadas,cantidadTareas);

    return 0;
}

void inicializarTareas(Tarea **tareasPendientes, Tarea **tareasRealizadas, int cantidadTareas){
    for (int i = 0; i < cantidadTareas; i++)
    {
        tareasPendientes[i] = NULL;
        tareasRealizadas[i] = NULL;
    }
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
    
    int respuesta;
    for (int i = 0; i < cantidad; i++)
    {
        printf("Se realizo la siguiente tarea? - %s (1.SI/0.NO): ", tareasPendientes[i]->Descripcion);
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

Tarea* BuscarTareaPorPalabra (Tarea **tareasPendientes,Tarea **tareasRealizadas, char * palabraBuscada,int cantidad){

    for (int i = 0; i < cantidad; i++)
    {
        if (tareasPendientes[i] != NULL)
        {
            char * resultadoDePendientes = strstr(tareasPendientes[i]->Descripcion, palabraBuscada);
            if (resultadoDePendientes != NULL)
            {
                return tareasPendientes[i];
            }
        }

        if (tareasRealizadas[i] != NULL)
        {
            char * resultadoDeRealizadas = strstr(tareasRealizadas[i]->Descripcion, palabraBuscada);        
            if (resultadoDeRealizadas != NULL)
            {
                return tareasRealizadas[i];
            }
        }
            
    }
    return NULL;
}

Tarea* BuscarTareaPorId(Tarea **tareasPendientes, Tarea **tareasRealizadas, int cantidad, int idBuscado){
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

void BuscarTarea(Tarea ** tareasPendientes, Tarea ** tareasRealizadas, int cantidadTareas){
    int tarea, id;
    Tarea *tareaAux;
    char *palabraBuscada=(char *)malloc(sizeof(char)*50);
    int bandera = 1;

    while (bandera == 1)
    {
        puts("****************BUSQUEDA DE TAREA *******************");
        puts("Ingrese el metodo de busqueda");
        printf("1.Por ID\n2.Por palabra\n3.Salir\n");
        scanf("%d", &tarea);

        switch (tarea)
        {
        case 1:
            puts("Ingrese el ID ");
            scanf("%d", &id);
            tareaAux=BuscarTareaPorId(tareasPendientes,tareasRealizadas,cantidadTareas,id);
            printf("Tarea encontrada: %s\n", tareaAux->Descripcion);
            break;

        case 2:
            printf("Ingrese la palabra buscada: ");
            scanf("%s", palabraBuscada);
            tareaAux = BuscarTareaPorPalabra(tareasPendientes, tareasRealizadas, palabraBuscada, cantidadTareas);
            free(palabraBuscada);
            printf("La tarea encontrada es: %s\n", tareaAux->Descripcion);
            printf("Nro de tarea: %d\n", tareaAux->TareaID);
            break;
        case 3:
            bandera = 0;
            break;
        default:
            puts("Valor ingresado incorrecto");
            break;
        }
    }
    
}

void liberarMemoria(Tarea ** tareasPendientes, Tarea **tareasRealizadas, int cantidadTareas){
    for (int i = 0; i < cantidadTareas; i++)
    {
        free (tareasPendientes);
        free (tareasPendientes[i]);
        free (tareasPendientes[i]->Descripcion);
    }
    
}