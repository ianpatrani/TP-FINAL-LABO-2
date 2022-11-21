#include "userLib.h"

void showPassword(stUser toShow)
{
    int iterator = 0;
    int j;
    int k;
    int decryptedPass[2][5];
    decryptMatrix(2, 5, toShow.keyPass, toShow.matrixPass, decryptedPass);
    stWord pass;

    for (j = 0; j < 2; j++)
    {
        for (k = 0; k < 5; k++)
        {
            pass.word[iterator] = (char)decryptedPass[j][k];
            iterator++;
        }
    }
    puts(pass.word);
}

void addUserToFile()
{
    FILE *userFile;
    stUser userAux;
    userFile = fopen(USERSFILEPATH, "ab");
    if (!userFile)
    {
        printf("Error en crear el fileUser / ruta invalida \n");
    }
    else
    {
        userAux = createOneUser();
        fwrite(&userAux, sizeof(stUser), 1, userFile);
        printf("Se ha registrado correctamente el usuario\n");
        fclose(userFile);
    }
}


void showAnUser (stUser toShow)
{
    stWord auxPass;
    printf("__________________________________\n");
    printf("%s", toShow.fullName);
    printf("\t\tID:%d\n", toShow.idUser);
    if (toShow.off == 1)
    {
        printf("\t*DADO DE BAJA*\n");
    }
    printf("__________________________________\n");
    printf("Anio de nacimiento:\t%d\n", toShow.birthYear);
    printf("Pais: \t\t\t%s\n", toShow.country);
    if(toShow.gender == 'm' || 'M')
    {
        printf("Genero: \t\tMASCULINO\n");
    }
    else
    {
        printf("Genero: \t\tFEMENINO\n");
    }
    printf("Password: \t\t");
    showPassword(toShow);


    printf("Total de cacnciones escuchadas: %d \n\n", toShow.totalSongsPlayed);
}

stUser createOneUser()
{
    stUser userAux;
    int idUser = totalUsers();/// funcion que trae cantidad de usuarios cargados en el fileUser y autoinrementa 1
    int iterator = 0;
    int checkName = 0;


    char passAux[11];        /// auxiliar de contrasenia
    char passAux1[11];       /// auxiliar de verificacion de contraseña
    int decryptedPass[2][5]; /// cambia la contraseña q ingresa el userAux a una matriz de enteros
    int keyPass[2][2];       /// matriz encriptadora
    int encryptedPass[2][5]; /// matriz Encriptada
    // CARGA DE 1 USUARIO POR TECLADO
    userAux.idUser = idUser;
    userAux.admin = 0;
    printf("Ingrese un nombre de usuario \n");
    fflush(stdin);
    gets(userAux.fullName);
    // VALIDO SI EL NOMBRE DE USER YA EXISTE
    checkName = nameValidation(userAux.fullName);
    while (checkName == 1)
    {
        printf("El nombre ya existe\n");
        printf("Ingrese otro\n");
        fflush(stdin);
        gets(userAux.fullName);
        checkName = nameValidation(userAux.fullName); // VALIDO NUEVAMENTE EL NOMBRE
    }
    do
    {
        system("cls");
        printf("Ingrese su password (10 caracteres obligatoriamente):\n");
        fflush(stdin);
        gets(passAux);
        printf("Una vez mas por favor :) \n");
        fflush(stdin);
        gets(passAux1);
    }
    while (strcmpi(passAux, passAux1) != 0);


    while (strlen(passAux) != (10 * sizeof(char)))
    {
        system("cls");
        printf("Recuerde la contrasenia debe tener 10 caracteres, ingrese otra por favor:\n");
        gets(passAux);
        getch();
    }

    createMatrixPass(2, 5, passAux, decryptedPass);          /// pasa pswd a matriz de enteros
    createKeyPass(2, keyPass);/// crea matriz testigo
    copyMatrix(2, 2, userAux.keyPass, keyPass);             /// copia la matriz encriptadora del userAux en su campo del userAux
    encryptMatrix(2, 5, keyPass, decryptedPass, encryptedPass); /// encripta la contraseña
    copyMatrix(2, 5, userAux.matrixPass, encryptedPass);         /// fileUserva la contrasenia encriptada en el campo pass de userAux




    printf("Ingrese anio de nacimiento\n");
    scanf("%d", &userAux.birthYear);

    printf("Ingrese Genero\n");
    printf("M: Masculino\n");
    printf("F: Femenino\n");
    printf("X: Otro\n");

    fflush(stdin);
    scanf("%c", &userAux.gender);

    printf("Ingrese pais de nacimiento\n");
    fflush(stdin);
    gets(userAux.country);
    userAux.totalSongsPlayed = 0;
    userAux.off = 0;

    while (iterator < 30)
    {
        userAux.songsPlayed[iterator] = -1;
        iterator++;
    }

    return userAux;
}



