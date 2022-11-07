#include "cellLib.h"




///FUNCIONES PARA LISTA SIMPLE DE CANCIONES
//inicLista()
//crearNodoLista()
//agregarAlPrincipio()
//agregarAlFinal()
//agregarEnOrdenPorNombreDeCancion()
//mostrarLista() // modularizar
//borrarNodoPorIdCancion()

///FUNCIONES PARA ÁRBOL DE CANCIONES
//inicArbol ()
//crearNodoArbol ()
//insertarNodoArbol (ordenado por idCancion)
//mostrarArbol (son tres funciones, recorriendo inOrder, postOrder, preOrder) // modularizar
//borrarUnNodoArbol (buscarlo por idCancion)
//buscarCancion (por idCancion)
//
//cargarArbolDesdeArchivo(): Al inicio del sistema, deberán cargar todas las canciones del archivo,
//sobre un árbol binario ordenado por idCancion, de forma tal que las búsquedas se realicen de forma
//más eficiente.
//
//Tenga en cuenta que, seguramente, su archivo de canciones está ordenado de forma creciente por
//idCancion y que si realiza un recorrido secuencial del archivo, la inserción en el árbol no se realizará
//de una forma óptima. Desarrolle una función (o varias) que logren realizar la inserción en el árbol,
//logrando que este quede lo más balanceado posible.

///FUNCIONES ESTRUCTURA DE ARREGLO DE USUARIOS
//Deberán codificar todas las funciones necesarias para administrar el TDA Arreglo de Listas, a saber
//(como mínimo):
//agregarUsuario() // crea un nuevo usuario en el arreglo
//buscarUsuario() // busca un usuario por idUsuario y retorna la posición que ocupa en el arreglo
//mostrarUsuarios() // muestra todo el arreglo de listas, cada usuario con sus canciones escuchadas
//agregarCancionToUsuario() // agrega una Cancion al Usuario correspondiente
//limpiarArregloDeListas() // esta función “vacía” todo el arreglo de listas, dejando la estructura preparada
//para volver a trabajar
//persistirCancionesEscuchadas() // esta función realizará la persistencia de todas las canciones
//escuchadas en el archivo correspondiente

///FUNCIONES CANCIONES ESCUCHADAS POR CADA USUARIO
//Esta estructura da forma al archivo de canciones escuchadas por cada usuario, en cada registro se
//almacena el id del usuario, el id de la canción y un id autoincremental para contabilizar los registros.
//A partir de esta información, se carga el arreglo de listas, buscando los datos del usuario en el archivo
//y los datos de la canción en el árbol de canciones. Para hacer esto, deberá desarrollar una serie de
//funciones que sean invocadas por la función pasarDeArchivoPlaylistToADL().
//Asimismo, deberá desarrollar las funciones necesarias para hacer el trabajo inverso. A partir del arreglo
//de listas que se va cargando y actualizando en memoria, realizar la persistencia de los datos en el
//archivo de canciones escuchadas recorriendo el ADL y tomando los datos allí almacenados.
//actualizarCancionesEscuchadas().
//Codificar las funciones necesarias para persistir esta estructura en un archivo binario y las que
//necesite para la interacción con el sistema.

///MENU PRINCIPAL
//Menú principal
//1. Ingreso con User y Pass para administradores
//2. Ingreso con User y Pass
//3. Registrarse

int main()
{
    int admin = 0;
    int idUser = start();
    if(idUser > 0)
    {
        admin = validAdmin(idUser);
        if (admin == 1)
        {
            adminMenu(idUser);
        }
        else
            userMenu(idUser);
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return 0;
}
