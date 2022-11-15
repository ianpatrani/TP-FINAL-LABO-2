#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "songLib.h"
#include "userLib.h"
#include "gotoxy.h"


typedef struct
{
    int idPlayList;
    int idUser;
    int idSong;
}stPlaylist;

int totalPlayLists();
stPlaylist createPlaylist (int idUser, int idSong);
void savePlaylist (stPlaylist toSave);


typedef struct
{
    stUser userValue;
    nodeSongList * songList;
    struct stCell * next;
}stCell;


stCell * loadListFromFile(stCell * userList);
stCell * createCellNode();
stCell * addUserToList(stCell * userList, nodeSongList * songList, stUser toAdd);
stCell * searchUserCellById(stCell * userList, int idUser);
stCell * addSongToUser(stCell * userList, int idUser, stSong toAdd);
stCell * clearSongList (stCell * cellList, int idUser);
void showUserPlaylists (stCell * userList);
void houseRecommendations (stCell * userList, int idUser);
void artistRecommendation (nodeSongList * userSongList, int totalPlays);
int totalPlaysByUser (stCell * userNode);
void morePopularRecommendation ();



stCell * inicList();
stCell * createNodePlayList(stUser toCreate);
stCell * addFirstCell(stCell * cellList, stCell * toAdd);
stCell * searchLastCell(stCell * cellList);
stCell * addLastCell(stCell * cellList, stCell * toAdd);
stCell * addCellInOrderByName(stCell * cellList, stCell * toAdd);

stCell * deleteCellById(stCell * cellList, int idSong);
void showCellNode(stCell * toShow);
void showCellList(stCell * toShow);
