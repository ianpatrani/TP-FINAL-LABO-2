#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h> ///me deja utilizar la funcion sleep


typedef struct
{
    int idCancion;
    char titulo[30];
    char artista[20];
    int duracion;
    char album[20];
    int anio;
    char genero[20];
    char comentario[100];
    int eliminado; // indica 1 o 0 si la canción fue eliminada
} stCancion;

typedef struct
{
    int idUsuario;
    char nombreUsuario[30];
    char pass[20];
    int anioNacimiento;
    char genero;
    char pais[20];
    int eliminado; // indica 1 o 0 si el cliente fue eliminado
} stUsuario;

typedef struct
{
    stCancion c;
    struct nodoListaCancion * sig;
} nodoListaCancion;

typedef struct
{
    stUsuario usr;
    nodoListaCancion * listaCanciones;
} stCelda;

typedef struct
{
    int idPlaylist;
    int idUsuario;
    int idCancion;
} stPlaylist;


///FUNCIONES PARA LISTA SIMPLE DE CANCIONES
nodoListaCancion *inicLista();
nodoListaCancion *crearNodoLista(stCancion cancion);
nodoListaCancion *agregarAlPrincipio(nodoListaCancion *lista, nodoListaCancion *nuevo);
nodoListaCancion *buscarUltimoNodo(nodoListaCancion *lista);
nodoListaCancion *agregarAlFinal(nodoListaCancion *lista, nodoListaCancion *nuevo);
nodoListaCancion *agregarEnOrdenPorNombreDeCancion(nodoListaCancion *lista, nodoListaCancion *nuevoNodo);
void mostrarNodo(nodoListaCancion *cancion);
void mostrarLista(nodoListaCancion *iterador);
void mostrarRecursivoHaciaAtras(nodoListaCancion *iterador);
nodoListaCancion *borrarNodoPorIdCancion(nodoListaCancion *lista, int ID);

int main()
{
    printf("Hello world!\n");
    return 0;
}

nodoListaCancion *inicLista()
{
    return NULL;
}

nodoListaCancion *crearNodoLista(stCancion cancion)
{
    nodoListaCancion *nodito = (nodoListaCancion*)malloc(sizeof(nodoListaCancion));
    nodito->c = cancion;
    nodito->sig = inicLista();
    return nodito;
}

nodoListaCancion *agregarAlPrincipio(nodoListaCancion *lista, nodoListaCancion *nuevo)
{
    if (lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        nuevo->sig = lista;
        lista = nuevo;
    }
    return lista;
}

nodoListaCancion *buscarUltimoNodo(nodoListaCancion *lista)
{
    nodoListaCancion *seg = lista;
    while (seg->sig != NULL)
    {
        seg = seg->sig;
    }
    return seg;
}

nodoListaCancion *agregarAlFinal(nodoListaCancion *lista, nodoListaCancion *nuevo)
{
    nodoListaCancion *ultimo;
    if (lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        ultimo = buscarUltimoNodo(lista);
        ultimo->sig = nuevo;
    }
    return lista;
}

nodoListaCancion *agregarEnOrdenPorNombreDeCancion(nodoListaCancion *lista, nodoListaCancion *nuevoNodo)
{
    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        if (strcmpi(nuevoNodo->c.titulo, lista->c.titulo) < 0)
        {
            lista = agregarAlPrincipio(lista, nuevoNodo);
        }
        else
        {
            nodoListaCancion *ante = lista;
            nodoListaCancion *aux = lista;
            while (aux != NULL && strcmpi(nuevoNodo->c.titulo, lista->c.titulo) > 0)
            {
                ante = aux;
                aux = aux->sig;
            }
            ante->sig = nuevoNodo;
            nuevoNodo->sig = aux;
        }
    }
}

void mostrarNodo(nodoListaCancion *cancion)
{
    printf("idCancion:.. %d \n", cancion->c.idCancion);
    printf("titulo:..... %s \n", cancion->c.titulo);
    printf("artista:.... %s \n", cancion->c.artista);
    printf("duracion:... %d \n", cancion->c.duracion);
    printf("album:...... %s \n", cancion->c.album);
    printf("anio:....... %d \n", cancion->c.anio);
    printf("genero:..... %s \n", cancion->c.genero);
    printf("comentario:. %s \n", cancion->c.comentario);
    printf("eliminado:.. %c \n", cancion->c.eliminado);
}

void mostrarLista(nodoListaCancion *iterador)
{
    if (iterador != NULL)
    {
        mostrarNodo(iterador);
        mostrarLista(iterador->sig);
    }
}

void mostrarRecursivoHaciaAtras(nodoListaCancion *iterador)
{
    if (iterador != NULL)
    {
        mostrarLista(iterador->sig);
        mostrarNodo(iterador);
    }
}

nodoListaCancion *borrarNodoPorIdCancion(nodoListaCancion *lista, int ID)
{
    nodoListaCancion *aux = inicLista();
    if(lista != NULL)
    {
        if(lista->c.idCancion == ID)
        {
            nodoListaCancion* aBorrar = lista;
            lista = lista-> sig;
            free(aBorrar);
        }
        else
        {
            lista->sig = borrarNodoPorIdCancion(lista->sig, ID);
        }
    }
}
