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

nodeTreeSong *startTree();
nodeTreeSong *createNodeTree(stSong song);
nodeTreeSong *insertNodeTree(nodeTreeSong *tree, stSong song);
void showNode(nodeTreeSong *song);
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

void showNode(nodeTreeSong *song)
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
