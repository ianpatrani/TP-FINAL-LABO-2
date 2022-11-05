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
    int duration;
    char album[20];
    int year;
    char gender[20];
    char comment[100];
    int off; // indica 1 o 0 si la cancion fue eliminada
} stSong;

typedef struct
{
    stSong value;
    struct nodeSongList * next;
}nodeSongList;

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
void updateSong(int idToUpdate);
int songNameValidation();
void showSongFile();

///LISTA DE CANCIONES

nodeSongList * startSongList();
nodeSongList * createSongNode(stSong toCreate);
nodeSongList * addSongFirst(nodeSongList * songList, nodeSongList * toAdd);
nodeSongList * searchLastNode(nodeSongList * songList);
nodeSongList * searchSongById(nodeSongList * songList, int idSong);
nodeSongList * addSongLast(nodeSongList * songList, nodeSongList * toAdd);
nodeSongList * addInOrderByName(nodeSongList * songList, nodeSongList * toAdd);
void showNode(nodeSongList * toShow);
void showSongList(nodeSongList * toShow);
void showBackwardsRevursive(nodeSongList * iterator);
nodeSongList * deleteSongById(nodeSongList * songList, int idSong);
nodeSongList * deleteSongList (nodeSongList * toDelete);


///ARBOL DE CANCIONES

nodeTreeSong * startTree();
nodeTreeSong * createNodeTree(stSong toCreate);
nodeTreeSong * insertNodeTree(nodeTreeSong * treeSong, stSong toInsert);
void showNodeTreeSong(nodeTreeSong * toShow);
void inOrder(nodeTreeSong * toShow);
void preOrder(nodeTreeSong * toShow);
void postOrder(nodeTreeSong * toShow);
nodeTreeSong * searchNodeByNodeID(nodeTreeSong *tree, int idToSearch);
nodeTreeSong * deleteTreeNode(nodeTreeSong *tree, int idToDelete);
void saveSongsInFile(stSong toSave[]);
nodeTreeSong * insertFromArray(stSong arraySong[], nodeTreeSong * treeSong, int valids, int midArray);
nodeTreeSong * fileToTree(nodeTreeSong * treeSong);

