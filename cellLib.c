#define PLAYLISTFILEPATH "playList.bin"

#include "cellLib.h"


///CELL LIB///
///CELL LIB///
///CELL LIB///
/*stCell * loadListFromFile(stCell * userList) ///levanta el archivo de stPlaylist y trae CADA canción al usuario de CADA registro stPlaylist.
{                                           ///recordar que el struct stPlaylist tiene 1 idSong y 1 idUser para relacionarlas.
                                                ///eso es lo que pide el enunciado.
                                                    ///PERO PERO PERO por qué no cargar la lista de canciones desde los idSong que almacena c/ user?
    FILE * fileUser;
    nodeSongList * auxSongList;
*/

stCell * loadListFromFile(stCell * userList) ///levanta el archivo de stPlaylist y trae CADA canción al usuario de CADA registro stPlaylist.
{
    FILE * filePL;
    filePL = fopen(PLAYLISTFILEPATH, "rb");

    nodeSongList * auxSongList;
    stUser userAux;
    stSong songAux;
    stPlaylist PLAux;

    nodeTreeSong * auxSongTree;
    auxSongTree = startTree();
    auxSongTree = fileToTree(auxSongTree);


    if(filePL)
    {
        while(!feof(filePL))
        {
            fread(&PLAux,1,sizeof(stPlaylist),filePL);
            userAux = searchUserFileById(PLAux.idUser);
            if (userAux.off == 1)
            {
                userList->userValue = userAux;
                songAux = searchNodeByNodeID(auxSongTree, PLAux.idSong);
                auxSongList = createSongNode(songAux);
                userList->songList = addSongLast(userList->songList, auxSongList);
            }

        }
    }
    else
    {
        printf("error en abrir el archivo!\n");
    }
    return userList;
}

stCell * createCellUser()
{
    stCell * userCellAux;
    stUser userAux;
    userAux = createOneUser();
    userCellAux->userValue = userAux;
    userCellAux->songList = startSongList();
    userCellAux->next = NULL;

    return userCellAux;
}

stCell * searchUserCellById(stCell * userList, int idUser)
{
    stCell * userAux = NULL;
    while (userList)
    {
        if(userList->userValue.idUser == idUser)
            userAux = userList;
        userList = userList->next;
    }
    return userAux;
}


void showUserPlaylists (stCell * userList)
{
    printf("\nMostrando el ADL de usuarios \n");
    if (userList)
    {
        showCellList(userList);
    }
    else
        printf("There is nothing to show\n");
}


stCell * clearSongList (stCell * cellList, int idUser)
{
    stCell * userAux;
    userAux = searchUserCellById(cellList, idUser);
    userAux->songList = deleteSongList(userAux->songList);

    return cellList;
}


stCell * startCellList()
{
    return NULL;
}

stCell * createCellNode (stUser toCreate, nodeSongList * songList)
{
    stCell * cellAux = (stCell*)malloc(sizeof(stCell));
    cellAux->userValue = toCreate;
    cellAux->songList = songList;
    cellAux->next = NULL;
    return cellAux;
}

stCell * addFirstCell(stCell * cellList, stCell * toAdd)
{
    if (!cellList)
    {
        cellList = toAdd;
    }
    else
    {
        toAdd->next = cellList;
        cellList = toAdd;
    }
    return cellList;
}

stCell * searchLastCell(stCell * userList)
{
    stCell * cellAux = userList;
    while (cellAux->next != NULL)
    {
        cellAux = cellAux->next;
    }
    return cellAux;
}

stCell * addLastCell(stCell * cellList, stCell * toAdd)
{
    stCell * lastSong;
    if (!cellList)
    {
        cellList = toAdd;
    }
    else
    {
        lastSong = searchLastSong(cellList);
        cellList->next = toAdd;
    }
    return cellList;
}

stCell * addCellInOrderByName(stCell * cellList, stCell * toAdd)
{
    if (!cellList)
    {
        cellList = toAdd;
    }
    else
    {
        if (strcmpi(toAdd->userValue.fullName, cellList->userValue.fullName) < 0)
        {
            cellList = addFirst(cellList, toAdd);
        }
        else
        {
            stCell * prev = cellList;
            stCell * cellAux = cellList;
            while (cellAux && (strcmpi(toAdd->userValue.fullName, cellList->userValue.fullName) > 0))
            {
                prev = cellAux;
                cellAux = cellAux->next;
            }
            prev->next = toAdd;
            toAdd->next = cellAux;
        }
    }
}


stCell * addCellInOrderById(stCell * cellList, stCell * toAdd)
{
    if (!cellList)
    {
        cellList = toAdd;
    }
    else
    {
        if (toAdd->userValue.idUser < cellList->userValue.idUser)
        {
            cellList = addFirst(cellList, toAdd);
        }
        else
        {
            stCell * prev = cellList;
            stCell * cellAux = cellList;
            while (cellAux && toAdd->userValue.idUser > cellAux->userValue.idUser)
            {
                prev = cellAux;
                cellAux = cellAux->next;
            }
            prev->next = toAdd;
            toAdd->next = cellAux;
        }
    }
}

