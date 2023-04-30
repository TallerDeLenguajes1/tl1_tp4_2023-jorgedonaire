#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
Nodo *CrearNodo(Tarea tarea);
void InsertarNodo(Nodo **Start, Tarea tarea);

Tarea cargar(int contador);
void mostrarLista(Nodo *tareas);
void controlarTareas(Nodo **TareasPendientes, Nodo **TareasRealizadas);
Nodo *extraerNodo(Nodo **Start, int id);
void mover(Nodo **TareasPendientes, Nodo **TareasRealizadas, int id);
Nodo *buscarTareaPorID(Nodo **TareasPendientes, Nodo **TareasRealizadas, int id);
Nodo *buscarTareaPorPalabra(Nodo **TareasPendientes, Nodo **TareasRealizadas, char *palabraBuscada);
void liberarMemoria(Nodo *tareas);
void eliminar(Nodo *nodo);
void MostrarDatos(Nodo **Lista);

int main(){
    int menu, idBuscado;
    int contador=0;
    char *palabraBuscada = (char*)malloc(sizeof(char)*100);
    Nodo * TareasPendientes, *TareasRealizadas, *TareasEnProceso;

    TareasPendientes = CrearListaVacia(); 
    TareasRealizadas = CrearListaVacia();
    TareasEnProceso = CrearListaVacia();
    
    do
    {
        puts("*********** MENU ***********");
        printf("\t1 - Cargar tareas\n");
        printf("\t2 - Controlar tareas\n");
        printf("\t3 - Mostrar tareas pendientes y realizadas\n");
        printf("\t4 - Buscar tareas por ID\n");
        printf("\t5 - Buscar tareas por palabra clave\n");
        printf("\t6 - Salir\n");
        puts("\n");
        printf("Ingrese una opcion: ");
        fflush(stdin);
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            do
            {
                contador++;
                Tarea tarea = cargar(contador);
                InsertarNodo(&TareasPendientes, tarea);
                printf("Desea agregar otra tarea? (1-SI , 2-NO):");
                fflush(stdin);
                scanf("%d", &menu);
            } while (menu == 1);
            break;

        case 2:
            controlarTareas(&TareasPendientes,&TareasRealizadas);
            break;
        case 3:
            printf("--------TAREAS PENDIENTES---------\n");
            mostrarLista(TareasPendientes);
            printf("--------TAREAS REALIZADAS---------\n");
            mostrarLista(TareasRealizadas);
            break;

        case 4:
            printf("------------BUSQUEDA POR ID-------------\n");
            printf("Ingrese el ID: ");
            fflush(stdin);
            scanf("%d", &idBuscado);
            Nodo *nodoBuscadoID = buscarTareaPorID(&TareasPendientes, &TareasRealizadas, idBuscado);
            printf("DESCRIPCION: %s\n", nodoBuscadoID->T.Descripcion);
            printf("TAREA Nro: %d\n", nodoBuscadoID->T.TareaID);
            printf("DURACION: %d\n", nodoBuscadoID->T.Duracion);
            break;
        case 5:
            printf("------------BUSQUEDA POR PALABRA-------------\n");
            printf("Ingrese la palabra clave: ");
            fflush(stdin);
            gets(palabraBuscada);
            Nodo *nodoBuscadoPorPalabra = buscarTareaPorPalabra(&TareasPendientes, &TareasRealizadas, palabraBuscada);
            free(palabraBuscada);
            printf("DESCRIPCION: %s \n", nodoBuscadoPorPalabra->T.Descripcion);
            printf("TAREA Nro: %d \n", nodoBuscadoPorPalabra->T.TareaID);
            printf("DURACION: %d \n", nodoBuscadoPorPalabra->T.Duracion);
            break;
        default:
            break;
        }
    printf("\n");
    } while (menu != 6);

    liberarMemoria(TareasPendientes);
    liberarMemoria(TareasRealizadas);
    fflush(stdin);
    getchar();
    return 0;
}

Nodo *CrearListaVacia(){
    return NULL;
}

Nodo *CrearNodo(Tarea tarea){
    srand(time(NULL));
    Nodo *NuevoNodo = (Nodo *) malloc(sizeof(Nodo));
    NuevoNodo->T = tarea;
    NuevoNodo->Siguiente=NULL;
    return NuevoNodo;
}

void InsertarNodo(Nodo **Start, Tarea tarea){ //inserta un nodo al comienza de la lista
    Nodo *NuevoNodo = CrearNodo(tarea);
    NuevoNodo->Siguiente=*Start;
    *Start = NuevoNodo;
}

Tarea cargar(int contador){
    srand(time(NULL));

    Tarea tarea;
    tarea.TareaID=contador;
    printf("++++++++++ TAREA Nro: %d ++++++++++\n", tarea.TareaID);
    puts("Ingrese una descripcion");
    tarea.Descripcion=malloc(sizeof(char)*100);
    fflush(stdin);
    gets(tarea.Descripcion);
    tarea.Duracion = 10 + rand()%101;
    return tarea;
}

