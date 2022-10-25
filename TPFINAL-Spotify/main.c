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

typedef struct
{
    stSong value;
    struct nodeTreeSong *left;
    struct nodeTreeSong *right;
} nodeTreeSong;

nodeTreeSong *startTree();
nodeTreeSong *createNodeTree(stSong song);
nodeTreeSong *insertNodeTree(nodeTreeSong *tree, stSong song);
void showNode(nodeTreeSong *song);
void inorder(nodeTreeSong *tree);
void preorder(nodeTreeSong *tree);
void postorder(nodeTreeSong *tree);
nodeTreeSong *searchNodeByNodeID(nodeTreeSong *tree, int idSong);
nodeTreeSong *deleteNode(nodeTreeSong *tree, int idSong);
void toFile(char nombrearchivo[], stSong song[]);
int countRegist(char nombrearchivo[]);
nodeTreeSong *insertFromArray(stSong arre[], nodeTreeSong *tree, int valid, int mid);
nodeTreeSong *fileToTree(char nombrearchivo[], nodeTreeSong *tree);

int main()
{
    printf("Hello world!\n");
    return 0;
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
        tree = crearNodoArbol(song);
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

void showNode(nodeTreeSong *song)
{
    printf("idSong:..... %d \n", song->value.idSong);
    printf("title:...... %s \n", song->value.title);
    printf("artist:..... %s \n", song->value.artist);
    printf("duration:... %d \n", song->value.duration);
    printf("album:...... %s \n", song->value.album);
    printf("year:....... %d \n", song->value.year);
    printf("genres:..... %s \n", song->value.genres);
    printf("comment:.... %s \n", song->value.comment);
    printf("deleted:.... %c \n", song->value.deleted);
}

void inorder(nodeTreeSong *tree)
{
    if (tree != NULL)
    {
        inorder(tree->left);
        showNode(tree);
        inorder(tree->right);
    }
}

void preorder(nodeTreeSong *tree)
{
    if (tree != NULL)
    {
        showNode(tree);
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
        showNode(tree);
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

void toFile(char nombrearchivo[], stSong song[])
{
    FILE *archi;
    archi = fopen(nombrearchivo, "rb");
    stSong s;
    int i = 0;
    if (archi != NULL)
    {
        while (!feof(archi))
        {
            fread(&s, sizeof(stSong), 1, archi);
            if (!feof(archi))
            {
                song[i] = s;
                i++;
            }
        }
    }
}

int countRegist(char nombrearchivo[])
{
    FILE *archi;
    archi = fopen(nombrearchivo, "rb");
    stSong song;
    int i = 0;
    if (archi != NULL)
    {
        while (!feof(archi))
        {
            fread(&song, sizeof(stSong), 1, archi);
            if (!feof(archi))
            {
                i++;
            }
        }
    }
    return i;
}

nodeTreeSong *insertFromArray(stSong arre[], nodeTreeSong *tree, int valid, int mid)
{
    int i = 0;
    srand(time(NULL));
    while (i < valid)
    {
        if (tree == NULL)
        {
            tree = insertNodeTree(tree, arre[mid]);
        }
        else
        {
            tree = insertNodeTree(tree, arre[rand() % valid]);
        }
        i++;
    }
    return tree;
}

nodeTreeSong *fileToTree(char nombrearchivo[], nodeTreeSong *tree)
{
    int var = countRegist(nombrearchivo);
    stSong array[var];
    toFile(nombrearchivo, array);
    int mid = mitad(var);
    tree = insertFromArray(array, tree, var, mid);
}
