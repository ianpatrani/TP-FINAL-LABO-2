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
    stUser user;
    struct node2User *next;
    struct node2User *prev;
} node2User;

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
    int idPlaylist;
    int idUser;
    int idSong;
} stPlaylist;

typedef struct
{
    stSong value;
    struct nodeSongTree *left;
    struct nodeSongTree *right;
} nodeSongTree;

nodeSongTree *startTree();
nodeSongTree *createNodeTree(stSong song);
nodeSongTree *insertNodeTree(nodeSongTree *tree, stSong song);
void showNode(nodeSongTree *song);
void inorder(nodeSongTree *tree);
void preorder(nodeSongTree *tree);
void postorder(nodeSongTree *tree);
nodeSongTree *searchNodeByNodeID(nodeSongTree *tree, int idSong);
nodeSongTree *deleteNode(nodeSongTree *tree, int idSong);
void toFile(char fileName[], stSong song[]);
int countRegist(char fileName[]);
nodeSongTree *insertFromArray(stSong array[], nodeSongTree *tree, int valids, int midSongArray);
nodeSongTree *fileToTree(char fileName[], nodeSongTree *tree);

int main()
{
    printf("Hello world!\n");
    return 0;
}

nodeSongTree *startTree()
{
    return NULL;
}

nodeSongTree *createNodeTree(stSong song)
{
    nodeSongTree *aux = (nodeSongTree *)malloc(sizeof(nodeSongTree));
    aux->value = song;
    aux->left = NULL;
    aux->right = NULL; 
    return aux;
}

nodeSongTree *insertNodeTree(nodeSongTree * tree, stSong song)
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

void showNode(nodeSongTree *song)
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

void inorder(nodeSongTree * tree)
{
    if (tree != NULL)
    {
        inorder(tree->left);
        showNode(tree);
        inorder(tree->right);
    }
}

void preorder(nodeSongTree *tree)
{
    if (tree != NULL)
    {
        showNode(tree);
        preorder(tree->left);
        preorder(tree->right);
    }
}

void postorder(nodeSongTree *tree)
{
    if (tree != NULL)
    {
        postorder(tree->left);
        postorder(tree->right);
        showNode(tree);
    }
}

nodeSongTree *searchNodeById(nodeSongTree *tree, int idSong)
{
    nodeSongTree *res = NULL;
    if (tree != NULL)
    {
        if (idSong == tree->value.idSong)
            res = tree;
        else if (idSong > tree->value.idSong)
            res = searchNodeById(tree->right, idSong);
        else
            res = searchNodeById(tree->left, idSong);
    }
    return res;
}

nodeSongTree *deleteNode(nodeSongTree *tree, int idSong) //MAL POR QUE NO REACOMODA EL ARBOL. 
{
    if (tree != NULL)
    {
        nodeSongTree * resId = searchNodeByNodeID(tree, idSong);

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
    FILE * file;
    file = fopen(fileName, "rb");
    stSong auxSong;
    int i = 0;
    if (file != NULL)
    {
        while (!feof(file))
        {
            fread(&auxSong, sizeof(stSong), 1, file);
            if (!feof(file))
            {
                song[i] = auxSong;
                i++;
            }
        }
    }
}



int countUserRegist(char fileName[])
{
    FILE * file;
    file = fopen(fileName, "rb");
    stSong auxSong;
    int i = 0;
    if (file != NULL)
    {
        while (!feof(file))
        {
            fread(&auxSong, sizeof(stSong), 1, file);
            if (!feof(file))
            {
                i++;
            }
        }
    }
    return i;
}

nodeSongTree * insertFromArray(stSong songArray[], nodeSongTree *tree, int valids, int midSongArray)
{
    int i = 0;
    srand(time(NULL));
    while (i < valids)
    {
        if (tree == NULL)
        {
            tree = insertNodeTree(tree, array[midSongArray]);
        }
        else
        {
            tree = insertNodeTree(tree, array[rand() % valids]);
        }
        i++;
    }
    return tree;
}

int midSongArraySongArray(int validss)
{
    int midSongArray;
    if (valids % 2 == 0)
    {
        midSongArray = valids / 2;
    }
    else
    {
        valids++;
        midSongArray = valids / 2;
    }
    return midSongArray;
}

nodeSongTree * fileToTree(char fileName[], nodeSongTree * songTree)
{
    int var = countRegist(fileName);
    stSong array[var];
    toFile(fileName, array);
    int midSongArray = midSongArray(var);
    tree = insertFromArray(array, songTree, var, midSongArray);
    return songTree; 
}
