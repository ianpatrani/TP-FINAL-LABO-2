#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED
#define USERSFILEPATH "UsersFile.bin"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userLinkedList.h"


//*****************************************************
//-----------------------------------------------------
//ESTRUCTURAS DE USUARIOS
//-----------------------------------------------------
typedef struct
{
    int idUser;
    char fullName[30];
    int keyPass[2][2]; ///matriz testigo / encriptadora / unica de c/user
    int matrixPass[2][5]; ///matriz que ingresa el usuario char convertido y almacenado en matriz de 2x2
    int birthYear;
    char gender;
    char country[20];
    int songsPlayed[30]; ///IDs de canciones reproducidas por el user
    int totalSongsPlayed; ///valitwo de songsPlayed
    int off; ///flag 0 = activo. 1 = off
    int admin; ///flag 0 = user random. 1 = user admin
}stUser;

typedef struct
{
    stUser value;
    struct node2User* next;
    struct node2User * prev;
}node2User;  ///al momento de pasar el archivo a la colecci�n, vuelca los usuarios en notwo de lista doblemente enlazada

typedef struct
{
    char word[11]; ///struct que permite en una funcion retornar una palabra
}stWord;


//-#################################################
//-                PARTE USUARIOS
//-#################################################
void addUserToFile();
void showUser();
int userValidation(,stUsuario user,int valids);
int searchUserByName(node2Player * userList,char name[]);
int totalUsers();
int searchUserById(node2Player * userList, int idUser);
node2User * loadUsersFromFile(node2User * userList);
void updateFile(node2Player * userList);
void deleteUser(node2Player * userList,int idUser);
void updateUser(node2Player,int subopciones);
stWord showPassword (stUser toShow);

///MATRICES
void showMatrix (int row, int column, int matrix[row][column]);
///muestra por pantalla cualquier matriz
void createMatrixPass (int two, int five, char pass[],  int matrixPass[two][five]);
///convierte en matriz de enteros el array de caracteres (contrase�a)
int computeDeterminant (int row, int column, int matrix[row][column]);
///calcula el determinante para validar la inversion del archivo
void encryptMatrix (int two, int five,int keyPass[two][two], int decryptedMatrix[two][five], int encryptedMatrix[two][five]);
///multiplica la matriz contrasenia por la matriz testigo de cada usuario
void createKeyPass (int two, int keyPass[two][two]);
///con una semilla, crea una matriz testigo random inversible
void invertMatrix (int two, int five,int keyPass[two][two]);
///realiza operacion para invertir matriz
void decryptMatrix (int two, int five,int keyPass[two][two], int matrixPass [two][five], int decryptedMatrix[two][five]);
///con la matriz testigo y la matriz encriptada, calcula la inversa y desencripta la matriz contrasenia de cada usuario
void multiplyMatrix (int two, int five,int firstMultiple[two][two], int secondMultiple [two][five], int result[two][five]);
///realiza la operacion de multiplicar matrices entre una de 2x2 y una de 2x5 (el resultado es una de 2x5)
int checkCompatibility (int two, int five, int matrixPass[two][five], int keyPass[two][two], char toCheckPass[]);
///desencripta la matriz contrasenia, y la compara con una contrasenia ingresada convertida en matriz, retorna flag 1 si es valido
void copyMatrix (int row, int column , int copyMatrix[row][column], int originalMatrix[row][column]);
///copia una matriz en otra, para poder trabajar y guardarlas en auxiliares



#endif // USUARIOS_H_INCLUDED
