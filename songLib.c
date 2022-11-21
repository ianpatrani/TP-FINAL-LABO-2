#include "songLib.h"

void showSongFileByArtist(char artistToShow[])
{
    FILE *songFile;
    stSong songAux;
    songFile = fopen(SONGSFILEPATH, "rb");

    if (songFile)
    {
        while (fread(&songAux, 1, sizeof(stSong), songFile) > 0)
        {
            if (strcmpi(songAux.artist, artistToShow) == 0)
            {
                showSong(songAux);
            }
        }
    }
}

void findSongByName()
{
    char nameToSearch[30];
    FILE *songFile;
    stSong songAux;
    songFile = fopen(SONGSFILEPATH, "rb");
    printf("Ingrese el titulo: \n");
    fflush(stdin);
    gets(nameToSearch);
    int flag = 0;
    if (songFile)
    {
        while (fread(&songAux, sizeof(stSong), 1, songFile) > 0 && flag == 0)
        {
            if (strcmpi(songAux.title, nameToSearch) == 0)
            {
                flag = 1;
                printf("Encontramos tu cancion :)  \n\n");
                showSong(songAux);
            }
        }
    }

    fclose(songFile);
}

stSong searchSongFileById(int idSong)
{
    FILE *fileSong = fopen(SONGSFILEPATH, "rb");
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
    int newId = 0;
    FILE *fileSong;
    stSong auxSong;
    fileSong = fopen(SONGSFILEPATH, "rb");
    if (fileSong)
    {
        while (!feof(fileSong))
        {
            fread(&auxSong, 1, sizeof(stSong), fileSong);

        }
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
        getch();
    }
    return newId;
}

