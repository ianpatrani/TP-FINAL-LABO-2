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
    int deleted; // indica 1 o 0 si la cancion fue eliminada
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
    stUser user;
    struct node2User *next;
    struct node2User *prev;
} node2User;

typedef struct
{
    int idPlaylist;
    int idUser;
    int idSong;
} stPlaylist;

typedef struct
{
    stSong value;
    struct nodeTreeSong *left;
    struct nodeTreeSong *right;
} nodeTreeSong;

/// FUNCIONES PARA LISTA SIMPLE DE CANCIONES
nodeListSong *inicList();
nodeListSong *createNodeList(stSong song);
nodeListSong *addToBegin(nodeListSong *list, nodeListSong *new);
nodeListSong *searchLastNode(nodeListSong *list);
nodeListSong *addToEnd(nodeListSong *list, nodeListSong *new);
nodeListSong *addInOrderBySongName(nodeListSong *list, nodeListSong *newNode);
void showNodenodeListSong(nodeListSong *song);
void showList(nodeListSong *iterator);
void showBackwardsRevursive(nodeListSong *iterator);
nodeListSong *deleteNodeByIdSong(nodeListSong *list, int ID);

/// FUNCIONES stSong
int idClienteNuevo(char archivo[]);
void altaDeCancion(char archivo[]);
void bajaDeCancion(char archivo[]);
void modificarCancion(char archivo[]);
int consultarSiExisteCancion(char archivo[], char tituloCancion[]);
void listarTodasLasCanciones(char archivo[]);

/// FUNCIONES PARA NODOARBOLCANCION
nodeTreeSong *startTree();
nodeTreeSong *createNodeTree(stSong song);
nodeTreeSong *insertNodeTree(nodeTreeSong *tree, stSong song);
void showNodenodeTreeSong(nodeTreeSong *song);
void inorder(nodeTreeSong *tree);
void preorder(nodeTreeSong *tree);
void postorder(nodeTreeSong *tree);
nodeTreeSong *searchNodeByNodeID(nodeTreeSong *tree, int idSong);
nodeTreeSong *deleteNode(nodeTreeSong *tree, int idSong);
void toFile(char fileName[], stSong song[]);
int countRegist(char fileName[]);
nodeTreeSong *insertFromArray(stSong array[], nodeTreeSong *tree, int valid, int middleArray);
nodeTreeSong *fileToTree(char fileName[], nodeTreeSong *tree);

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
        fseek(archivito, sizeof(stSong), SEEK_END);
        i = ftell(archivito) / sizeof(stSong);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
    return i++;
}

