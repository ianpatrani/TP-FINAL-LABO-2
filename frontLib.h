#include "cellLib.h"

void userProfile (int idUser);
///perdil de usuario [ruta-ID]
int validUser (char nameUser[]);
///busca usuario en archivo y retorna su id si exite o "0"[Ruta-Name]
int login ();
///menu login[ruta]
int start ();
///menu inicio [ruta]
void playMovie(int idUser, int idSong);
///Suma 1 en vistos de la pelicula y reprod y se guarda en historial de usuario
void userMenu(int idUser);
///interfaz de menu de usuario no administrador
void optionMenuUser (int option);
///opciones de printf de usuario no administrador
void optionMenuAdmin (int option);
///opciones de mostrado de la interfaz de menu de usuario administrador
void adminMenu(int idUser);
///interfaz de menu de usuario administrador administrador
void userCrud();
///alta baja y modificacion de usuarios(para administrador)
void songCrud ();
///alta baja y modificacion de peliculas(para administrador)
void userCrudMenu (int iOption);
///interfaz de menu de ABM de usuarios de administrador
void songCrudMenu(int iOption);
///interfaz de menu de ABM de peliculas de administrador
int validAdmin (char cUser[], int iId);
///validacion de tipo de usuario (admin o no)
void passW(char []);
///Le ingresa al string traido por local una password en **
///Exacamente 10 caracteres
void playing();
