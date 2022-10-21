#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int idCancion;
    char titulo[30];
    char artista[20];
    int duracion;
    char album[20];
    int anio;
    char genero[20];
    char comentario[100];
    int eliminado; // indica 1 o 0 si la canci�n fue eliminada
} stCancion;







 typedef struct
{
    int idSong;
    char title[30];
    char artist[20];
    int duration;
    char album[20];
    int year;
    char gender[20];
    char comments[100];
    int off; // indica 1 o 0 si la canci�n fue eliminada
} stSong;

typedef struct
{
    stSong value;
    struct songListNode * next;
} songListNode;




typedef struct
{
 int idPlaylist;
 int idUsuario;
 int idCancion;
} stPlaylist;






///FUNCIONES PARA LISTA SIMPLE DE CANCIONES
//inicLista()
//crearNodoLista()
//agregarAlPrincipio()
//agregarAlFinal()
//agregarEnOrdenPorNombreDeCancion()
//mostrarLista() // modularizar
//borrarNodoPorIdCancion()

///FUNCIONES PARA �RBOL DE CANCIONES
//inicArbol ()
//crearNodoArbol ()
//insertarNodoArbol (ordenado por idCancion)
//mostrarArbol (son tres funciones, recorriendo inOrder, postOrder, preOrder) // modularizar
//borrarUnNodoArbol (buscarlo por idCancion)
//buscarCancion (por idCancion)
//
//cargarArbolDesdeArchivo(): Al inicio del sistema, deber�n cargar todas las canciones del archivo,
//sobre un �rbol binario ordenado por idCancion, de forma tal que las b�squedas se realicen de forma
//m�s eficiente.
//
//Tenga en cuenta que, seguramente, su archivo de canciones est� ordenado de forma creciente por
//idCancion y que si realiza un recorrido secuencial del archivo, la inserci�n en el �rbol no se realizar�
//de una forma �ptima. Desarrolle una funci�n (o varias) que logren realizar la inserci�n en el �rbol,
//logrando que este quede lo m�s balanceado posible.

///FUNCIONES ESTRUCTURA DE ARREGLO DE USUARIOS
//Deber�n codificar todas las funciones necesarias para administrar el TDA Arreglo de Listas, a saber
//(como m�nimo):
//agregarUsuario() // crea un nuevo usuario en el arreglo
//buscarUsuario() // busca un usuario por idUsuario y retorna la posici�n que ocupa en el arreglo
//mostrarUsuarios() // muestra todo el arreglo de listas, cada usuario con sus canciones escuchadas
//agregarCancionToUsuario() // agrega una Cancion al Usuario correspondiente
//limpiarArregloDeListas() // esta funci�n �vac�a� todo el arreglo de listas, dejando la estructura preparada
//para volver a trabajar
//persistirCancionesEscuchadas() // esta funci�n realizar� la persistencia de todas las canciones
//escuchadas en el archivo correspondiente

///FUNCIONES CANCIONES ESCUCHADAS POR CADA USUARIO
//Esta estructura da forma al archivo de canciones escuchadas por cada usuario, en cada registro se
//almacena el id del usuario, el id de la canci�n y un id autoincremental para contabilizar los registros.
//A partir de esta informaci�n, se carga el arreglo de listas, buscando los datos del usuario en el archivo
//y los datos de la canci�n en el �rbol de canciones. Para hacer esto, deber� desarrollar una serie de
//funciones que sean invocadas por la funci�n pasarDeArchivoPlaylistToADL().
//Asimismo, deber� desarrollar las funciones necesarias para hacer el trabajo inverso. A partir del arreglo
//de listas que se va cargando y actualizando en memoria, realizar la persistencia de los datos en el
//archivo de canciones escuchadas recorriendo el ADL y tomando los datos all� almacenados.
//actualizarCancionesEscuchadas().
//Codificar las funciones necesarias para persistir esta estructura en un archivo binario y las que
//necesite para la interacci�n con el sistema.

///MENU PRINCIPAL
//Men� principal
//1. Ingreso con User y Pass para administradores
//2. Ingreso con User y Pass
//3. Registrarse

int main()
{
    printf("Hello world!\n");
    return 0;
}