void altaDeCancion(char archivo[])
{
    stSong cancion;
    FILE *archivito;
    archivito = fopen(archivo, "ab");

    if (archivito != NULL)
    {
        cancion.idSong = idClienteNuevo(archivo);

        do
        {
            printf("Ingrese titulo: ");
            fflush(stdin);
            scanf("%s", &cancion.title);
        }
        while (strlen(cancion.title) > 30);
        do
        {
            printf("Ingrese artista: ");
            fflush(stdin);
            scanf("%s", &cancion.artist);
        }
        while (strlen(cancion.artist) > 30);
        do
        {
            printf("Ingrese duracion: ");
            fflush(stdin);
            scanf("%.2f", &cancion.duration);
        }
        while (cancion.duration <= 0);

        do
        {
            printf("Ingrese album: ");
            fflush(stdin);
            scanf("%s", &cancion.album);
        }
        while (strlen(cancion.album) > 30);

        do
        {
            printf("Ingrese anio: ");
            fflush(stdin);
            scanf("%i", &cancion.year);
        }
        while (cancion.year != 0);

        do
        {
            printf("Ingrese genero: ");
            fflush(stdin);
            scanf("%s", &cancion.gender);
        }
        while (strlen(cancion.gender) > 30);

        do
        {
            printf("Ingrese comentario: ");
            fflush(stdin);
            scanf("%s", &cancion.comment);
        }
        while (strlen(cancion.comment) <= 100);

        cancion.deleted = 1;

        fwrite(&cancion, sizeof(stSong), 1, archivito);
        fclose(archivito);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
}

void bajaDeCancion(char archivo[])
{
    stSong cancion;
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
        while (aux == 0 && (fread(&cancion, sizeof(stSong), 1, archivito) > 0))
        {

            if (cancion.idSong == idBaja)
            {
                cancion.deleted = 0;
                fseek(archivito, (-1) * sizeof(stSong), SEEK_CUR);
                fwrite(&cancion, sizeof(stSong), 1, archivito);
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
    stSong cancion;
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
}

nodeListSong *inicList()
{
    return NULL;
}

nodeListSong *createNodeList(stSong song)
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

nodeListSong *searchLastNode(nodeListSong *list)
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
        ultimo = searchLastNode(list);
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

void showNodenodeListSong(nodeListSong *song)
{
    printf("idSong:..... %d \n", song->value.idSong);
    printf("title:...... %s \n", song->value.title);
    printf("artist:..... %s \n", song->value.artist);
    printf("duration:... %d \n", song->value.duration);
    printf("album:...... %s \n", song->value.album);
    printf("year:....... %d \n", song->value.year);
    printf("gender:..... %s \n", song->value.gender);
    printf("comment:.... %s \n", song->value.comment);
    printf("deleted:.... %c \n", song->value.deleted);
}

void showList(nodeListSong *iterator)
{
    if (iterator != NULL)
    {
        showNodenodeListSong(iterator);
        showList(iterator->next);
    }
}

void showBackwardsRevursive(nodeListSong *iterator)
{
    if (iterator != NULL)
    {
        showList(iterator->next);
        showNodenodeListSong(iterator);
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

nodeTreeSong *startTree()
{
    return NULL;
}

nodeTreeSong *createNodeTree(stSong song)
{
    nodeTreeSong *aux = (nodeTreeSong *)malloc(sizeof(nodeTreeSong));
    aux->value = song;
    aux->left = NULL;
    aux->right = NULL;
    return aux;
}

nodeTreeSong *insertNodeTree(nodeTreeSong *tree, stSong song)
{
    if (tree == NULL)
    {
        tree = createNodeTree(song);
    }
    else
    {
        if (song.idSong > tree->value.idSong)
        {
            tree->right = insertNodeTree(tree->right, song);
        }
        else
        {
            tree->left = insertNodeTree(tree->left, song);
        }
    }
    return tree;
}

void showNodenodeTreeSong(nodeTreeSong *song)
{
    printf("idSong:..... %d \n", song->value.idSong);
    printf("title:...... %s \n", song->value.title);
    printf("artist:..... %s \n", song->value.artist);
    printf("duration:... %d \n", song->value.duration);
    printf("album:...... %s \n", song->value.album);
    printf("year:....... %d \n", song->value.year);
    printf("gender:..... %s \n", song->value.gender);
    printf("comment:.... %s \n", song->value.comment);
    printf("deleted:.... %c \n", song->value.deleted);
}

void inorder(nodeTreeSong *tree)
{
    if (tree != NULL)
    {
        inorder(tree->left);
        showNodenodeTreeSong(tree);
        inorder(tree->right);
    }
}

void preorder(nodeTreeSong *tree)
{
    if (tree != NULL)
    {
        showNodenodeTreeSong(tree);
        preorder(tree->left);
        preorder(tree->right);
    }
}

void postorder(nodeTreeSong *tree)
{
    if (tree != NULL)
    {
        postorder(tree->left);
        postorder(tree->right);
        showNodenodeTreeSong(tree);
    }
}

nodeTreeSong *searchNodeByNodeID(nodeTreeSong *tree, int idSong)
{
    nodeTreeSong *res = NULL;
    if (tree != NULL)
    {
        if (idSong == tree->value.idSong)
            res = tree;
        else if (idSong > tree->value.idSong)
            res = searchNodeByNodeID(tree->right, idSong);
        else
            res = searchNodeByNodeID(tree->left, idSong);
    }
    return res;
}

nodeTreeSong *deleteNode(nodeTreeSong *tree, int idSong)
{
    if (tree != NULL)
    {
        nodeTreeSong *resId = searchNodeByNodeID(tree, idSong);

        if (idSong == resId)
        {
            free(tree);
            tree = NULL;
        }
    }
    return tree;
}

void toFile(char fileName[], stSong song[])
{
    FILE *file;
    file = fopen(fileName, "rb");
    stSong s;
    int i = 0;
    if (file != NULL)
    {
        while (!feof(file))
        {
            fread(&s, sizeof(stSong), 1, file);
            if (!feof(file))
            {
                song[i] = s;
                i++;
            }
        }
    }
}

int countRegist(char fileName[])
{
    FILE *file;
    file = fopen(fileName, "rb");
    stSong song;
    int i = 0;
    if (file != NULL)
    {
        while (!feof(file))
        {
            fread(&song, sizeof(stSong), 1, file);
            if (!feof(file))
            {
                i++;
            }
        }
    }
    return i;
}

nodeTreeSong *insertFromArray(stSong array[], nodeTreeSong *tree, int valid, int middleArray)
{
    int i = 0;
    srand(time(NULL));
    while (i < valid)
    {
        if (tree == NULL)
        {
            tree = insertNodeTree(tree, array[middleArray]);
        }
        else
        {
            tree = insertNodeTree(tree, array[rand() % valid]);
        }
        i++;
    }
    return tree;
}

int middleArray(int valid)
{
    int var;
    if (valid % 2 == 0)
    {
        var = valid / 2;
    }
    else
    {
        valid++;
        var = valid / 2;
    }
    return var;
}

nodeTreeSong *fileToTree(char fileName[], nodeTreeSong *tree)
{
    int var = countRegist(fileName);
    stSong array[var];
    toFile(fileName, array);
    int mide = middleArray(var);
    tree = insertFromArray(array, tree, var, mide);
}
