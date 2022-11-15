#include "frontLib.h"

int start()
{
    int iIterator = -1;
    int iOption;
    char cControl = 's';
    while(cControl == 's')
    {
        if(iIterator == 0)
            iOption = 3;
        startMenu(&iOption);
        switch(iOption)
        {
        case 1:
            //Iniciar sesion
            system("cls");
            iIterator = login();
            cControl = 'n';
            break;
        case 2:
            //Crear una cuenta
            system("cls");
            addUserToFile();
            break;
        case 3:
            //Salir
            system("cls");
            printf("Hasta prontos!!!");
            cControl = 'n';
            break;
        }
    }
    return iIterator;
}
void startMenu (int iOption)
{

    printf("*--------------*\n");

    printf("1*Iniciar sesion\n");

    printf("2*Registrarse\n");
    printf("3*Salir\n");

    printf("*--------------*\n");

    scanf("%d", iOption);
}

int login ()
{
    int u = 0;
    stUser userAux;

    char userName[30];
    char auxPass[11];
    int encryptedMatrix [2][5];
    int decryptedMatrix[2][5];
    int i = 0;

    //contador
    int idUser = -1;
    ///idUser sera retornado con el iD del usuario que ingreso
    //indica usuario correcto

    printf("Ingrese Usuario:\n");
    fflush(stdin);

    gets(userName);
    userAux = searchUserFileByName(userName);

    while((strcmpi(userAux.fullName, userName)) != 0)
    {
        system("cls");

        printf("Usuario inexistente, ingrese nuevamente:\n");
        fflush(stdin);

        gets(userName);
        userAux = searchUserFileByName(userName);

    }
    system("cls");
    printf("Ingrese su contrasenia:\n");
    gets(auxPass);
    while(i < 3 && idUser == -1)
    {
        u = chkPswdCompatiblty(userAux, auxPass);
        if(u == 0)
        {
            system("cls");
            printf("Contrasenia incorrecta \(%d intentos restantes\)\n", (2 - i));
            printf("Ingrese contrasenia nuevamente\n");
            fflush(stdin);
            gets(auxPass);
            i++;
        }
        else
        {
            system("cls");
            printf("Login Exitoso\n");
            idUser = validUser(userName);
        }
    }

    if(i == 3 & idUser == 0)
    {
        printf("Intentos de login agotados...\n");
        printf("Intente nuevamente mas tarde\n\n\n\n");
    }

    return idUser;
}

int validUser (char userName[])
{
    stUser userAux;
    int idUser = 0;
    //Id que se retornara al login para saber que usuario ingreso
    FILE * userFile = fopen(USERSFILEPATH, "rb");
    if(userFile)
    {
        while(!feof(userFile))
        {
            fread(&userAux, sizeof(stUser), 1, userFile);
            if(!feof(userFile) && strcmpi(userName, userAux.fullName) == 0)
            {
                idUser = userAux.idUser;
            }
        }
        if(fclose(userFile))
        {
            printf("*ERROR*\n");
            printf("El archivo no se pudo cerrar correctamente\n");
        }
    }
    else
    {
        printf("*ERROR*\n");
        printf("El archivo no se pudo abrir correctamente\n");
    }
    return idUser;
}
void userProfile (int idUser)
{
    stUser userAux;
    FILE * userFile = fopen(USERSFILEPATH, "rb");
    if(userFile)
    {
        fseek(userFile, (idUser -1)  * (sizeof(stUser)), SEEK_SET);
        fread(&userAux, sizeof(stUser), 1, userFile);
        showAnUser(userAux);///////////////////////////////////////////////agregar mostrar 1
        if(fclose(userFile))
        {
            printf("*ERROR*\n");
            printf("El archivo no se pudo cerrar correctamente\n");
        }
    }
    else
    {
        printf("*ERROR*\n");
        printf("El archivo no se pudo abrir correctamente\n");
    }
}

void playing()
{
    int i = 8;

    while(i < 101)
    {
        puts("***Reproduccion en curso***\n");
        gotoxy(i-1,24);
        putchar(255);
        gotoxy(i,24);
        printf("%% %d \n", i);
        gotoxy(i,25);
        putchar(219);
        i++;
    }
}