void loadSongToFile()
{
    stSong auxSong;
    FILE *fileSong;
    fileSong = fopen(SONGSFILEPATH, "a+b");

    if (fileSong)
    {
        auxSong.idSong = totalSongs()+1;

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
    FILE *fileSong = fopen(SONGSFILEPATH, "a+b");
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
    FILE *fileSong;
    fileSong = fopen(SONGSFILEPATH, "r+b");
    int id = 0;
    int option = 0;
    float durationAux = 0;
    auxSong = searchSongFileById(idToUpdate);

    if (auxSong.idSong == idToUpdate)
    {
        printf("Esta por modificar la siguiente cancion: \n");
        showSong(auxSong);
        printf("\n");
        puts("Opcion 1 - titulo");
        puts("Opcion 2 - artista");
        puts("Opcion 3 - duracion");
        puts("Opcion 4 - album");
        puts("Opcion 5 - anio");
        puts("Opcion 6 - genero");
        puts("Opcion 7 - comentario");
        puts("Opcion 8 - eliminado\n");

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
    fclose(fileSong);
}

void upSong(int idSong)
/// Busca por 'ID' la cancion y le marca un '0'(habilitado)
{
    FILE *songFile;
    stSong songAux;
    if ((songFile = fopen(SONGSFILEPATH, "r+b")))
    {
        fseek(songFile, (idSong - 1) * (sizeof(stSong)), SEEK_SET);
        fread(&songAux, sizeof(stSong), 1, songFile);
        if (songAux.off == 1)
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
    FILE *songFile;
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

int searchSongFileByName(char nameToSearch[])
{
    FILE *songFile;
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
    FILE *songFile;
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
    FILE *songFile;
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
    FILE *songFile;
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

void showSong(stSong toShow)
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
        printf("Ingrese el ID de la pelicula: \n");
        scanf("%d", &idSong);
        system("cls");
        printf("El ID ingresado es: %d, es correcto?", idSong);
        fflush(stdin);
        scanf("%c", &cControl);
        if (idSong < 0 || idSong > songTotal)
        {
            system("cls");
            printf("El ID ingresado no existe\n");
            cControl = 'n';
        }
    } while (cControl != 's');
    return idSong;
}

/// FUNCIONES LISTA DE CANCIONES
/// FUNCIONES LISTA DE CANCIONES
/// FUNCIONES LISTA DE CANCIONES

nodeSongList *startSongList()
{
    return NULL;
}

nodeSongList *createSongNode(stSong toCreate)
{
    nodeSongList *songAux = (nodeSongList *)malloc(sizeof(nodeSongList));
    songAux->value = toCreate;
    songAux->next = NULL;
    return songAux;
}

nodeSongList *addSongFirst(nodeSongList *songsongList, nodeSongList *toAdd)
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

nodeSongList *searchLastSong(nodeSongList *songList)
{
    nodeSongList *songAux = songList;
    while (songAux->next != NULL)
    {
        songAux = songAux->next;
    }
    return songAux;
}

nodeSongList *addSongLast(nodeSongList *songList, nodeSongList *toAdd)
{
    nodeSongList *lastSong;
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

nodeSongList *addInOrderBySongName(nodeSongList *songList, nodeSongList *toAdd)
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
            nodeSongList *prev = songList;
            nodeSongList *songAux = songList;
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

void showNode(nodeSongList *song)
{
    puts("\n-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-");
    printf("ID: %d \n", song->value.idSong);
    printf("Titulo: %s \n", song->value.title);
    printf("Artista: %s \n", song->value.artist);
    printf("Album: %s \n", song->value.album);
    printf("Lanzamiento: %d \n", song->value.year);
    printf("Duracion:... %.2f \n", song->value.duration);
    printf("Genero:..... %s \n", song->value.gender);
}

void showSongList(nodeSongList *toShow)
{
    if (toShow)
    {
        showNode(toShow);
        showSongList(toShow->next);
    }
}

nodeSongList *deleteNodeById(nodeSongList *songList, int idSong)

{
    nodeSongList *next;
    nodeSongList *prev;

    if ((songList) && (songList->value.idSong == idSong))
    {
        nodeSongList *auxSong = songList;
        songList = songList->next;
        free(auxSong);
    }
    else
    {
        next = songList;
        while ((next) && (next->value.idSong != idSong))
        {
            prev = next;
            next = next->next;
        }

        if (next)
        {
            prev->next = next->next;
            free(next);
        }
    }
    return songList;
}

nodeSongList *deleteSongList(nodeSongList *toDelete)
{
    nodeSongList *next;
    nodeSongList *auxSong;
    auxSong = toDelete;
    while (auxSong != NULL)
    {
        next = auxSong->next;
        free(auxSong);
        auxSong = next;
    }
    return auxSong;
}

nodeSongList *searchSongById(nodeSongList *songList, int idSong)

{
    nodeSongList *seg;
    seg = songList;

    while ((seg) && (seg->value.idSong != idSong))
    {
        seg = seg->next;
    }

    return seg;
}

///////////////FUNCIONES ARBOL DE CANCIONES//////////////////
///////////////FUNCIONES ARBOL DE CANCIONES//////////////////

///////////////FUNCIONES ARBOL DE CANCIONES//////////////////

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
    if (tree)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        showSong(tree->value);
    }
}

nodeTreeSong *searchNodeById(nodeTreeSong *treeSong, int idSong)
{

    nodeTreeSong *auxSong = NULL;
    if (treeSong)
    {
        if (idSong == treeSong->value.idSong) //--->Si lo encuentra devuelve el arbol como respuesta
            auxSong = treeSong;
        else
        {
            if (idSong > treeSong->value.idSong)                   //---->Si el dato es mayor que el dato en la raiz se busca por derecha y si es menor se busca por izquierda
                auxSong = searchNodeById(treeSong->right, idSong); // se hace llamada recursiva hasta encontrar el dato
            else
                auxSong = searchNodeById(treeSong->left, idSong); // se hace llamada recursiva hasta encontrar el dato
        }
    }
    return auxSong; //-->En caso que no encuentre el dato devuelve NULL como respuesta
}

nodeTreeSong *deleteTreeNode(nodeTreeSong *tree, int idSong)
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

nodeTreeSong *insertFromArray(stSong songArray[], nodeTreeSong *songTree, int valids, int midArray)
{
    int i = 0;
    srand(time(NULL));
    while (i < valids)
    {
        if (songTree == NULL)
        {
            songTree = insertNodeTree(songTree, songArray[midArray]);
        }
        else
        {
            songTree = insertNodeTree(songTree, songArray[rand()]);
        }
        i++;
    }
    return songTree;
}

int midArray(int valids)
{
    int mid;
    if (valids % 2 == 0)
    {
        mid = valids / 2;
    }
    else
    {
        valids++;
        mid = valids / 2;
    }
    return mid;
}

nodeTreeSong *fileToSongTree(nodeTreeSong *songTree)
{
    int totalValues = totalSongs(); // se cuenta la cantidad de canciones que hay en el archivo
    int i = 0;
    stSong arraySong[totalValues];

    fileToSongArray(arraySong, totalValues);
    songTree = selectRoot(songTree);                                     /// selecciona la raiz del arbol desde el medio del array
    songTree = nonRepetitiveInsertion(songTree, arraySong, totalValues); /// inserta sin repetir y de manera aleatoria en el arbol
    return songTree;
}

void fileToSongArray(stSong arraySong[], int totalValues)
{
    FILE *songFile;
    songFile = fopen(SONGSFILEPATH, "rb");
    int i = 0;
    if (songFile)
    {
        while (fread(&arraySong[i], sizeof(stSong), 1, songFile) > 0)
        {
            i++;
        }
    }
    fclose(songFile);
}

nodeTreeSong *selectRoot(nodeTreeSong *treeSong)
{
    FILE *songFile = fopen(SONGSFILEPATH, "rb");
    int totalValues = 0;
    totalValues = totalSongs();
    int treeRoot = totalValues / 2;
    stSong auxSong;

    if (songFile)
    {
        fseek(songFile, treeRoot * sizeof(stSong), SEEK_SET);
        fread(&auxSong, 1, sizeof(stSong), songFile);
        treeSong = insertNodeTree(treeSong, auxSong);
        fclose(songFile);
    }
    return treeSong;
}

nodeTreeSong *nonRepetitiveInsertion(nodeTreeSong *treeSong, stSong arraySong[], int totalValues)
{
    flagedSong copiedArray[totalValues];
    nodeTreeSong *auxTreeSong;
    stSong songAux;
    auxTreeSong = startTree();
    auxTreeSong = selectRoot(auxTreeSong);

    int i = 0;

    int lenght = totalValues;
    int randomPos;
    srand(time(NULL));
    while (i < totalValues)
    {
        if (arraySong[i].idSong != auxTreeSong->value.idSong)
        {
            copiedArray[i].flag = 0;
            copiedArray[i].songValue = arraySong[i];
            i++;
        }
        else
        {
            copiedArray[i].flag = 1;
            copiedArray[i].songValue = arraySong[i];
            lenght--;
            i++;
        }
    }
    i = 0;

    while (lenght > 0)
    {
        randomPos = rand() % totalValues;

        if (copiedArray[randomPos].flag == 0)
        {
            songAux = copiedArray[randomPos].songValue;
            copiedArray[randomPos].flag = 1;
            treeSong = insertNodeTree(treeSong, songAux);
            i++;
            lenght--;
        }
    }
    return treeSong;
}

int maxTimesPlayed()
{
    int maxValue = 0;
    FILE *songFile;
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
