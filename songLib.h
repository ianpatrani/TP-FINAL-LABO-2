#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define SONGSFILEPATH "SongsFile.bin"

typedef struct
{
    int idSong;
    char title[30];
    char artist[20];
    float duration;
    char album[20];
    int year;
    char gender[20];
    char comment[100];
    int timesPlayed; // veces que se reprodujo
    int off;         // indica 1 o 0 si la cancion fue eliminada
} stSong;

typedef struct
{
    stSong songValue;
    int flag;
} flagedSong;

typedef struct
{
    stSong value;
    struct nodeSongList *next;
} nodeSongList;

typedef struct
{
    stSong value;
    struct nodeTreeSong *left;
    struct nodeTreeSong *right;
} nodeTreeSong;

stSong searchSongFileById(int idSong);
int totalSongs();
void loadSongToFile();
void deleteSongFromFile(int idSong);
void upSong(int idSong);
void updateSong(int idToUpdate);
int songNameValidation();
void showSongFile();
int songIdValidation();
int getSongId();
int searchSongFileByName(char nameToSearch[]);
void showSongFileByArtist(char artistToShow[]);
int maxTimesPlayed();
void showSong(stSong toShow);

/// LISTA DE CANCIONES

nodeSongList *startSongList();
nodeSongList *createSongNode(stSong toCreate);
nodeSongList *addSongFirst(nodeSongList *songList, nodeSongList *toAdd);
nodeSongList *searchLastNode(nodeSongList *songList);
nodeSongList *searchSongById(nodeSongList *songList, int idSong);
nodeSongList *addSongLast(nodeSongList *songList, nodeSongList *toAdd);
nodeSongList *addInOrderByName(nodeSongList *songList, nodeSongList *toAdd);
void showNode(nodeSongList *toShow);
void showSongList(nodeSongList *toShow);
void showBackwardsRevursive(nodeSongList *iterator);
nodeSongList *deleteSongById(nodeSongList *songList, int idSong);
nodeSongList *deleteSongList(nodeSongList *toDelete);

/// ARBOL DE CANCIONES

nodeTreeSong *startTree();
nodeTreeSong *createNodeTree(stSong toCreate);
nodeTreeSong *insertNodeTree(nodeTreeSong *treeSong, stSong toInsert);
void showNodeTreeSong(nodeTreeSong *toShow);
void inOrder(nodeTreeSong *toShow);
void preOrder(nodeTreeSong *toShow);
void postOrder(nodeTreeSong *toShow);
nodeTreeSong *searchNodeById(nodeTreeSong *treeSong, int idSong);
nodeTreeSong *deleteTreeNode(nodeTreeSong *tree, int idToDelete);
nodeTreeSong *fileToSongTree(nodeTreeSong *songTree);
void fileToSongArray(stSong arraySong[], int totalValues);
nodeTreeSong *selectRoot(nodeTreeSong *treeSong);
nodeTreeSong *nonRepetitiveInsertion(nodeTreeSong *treeSong, stSong arraySong[], int totalValues);
void findSongByName();
