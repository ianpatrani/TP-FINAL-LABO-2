#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h> ///me deja utilizar la funcion sleep

typedef struct
{
    int idSong;
    char title[30];
    char artist[20];
    int duration;
    char album[20];
    int year;
    char gender[20];
    char comment[100];
    int deleted; // indica 1 o 0 si la canci�n fue eliminada
} stSong;



typedef struct
{
    int idUser;
    char name[30];  // name and lastName
    int pass[2][5]; // la pswd es una matriz que se encripta y desencripta con un key generado para c/ user.
    int birthYear;
    char gender; //
    char country[20];
    int songPlays[30]; // cantidad de canciones reproducidas
    int off;           // indica 1 o 0 si el cliente fue deleted ->1  / 0 no
} stUser;

typedef struct
{
    stSong value;
    struct nodeListSong *next;
} nodeListSong;

typedef struct
{
    int idSong;
    char title[30];
    char artist[20];
    int duration;
    char album[20];
    int year;
    char genres[20];
    char comment[100];
    int deleted; // indica 1 o 0 si la canci�n fue eliminada
} stSong;

typedef struct
{
    stUser user;
    node2User *next;
    node2User *prev;
} node2User; /// LISTA ENLAZADA DE USUARIOS

typedef struct
{
    int idPlaylist;
    int idUser;
    int idSong;
} stPlaylist;

/// FUNCIONES PARA LISTA SIMPLE DE CANCIONES
nodeListSong *inicList();
nodeListSong *createNodoList(stCancion song);
nodeListSong *addToBegin(nodeListSong *list, nodeListSong *new);
nodeListSong *searchLastNodo(nodeListSong *list);
nodeListSong *addToEnd(nodeListSong *list, nodeListSong *new);
nodeListSong *addInOrderBySongName(nodeListSong *list, nodeListSong *nuevoNodo);
void showNode(nodeListSong *song);
void showList(nodeListSong *iterator);
void showBackwardsRevursive(nodeListSong *iterator);
nodeListSong *deleteNodeByIdSong(nodeListSong *list, int ID);

int main()
{
    printf("Hello world!\n");
    return 0;
}

nodeListSong *inicList()
{
    return NULL;
}

nodeListSong *createNodoList(stCancion song)
{
    nodeListSong *nodito = (nodeListSong *)malloc(sizeof(nodeListSong));
    nodito->value = song;
    nodito->next = inicList();
    return nodito;
}

nodeListSong *addToBegin(nodeListSong *list, nodeListSong *new)
{
    if (list == NULL)
    {
        list = new;
    }
    else
    {
        new->next = list;
        list = new;
    }
    return list;
}

nodeListSong *searchLastNodo(nodeListSong *list)
{
    nodeListSong *aux = list;
    while (aux->next != NULL)
    {
        aux = aux->next;
    }
    return aux;
}

nodeListSong *addToEnd(nodeListSong *list, nodeListSong *new)
{
    nodeListSong *ultimo;
    if (list == NULL)
    {
        list = new;
    }
    else
    {
        ultimo = searchLastNodo(list);
        ultimo->next = new;
    }
    return list;
}

nodeListSong *addInOrderBySongName(nodeListSong *list, nodeListSong *nuevoNodo)
{
    if (list == NULL)
    {
        list = nuevoNodo;
    }
    else
    {
        if (strcmpi(nuevoNodo->value.title, list->value.title) < 0)
        {
            list = addToBegin(list, nuevoNodo);
        }
        else
        {
            nodeListSong *ante = list;
            nodeListSong *aux = list;
            while (aux != NULL && strcmpi(nuevoNodo->value.title, list->value.title) > 0)
            {
                ante = aux;
                aux = aux->next;
            }
            ante->next = nuevoNodo;
            nuevoNodo->next = aux;
        }
    }
}

void showNode(nodeListSong *song)
{
    printf("idSong:.. %d \n", song->value.idSong);
    printf("title:..... %s \n", song->value.title);
    printf("artist:.... %s \n", song->value.artist);
    printf("duration:... %d \n", song->value.duration);
    printf("album:...... %s \n", song->value.album);
    printf("year:....... %d \n", song->value.year);
    printf("genres:..... %s \n", song->value.genres);
    printf("comment:. %s \n", song->value.comment);
    printf("deleted:.. %c \n", song->value.deleted);
}

void showList(nodeListSong *iterator)
{
    if (iterator != NULL)
    {
        showNode(iterator);
        showList(iterator->next);
    }
}

void showBackwardsRevursive(nodeListSong *iterator)
{
    if (iterator != NULL)
    {
        showList(iterator->next);
        showNode(iterator);
    }
}

nodeListSong *deleteNodeByIdSong(nodeListSong *list, int ID)
{
    nodeListSong *aux = inicList();
    if (list != NULL)
    {
        if (list->value.idSong == ID)
        {
            nodeListSong *deletedNode = list;
            list = list->next;
            free(deletedNode);
        }
        else
        {
            list->next = deleteNodeByIdSong(list->next, ID);
        }
    }
}