//-----------------------------------------------------
// A.1)FUNCION ADICIONAL QUE VALIDA SI EL USER EXISTE
//-----------------------------------------------------

int nameValidation(char toCheck[])
{
    int flag = -1;
    flag = searchUserByName(toCheck);
    return flag;
}

//-----------------------------------------------------
// FUNCION BAJA DE USERS REGISTRADOS EN EL ARCHIVO /
//-----------------------------------------------------

int deleteUser(int idUser)
{
    FILE * userFIle = fopen(USERSFILEPATH, "r+b");
    int pos = 0, flag = 0;
    stUser userAux;
    if (userFIle)
    {
        pos = searchUserById(idUser);                 /// busco la pos del user en el archivo por id.
        fseek(userFIle, pos * sizeof(stUser), 0);     /// busco en el archivo
        fread(&userAux, sizeof(stUser), 1, userFIle); /// escribo en el aux de persona
        userAux.off = 1;
        flag = 1;
    }
    fclose(userFIle);
    return flag;
}

void upUser(int idUser)
{
    FILE * fileUser;
    stUser userAux;
    if((fileUser = fopen(USERSFILEPATH, "r+b")))
    {
        fseek(fileUser, (idUser - 1) * (sizeof(stUser)), SEEK_SET);
        fread(&userAux, sizeof(stUser), 1, fileUser);
        if(userAux.off == 1)
        {
            userAux.off = 0;
            fseek(fileUser, (idUser - 1) * (sizeof(stUser)), SEEK_SET);
            fwrite(&userAux, sizeof(stUser), 1, fileUser);
        }
        else
        {
            system("cls");
            printf("El usuario ya se encuentra dado de alta\n");
        }
    }
}

int searchUserById(int idUser)
{
    FILE * userFile = fopen(USERSFILEPATH, "rb");
    int pos = -1, iterator = 0, flag = 0;
    stUser userAux;
    if(userFile)
    {
        while(!feof(userFile) && flag == 0)
        {
            fread(&userAux,sizeof(stUser),1,userFile);
            if(!feof(userFile))
            {
                if(idUser == userAux.idUser)
                {
                    pos = iterator;
                    flag = 1;
                }
                else
                {
                    iterator++;
                }
            }
        }
    }
    fclose(userFile);
    return pos;
}


nodeUser * loadUsersFromFile(nodeUser * userList)
{
    FILE *fileUser;
    nodeUser * auxNode;
    stUser userAux;
    fileUser = fopen(USERSFILEPATH, "r+b");

    if (fileUser)
    {
        while (!feof(fileUser))
        {
            fread(&userAux, sizeof(stUser), 1, fileUser);

            auxNode = createUserNode(userAux);

            userList = addLast(userList, auxNode);
        }
        fclose(fileUser);
    }
    else
    {
        printf("El fileUser no existe / error de lectura!!\n");
    }

    return userList;
}

void showUsers(nodeUser *userList)
{
    userList = loadUsersFromFile(userList);
    showUserList(userList);
}


int getUserIdToUpdate ()
{
    int idUser;
    char cControl = 's';
    int total = totalUsers();

    system("cls");
    printf("Ingrese el ID del usuario que desea modificar \n");
    scanf("%d", &idUser);
    searchUserById(idUser);




    return idUser;
}

//-----------------------------------
// D.2)FUNCION QUE BUSCA USER POR ID
//-----------------------------------

