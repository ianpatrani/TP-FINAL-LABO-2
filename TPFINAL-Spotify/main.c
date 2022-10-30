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
/// FUNCIONES STCANCION
int idClienteNuevo(char archivo[]);
void altaDeCancion(char archivo[]);
void bajaDeCancion(char archivo[]);
void modificarCancion(char archivo[]);
int consultarSiExisteCancion(char archivo[], char tituloCancion[]);
void listarTodasLasCanciones(char archivo[]);

int main()
{
    char usuario[20];
    char password[20];

    printf("\t MENU PRINCIPAL \n");
    printf("\t1. Ingreso con User y Pass para administradores\n");
    printf("\t2. Ingreso con User y Pass para usuarios\n");
    printf("\t3. Registrarse\n");

    return 0;
}

int idClienteNuevo(char archivo[])
{
    FILE *archivito;
    archivito = fopen(archivo, "rb");
    int i = 0;
    if (archivito != NULL)
    {
        fseek(archivito, sizeof(stCancion), SEEK_END);
        i = ftell(archivito) / sizeof(stCancion);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
    return i++;
}

void altaDeCancion(char archivo[])
{
    stCancion cancion;
    FILE *archivito;
    archivito = fopen(archivo, "ab");

    if (archivito != NULL)
    {
        cancion.idCancion = idClienteNuevo(archivo);

        do
        {
            printf("Ingrese titulo: ");
            fflush(stdin);
            scanf("%s", &cancion.titulo);
        } while (strlen(cancion.titulo) > 30);
        do
        {
            printf("Ingrese artista: ");
            fflush(stdin);
            scanf("%s", &cancion.artista);
        } while (strlen(cancion.artista) > 30);
        do
        {
            printf("Ingrese duracion: ");
            fflush(stdin);
            scanf("%.2f", &cancion.duracion);
        } while (cancion.duracion <= 0);

        do
        {
            printf("Ingrese album: ");
            fflush(stdin);
            scanf("%s", &cancion.album);
        } while (strlen(cancion.album) > 30);

        do
        {
            printf("Ingrese anio: ");
            fflush(stdin);
            scanf("%i", &cancion.anio);
        } while (cancion.anio != 0);

        do
        {
            printf("Ingrese genero: ");
            fflush(stdin);
            scanf("%s", &cancion.genero);
        } while (strlen(cancion.genero) > 30);

        do
        {
            printf("Ingrese comentario: ");
            fflush(stdin);
            scanf("%s", &cancion.comentario);
        } while (strlen(cancion.comentario) <= 100);

        cancion.eliminado = 1;

        fwrite(&cancion, sizeof(stCancion), 1, archivito);
        fclose(archivito);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
}

void bajaDeCancion(char archivo[])
{
    stCancion cancion;
    FILE *archivito;
    archivito = fopen(archivo, "r+b");
    int aux = 0;
    char ok = 's';
    char idBaja;

    printf("Ingrese el id de la cancion que quiere dar de baja\n");
    fflush(stdin);
    scanf("%d", idBaja);

    if (archivito != NULL && ok == 's')
    {
        while (aux == 0 && (fread(&cancion, sizeof(stCancion), 1, archivito) > 0))
        {

            if (cancion.idCancion == idBaja)
            {
                cancion.eliminado = 0;
                fseek(archivito, (-1) * sizeof(stCancion), SEEK_CUR);
                fwrite(&cancion, sizeof(stCancion), 1, archivito);
                aux = 1;
            }
        }
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
    fclose(archivito);
}

void modificarCancion(char archivo[])
{
    stCancion cancion;
    FILE *archivito;
    archivito = fopen(archivo, "r+b");
    int id;
    int eleccion;

    printf("Ingrese id de la cancion:\n");
    scanf("%d", &id);
    system("cls");

    puts("Opcion 1 - titulo");
    puts("Opcion 2 - artista");
    puts("Opcion 3 - duracion");
    puts("Opcion 4 - album");
    puts("Opcion 5 - anio");
    puts("Opcion 6 - genero");
    puts("Opcion 7 - comentario");
    puts("Opcion 8 - eliminado");

    printf("Ingrese eleccion:\n");
    scanf("%d", &eleccion);
    system("cls");

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
