#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>

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

Tarea cargar();
void mostrarLista(Nodo *tareas);
// void EliminarNodo(Nodo * nodo);

int main(){
    int menu;
    Nodo * TareasPendientes, *TareasRealizadas;

    TareasPendientes = CrearListaVacia(); 
    TareasRealizadas = CrearListaVacia();
    
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
        puts("Ingrese una opcion: ");
        fflush(stdin);
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            
            do
            {
                Tarea tarea = cargar();
                InsertarNodo(&TareasPendientes, tarea);
                printf("Desea agregar otra tarea? (1-SI , 2-NO):");
                fflush(stdin);
                scanf("%d", &menu);
            } while (menu == 1);
            
            break;
        default:
            break;
        }
        
    } while (menu == 1);

    mostrarLista(TareasPendientes);
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

Tarea cargar(){
    srand(time(NULL));

    Tarea tarea;
    tarea.TareaID=1;
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
    Nodo *auxPendientes, *auxRealizadas;

    printf("Control de Tareas");
    mostrarLista(TareasPendientes);
}
// void EliminarNodo(Nodo * nodo){
//     if (!nodo)
//     {
//         free(nodo);
//     }
    
// }