void userMenu (int idUser)
{
    int option;
    int idSong = 0;
    stCell * userList = startCellList();/// CREA LA LISTA DE USUARIOS
    printf("TEST 1 STEP \n ");
    userList = loadListFromFile(userList);/// CARGA LA LISTA DE US
    showCellList(userList);
    stCell * userAux;

    char cControl = 's';
    while(cControl == 's')
    {
        system("cls");
        optionUserMenu(&option);
        switch(option)
        {
        case 1:
            system("cls");
            printf("TEST 2 STEP \n ");
            userAux = searchUserCellById(userList, idUser);// busca el user por id y lo almacena en la variable aux
            printf("TEST 3 STEP \n ");
            showCellNode(userAux); ///printea el user
            puts("press enter..\n");
            getch();
            break;
        case 2:
            system("cls");
            idSong = songIdValidation(); //valida el tema
            playSong(idUser, idSong); ///reproduce la peli y genera el strcut playList
            ///reproducir peli
            break;
        case 3:
            system("cls");
            showSongFile();/// muestra la lista de canciones disponibles desde el archivo
            puts("press enter..\n");
            getch();
            break;
        case 4:
            system("cls");
            findSongByName();
            gotoxy(30, 25);
            puts("press enter..\n");
            getch();
            break;
        case 5:
            system("cls");
            updateUser(idUser);
            gotoxy(30, 25);
            puts("press enter..\n");
            getch();
            break;
        case 6:
            system("cls");
            houseRecommendations(userList, idUser);
            puts("press enter..\n");
            getch();
            break;

        case 7:
            system("cls");
            gotoxy(30, 20);
            puts("\n\n\nHasta pronto!!!\n");
            cControl = 'n';
            break;
        }
    }
}

void optionUserMenu (int option)
{
    system("cls");
    gotoxy(30, 20);
    printf("1* Perfil\n");
    gotoxy(30, 21);
    printf("2* Reproducir Cancion (ID)\n");
    gotoxy(30, 22);
    printf("3* Listado de canciones disponibles por genero o por nombre\n");
    gotoxy(30, 23);
    printf("4* Buscar cancion por nombre\n");
    gotoxy(30, 24);
    printf("5* Modificar Usuario\n");
    gotoxy(30, 25);
    printf("6* Recomendaciones hechas para vos ;) \n");
    gotoxy(30, 26);
    printf("7* Cerrar sesion\n");
    gotoxy(30, 27);
    scanf("%d", option);
}
void optionsAdminMenu (int option)
{
    system("cls");
    gotoxy(30, 20);
    printf("1* Perfil\n");
    gotoxy(30, 21);
    printf("2* Usuarios\n");
    gotoxy(30, 22);
    printf("3* Canciones\n");
    gotoxy(30, 23);
    printf("4* Cerrar sesion\n");
    gotoxy(30, 24);
    scanf("%d", option);
}
void adminMenu (int idUser)
{
    int option;
    int idSong = 0;
    int totalMovies = 0;
    char cControl = 's';
    while(cControl == 's')
    {
        system("cls");
        optionsAdminMenu(&option);
        switch(option)
        {
        case 1:
            system("cls");
            userProfile(idUser);
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 2:
            system("cls");
            userCrud();
            puts("press enter..\n");
            getch();
            break;
        case 3:
            system("cls");
            songCrud();
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 4:
            system("cls");
            gotoxy(30, 20);
            printf("Gracias, vuelva prontos =)\n");
            cControl = 'n';
            break;
        }
    }
}
void userCrud ()
{
    int iOption = 0;
    int idUser = 0;
    int iAux = 0;

    char cControl = 's';
    nodeUser * userList = startUserList();
    nodeUser * auxUser;
    userList = loadUsersFromFile(userList);

    while(cControl == 's')
    {
        system("cls");
        userCrudMenu(&iOption);
        switch(iOption)
        {
        case 1:
            system("cls");
            showUsers(userList);
            puts("press enter..\n");
            getch();
            break;
        case 2:
            system("cls");
            idUser = getUserIdToUpdate();
            system("cls");
            userProfile(idUser);
            updateUser(idUser);
            system("cls");
            userProfile(idUser);
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 3:
            system("cls");
            addUserToFile();
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 4:
            system("cls");
            idUser = getUserIdToUpdate();
            iAux = deleteUser(idUser);
            if(iAux == 0)
            {
                gotoxy(30, 25);
                puts("User no pudo darse de baja\n");
            }
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 5:
            system("cls");
            idUser = getUserIdToUpdate();
            upUser(idUser);
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 6:
            system("cls");
            cControl = 'n';
            break;
        }
    }
}

