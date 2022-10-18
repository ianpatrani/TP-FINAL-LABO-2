#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h> ///me deja utilizar la funcion sleep

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
    int eliminado; // indica 1 o 0 si la canción fue eliminada
} stCancion;

typedef struct
{
    int idUsuario;
    char nombreUsuario[30];
    char pass[20];
    int anioNacimiento;
    char genero;
    char pais[20];
    int eliminado; // indica 1 o 0 si el cliente fue eliminado
} stUsuario;

typedef struct
{
    stCancion c;
    struct nodoListaCancion *sig;
} nodoListaCancion;

typedef struct
{
    stUsuario usr;
    nodoListaCancion *listaCanciones;
} stCelda;

typedef struct
{
    int idPlaylist;
    int idUsuario;
    int idCancion;
} stPlaylist;

/// FUNCIONES STCANCION
int idClienteNuevo(char archivo[]);
void altaDeCancion(char archivo[]);
void bajaDeCancion(char archivo[]);
void modificarCancion(char archivo[]);
int consultarSiExisteCancion(char archivo[], char tituloCancion[]);
void listarTodasLasCanciones(char archivo[]);

int main()
{
    char usuario[20];
    char password[20];

    printf("\t MENU PRINCIPAL \n");
    printf("\t1. Ingreso con User y Pass para administradores\n");
    printf("\t2. Ingreso con User y Pass para usuarios\n");
    printf("\t3. Registrarse\n");

    return 0;
}

