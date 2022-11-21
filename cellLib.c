#define PLAYLISTFILEPATH "playList.bin"

#include "cellLib.h"

/// CELL LIB///
/// CELL LIB///
/// CELL LIB///

void houseRecommendations(stCell *userList, int idUser)
{
    stCell *userAux = searchUserCellById(userList, idUser);
    int totalPlays = userAux->userValue.totalSongsPlayed;

    if (totalPlays > 0)
    {
        artistRecommendation(userAux->songList, totalPlays);
    }
    else
    {
        morePopularRecommendation();
    }
}

void morePopularRecommendation()
{
    int recordPlays = maxTimesPlayed();
    FILE *songFile = fopen(SONGSFILEPATH, "rb");
    stSong auxSong;
    int itrtor = 3;

    if (songFile)
    {
        printf("Estas son unas de las 3 canciones mas escuchadas de la plataforma =O \nDale una chance!\n");
        while (fread(&auxSong, 1, sizeof(stSong), songFile) > 1 && itrtor > 0)
        {
            if ((auxSong.timesPlayed > (recordPlays - 3)) && auxSong.timesPlayed <= recordPlays)
            {
                showSong(auxSong);
                itrtor--;
            }
        }
    }
}

void artistRecommendation(nodeSongList *userSongList, int totalPlays)
{
    int randListPos = rand() % 1 + (totalPlays - 1); /// retorna un punto aleatorio de la lista por id
    int i = 1;
    nodeSongList *songAux;
    songAux = userSongList;
    while (songAux && i < randListPos)
    {
        songAux = songAux->next;
        i++;
    }
    printf("Quiza te interese escuchar nuevamente a %s? :)\n\n", songAux->value.artist);
    showSongFileByArtist(songAux->value.artist);
}

stCell *loadListFromFile(stCell *userList) /// levanta el archivo de stPlaylist y trae CADA canción al usuario de CADA registro stPlaylist.
{
    FILE *filePL;
    FILE *fileUser;
    filePL = fopen(PLAYLISTFILEPATH, "rb");
    fileUser = fopen(USERSFILEPATH, "rb");

    stCell *cellAux;

    stUser userAux;
    stSong songAux;
    stPlaylist PLAux;

    nodeTreeSong *treeSong;
    treeSong = startTree();
    treeSong = fileToSongTree(treeSong);
    nodeTreeSong *auxSongTree;

    if (fileUser) // si hay usuarios los carga.. aunque no hayan escuchado nada
    {
        while (fread(&userAux, 1, sizeof(stUser), fileUser) > 0)
        {
            nodeSongList * auxSongList = startSongList();
            if (userAux.off == 0) // siempre y cuando no esten dados de baja
            {
                userList = addLastCell(userList, createCellNode(userAux, auxSongList)); // agrega si o si la celda aunque no tenga lista de canciones.
                if (fopen(PLAYLISTFILEPATH, "rb") > 0)                                  // aca utilizamos la estructura playlist para buscar si el usuario tiene canciones reproducidas y saber cuales son
                {
                    while (fread(&PLAux, 1, sizeof(stPlaylist), filePL) > 0)
                    {
                        if (PLAux.idUser == userAux.idUser) // si el usuario es el mismo que la estructura playList ingresa
                        {
                            auxSongTree = searchNodeById(treeSong, PLAux.idSong); /// busca en el arbol x id de cancion
                            if (auxSongTree)
                            {
                                auxSongList = createSongNode(auxSongTree->value);
                                cellAux = searchUserCellById(userList, userAux.idUser);
                                cellAux->songList = addSongLast(cellAux->songList, auxSongList);
                            }
                            /// crea un nodo para la lista de canciones del user
                            /// y la agrega ultima
                        }
                    }
                }
                fclose(filePL);
            }
        }
        fclose(fileUser);
    }
    else
    {
        printf("Error al abrir el archivo\n");
    }
    return userList;
}

stCell *createCellUser()
{
    stCell *userCellAux;
    stUser userAux;
    userAux = createOneUser();
    userCellAux->userValue = userAux;
    userCellAux->songList = startSongList();
    userCellAux->next = NULL;

    return userCellAux;
}

stCell *searchUserCellById(stCell *userList, int idUser)
{
    stCell *userAux = userList;
    if (userAux)
    {
        while (userAux && userAux->userValue.idUser != idUser)
        {
            userAux = userAux->next;
        }
    }
    return userAux;
}

void showUserPlaylists(stCell *userList)
{
    printf("\nMostrando lista de usuarios \n");
    if (userList)
    {
        showCellList(userList);
    }
    else
        printf("There is nothing to show\n");
}

stCell *clearSongList(stCell *cellList, int idUser)
{
    stCell *userAux;
    userAux = searchUserCellById(cellList, idUser);
    userAux->songList = deleteSongList(userAux->songList);

    return cellList;
}

stCell *startCellList()
{
    return NULL;
}

stCell *createCellNode(stUser toCreate, nodeSongList *songList)
{
    stCell *cellAux = (stCell *)malloc(sizeof(stCell));
    cellAux->userValue = toCreate;
    cellAux->songList = songList;
    cellAux->next = NULL;
    return cellAux;
}

stCell *addFirstCell(stCell *cellList, stCell *toAdd)
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