void showCellNode(stCell * toShow)
{
    puts("-------------------------------------------------------------------\n");
    printf("ID USUARIO: %d\n",toShow->userValue.idUser);
    printf("NOMBRE COMPLETO: %s\n", toShow->userValue.fullName);
    stWord pass = showPassword(toShow->userValue);
    printf("PASS: %s\n", pass);
    printf("Anio Nacimiento: %i\n",toShow->userValue.birthYear);
    printf("Genero: ");
    if (toShow->userValue.gender == 'f')
    {
        printf("Femenino\n");
    }
    else
    {
        printf("Masculino\n");
    }
    printf("country de origen: %s\n",toShow->userValue.country);
    printf("Cantidad de canciones escuchadas: %d\n",toShow->userValue.songsPlayed);
    printf("Canciones escuchadas: \n");
    showSongList(toShow->songList); ///muestra la lista de canciones del usuario

    if (toShow->userValue.off == 0)
    {
        printf("Estado: ACTIVO\n");
    }
    else
    {
        printf("Estado: INACTIVO\n");
    }
    puts("-------------------------------------------------------------------\n");
}

void showCellList(stCell * toShow) ///recursiva
{
    if (toShow)
    {
        showCellNode(toShow);
        showSongList(toShow->songList);
        showCellList(toShow->next);
    }
}


stCell * addSongToUser(stCell * userList, int idUser, stSong toAdd)
{
    nodeSongList * auxSong = createSongNode(toAdd);
    stCell * auxUser;
    auxUser = searchUserCellById(userList, idUser);
    if(auxUser)
    {
        auxUser->songList = addLast(auxUser->songList, auxSong);
        savePlaylist(createPlaylist(idUser, toAdd.idSong)); ///En la accion de escuchar una cacncion, se crea un registro playList y se guarda
    }
    else
    {
        printf("El user no existe\n");
    }
    return userList;
}


///PLAYLIST LIB ///
///PLAYLIST LIB ///
///PLAYLIST LIB ///
///PLAYLIST LIB ///


int totalPlaylists()
{
    int total = 0;
    FILE * playListFile;
    stPlaylist playListAux;
    playListFile = fopen(PLAYLISTFILEPATH, "r+b");

    if (playListFile) // EN CASO DE DAR OK EN LA LECTURA DEVUELVE LA CANTIDAD EXACTA DE PLAYLISTS EN EL ARCHIVO
    {
        while (fread(&playListAux, sizeof(stPlaylist), 1, playListFile) > 0)
        {
            total++;
        }
        fclose(playListFile);
    }
    return total;
}

stPlaylist createPlaylist (int idUser, int idSong)
{
    int asd = 0;
    stPlaylist playListAux;
    playListAux.idPlayList = totalPlaylists() + 1;
    playListAux.idUser = idUser;
    playListAux.idSong = idSong;
    return playListAux;
}

void savePlaylist (stPlaylist toSave)
{

    FILE * playListFile;
    playListFile = fopen(PLAYLISTFILEPATH, "a+b");
    fwrite(&toSave, sizeof(stPlaylist), 1, playListFile);
    fclose(playListFile);
}

void playSong (int idUser, int idSong)
/// Reproduce la cancion, genera el stPlayList correspondiente y se guarda en historial de usuario
{
    stUser userAux;
    stSong songAux;
    FILE * userFile;
    FILE * songFile;

    char peli[30];

    if((songFile = fopen(SONGSFILEPATH, "r+b")) != NULL) ///valida que haya archivo
    {
        fseek(songFile,(idSong-1) * sizeof(stSong), SEEK_SET); ///se posiciona dondce esta el ID en el archivo
        fread(&songAux, sizeof(stPelicula), 1, pFile);///lo guarda en el aux de cancion
        system("cls");
        gotoxy(30, 20);
        printf("Usted esta escuchando %s - %s\n", songAux.title, songAux.artist);
        gotoxy(30, 21);
        loading();

//        printf("Presione enter cuando finalice la reproduccion\n");
        getch();
    }

    if((userFile = fopen(USERSFILEPATH, "r+b")) != NULL)
    {
        fseek(userFile,(idUser-1) * sizeof(stUser), SEEK_SET);
        fread(&userAux, sizeof(stUser), 1, userFile);
        userAux.songsPlayed[userAux.songsPlayed] = idSong;
        userAux.totalSongsPlayed ++;
        fseek(userFile,(idUser-1) * sizeof(stUser), SEEK_SET);
        fwrite(&userAux, sizeof(stUser), 1, userFile);
    }

    stPlaylist PLAux;
    PLAux = createPlaylist(idUser, idSong);
    savePlaylist(PLAux);
}
