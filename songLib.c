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
    FILE * songFile;
    songFile = fopen(SONGSFILEPATH, "rb");
    int i = 0;
    if (songFile != NULL)
    {
        fseek(songFile, sizeof(stSong), SEEK_END);
        i = ftell(songFile) / sizeof(stSong);
    }
    else
    {
        printf("ERROR de datos - El SONGSFILEPATH no pudo ser abierto");
    }
    return i++;
}

void loadSongToFile()
{
    stSong songAux;
    FILE * songFile;
    songFile = fopen(SONGSFILEPATH, "ab");

    if (songFile)
    {
        songAux.idSong = songIdCreator();

        do
        {
            printf("Ingrese titulo: ");
            fflush(stdin);
            scanf("%s", &songAux.title);
        } while (strlen(songAux.title) > 30);
        do
        {
            printf("Ingrese artista: ");
            fflush(stdin);
            scanf("%s", &songAux.artist);
        } while (strlen(songAux.artist) > 30);
        do
        {
            printf("Ingrese duracion: ");
            fflush(stdin);
            scanf("%f", &songAux.duration);
        } while (songAux.duration <= 0);

        do
        {
            printf("Ingrese album: ");
            fflush(stdin);
            scanf("%s", &songAux.album);
        } while (strlen(songAux.album) > 30);

        do
        {
            printf("Ingrese anio: ");
            fflush(stdin);
            scanf("%d", &songAux.year);
        } while (songAux.year == 0);

        do
        {
            printf("Ingrese genero: ");
            fflush(stdin);
            scanf("%s", &songAux.gender);
        } while (strlen(songAux.gender) > 30);

        do
        {
            printf("Ingrese comentario: ");
            fflush(stdin);
            scanf("%s", &songAux.comment);
        } while (strlen(songAux.comment) > -1);

        songAux.off = 1;

        fwrite(&songAux, sizeof(stSong), 1, songFile);
        fclose(songFile);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
}

void deleteSongFromFile(int idToDelte)
{
    stSong songAux;
    FILE * songFile;
    songFile = fopen(SONGSFILEPATH, "r+b");
    int aux = 0;
    char ok = 's';

    if (songFile != NULL && ok == 's')
    {
        while (aux == 0 && (fread(&songAux, sizeof(stSong), 1, songFile) > 0))
        {

            if (songAux.idSong == idToDelte)
            {
                songAux.off = 0;
                fseek(songFile, (-1) * sizeof(stSong), SEEK_CUR);
                fwrite(&songAux, sizeof(stSong), 1, songFile);
                aux = 1;
            }
        }
    }
    else
    {
        printf("ERROR de datos - El SONGSFILEPATH no pudo ser abierto");
    }
    fclose(songFile);
}
int totalSongs()
{
    int total = 0;
    FILE * fileSong;
    stSong songAux;
    fileSong = fopen(SONGSFILEPATH, "r+b");

    if (fileSong) // EN CASO DE DAR OK EN LA LECTURA DEVUELVE LA CANTIDAD EXACTA DE CANCIONES EN EL songFile
    {
        while (fread(&songAux, sizeof(stSong), 1, fileSong) > 0)
        {
            total++;
        }
        fclose(fileSong);
    }
    return total;
}
void updateSong(int idToUpdate)
{
    stSong songAux;
    FILE * songFile;
    songFile = fopen(SONGSFILEPATH, "r+b");
    int option;

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
    system("cls");

    if (songFile != NULL)
    {
        while (fread(&songAux, sizeof(stSong), 1, songFile) > 0)
        {

            if (songAux.idSong == idToUpdate)
            {
                switch (option)
                {
                case 1:
                    printf("\nIngrese nuevo titulo:");
                    fflush(stdin);
                    scanf("%s", &songAux.title);
                    break;
                case 2:
                    printf("\nIngrese nuevo artista:");
                    fflush(stdin);
                    scanf("%s", &songAux.artist);
                    break;
                case 3:
                    printf("\nIngrese nueva duracion: ");
                    fflush(stdin);
                    scanf("%s", &songAux.duration);
                    break;
                case 4:
                    printf("\nIngrese nuevo album: ");
                    fflush(stdin);
                    scanf("%s", &songAux.album);
                    break;
                case 5:
                    printf("\nIngrese nuevo anio: ");
                    fflush(stdin);
                    scanf("%d", &songAux.year);
                    break;
                case 6:
                    printf("\nIngrese nuevo genero: ");
                    fflush(stdin);
                    scanf("%s", &songAux.gender);
                    break;
                case 7:
                    printf("\nIngrese nuevo comentario: ");
                    fflush(stdin);
                    scanf("%s", &songAux.comment);
                    break;
                case 8:
                    printf("\nIngrese eliminado: ");
                    fflush(stdin);
                    scanf("%d", &songAux.off);
                    break;
                }

                fseek(songFile, (-1) * sizeof(stSong), SEEK_CUR);
                fwrite(&songAux, sizeof(stSong), 1, songFile);
                fseek(songFile, sizeof(stSong), SEEK_END);
            }
        }
    }
    fclose(songFile);
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
            flag = strcmp(songAux.title, nameToSearch);
        }
    }
    return flag;
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
            printf("\n IdsongAux: %d", toShow.idSong);
            printf("\n Titulo: %s", toShow.title);
            printf("\n Artista: %s", toShow.artist);
            printf("\n Duracion: %.2f", toShow.duration);
            printf("\n Album: %s", toShow.album);
            printf("\n Anio: %d", toShow.year);
            printf("\n Genero: %s", toShow.gender);
            printf("\n Comentario: %s", toShow.comment);
            printf("\n Eliminado 1-Si/0-No: %d", toShow.off);
            puts("\n-------------------------------------");
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

void saveSongsInFile(stSong toSave[])
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
    int var = totalSongs();
    stSong songArray[var];

    saveSongsInFile(songArray);
    int mid = midArray(var);
    songTree = insertFromArray(songArray, songTree, var, mid);
    return songTree;
}


