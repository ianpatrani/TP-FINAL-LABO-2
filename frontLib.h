#include "cellLib.h"

int login();
///menu login

int start ();
///menu inicio

void userProfile (int idUser);
///muestra perfil del usuario en la sesion actual

int validUser (char nameUser[]);
///busca usuario en archivo y retorna su id si exite o "0"

int validAdmin (int idUser);
///return true si es admin

void playSong(int idUser, int idSong);
/// Reproduce la cancion; se guarda en el historial de usuario; crea un struct stPlaylist y lo persiste

void userMenu(int idUser);
///interfaz de menu de usuario no administrador

void optionMenuUser (int option);
///opciones de printf de usuario no administrador

void optionMenuAdmin (int option);
///opciones de mostrado de la interfaz de menu de usuario administrador

void adminMenu(int idUser);
///interfaz menu admin

void userCrud(stCell * userList);
///C(create)R(read)U(update)D(delete) de users

void songCrud ();
///C(create)R(read)U(update)D(delete) de canciones

void userCrudMenu (int iOption);
///interfaz del crud de usuarios

void songCrudMenu(int iOption);
///interfaz del crud de canciones



void hidePswd(char toShow[]);
///funcion extra que oculta los caracteres que ingresa el user en tiempo real.

void playing();
///funcion extra que simula una reproducción por pantalla