void mostrarLista(Nodo *tareas){
    Nodo *aux = tareas;
    while (aux != NULL)
    {
        printf("-----Tarea Nro: %d -------\n", aux->T.TareaID);
        printf("Descripcion: %s\n", aux->T.Descripcion);
        printf("Duracion: %d\n", aux->T.Duracion);

        aux=aux->Siguiente;
    }
    
}

void controlarTareas(Nodo **TareasPendientes, Nodo **TareasRealizadas){
    int id, opcion;
    Nodo *auxPendientes, *auxRealizadas;
    printf("\n");
    printf("Control de Tareas\n");
    puts("-------TAREAS PENDIENTES-------");
    mostrarLista(*TareasPendientes);
    printf("Indique el ID de la tarea a controlar: ");
    fflush(stdin);
    scanf("%d", &id);
    printf("Se realizo esta tarea? (1-SI , 2 -NO)");
    fflush(stdin);
    scanf("%d", &opcion);

    if (opcion == 1)
    {
        mover(TareasPendientes,TareasRealizadas,id);
    }
    
}

Nodo *extraerNodo(Nodo **Start, int id){
    Nodo *aux=*Start;
    Nodo *auxAnterior=*Start;

    while (aux && aux->T.TareaID != id) //Recorre la lista
    {
        auxAnterior = aux;
        aux = aux->Siguiente;
    }

    if (aux) //Si lo encuentra
    {
        if (*Start == aux) //Si es el 1er elemento de la lista
        {
            *Start = aux->Siguiente;
        }else // Si es cualquier otro
        {
            auxAnterior->Siguiente = aux->Siguiente;
        }
        aux->Siguiente=NULL; //porque? si no es el ultimo elemento?
    }
    
    return aux;
}

void mover(Nodo **TareasPendientes, Nodo **TareasRealizadas, int id){
    Nodo *aux = extraerNodo(TareasPendientes, id);
    InsertarNodo(TareasRealizadas,aux->T);
}

Nodo *buscarTareaPorID(Nodo **TareasPendientes, Nodo **TareasRealizadas, int id){
    Nodo *auxTareasPendientes = *TareasPendientes;
    Nodo *auxTareasRealizadas = *TareasRealizadas;

    while (auxTareasPendientes)
    {
        if (id == auxTareasPendientes->T.TareaID)
        {
            return auxTareasPendientes;
        }
    auxTareasPendientes = auxTareasPendientes->Siguiente;
    }

    while (auxTareasRealizadas)
    {
        if (id == auxTareasRealizadas->T.TareaID)
        {
            return auxTareasRealizadas;
        }
        
    }
    
    return NULL;
}

Nodo *buscarTareaPorPalabra(Nodo **TareasPendientes, Nodo **TareasRealizadas, char *palabraBuscada){
    Nodo *auxTareasPendientes = *TareasPendientes;
    Nodo *auxTareasRealizadas = *TareasRealizadas;

    while (auxTareasPendientes)
    {
        if (strstr(auxTareasPendientes->T.Descripcion,palabraBuscada))
        {
            return auxTareasPendientes;
        }
    auxTareasPendientes = auxTareasPendientes->Siguiente;
    }
    
    while (auxTareasRealizadas)
    {
        if (strstr(auxTareasRealizadas->T.Descripcion,palabraBuscada))
        {
            return auxTareasRealizadas;
        }
    auxTareasRealizadas = auxTareasRealizadas->Siguiente;
    }
    return NULL;
}

void liberarMemoria(Nodo *tareas){
    Nodo *aux = tareas;
    Nodo *auxAnterior = tareas;
    Nodo *auxActual = tareas;

    while (aux)
    {
        if (aux->T.Descripcion)
        {
            free(aux->T.Descripcion);
        }
        aux = aux->Siguiente;
    }
    
    while (auxActual)
    {
        auxAnterior = auxActual;
        auxActual = auxActual->Siguiente;
        free(auxAnterior);
    }
    
}

//modificaciones para el tp 5

void eliminar(Nodo *nodo){
    free(nodo->T.Descripcion);
    free(nodo);
}

void MostrarDatos(Nodo **Lista){
    int contador=0, tiempoTotal=0;

    Nodo *auxLista = *Lista;
    while (auxLista)
    {
        contador++;
        tiempoTotal = tiempoTotal+auxLista->T.Duracion;
        auxLista = auxLista->Siguiente;
    }
    printf("La cantidad de tareas en esta lista es: %d\n", contador);
    printf("El tiempo total de las tareas asociadas a esta lista es: %d\n", tiempoTotal);
}