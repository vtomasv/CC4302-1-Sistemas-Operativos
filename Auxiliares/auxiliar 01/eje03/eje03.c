/*
#===============================================================================
#|        _____           _
#|       / ____|         | |
#|  _ __ | (___  _   _ ___| |_ ___ _ __ ___
#|  | '_ \ \___ \| | | / __| __/ _ \ '_ ` _ \
#|  | | | |____) | |_| \__ \ ||  __/ | | | | |
#|  |_| |_|_____/ \__, |___/\__\___|_| |_| |_|
#|               __/ |        Prof. Luis Mateu
#|              |___/
#| - CC41B Sistemas Operativos | DCC | Universidad de Chile
#===============================================================================


# ==============================================================================
# |        Documentacion de Controles de cambio                                |
# ==============================================================================
# @author Tomas Vera <tvera@kvz.cl>
# @doc
# @copyleft 2017
# @title
# ==============================================================================
# | Historial de cambios
# ==============================================================================
# | {Cambio, ID-REQ, Fecha, Responsable}
# ==============================================================================

# ==============================================================================
#  Se captura una entreada desde la entrada
# ==============================================================================
*/
#include "nSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Funcion que crea un string aleatorio del largo indicado
char *randstring(int length);

// Crea un archivo con el nombre file+numberFile.txt
int fileGenerator(int numberFile);

// Funcion principal de entrada al programa
int nMain(){

  srand(time(0)); // Se inicializa la semilla random

  nPrintf("Cuantos archivos desea crear? \n");
  char buffer[4];
  nRead(0, buffer, 4);
  int n = atoi(buffer); // Se pide al usuario que ingrese el numero de archivos a generar

  //Se crean tantos descriptores de tareas como archivos en paralelo
  // se quieran crear.
  nTask creadoresDeArchivos[n];

  // Por cada uno de los archivos a crear se crea una tarea y se inicia
  for(int i = 0; i < n ; i++){
    creadoresDeArchivos[i] = nEmitTask(fileGenerator, i);
  }

  // Se espera que las tareas terminen en forma secuencial
  for(int i = 0; i < n ; i++){
    nWaitTask(creadoresDeArchivos[i]);
  }

}

// Genera una archivo con el nombre File(i).txt con contenido aleatorio
int fileGenerator(int numberFile){


  char * s = NULL;
  asprintf(&s, "%s%d.txt", "file", numberFile); // Se crea el nombre del archivo

  //Se abre el archivo para su posterir escritura (si no existe lo crea)
  int fileDesc = nOpen(s, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);

  // Crea un numero aleatorio de filas para el archivo.
  int lineas = rand() % 100;
  for(int i = 0; i < lineas; i++){
    char *str = (randstring)(30);
    nWrite(fileDesc, str, (unsigned)strlen(str)); // Escribe sobre el archivo
    nWrite(fileDesc, "\n", (unsigned)strlen("\n")); // Le da un enter
    nFree(str);
  }

  // Se cierra el archivo.
  nClose(fileDesc);

}


// Funcion que crea un String aleatorio
// Creditos http://codereview.stackexchange.com/questions/29198/random-string-generator-in-c
// Se modifico para que pida la memoria por medio de los comando de nSystem 
char *randstring(int length) {
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    size_t stringLen = 26*2+10+7;
    char *randomString;

    randomString = nMalloc(sizeof(char) * (length +1));

    if (!randomString) {
        return (char*)0;
    }

    unsigned int key = 0;

    for (int n = 0;n < length;n++) {
        key = rand() % stringLen;
        randomString[n] = string[key];
    }

    randomString[length] = '\0';

    return randomString;
}