void songCrud()
{
    int iOption = 0;
    int idSong = 0;
    char cControl = 's';
    int songTotal = totalSongs();


    while(cControl == 's')
    {
        system("cls");
        songCrudMenu(&iOption);
        switch(iOption)
        {
        case 1:
            system("cls");
            showSongFile();
            puts("press enter..\n");
            getch();
            break;
        case 2:
            system("cls");
            idSong = getSongId();
            system("cls");
            updateSong(idSong);
            puts("press enter..\n");
            getch();
            break;
        case 3:
            system("cls");
            loadSongToFile();
            puts("press enter..\n");
            getch();
            break;
        case 4:
            system("cls");
            idSong = getSongId();
            deleteSongFromFile(idSong);
            puts("press enter..\n");
            getch();
            break;
        case 5:
            system("cls");
            idSong = getSongId();
            upSong(idSong);
            puts("press enter..\n");
            getch();
            break;
        case 6:
            system("cls");
            cControl = 'n';
            break;
        }
    }
}

void userCrudMenu (int iOption)
{
    gotoxy(30, 20);
    printf("1* Listado de Usuarios\n");
    gotoxy(30, 21);
    printf("2* Modificar usuario\n");
    gotoxy(30, 22);
    printf("3* Alta usuario\n");
    gotoxy(30, 23);
    printf("4* Baja usuario\n");
    gotoxy(30, 24);
    printf("5* Reestablecer usuario\n");
    gotoxy(30, 25);
    printf("6* Menu principal\n");
    gotoxy(30, 26);
    scanf("%d", iOption);
}
void songCrudMenu (int iOption)
{
    gotoxy(30, 20);
    printf("1* Listado de canciones\n");
    gotoxy(30, 21);
    printf("2* Modificar cancion (ID)\n");
    gotoxy(30, 22);
    printf("3* Alta de cancion (ID)\n");
    gotoxy(30, 23);
    printf("4* Baja de cancion (ID)\n");
    gotoxy(30, 24);
    printf("5* Reestablecer cancion (ID)\n");
    gotoxy(30, 25);
    printf("6* Menu principal\n");
    gotoxy(30, 26);
    scanf("%d", iOption);
}
int validAdmin (int idUser)
{
    FILE * userFile;
    stUser userAux;
    if ((userFile = fopen(USERSFILEPATH, "rb") ))
    {
        fseek(userFile, (idUser - 1) * sizeof(stUser), 0);
        fread(&userAux, sizeof(stUser), 1, userFile);
    }
    else
    {
        printf("*ERROR*");
        printf("El archivo no se abrio correctamente\n");
    }

    return userAux.admin;
}

void hidePswd (char toShow[])
{
///Le ingresa al string traido por local una password en **
///Exacamente 10 caracteres
    int iterator = 0;
///Contador para que en la pos 10 se cree "\0"
    for(iterator = 0; iterator < 10; iterator++)
    {
        fflush(stdin),
               toShow[iterator] = getch();
        while(toShow[iterator] == 8 && iterator >= 0)
        {
            if(iterator > 0)
            {
                iterator--;
            }
            putchar(8);
            putchar(' ');
            putchar(8);
            fflush(stdin);
            toShow[iterator] = getch();
        }
        printf("*");
    }
    toShow[iterator] = '\0';
}
