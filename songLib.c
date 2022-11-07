#include "songLib.h"

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

    if (fileSong != NULL)
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
        scanf("%d", &auxSong.duration);

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
    int id;
    int option;

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
                    gets(auxSong.duration);
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
    printf("\n Duracion:.......... %d", toShow.duration);
    printf("\n Album:..............%s", toShow.album);
    printf("\n Anio:.............. %d", toShow.year);
    printf("\n Genero:............ %s", toShow.gender);
    printf("\n Comentario:........ %s", toShow.comment);
    printf("\n Eliminado 1-Si/0-No:%d", toShow.off);
    puts("\n-------------------------------------");
}
int getSongId (char cMovies[])
{
    getIdSong()
    char cControl = 's';
    int totalIdM = 0;
    int iIdM;
    do
    {
        system("cls");
        gotoxy(30, 20);
        printf("Ingrese el ID de la pelicula: \n");
        gotoxy(30, 21);
        scanf("%d", &iIdM);
        system("cls");
        totalIdM = calculateAmount(cMovies);
        gotoxy(30, 20);
        printf("El ID ingresado es: %d, es correcto?", iIdM);
        fflush(stdin);
        gotoxy(30, 21);
        scanf("%c", &cControl);
        if (iIdM<0 || iIdM>totalIdM)
        {
            system("cls");
            gotoxy(30, 20);
            printf("El ID ingresado no existe\n");
            cControl = 'n';
        }
    }
    while (cControl != 's');
    return iIdM;
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

///////////////FUNCIONES ARBOL DE auxSongES//////////////////
///////////////FUNCIONES ARBOL DE auxSongES//////////////////

///////////////FUNCIONES ARBOL DE auxSongES//////////////////



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

nodeTreeSong * searchNodeByNodeID(nodeTreeSong *tree, int idSong)
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

nodeTreeSong * deleteTreeNode(nodeTreeSong *tree, int idSong)
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

void loadArrayFromSongFile(stSong toSave[])
{
    FILE * songFile;
    songFile = fopen(SONGSFILEPATH, "rb");
    stSong songAux;
    int i = 0;
    if (songFile)
    {
        while (!feof(songFile))
        {
            fread(&songAux, sizeof(stSong), 1, songFile);
            if (!feof(songFile))
            {
                toSave[i] = songAux;
                i++;
            }
        }
    }
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
    int var = songIdCreator();
    stSong songArray[var];
    loadArrayFromSongFile(songArray);
    int mid = midArray(var);
    songTree = insertFromArray(songArray, songTree, var, mid);
    return songTree;
}


