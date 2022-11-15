#include "songLib.h"


void showSongFileByArtist (char artistToShow[])
{
    FILE * songFile;
    stSong songAux;
    songFile = fopen(SONGSFILEPATH, "rb");

    if (songFile)
    {
        while (fread(&songAux, sizeof(stSong), 1, songFile) > 0)
        {
            if (strcmpi(songAux.artist, artistToShow) == 0)
            {
                showSong(songAux);
            }
        }
    }
}

void findSongByName ()
{
    char nameToSearch[30];
    FILE * songFile;
    stSong songAux;
    songFile = fopen(SONGSFILEPATH, "rb");
    printf("Ingrese el titulo: \n");
    fflush(stdin);
    gets(nameToSearch);

    if (songFile)
    {
        while (fread(&songAux, sizeof(stSong), 1, songFile) > 0)
        {
            if (strcmpi(songAux.title, nameToSearch == 0))
            {
                printf("Encontramos tu cancion :)  \n\n");
                showSong(songAux);
            }
        }
    }
}

stSong searchSongFileById(int idSong)
{
    FILE * fileSong = fopen(SONGSFILEPATH, "rb");
    stSong songAux;
    if (fileSong)
    {
        while (!feof(fileSong))
        {
            fread(&songAux, sizeof(stSong), 1, fileSong);

            if (idSong == songAux.idSong)
            {
                return songAux;
            }
        }
    }
    fclose(fileSong);
}