stUser searchUserFileById(int idUser)
{
    FILE *fileUser = fopen(USERSFILEPATH, "rb");
    stUser userAux;
    if (fileUser)
    {
        while (!feof(fileUser))
        {
            fread(&userAux, sizeof(stUser), 1, fileUser);

            if (idUser == userAux.idUser)
            {
                fclose(fileUser);
                return userAux;
            }
        }
    }
    fclose(fileUser);
}

stUser searchUserFileByName (char userName[])
{
    FILE * fileUser = fopen(USERSFILEPATH, "rb");

    int iterator = 0;
    stUser userAux;
    if (fileUser)
    {
        while (!feof(fileUser) && (strcmpi(userAux.fullName, userName) != 0))
        {
            fread(&userAux, sizeof(stUser), 1, fileUser);
        }
    }
    fclose(fileUser);
    return userAux;
}

int searchUserByName(char fullName[])
{
    FILE * fileUser = fopen(USERSFILEPATH, "rb");
    int flag = -1;
    stUser userAux;
    if (fileUser)
    {
        while (!feof(fileUser) && (flag == -1))
        {
            fread(&userAux, sizeof(stUser), 1, fileUser);
            if (strcmpi(userAux.fullName, fullName) == 0)
            {
                flag = 1;
            }
        }
    }
    fclose(fileUser);
    return flag;
}

//-----------------------------------------------
//------------------------------------------------
// D.4)FUNCION QUE RETORNA LA  CANTIDAD DE REGISTROS VALIDOS EN EL fileUser
//------------------------------------------------
int totalUsers()
{
    int total = 0;
    FILE * fileUser;
    stUser userAux;
    fileUser = fopen(USERSFILEPATH, "r+b");

    if (fileUser) // EN CASO DE DAR OK EN LA LECTURA DEVUELVE LA CANTIDAD EXACTA DE USUARIOS EN EL fileUser
    {
        while (fread(&userAux, sizeof(stUser), 1, fileUser) > 0)
        {
            total++;
        }
        fclose(fileUser);
    }
    return total;
}
//-***************************************************************************************
// FUNCION DE ACTUALIZACION DE USUARIOS
//------------------------------------------
int saveUserList(nodeUser * userList)
{
    int flag = 0; ///devuelve lo que devuelve fwrite, sirve para validar escritura
    FILE *fileUser;
    fileUser = fopen(USERSFILEPATH, "wb");
    if (fileUser)
    {
        while (userList)
        {
            flag = fwrite(&userList->value, sizeof(stUser), 1, fileUser);
            userList = userList->next;
        }
        fclose(fileUser);
    }
    return flag;
}

//---------------------------------------
// FUNCION QUE MODIFICA UN USUARIO
//----------------------------------------

void updateUser(int idUser)
{
    FILE * fileUser = fopen(USERSFILEPATH, "r+b");
    stUser userAux;
    int keyPass[2][2];
    int decryptedMatrix[2][5];
    int encryptedMatrix[2][5];
    stWord passAuxWord;
    char passAux[15];
    int fieldOption = 0;
    char newName[20];
    int posInFile = searchUserById(idUser);
    if (fileUser)
    {
        fseek(fileUser, posInFile * sizeof(stUser), 0);
        fread(&userAux, sizeof(stUser), 1, fileUser);
        if (idUser == userAux.idUser)
        {
            do
            {
                printf("1.Nombre de usuario: %s\n", userAux.fullName);
                printf("Password: ");
                showPassword(userAux);
                printf("\n3.Nacimiento: %d\n", userAux.birthYear);
                printf("4.Genero: %c\n", userAux.gender);
                printf("5.Pais: %s\n", userAux.country);
                printf("6. Switch admin \n");

                printf("\n\nEscriba el numero del campo que desea modificar o 7 para salir :");
                scanf("%d", &fieldOption);

                switch (fieldOption)
                {
                case 1:
                    printf("Ingrese nuevo nombre: ");
                    fflush(stdin);
                    gets(newName);
                    if (nameValidation(newName) == 0)
                    {
                        strcpy(userAux.fullName, newName);
                    }
                    else
                    {
                        printf("\nEl nombre elegido ya esta en uso.");
                    }
                    break;

                case 2:
                    printf("\nIngrese Pass: ");
                    fflush(stdin);
                    gets(passAux);
                    createMatrixPass(2, 5, passAux, decryptedMatrix);
                    encryptMatrix(2, 5, userAux.keyPass, decryptedMatrix, encryptedMatrix);
                    copyMatrix(2, 5, userAux.matrixPass, encryptedMatrix);
                    break;

                case 3:
                    printf("\nIngrese anio de nacimiento:");
                    scanf("%d", &userAux.birthYear);
                    break;

                case 4:
                    printf("\nIngrese genero:");
                    fflush(stdin);
                    scanf("%c", &userAux.gender);
                    break;

                case 5:
                    printf("\nIngrese pais:");
                    fflush(stdin);
                    gets(userAux.country);
                    break;
                case 6:
                    printf("Esta switcheando el admin del user \n");
                    int admn = validAdmin(userAux.idUser);
                    printf("%d", admn);
                    getch();
                    if (admn == 0)
                    {
                        userAux.admin = 1;
                    }
                    else
                    {
                        printf("aqui bebe \n");
                        userAux.admin = 0;
                    }
                }
            }
            while (fieldOption != 7);

            fseek(fileUser, (posInFile) * sizeof(stUser), 0);
            fwrite(&userAux, sizeof(stUser), 1, fileUser);
            fclose(fileUser);
        }
        else
        {
            printf("El usuario no existe \n");
        }
    }
}