int idClienteNuevo(char archivo[])
{
    FILE *archivito;
    archivito = fopen(archivo, "rb");
    int i = 0;
    if (archivito != NULL)
    {
        fseek(archivito, sizeof(stCancion), SEEK_END);
        i = ftell(archivito) / sizeof(stCancion);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
    return i++;
}

void altaDeCancion(char archivo[])
{
    stCancion cancion;
    FILE *archivito;
    archivito = fopen(archivo, "ab");

    if (archivito != NULL)
    {
        cancion.idCancion = idClienteNuevo(archivo);

        do
        {
            printf("Ingrese titulo: ");
            fflush(stdin);
            scanf("%s", &cancion.titulo);
        } while (strlen(cancion.titulo) > 30);
        do
        {
            printf("Ingrese artista: ");
            fflush(stdin);
            scanf("%s", &cancion.artista);
        } while (strlen(cancion.artista) > 30);
        do
        {
            printf("Ingrese duracion: ");
            fflush(stdin);
            scanf("%.2f", &cancion.duracion);
        } while (cancion.duracion <= 0);

        do
        {
            printf("Ingrese album: ");
            fflush(stdin);
            scanf("%s", &cancion.album);
        } while (strlen(cancion.album) > 30);

        do
        {
            printf("Ingrese anio: ");
            fflush(stdin);
            scanf("%i", &cancion.anio);
        } while (cancion.anio != 0);

        do
        {
            printf("Ingrese genero: ");
            fflush(stdin);
            scanf("%s", &cancion.genero);
        } while (strlen(cancion.genero) > 30);

        do
        {
            printf("Ingrese comentario: ");
            fflush(stdin);
            scanf("%s", &cancion.comentario);
        } while (strlen(cancion.comentario) <= 100);

        cancion.eliminado = 1;

        fwrite(&cancion, sizeof(stCancion), 1, archivito);
        fclose(archivito);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
}

void bajaDeCancion(char archivo[])
{
    stCancion cancion;
    FILE *archivito;
    archivito = fopen(archivo, "r+b");
    int aux = 0;
    char ok = 's';
    char idBaja;

    printf("Ingrese el id de la cancion que quiere dar de baja\n");
    fflush(stdin);
    scanf("%d", idBaja);

    if (archivito != NULL && ok == 's')
    {
        while (aux == 0 && (fread(&cancion, sizeof(stCancion), 1, archivito) > 0))
        {

            if (cancion.idCancion == idBaja)
            {
                cancion.eliminado = 0;
                fseek(archivito, (-1) * sizeof(stCancion), SEEK_CUR);
                fwrite(&cancion, sizeof(stCancion), 1, archivito);
                aux = 1;
            }
        }
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
    fclose(archivito);
}

void modificarCancion(char archivo[])
{
    stCancion cancion;
    FILE *archivito;
    archivito = fopen(archivo, "r+b");
    int id;
    int eleccion;

    printf("Ingrese id de la cancion:\n");
    scanf("%d", &id);
    system("cls");

    puts("Opcion 1 - titulo");
    puts("Opcion 2 - artista");
    puts("Opcion 3 - duracion");
    puts("Opcion 4 - album");
    puts("Opcion 5 - anio");
    puts("Opcion 6 - genero");
    puts("Opcion 7 - comentario");
    puts("Opcion 8 - eliminado");

    printf("Ingrese eleccion:\n");
    scanf("%d", &eleccion);
    system("cls");

    if (archivito != NULL)
    {
        while (fread(&cancion, sizeof(stCancion), 1, archivito) > 0)
        {

            if (cancion.idCancion == id)
            {
                switch (eleccion)
                {
                case 0:
                    printf("\nIngrese nuevo titulo:");
                    fflush(stdin);
                    scanf("%s", &cancion.titulo);
                    break;
                case 1:
                    printf("\nIngrese nuevo artista:");
                    fflush(stdin);
                    scanf("%s", &cancion.artista);
                    break;
                case 3:
                    printf("\nIngrese nueva duracion: ");
                    fflush(stdin);
                    scanf("%s", &cancion.duracion);
                    break;
                case 4:
                    printf("\nIngrese nuevo album: ");
                    fflush(stdin);
                    scanf("%s", &cancion.album);
                    break;
                case 5:
                    printf("\nIngrese nuevo anio: ");
                    fflush(stdin);
                    scanf("%d", &cancion.anio);
                    break;
                case 6:
                    printf("\nIngrese nuevo genero: ");
                    fflush(stdin);
                    scanf("%s", &cancion.genero);
                    break;
                case 7:
                    printf("\nIngrese nuevo comentario: ");
                    fflush(stdin);
                    scanf("%s", &cancion.comentario);
                    break;
                case 8:
                    printf("\nIngrese eliminado: ");
                    fflush(stdin);
                    scanf("%d", &cancion.eliminado);
                    break;
                }

                fseek(archivito, (-1) * sizeof(stCancion), SEEK_CUR);
                fwrite(&cancion, sizeof(stCancion), 1, archivito);
                fseek(archivito, sizeof(stCancion), SEEK_END);
            }
        }
    }
    fclose(archivito);
}

int consultarSiExisteCancion(char archivo[], char tituloCancion[])
{
    FILE *archivito;
    stCancion cancion;
    archivito = fopen(archivo, "rb");
    int resultado = 1;

    if (archivito != NULL)
    {
        while (fread(&cancion, sizeof(stCancion), 1, archivito) > 0)
        {
            resultado = strcmp(cancion.titulo, tituloCancion);

            if (resultado == 0)
            {
                printf("Ya existe cancion\n");
            }
        }
    }
    return resultado;
}

void listarTodasLasCanciones(char archivo[])
{
    FILE *archivito;
    stCancion cancion;
    archivito = fopen(archivo, "rb");
    int i = 0;

    if (archivito != NULL)
    {
        while (fread(&cancion, sizeof(stCancion), 1, archivito) > 0)
        {
            printf("\n Registro numero %d", i++);
            puts("\n-------------------------------------");
            printf("\n IdCancion: %d", cancion.idCancion);
            printf("\n Titulo: %s", cancion.titulo);
            printf("\n Artista: %s", cancion.artista);
            printf("\n Duracion: %.2f", cancion.duracion);
            printf("\n Album: %s", cancion.album);
            printf("\n Anio: %d", cancion.anio);
            printf("\n Genero: %s", cancion.genero);
            printf("\n Comentario: %s", cancion.comentario);
            printf("\n Eliminado 1-Si/0-No: %d", cancion.eliminado);
            puts("\n-------------------------------------");
        }
    }
    fclose(archivito);
}
