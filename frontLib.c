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
            gotoxy(30,  20);
            printf("Hasta prontos!!!");
            cControl = 'n';
            break;
        }
    }
    return iIterator;
}
void startMenu (int iOption)
{
    gotoxy(30,  20);
    printf("*--------------*\n");
    gotoxy(30, 21);
    printf("1*Iniciar sesion\n");
    gotoxy(30, 22);
    printf("2*Registrarse\n");
    gotoxy(30, 23);
    printf("3*Salir\n");
    gotoxy(30, 24);
    printf("*--------------*\n");
    gotoxy(30, 25);
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
    int idUser = 0;
    ///idUser sera retornado con el iD del usuario que ingreso
    //indica usuario correcto
    gotoxy(30, 20);
    printf("Ingrese Usuario:\n");
    fflush(stdin);
    gotoxy(30, 21);
    gets(userName);
    userAux = searchUserFileByName(userName);
    while((strcmpi(userAux.fullName, userName)) != 0)
    {
        system("cls");
        gotoxy(30, 20);
        printf("Usuario inexistente, ingrese nuevamente:\n");
        fflush(stdin);
        gotoxy(30, 21);
        gets(userName);
        userAux = searchUserFileByName(userName);
        system("cls");
    }
    system("cls");
    gotoxy(30, 20);
    printf("Ingrese su contrasenia:\n");
    gotoxy(30, 21);
    passW(auxPass);
    getch();
    while(i < 3 && idUser == 0)
    {

        u = checkCompatibility(2, 5, userAux.matrixPass, userAux.keyPass, auxPass);
        if(u == 0)
        {
            system("cls");
            gotoxy(30, 20);
            printf("Contrasenia incorrecta \(%d intentos restantes\)\n", (2 - i));
            gotoxy(30, 21);
            printf("Ingrese contrasenia nuevamente\n");
            gotoxy(30, 22);
            passW(auxPass);
            getch();
            i++;
        }
        else
        {
            system("cls");
            gotoxy(30, 20);
            printf("Login Exitoso\n");
            idUser = validUser(userName);
        }
    }

    if(i == 3 & idUser == 0)
    {
        system("cls");
        gotoxy(30, 20);
        printf("Intentos de login agotados...\n");
        gotoxy(30, 21);
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
    if(pFile)
    {
        fseek(pFile, (idUser -1)  * (sizeof(stUser)), SEEK_SET);
        fread(&userAux, sizeof(stUser), 1, userFile);
        showAnUser(userAux);///////////////////////////////////////////////agregar mostrar 1
        if(fclose(pFile))
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
        gotoxy(30,22);
        puts("***Reproduccion en curso***\n");
        gotoxy(i-1,24);
        putchar(255);
        gotoxy(i,24);
        printf("%% %d \n", i);
        gotoxy(i,25);
        putchar(219);
        Sleep(50);
        i++;
    }
}


void userMenu (int idUser)
{
    int option;
    int idSong = 0;



    int totalIdM = 0;
    char cControl = 's';
    while(cControl == 's')
    {
        system("cls");
        optionMenuUser(&option);
        switch(option)
        {
        case 1:
            system("cls");
            userProfile(idUser);
            puts("press enter..\n");
            getch();
            break;
        case 2:
            system("cls");
            idSong = getId();
            playSong(idUser, idSong);
            ///reproducir peli
            break;
        case 3:
            system("cls");
            showSongFile();
            puts("press enter..\n");
            getch();
            break;
        case 4:
            system("cls");
            searc(cMovies);
            gotoxy(30, 25);
            puts("press enter..\n");
            getch();
            break;
        case 5:
            system("cls");
            updateFileUser(cUser, idUser);
            gotoxy(30, 25);
            puts("press enter..\n");
            getch();
            break;
        case 6:
            system("cls");
            recomend(cUser, cMovies, idUser);
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

void optionMenuUser (int option)
{
    system("cls");
    gotoxy(30, 20);
    printf("1* Perfil\n");
    gotoxy(30, 21);
    printf("2* Reproducir Cancion (ID)\n");
    gotoxy(30, 22);
    printf("3* Listado de canciones disponibles\n");
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
void optionMenuAdmin (int option)
{
    system("cls");
    gotoxy(30, 20);
    printf("1* Perfil\n");
    gotoxy(30, 21);
    printf("2* Usuarios\n");
    gotoxy(30, 22);
    printf("3* Peliculas\n");
    gotoxy(30, 23);
    printf("4* Cerrar sesion\n");
    gotoxy(30, 24);
    scanf("%d", option);
}
void menuAdmin (char cMovies[], char cUser[], int idUser)
{
    int option;
    int idUserM=0;
    int totalIdM=0;
    char cControl = 's';
    while(cControl == 's')
    {
        system("cls");
        optionMenuAdmin(&option);
        switch(option)
        {
        case 1:
            system("cls");
            userProfile(cUser, idUser);
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 2:
            system("cls");
            abmUser(cUser);
            puts("press enter..\n");
            getch();
            break;
        case 3:
            system("cls");
            abmMovie(cMovies);
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
void abmUser (char cUser[])
{
    int iOption = 0;
    int idUser = 0;
    int totalId=0;
    char cControl = 's';

    while(cControl == 's')
    {
        system("cls");
        menuAbmUser(&iOption);
        switch(iOption)
        {
        case 1:
            system("cls");
            showUsers(cUser);
            puts("press enter..\n");
            getch();
            break;
        case 2:
            system("cls");
            idUser = validIdU(cUser);
            system("cls");
            userProfile(cUser, idUser);
            updateFileUser(cUser, idUser);
            ///modifica un usuario
            system("cls");
            userProfile(cUser, idUser);
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 3:
            system("cls");
            loadUser(cUser);
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 4:
            system("cls");
            validIdU(cUser);
            kickUser(cUser, idUser);
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 5:
            system("cls");
            validIdU(cUser);
            upUser(cUser, idUser);
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
void abmMovie (char cMovies[])
{
    int iOption = 0;
    int idUserM = 0;
    char cControl = 's';
    int totalIdM=0;

    while(cControl == 's')
    {
        system("cls");
        menuAbmMovie(&iOption);
        switch(iOption)
        {
        case 1:
            system("cls");
            showMovies(cMovies);
            puts("press enter..\n");
            getch();
            break;
        case 2:
            system("cls");
            idUserM = validIdM(cMovies);
            system("cls");
            updateFile(cMovies, idUserM);
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 3:
            system("cls");
            loadFileMovie(cMovies);
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 4:
            system("cls");
            idUserM = validIdM(cMovies);
            kickMovie(cMovies, idUserM);
            ///baja de pelicula
            gotoxy(30, 25);
            puts("press enter..\n");
            gotoxy(30, 26);
            getch();
            break;
        case 5:
            system("cls");
            idUserM = validIdM(cMovies);
            upMovie(cMovies, idUserM);
            /// reestablece pelicula
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
void menuAbmUser (int iOption)
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
void menuAbmMovie (int iOption)
{
    gotoxy(30, 20);
    printf("1* Listado de Peliculas\n");
    gotoxy(30, 21);
    printf("2* Modificar pelicula (ID)\n");
    gotoxy(30, 22);
    printf("3* Alta de peliculas (ID)\n");
    gotoxy(30, 23);
    printf("4* Baja pelicula (ID)\n");
    gotoxy(30, 24);
    printf("5* Reestablecer pelicula (ID)\n");
    gotoxy(30, 25);
    printf("6* Menu principal\n");
    gotoxy(30, 26);
    scanf("%d", iOption);
}
int validAdmin (char cUser[], int idUser)
{
    FILE * pFile;
    stUsuario stUser;
    if ((pFile=fopen(cUser, "rb") ))
    {
        fseek(pFile, (idUser - 1) * sizeof(stUsuario), 0);
        fread(&stUser, sizeof(stUsuario), 1, pFile);
        if((fclose(pFile) == -1))
        {
            printf("*ERROR*\n");
            printf("El archivo no se cerro correctamente\n");
        }
    }
    else
    {
        printf("*ERROR*");
        printf("El archivo no se abrio correctamente\n");
    }

    return stUser.admin;
}


