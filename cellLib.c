#define USERSPLAYLISTS "UserPlayLists.bin"

#include "cellLib.h"


/*
stCell * loadListFromFile(stCell * userList) ///levanta el archivo de stPlaylist y trae CADA canción al usuario de CADA registro stPlaylist.
{                                       ///recordar que el struct stPlaylist tiene 1 idSong y 1 idUser para relacionarlas.
    FILE * fileUser;                    ///eso es lo que pide el enunciado.
    nodeSongList * auxSongList;            ///PERO PERO PERO por qué no cargar la lista de canciones desde los idSong que almacena c/ user?
    stUser userAux;

    stSong * songList;

    fileUser = fopen(USERSFILEPATH,"rb");
    fileSong = fopen(SONGFILEPATH, "rb");
    filePlayList = fopen(PLAYLISTFILEPATH, "rb");
    if(fileUser)
    {
        while(!feof(fileUser))
        {
            fread(&userAux,1,sizeof(stUser),fileUser);

            ///PARA BUSCAR CANCIONES X ID, ES MEJOR HACERLO MEDIANTE EL ARBOL AL SER MAS OPTIMO PARA ESO
            ///UNA VEZ CON LA LIBRERIA DE ARBOL, AGREGAR QUE ACÁ A LA LISTA DE USER

            ///MIENTRAS USERAUX->SONGPLAYED != 0
            ///ALGORITMO DE BUSQUEDA DE CANCION X ID QUE DEVUELVA STSONG DEL ID ACTUAL -> Y ACA CREAR NODO SONG
            ///SONG LIST = CARGA EL NODO EN LA LISTA
            ///USERAUX->SONGPLAYED[i++];

            userList = addUserToList(userList,auxSongList); ///ACA PASA LA LISTA CARGADA ARRIBA DE CANCIONES ESCUCHADAS X EL USER
        }
    }
    else
    {
        printf("error en abrir el archivo!\n");
    }
    return userList;
}
*/


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

stCell * addUserToList(stCell * userList, nodeSongList * songList, stUser toAdd)
{
    stCell * userAux;
    userAux = createCellNode(toAdd, songList);
    if(userList)
    {
        userList = addLastCell(userList,userAux);
    }
    userAux->songList = songList;
    return userAux;
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




stCell * addSongToUser(stCell * userList, int idUser, stSong toAdd)
{
    nodeSongList * auxSong = createSongNode(toAdd);
    stCell * auxUser;
    auxUser = searchUserCellById(userList, idUser);
    if(auxUser)
    {
        auxUser->songList = addLast(auxUser->songList, auxSong);
    }
    return userList;
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

stCell * addCellInOrderById(stCell *cellList, stCell * toAdd)
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