nodeUser * startUserList()
{
    return NULL;
}

nodeUser * createUserNode (stUser user)
{
    nodeUser * aux = (nodeUser*) malloc(sizeof(nodeUser));
    aux->value = user;
    aux->next = NULL;
    return aux;
}

nodeUser * addFirst(nodeUser * userList, nodeUser * toAdd)
{

    if (!userList)
    {
        userList = toAdd;
    }
    else
    {
        toAdd->next = userList;
        userList = toAdd;
    }
    return userList;
}




nodeUser * searchLastUser(nodeUser * userList) ///retorna el ultimo usuario, de manera recursiva
{
    nodeUser * aux = NULL;

    if(userList)
    {
        if(userList->next == NULL)
        {
            aux = userList;
        }
        else
        {
            aux = searchLastUser(userList->next);
        }
    }
    return aux;
}

nodeUser * addLast(nodeUser * userList, nodeUser * toAdd)
{
    if(!userList)
    {
        userList = toAdd;
    }
    else
    {
        nodeUser * last = searchLastUser(userList);
        last->next = toAdd;
    }
    return userList;
}


nodeUser * insertUser(nodeUser * userList, nodeUser * toInsert)
{
    if(!userList)
    {
        userList = toInsert;
    }
    else if ((toInsert->value.idUser) < (userList->value.idUser))
    {
        userList = addFirst(userList, toInsert);
    }
    else
    {

        nodeUser * prev = userList;
        nodeUser * next = userList;

        while(next && (next->value.idUser < toInsert->value.idUser))
        {
            prev = next;
            next = next->next;
        }
        prev->next = toInsert;
        toInsert->next = next;
    }
    return userList;
}

nodeUser * deleteNode(nodeUser * userList, int idUser)
{
    nodeUser * prev = NULL;
    nodeUser * next = NULL;

    if(userList)
    {
        if(userList->value.idUser == idUser)
        {
            nodeUser * toDelete = userList;
            userList = userList->next;
            free(toDelete);
        }
        else
        {
            next = userList->next;
            while(next && next->value.idUser != idUser)
            {
                prev = next;
                next = next->next;
            }
            if(next)
            {
                prev->next = next->next; //salteo el nodo que quiero eliminar.
                free(next); //elimino el nodo.
            }
        }
    }
    return userList;

}


nodeUser * deleteFirst (nodeUser * userList)
{
    nodeUser * aux = userList;
    if (userList)
    {
        userList = userList->next;
        free(aux);
    }
    return userList;
}




void showUserList(nodeUser * toShow) ///recursiva
{
    if (toShow)
    {
        showAnUser(toShow->value);
        showUserList(toShow->next);

    }
}



/// MATRICES