int songIdCreator()
{
    FILE * fileSong;
    fileSong = fopen(SONGSFILEPATH, "rb");
    int i = 0;
    if (fileSong)
    {
        fseek(fileSong, sizeof(stSong), SEEK_END);
        i = ftell(fileSong) / sizeof(stSong);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
    return i++;
}

void loadSongToFile()
{
    stSong auxSong;
    FILE * fileSong;
    fileSong = fopen(SONGSFILEPATH, "ab");

    if (fileSong)
    {
        auxSong.idSong = songIdCreator();

        printf("Ingrese titulo: ");
        fflush(stdin);
        gets(auxSong.title);

        printf("Ingrese artista: ");
        fflush(stdin);
        gets(auxSong.artist);

        printf("Ingrese duracion: ");
        fflush(stdin);
        scanf("%f", &auxSong.duration);

        printf("Ingrese album: ");
        fflush(stdin);
        gets(auxSong.album);

        printf("Ingrese anio: ");
        fflush(stdin);
        scanf("%i", &auxSong.year);

        printf("Ingrese genero: ");
        fflush(stdin);
        gets(auxSong.gender);

        printf("Ingrese comentario: ");
        fflush(stdin);
        gets(auxSong.comment);

        auxSong.off = 1;
        auxSong.timesPlayed = 0;

        fwrite(&auxSong, sizeof(stSong), 1, fileSong);
        fclose(fileSong);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
}

void deleteSongFromFile(int idToDelte)
{
    FILE * fileSong = fopen(SONGSFILEPATH, "a+b");
    stSong auxSong;
    int aux = 0;
    int idBaja;

    showSongFile();

    printf("Ingrese el id de la auxSong que quiere dar de baja\n");
    scanf("%d", &idBaja);

    if (fileSong != NULL)
    {
        while (aux == 0 && (fread(&auxSong, sizeof(stSong), 1, fileSong) > 0))
        {
            if (auxSong.idSong == idBaja)
            {
                auxSong.off = 0;
                fseek(fileSong, (-1) * sizeof(stSong), SEEK_CUR);
                fwrite(&auxSong, sizeof(stSong), 1, fileSong);
                aux = 1;
            }
        }
    }
    fclose(fileSong);
}


void updateSong(int idToUpdate)
{
    stSong auxSong;
    FILE * fileSong;
    fileSong = fopen(SONGSFILEPATH, "r+b");
    int id = 0;
    int option = 0;
    float durationAux  = 0;

    showSongFile();

    if (fileSong != NULL)
    {
        while (fread(&auxSong, sizeof(stSong), 1, fileSong) > 0)
        {

            if (auxSong.idSong == idToUpdate)
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
                scanf("%d", &option);
                switch (option)
                {
                case 1:
                    printf("\nIngrese nuevo titulo:");
                    fflush(stdin);
                    gets(auxSong.title);
                    break;
                case 2:
                    printf("\nIngrese nuevo artista:");
                    fflush(stdin);
                    gets(auxSong.artist);
                    break;
                case 3:
                    printf("\nIngrese nueva duracion: ");
                    fflush(stdin);
                    scanf("%f", &durationAux);
                    break;
                case 4:
                    printf("\nIngrese nuevo album: ");
                    fflush(stdin);
                    gets(auxSong.album);
                    break;
                case 5:
                    printf("\nIngrese nuevo anio: ");
                    fflush(stdin);
                    scanf("%d", &auxSong.year);
                    break;
                case 6:
                    printf("\nIngrese nuevo genero: ");
                    fflush(stdin);
                    gets(auxSong.gender);
                    break;
                case 7:
                    printf("\nIngrese nuevo comentario: ");
                    fflush(stdin);
                    gets(auxSong.comment);
                    break;
                case 8:
                    printf("\nIngrese eliminado: ");
                    fflush(stdin);
                    scanf("%d", &auxSong.off);
                    break;
                }

                fseek(fileSong, (-1) * sizeof(stSong), SEEK_CUR);
                fwrite(&auxSong, sizeof(stSong), 1, fileSong);
                fseek(fileSong, sizeof(stSong), SEEK_END);
            }
        }
    }
    fclose(fileSong);
}


void upSong(int idSong)
///Busca por 'ID' la cancion y le marca un '0'(habilitado)
{
    FILE * songFile;
    stSong songAux;
    if((songFile = fopen(SONGSFILEPATH, "r+b")))
    {
        fseek(songFile, (idSong - 1) * (sizeof(stSong)), SEEK_SET);
        fread(&songAux, sizeof(stSong), 1, songFile);
        if(songAux.off == 1)
        {
            songAux.off = 0;
            fseek(songFile, (idSong - 1) * (sizeof(stSong)), SEEK_SET);
            fwrite(&songAux, sizeof(stSong), 1, songFile);
        }
        else
        {
            system("cls");
            printf("La cancion ya se encuentra dada de alta\n");
        }
    }
}

int songNameValidation(char nameToSearch[])
{
    FILE * songFile;
    stSong songAux;
    songFile = fopen(SONGSFILEPATH, "rb");
    int flag = 1;

    if (songFile != NULL)
    {
        while (fread(&songAux, sizeof(stSong), 1, songFile) > 0)
        {
            flag = strcmpi(songAux.title, nameToSearch);
        }
    }
    return flag;
}

int searchSongFileByName (char nameToSearch[])
{
    FILE * songFile;
    stSong songAux;
    songFile = fopen(SONGSFILEPATH, "rb");
    int auxId = -1;

    if (songFile)
    {
        while (fread(&songAux, sizeof(stSong), 1, songFile) > 0)
        {
            if (strcmpi(songAux.title, nameToSearch == 0))
                auxId = songAux.idSong;
        }
    }
    return auxId;
}
int totalSongs()
{
    int total = 0;
    FILE * songFile;
    stSong songAux;
    songFile = fopen(SONGSFILEPATH, "r+b");

    if (songFile) // EN CASO DE DAR OK EN LA LECTURA DEVUELVE LA CANTIDAD EXACTA DE USUARIOS EN EL fileUser
    {
        while (fread(&songAux, sizeof(stSong), 1, songFile) > 0)
        {
            total++;
        }
        fclose(songFile);
    }
    return total;
}

int songIdValidation()
{
    int idSong = 0;
    FILE * songFile;
    stSong songAux;
    songFile = fopen(SONGSFILEPATH, "rb");
    int auxId = -1;

    system("cls");
    printf("Ingrese el ID de la pelicula: \n");
    scanf("%d", &idSong);

    if (songFile)
    {
        while (fread(&songAux, sizeof(stSong), 1, songFile) > 0)
        {
            if (songAux.idSong == idSong)
            {
                auxId = songAux.idSong;
            }
        }
        if (auxId == -1)
        {
            printf("El id de la cancion ingresada no es correcto\n");
        }
    }
    return auxId;
}

void showSongFile()
{
    FILE * songFile;
    stSong auxSong;
    songFile = fopen(SONGSFILEPATH, "rb");
    if (songFile)
    {
        while (fread(&auxSong, sizeof(stSong), 1, songFile) > 0)
        {
            showSong(auxSong);
        }
    }
    fclose(songFile);
}

void showSong (stSong toShow)
{
    puts("\n-------------------------------------");
    printf("\n IdCancion:..........%d", toShow.idSong);
    printf("\n Titulo:............ %s", toShow.title);
    printf("\n Artista:........... %s", toShow.artist);
    printf("\n Duracion:.......... %.2f", toShow.duration);
    printf("\n Album:..............%s", toShow.album);
    printf("\n Anio:.............. %d", toShow.year);
    printf("\n Genero:............ %s", toShow.gender);
    printf("\n Comentario:........ %s", toShow.comment);
    printf("\n Eliminado 1-Si/0-No:%d", toShow.off);
    puts("\n-------------------------------------");
}
int getSongId()
{
    char cControl = 's';
    int songTotal = totalSongs();
    int idSong;
    do
    {
        system("cls");
        gotoxy(30, 20);
        printf("Ingrese el ID de la pelicula: \n");
        gotoxy(30, 21);
        scanf("%d", &idSong);
        system("cls");
        gotoxy(30, 20);
        printf("El ID ingresado es: %d, es correcto?", idSong);
        fflush(stdin);
        gotoxy(30, 21);
        scanf("%c", &cControl);
        if (idSong < 0 || idSong > songTotal)
        {
            system("cls");
            gotoxy(30, 20);
            printf("El ID ingresado no existe\n");
            cControl = 'n';
        }
    }
    while (cControl != 's');
    return idSong;
}

///FUNCIONES LISTA DE CANCIONES
///FUNCIONES LISTA DE CANCIONES
///FUNCIONES LISTA DE CANCIONES
///FUNCIONES LISTA DE CANCIONES
///FUNCIONES LISTA DE CANCIONES



nodeSongList * startSongList()
{
    return NULL;
}

nodeSongList * createSongNode (stSong toCreate)
{
    nodeSongList * songAux = (nodeSongList*)malloc(sizeof(nodeSongList));
    songAux->value = toCreate;
    songAux->next = NULL;
    return songAux;
}

nodeSongList * addSongFirst(nodeSongList * songsongList, nodeSongList * toAdd)
{
    if (!songsongList)
    {
        songsongList = toAdd;
    }
    else
    {
        toAdd->next = songsongList;
        songsongList = toAdd;
    }
    return songsongList;
}



nodeSongList * searchLastSong(nodeSongList * songList)
{
    nodeSongList * songAux = songList;
    while (songAux->next != NULL)
    {
        songAux = songAux->next;
    }
    return songAux;
}

nodeSongList * addSongLast(nodeSongList * songList, nodeSongList * toAdd)
{
    nodeSongList * lastSong;
    if (!songList)
    {
        songList = toAdd;
    }
    else
    {
        lastSong = searchLastSong(songList);
        lastSong->next = toAdd;
    }
    return songList;
}

nodeSongList * addInOrderBySongName(nodeSongList *songList, nodeSongList * toAdd)
{
    if (!songList)
    {
        songList = toAdd;
    }
    else
    {
        if (strcmpi(toAdd->value.title, songList->value.title) < 0)
        {
            songList = addFirst(songList, toAdd);
        }
        else
        {
            nodeSongList * prev = songList;
            nodeSongList * songAux = songList;
            while (songAux && (strcmpi(toAdd->value.title, songList->value.title) > 0))
            {
                prev = songAux;
                songAux = songAux->next;
            }
            prev->next = toAdd;
            toAdd->next = songAux;
        }
    }
}

void showNode(nodeSongList * song)
{
    printf("idSong:.. %d \n", song->value.idSong);
    printf("title:..... %s \n", song->value.title);
    printf("artist:.... %s \n", song->value.artist);
    printf("duration:... %d \n", song->value.duration);
    printf("album:...... %s \n", song->value.album);
    printf("year:....... %d \n", song->value.year);
    printf("genres:..... %s \n", song->value.gender);
    printf("comment:. %s \n", song->value.comment);
    printf("deleted:.. %c \n", song->value.off);
}

void showSongList(nodeSongList * toShow)
{
    if (toShow)
    {
        showNode(toShow);
        showSongList(toShow->next);
    }
}

nodeSongList * deleteNodeById(nodeSongList * songList, int idSong)

{
    nodeSongList * next;
    nodeSongList * prev;



    if((songList) && (songList->value.idSong == idSong))
    {
        nodeSongList * auxSong = songList;
        songList = songList->next;
        free(auxSong);
    }
    else
    {
        next = songList;
        while((next) && (next->value.idSong != idSong))
        {
            prev = next;
            next = next->next;
        }

        if(next)
        {
            prev->next = next->next;
            free(next);
        }
    }
    return songList;

}

nodeSongList * deleteSongList (nodeSongList * toDelete)
{
    nodeSongList * next;
    nodeSongList * auxSong;
    auxSong = toDelete;
    while(auxSong != NULL)
    {
        next = auxSong->next;
        free(auxSong);
        auxSong =  next;
    }
    return auxSong;
}

nodeSongList * searchSongById(nodeSongList * songList, int idSong)

{
    nodeSongList * next;
    nodeSongList * prev;

    if((songList) && (songList->value.idSong == idSong))
    {
        nodeSongList * auxSong = songList;
        songList = songList->next;
        free(auxSong);
    }
    else
    {
        next = songList;

        while(next && (next->value.idSong != idSong))
        {
            prev = next;
            next = next->next;
        }

        if(next)
        {
            prev->next = next->next;
            free(next);
        }
    }
    return songList;
}

///////////////FUNCIONES ARBOL DE CANCIONES//////////////////
///////////////FUNCIONES ARBOL DE CANCIONES//////////////////

///////////////FUNCIONES ARBOL DE CANCIONES//////////////////



nodeTreeSong *startTree()
{
    return NULL;
}

nodeTreeSong * createNodeTree(stSong song)
{
    nodeTreeSong *aux = (nodeTreeSong *)malloc(sizeof(nodeTreeSong));
    aux->value = song;
    aux->left = NULL;
    aux->right = NULL;
    return aux;
}

nodeTreeSong * insertNodeTree(nodeTreeSong *tree, stSong song)
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


void inOrder(nodeTreeSong *tree)
{
    if (tree != NULL)
    {
        inOrder(tree->left);
        showSong(tree->value);
        inOrder(tree->right);
    }
}

void preOrder(nodeTreeSong *tree)
{
    if (tree != NULL)
    {
        showSong(tree->value);
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

void postOrder(nodeTreeSong *tree)
{
    if (tree )
    {
        postOrder(tree->left);
        postOrder(tree->right);
        showSong(tree->value);
    }
}

nodeTreeSong * searchNodeById(nodeTreeSong * treeSong, int idSong)
{

    nodeTreeSong * auxSong = NULL;
    if (treeSong)
    {
        if (idSong == treeSong->value.idSong)//--->Si lo encuentra devuelve el arbol como respuesta
            auxSong = treeSong;
        else
        {
            if (idSong > treeSong->value.idSong)//---->Si el dato es mayor que el dato en la raiz se busca por derecha y si es menor se busca por izquierda
                auxSong = searchNodeById(treeSong->right, idSong);//se hace llamada recursiva hasta encontrar el dato
            else
                auxSong = searchNodeById(treeSong->left, idSong);//se hace llamada recursiva hasta encontrar el dato
        }
    }
    return auxSong;//-->En caso que no encuentre el dato devuelve NULL como respuesta
}

nodeTreeSong * deleteTreeNode(nodeTreeSong *tree, int idSong)
{
    if (tree != NULL)
    {
        nodeTreeSong *resId = searchNodeById(tree, idSong);

        if (idSong == resId)
        {
            free(tree);
            tree = NULL;
        }
    }
    return tree;
}

nodeTreeSong * insertFromArray(stSong songArray[], nodeTreeSong *songTree, int valid, int midArray)
{
    int i = 0;
    srand(time(NULL));
    while (i < valid)
    {
        if (songTree == NULL)
        {
            songTree = insertNodeTree(songTree, songArray[midArray]);
        }
        else
        {
            songTree = insertNodeTree(songTree, songArray[rand() % valid]);
        }
        i++;
    }
    return songTree;
}

int midArray(int valids)
{
    int var;
    if (valids % 2 == 0)
    {
        var = valids / 2;
    }
    else
    {
        valids++;
        var = valids / 2;
    }
    return var;
}

nodeTreeSong * fileToTree(nodeTreeSong * songTree)
{
    FILE * songFile;
    songFile = fopen(SONGSFILEPATH, "rb");
    stSong songAux;
    int dim = totalSongs();
    int i = 0;
    stSong songArray[dim];
    if (songFile)
    {
        while (!feof(songFile) && i<dim)
        {
            fread(&songArray[i] , sizeof(stSong), 1, songFile);
            i++;
        }
    }

    int mid = midArray(dim);
    songTree = insertFromArray(songArray, songTree, dim, mid);
    return songTree;
}

int maxTimesPlayed()
{
    int maxValue = 0;
    FILE * songFile;
    stSong songAux;
    songFile = fopen(SONGSFILEPATH, "r+b");

    if (songFile)
    {
        while (fread(&songAux, sizeof(stSong), 1, songFile) > 0)
        {
            if (songAux.timesPlayed > maxValue)
            {
                maxValue = songAux.timesPlayed;
            }
        }
        fclose(songFile);
    }
    return maxValue;
}



