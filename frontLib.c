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
            printf("Hasta pronto!!");
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
    hidePswd(auxPass);
    getch();
    while(i < 3 && idUser == -1)
    {
        u = chkPswdCompatiblty(userAux, auxPass);
        if(u == 0)
        {
            system("cls");
            printf("Contrasenia incorrecta \(%d intentos restantes\)\n", (2 - i));
            printf("Ingrese contrasenia nuevamente\n");
            fflush(stdin);
            hidePswd(auxPass);
            getch();
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
    userList = loadListFromFile(userList);/// CARGA LA LISTA DE US
    char cControl = 's';
    while(cControl == 's')
    {
        system("cls");
        optionUserMenu(&option);
        switch(option)
        {
        case 1:
            system("cls");
            showCellNode(searchUserCellById(userList, idUser)); ///printea el user
            puts("press enter..\n");
            getch();
            break;
        case 2:
            system("cls");
            idSong = songIdValidation(); //valida el tema
            playSong(idUser, idSong);
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
            puts("press enter..\n");
            getch();
            break;
        case 5:
            system("cls");
            updateUser(idUser);
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
            puts("\n\n\nHasta pronto!!!\n");
            cControl = 'n';
            break;
        }
    }
}

void optionUserMenu (int option)
{
    system("cls");

    printf("1* Perfil\n");

    printf("2* Reproducir Cancion (ID)\n");

    printf("3* Listado de canciones disponibles \n");

    printf("4* Buscar cancion por nombre\n");

    printf("5* Modificar Usuario\n");

    printf("6* Recomendaciones hechas para vos ;) \n");

    printf("7* Cerrar sesion\n");

    scanf("%d", option);
}

void optionsAdminMenu (int option)
{
    system("cls");

    printf("1* Perfil\n");

    printf("2* Usuarios\n");

    printf("3* Canciones\n");

    printf("4* Cerrar sesion\n");

    scanf("%d", option);
}
void adminMenu (int idUser)
{
    int option;
    int idSong = 0;
    int totalMovies = 0;
    char cControl = 's';
    stCell * userList = startCellList();
    userList = loadListFromFile(userList);


    while(cControl == 's')
    {
        system("cls");
        optionsAdminMenu(&option);
        switch(option)
        {
        case 1:
            system("cls");
            showCellNode(searchUserCellById(userList, idUser));
            puts("press enter..\n");
            getch();
            break;
        case 2:
            system("cls");
            userCrud(userList);
            puts("press enter..\n");
            getch();
            break;
        case 3:
            system("cls");
            songCrud();
            puts("press enter..\n");
            getch();
            break;
        case 4:
            system("cls");
            printf("Esperamos que hayas disfrutado =)\n");
            cControl = 'n';
            break;
        }
    }
}
void userCrud (stCell * userList)
{
    int iOption = 0;
    int idUser = 0;
    int iAux = 0;

    char cControl = 's';

    while(cControl == 's')
    {
        system("cls");
        userCrudMenu(&iOption);
        switch(iOption)
        {
        case 1:
            system("cls");
            showCellList(userList);
            puts("press enter..\n");
            getch();
            break;
        case 2:
            system("cls");
            idUser = getUserIdToUpdate();
            system("cls");
            if(idUser != -1)
            {
                showCellNode(searchUserCellById(userList, idUser));
                updateUser(idUser);
                system("cls");
                showCellNode(searchUserCellById(userList, idUser));
            }
            puts("press enter..\n");
            getch();
            break;
        case 3:
            system("cls");
            addUserToFile();

            puts("press enter..\n");

            getch();
            break;
        case 4:
            system("cls");
            idUser = getUserIdToUpdate();
            iAux = deleteUser(idUser);
            if(iAux == 0)
            {

                puts("User no pudo darse de baja\n");
            }

            puts("press enter..\n");

            getch();
            break;
        case 5:
            system("cls");
            idUser = getUserIdToUpdate();
            upUser(idUser);

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

    printf("1* Listado de Usuarios\n");

    printf("2* Modificar usuario\n");

    printf("3* Alta usuario\n");

    printf("4* Baja usuario\n");

    printf("5* Reestablecer usuario\n");

    printf("6* Menu principal\n");

    scanf("%d", iOption);
}
void songCrudMenu (int iOption)
{

    printf("1* Listado de canciones\n");

    printf("2* Modificar cancion (ID)\n");

    printf("3* Alta de cancion (ID)\n");

    printf("4* Baja de cancion (ID)\n");

    printf("5* Reestablecer cancion (ID)\n");

    printf("6* Menu principal\n");

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