void showMatrix(int row, int column, int matrix[row][column])
{
    int i;
    int u;
    int aux;

    for (i = 0; i < row; i++)
    {
        for (u = 0; u < column; u++)
        {
            printf("[%d] ", matrix[i][u]);
        }
        printf("\n");
    }
}

void multiplyMatrix(int two, int five, int firstMultiple[two][two], int secondMultiple[two][five], int result[two][five])
{

    int i = 0;
    int u;
    int q = 1;

    for (u = 0; u < five; u++)
    {
        result[i][u] = (firstMultiple[i][i] * secondMultiple[i][u]) + (firstMultiple[i][q] * secondMultiple[q][u]);

        result[q][u] = (firstMultiple[q][i] * secondMultiple[i][u]) + (firstMultiple[q][q] * secondMultiple[q][u]);
    }
}


void createMatrixPass(int two, int five, char pass[], int matrixPass[two][five])
{
    int iterator = 0;
    int j;
    int k;

    for (j = 0; j < 2; j++)
    {
        for (k = 0; k < 5; k++)
        {
            matrixPass[j][k]=(int)pass[iterator];
            iterator++;
        }
    }
}
void pasar_pswd_matriz (int dos, int cinco, char contrasenia[],  int matriz_contrasenia[dos][cinco])
{
    int j=0;
    int i;
    int u;


    for (i=0; i<2; i++)
    {
        for (u=0; u<5; u++)
        {
            matriz_contrasenia[i][u]=(int)contrasenia[j];


            j++;

        }
    }

}
int computeDeterminant(int row, int column, int matrix[row][column])
{
    int determinant = 0;
    determinant = ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    return determinant;
}


void encryptMatrix(int two, int five, int keyPass[two][two], int decryptedMatrix[two][five], int encryptedMatrix[two][five])
{
    multiplyMatrix(2, 5, keyPass, decryptedMatrix, encryptedMatrix);
}

void decryptMatrix(int two, int five, int keyPass[two][two], int matrixPass[two][five], int decryptedMatrix[two][five])
{
    invertMatrix(2, keyPass);

    multiplyMatrix(2, 5, keyPass,matrixPass, decryptedMatrix);
}

void createKeyPass(int two, int keyPass[two][two])
{
    srand(time(NULL));
    do
    {
        int aux = rand() % 100;

        keyPass[0][0] = aux;
        keyPass[0][1] = aux - 1;
        keyPass[1][0] = aux + 1;
        keyPass[1][1] = aux;
    }
    while (computeDeterminant(2, 2, keyPass) == 0);
}

void invertMatrix(int two, int keyPass[two][two])
{
    int determinant = computeDeterminant(two, two, keyPass);

    int p00 = keyPass[0][0];
    int p01 = keyPass[0][1];

    keyPass[0][0] = (keyPass[1][1])/determinant;
    keyPass[0][1] = -1*(p01)/determinant;
    keyPass[1][0] = -1*(keyPass[1][0])/determinant;
    keyPass[1][1] = (p00)/determinant;
}




int chkPswdCompatiblty(stUser toCompare, char toCheckPass[])
{
    int j;
    int k;
    int iterator = 0;
    int flag = 0;
    int toCheckMatrix[2][5];
    int decryptedMatrix[2][5];

    createMatrixPass(2, 5, toCheckPass, toCheckMatrix);
    /// crea la matriz de la contrasenia ingresada
    decryptMatrix(2, 5, toCompare.keyPass, toCompare.matrixPass, decryptedMatrix);
    for (j = 0; j < 2; j++)
    {
        for (k = 0; k < 5; k++)
        {
            if (decryptedMatrix[j][k] == toCheckMatrix[j][k])
            {
                iterator++;
            }
        }
    }
    if (iterator == 10) // es decir que coincidieron todos los chars
    {
        flag = 1; /// flag 1 == ta ok
    }
    return flag;
}

void copyMatrix(int rows, int columns, int copy[rows][columns], int original[rows][columns])
{
    int j = 0;
    int k = 0;
    for (j = 0; j < rows; j++)
    {
        for (k = 0; k < columns; k++)
        {
            copy[j][k] = original[j][k];
        }
    }
}