stCell *searchLastCell(stCell *userList)
{
    stCell *cellAux = userList;
    while (cellAux->next)
    {
        cellAux = cellAux->next;
    }
    return cellAux;
}

stCell *addLastCell(stCell *cellList, stCell *toAdd)
{
    stCell *lastUser;
    if (!cellList)
    {
        cellList = toAdd;
    }
    else
    {
        lastUser = searchLastCell(cellList);
        lastUser->next = toAdd;
    }
    return cellList;
}

stCell *addCellInOrderByName(stCell *cellList, stCell *toAdd)
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
            stCell *prev = cellList;
            stCell *cellAux = cellList;
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

stCell *addCellInOrderById(stCell *cellList, stCell *toAdd)
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
            stCell *prev = cellList;
            stCell *cellAux = cellList;
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

void showCellNode(stCell *toShow)
{
    puts("-------------------------------------------------------------------\n");
    printf("ID USUARIO: %d\n", toShow->userValue.idUser);
    printf("NOMBRE COMPLETO: %s\n", toShow->userValue.fullName);

    printf("PASSWORD: ");
    showPassword(toShow->userValue);
    printf("Anio Nacimiento: %i\n", toShow->userValue.birthYear);
    printf("Genero: ");
    if (toShow->userValue.gender == "f")
    {
        printf("Femenino\n");
    }
    else if (toShow->userValue.gender == "m")
    {
        printf("Masculino\n");
    }

    printf("Country de origen: %s\n", toShow->userValue.country);
    printf("Cantidad de canciones escuchadas: %d\n", toShow->userValue.totalSongsPlayed);
    printf("Canciones escuchadas: \n");
    showSongList(toShow->songList); /// muestra la lista de canciones del usuario
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

void showCellList(stCell *toShow) /// recursiva
{
    if (toShow)
    {
        showCellNode(toShow);
        showCellList(toShow->next);
    }
}

stCell *addSongToUser(stCell *userList, int idUser, stSong toAdd)
{
    nodeSongList *auxSong = createSongNode(toAdd);
    stCell *auxUser;
    auxUser = searchUserCellById(userList, idUser);
    if (auxUser)
    {
        auxUser->songList = addLast(auxUser->songList, auxSong);
        savePlaylist(createPlaylist(idUser, toAdd.idSong)); /// En la accion de escuchar una cacncion, se crea un registro playList y se guarda
    }
    else
    {
        printf("El user no existe\n");
    }
    return userList;
}

/// PLAYLIST LIB ///
/// PLAYLIST LIB ///
/// PLAYLIST LIB ///
/// PLAYLIST LIB ///

int totalPlaylists()
{
    int total = 0;
    FILE *playListFile;
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

stPlaylist createPlaylist(int idUser, int idSong)
{
    stPlaylist playListAux;
    playListAux.idPlayList = totalPlaylists() + 1;
    playListAux.idUser = idUser;
    playListAux.idSong = idSong;
    return playListAux;
}

void savePlaylist(stPlaylist toSave)
{

    FILE *playListFile = fopen(PLAYLISTFILEPATH, "ab");
    fwrite(&toSave, sizeof(stPlaylist), 1, playListFile);
    fclose(playListFile);
}

void playSong(int idUser, int idSong)
/// Reproduce la cancion, genera el stPlayList correspondiente y se guarda en historial de usuario
{
    stUser userAux;
    stSong songAux;
    FILE *userFile;
    FILE *songFile;

    if ((songFile = fopen(SONGSFILEPATH, "r+b")) && (idSong != -1)) /// valida que haya archivo
    {
<<<<<<< HEAD
        fseek(songFile, (idSong-1) * sizeof(stSong), SEEK_SET); /// se posiciona dondce esta el ID en el archivo
=======
        fseek(songFile, (idSong - 1) * sizeof(stSong), SEEK_SET); /// se posiciona dondce esta el ID en el archivo
>>>>>>> 591ff838a8f2c7e5910d0a9f3304bc9c55c07e8e
        fread(&songAux, sizeof(stSong), 1, songFile);             /// lo escribe en el auxSong

        system("cls");

        printf("Usted esta escuchando %s - %s\n", songAux.title, songAux.artist); /// front de reproduccion del tema

        playing(); /// front de reproduccion del tema

        getch();
        if (userFile = fopen(USERSFILEPATH, "r+b"))
        {
            userAux = searchUserFileById(idUser);
            userAux.songsPlayed[userAux.totalSongsPlayed] = idSong;  /// busca el usuario en el archivo y le agrega el id de la canci�n en la sig pos
            userAux.totalSongsPlayed = userAux.totalSongsPlayed + 1; /// suma 1 el total de canciones reproducidas
            fseek(userFile, ((idUser - 1) * sizeof(stUser)), SEEK_SET);
            fwrite(&userAux, sizeof(stUser), 1, userFile);
            fseek(userFile, sizeof(stUser), SEEK_END);
        }

        stPlaylist PLAux;
        PLAux = createPlaylist(idUser, idSong); // crea un struct playList
        savePlaylist(PLAux);                    /// guarda el struct en el archivo de playList
    }
    else
    {
        printf("No existe la cancion\n");
    }

    fclose(userFile);
    fclose(songFile);
}
