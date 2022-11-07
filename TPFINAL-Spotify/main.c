#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h> ///SLEEP()

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
nodeListSong *leerArchivoYPasarALista(char archivo[], nodeListSong *lista);

/// FUNCIONES stSong
int idNewSong(char archivo[]);
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

    altaDeCancion("canciones.bin");
    listarTodasLasCanciones("canciones.bin");

    nodeListSong *listaCanciones = inicList();

    listaCanciones = leerArchivoYPasarALista("canciones.bin", listaCanciones);

    showList(listaCanciones);


    return 0;
}

int idNewSong(char archivo[])
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
    stSong song;
    FILE *archivito;
    archivito = fopen(archivo, "ab");

    if (archivito != NULL)
    {
        song.idSong = idNewSong(archivo);

        printf("Ingrese titulo: ");
        fflush(stdin);
        gets(song.title);

        printf("Ingrese artista: ");
        fflush(stdin);
        gets(song.artist);

        printf("Ingrese duracion: ");
        fflush(stdin);
        scanf("%d", &song.duration);

        printf("Ingrese album: ");
        fflush(stdin);
        gets(song.album);

        printf("Ingrese anio: ");
        fflush(stdin);
        scanf("%i", &song.year);

        printf("Ingrese genero: ");
        fflush(stdin);
        gets(song.gender);

        printf("Ingrese comentario: ");
        fflush(stdin);
        gets(song.comment);

        song.deleted= 1;

        fwrite(&song, sizeof(stSong), 1, archivito);
        fclose(archivito);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
}

void bajaDeCancion(char archivo[])
{
    FILE *archivito = fopen(archivo, "a+b");
    stSong song;
    int aux = 0;
    int idBaja;

    listarTodasLasCanciones("canciones.bin");

    printf("Ingrese el id de la cancion que quiere dar de baja\n");
    scanf("%d", &idBaja);

    if (archivito != NULL)
    {
        while (aux == 0 && (fread(&song, sizeof(stSong), 1, archivito) > 0))
        {
            if (song.idSong == idBaja)
            {
                song.deleted = 0;
                fseek(archivito, (-1) * sizeof(stSong), SEEK_CUR);
                fwrite(&song, sizeof(stSong), 1, archivito);
                aux = 1;
            }
        }
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

    listarTodasLasCanciones("canciones.bin");

    printf("Ingrese id de la cancion:\n");
    scanf("%d", &id);

    if (archivito != NULL)
    {
        while (fread(&cancion, sizeof(stSong), 1, archivito) > 0)
        {

            if (cancion.idSong == id)
            {
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
                switch (eleccion)
                {
                case 1:
                    printf("\nIngrese nuevo titulo:");
                    fflush(stdin);
                    gets(cancion.title);
                    break;
                case 2:
                    printf("\nIngrese nuevo artista:");
                    fflush(stdin);
                    gets(cancion.artist);
                    break;
                case 3:
                    printf("\nIngrese nueva duracion: ");
                    fflush(stdin);
                    gets(cancion.duration);
                    break;
                case 4:
                    printf("\nIngrese nuevo album: ");
                    fflush(stdin);
                    gets(cancion.album);
                    break;
                case 5:
                    printf("\nIngrese nuevo anio: ");
                    fflush(stdin);
                    scanf("%d", &cancion.year);
                    break;
                case 6:
                    printf("\nIngrese nuevo genero: ");
                    fflush(stdin);
                    gets(cancion.gender);
                    break;
                case 7:
                    printf("\nIngrese nuevo comentario: ");
                    fflush(stdin);
                    gets(cancion.comment);
                    break;
                case 8:
                    printf("\nIngrese eliminado: ");
                    fflush(stdin);
                    scanf("%d", &cancion.deleted);
                    break;
                }

                fseek(archivito, (-1) * sizeof(stSong), SEEK_CUR);
                fwrite(&cancion, sizeof(stSong), 1, archivito);
                fseek(archivito, sizeof(stSong), SEEK_END);
            }
        }
    }
    fclose(archivito);
}

int consultarSiExisteCancion(char archivo[], char tituloCancion[])
{
    FILE *archivito;
    stSong cancion;
    archivito = fopen(archivo, "rb");
    int resultado = 1;

    if (archivito != NULL)
    {
        while (fread(&cancion, sizeof(stSong), 1, archivito) > 0)
        {
            resultado = strcmpi(cancion.title, tituloCancion);

            if (resultado == 0)
            {
                printf("Ya existe cancion\n");
            }
        }
    }
    return resultado;
}

void listarTodasLasCanciones(char archivo[])
{
    FILE *archivito;
    stSong cancion;
    archivito = fopen(archivo, "rb");
    int i = 0;

    if (archivito != NULL)
    {
        while (fread(&cancion, sizeof(stSong), 1, archivito) > 0)
        {
            printf("\n Registro numero %d", i++);
            puts("\n-------------------------------------");
            printf("\n IdCancion:..........%d", cancion.idSong);
            printf("\n Titulo:............ %s", cancion.title);
            printf("\n Artista:........... %s", cancion.artist);
            printf("\n Duracion:.......... %d", cancion.duration);
            printf("\n Album:..............%s", cancion.album);
            printf("\n Anio:.............. %d", cancion.year);
            printf("\n Genero:............ %s", cancion.gender);
            printf("\n Comentario:........ %s", cancion.comment);
            printf("\n Eliminado 1-Si/0-No:%d", cancion.deleted);
            puts("\n-------------------------------------");
        }
    }
    fclose(archivito);
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
    printf("\n IdCancion:..........%d", song->value.idSong);
    printf("\n Titulo:............ %s", song->value.title);
    printf("\n Artista:........... %s", song->value.artist);
    printf("\n Duracion:.......... %d", song->value.duration);
    printf("\n Album:..............%s", song->value.album);
    printf("\n Anio:.............. %d", song->value.year);
    printf("\n Genero:............ %s", song->value.gender);
    printf("\n Comentario:........ %s", song->value.comment);
    printf("\n Eliminado 1-Si/0-No:%d", song->value.deleted);
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

nodeListSong *leerArchivoYPasarALista(char archivo[], nodeListSong *lista)
{
    FILE *archi = fopen(archivo, "rb");
    stSong song;
    nodeListSong *nuevo;

    if (archi != NULL)
    {
        while (fread(&song, sizeof(stSong), 1, archi) > 0)
        {
            nuevo = createNodeList(song);
            lista = addToBegin(lista, nuevo);
        }
    }
    fclose(archi);
    return lista;
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
    printf("\n IdCancion:..........%d", song->value.idSong);
    printf("\n Titulo:............ %s", song->value.title);
    printf("\n Artista:........... %s", song->value.artist);
    printf("\n Duracion:.......... %d", song->value.duration);
    printf("\n Album:..............%s", song->value.album);
    printf("\n Anio:.............. %d", song->value.year);
    printf("\n Genero:............ %s", song->value.gender);
    printf("\n Comentario:........ %s", song->value.comment);
    printf("\n Eliminado 1-Si/0-No:%d", song->value.deleted);
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
