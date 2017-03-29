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
# |        Documentacion de Controles de cambio                    |
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
# Busqueda en profundidad en un arbol de manera secuencial
# ==============================================================================
*/
#include "nSystem.h"
#include <time.h>
#include <stdlib.h>



// Estructura de datos que representa a un arbol
typedef struct Nodo {
  int valor;
  struct Nodo *izq;
  struct Nodo *der;

} Nodo;

int encontrado = FALSE;

/* [ Prototipos ] */
int buscaSeq1(Nodo *node, int num);
int buscaSeq2(Nodo *node, int num);
int buscaSeq3(Nodo *node, int num, int *econtrado);
int buscaSeq4(Nodo *root, int num, int *encontrado, nSem mutex);

// Inicializa un arbol con un numero al azar
Nodo* inicializarArbol()
{
  int valorR = rand() % 100;

  Nodo* root = (Nodo*)nMalloc(sizeof(Nodo));
  root->valor = valorR;
  root->der = NULL;
  root->izq = NULL;

  return root;
}



// Simulacion basica muy basica de un arbol de profundidad :: profundidad
// Es un algoritmo recursivo basic
void crearArbol(Nodo *root, int profundidad ){

  if (profundidad != 0 ){

    root->der = inicializarArbol();
    root->izq = inicializarArbol();

    crearArbol(root->izq, (profundidad - 1 ));
    crearArbol(root->der, (profundidad - 1 ));
  }

}


/*******************************************************************************
* Imprime un arbol en pantalla
********************************************************************************/
// Una forma bien simpre de imprimir un arbol
void print2DUtil(Nodo* root, int space)
{
    // Caso Base
    if (root == NULL)
        return;

    // Es el espacio que se da entre niveles
    space += 10;

    // Se procesa el hijo derecho
    print2DUtil(root->der, space);

    // Se imprime es espacio
    //  se cuentan los espacios
    nPrintf("\n");
    for (int i = 10; i < space; i++)
        nPrintf(" ");
    nPrintf("%d\n", root->valor);

    // se procesa el hijo izquierdo
    print2DUtil(root->izq, space);
}

// Wrapper de print2DUtil()
void print2D(Nodo* root)
{
   // Pasa el espacio 0 para el primer nodo
   print2DUtil(root, 0);
}


// Funcion principal que ejecuta los tres modelos de busqueda
int nMain(){
  //Semilla de random
  srand(time(0));

  // Nodo raiz para la simulacion de arboles
  Nodo* root = inicializarArbol();

  // Se procede a crear un arbol
  crearArbol(root, 5 );

  // Se pinta el arbol creado para visualizar en pantalla
  print2D(root);

  // Crea un numero al azar para buscarlo en el arbol
  int number = rand() % 100;

  // Busca en forma secuancial dentro del arbol
  // hasta que enciuentre un numero
  nPrintf("Busqueda Secuencial sin Threads \n");
  while (!buscaSeq1(root, number))
  {
    number = rand() % 100;
  }
  nPrintf("Encontro %d\n", number);


  // Busca en forma secuancial dentro del arbol
  // hasta que enciuentre un numero
  nPrintf("Busqueda Secuencial con Threads \n");
  number = rand() % 100;
  while (!buscaSeq2(root, number))
  {
    number = rand() % 100;
  }
  nPrintf("Encontro %d\n", number);

  // Busca en forma secuancial dentro del arbol
  // hasta que enciuentre un numero
  nPrintf("Busqueda Secuencial con Threads usando una variable compartida \n");
  number = rand() % 100;
  while (!buscaSeq3(root, number, &encontrado))
  {
    number = rand() % 100;
  }
  nPrintf("Encontro %d\n", number);



  // Busca en forma secuancial dentro del arbol
  // hasta que enciuentre un numero
  nPrintf("Busqueda Secuencial con Threads usando una variable compartida con semaforos \n");
  nSem sem= nMakeSem(1);

  encontrado = FALSE;
  number = rand() % 100;

  while (!buscaSeq4(root, number, &encontrado, sem))
  {
    number = rand() % 100;
  }
  nPrintf("Encontro %d\n", number);

  nDestroySem(sem);

}

/*******************************************************************************
* Busqueda secuencial en profundidad un arbol binario
********************************************************************************/
int buscaSeq1(Nodo *root, int num){

  //Preguntamos si el root no es nulo (no lo econtro)
  if(root !=  NULL ){
    if(root->valor  == num){
      return TRUE;
    }
    else {
      return buscaSeq1(root->izq, num) || buscaSeq1(root->der, num);
    }
  }
  else{
    return FALSE;
  }

}

/*******************************************************************************
* Busqueda secuencial en profundidad un arbol binario
********************************************************************************/
int buscaSeq2(Nodo *root, int num){

  //Preguntamos si el root no es nulo (no lo econtro)
  if(root !=  NULL){
    if(root->valor  == num){ // Si el valor es igual al buscado lo encontramos
      return TRUE;
    }
    else {
      // Se crean dos threads para buscar en paralelo 
      nTask izqThread = nEmitTask(buscaSeq2,root->izq, num);
      nTask derThread = nEmitTask(buscaSeq2,root->der, num);
      int izqResultado = nWaitTask(izqThread);
      int derResultado = nWaitTask(derThread);
      return izqResultado || derResultado;
    }
  }
  else{
    return FALSE;
  }

}


/*******************************************************************************
* Busqueda secuencial en profundidad un arbol binario | no tan seguro
********************************************************************************/
int buscaSeq3(Nodo *root, int num, int *termina){
  //Preguntamos si el root no es nulo (no lo econtro)
  if(root !=  NULL && !*termina){
    if(root->valor  == num){
      *termina = TRUE;
      return TRUE;
    }
    else {
      nTask izqThread = nEmitTask(buscaSeq3,root->izq, num, termina);
      nTask derThread = nEmitTask(buscaSeq3,root->der, num, termina);
      int izqResultado = nWaitTask(izqThread);
      int derResultado = nWaitTask(derThread);
      return izqResultado || derResultado;
    }
  }
  else{
    return *termina;
  }

}

/*******************************************************************************
* Busqueda secuencial en profundidad un arbol binario con semaforos | seguro
********************************************************************************/
int buscaSeq4(Nodo *root, int num, int *termina, nSem mutex){
  //Preguntamos si el root no es nulo (no lo econtro)
  if(root !=  NULL && !*termina ){
    if(root->valor  == num){
      nWaitSem(mutex);
        *termina = TRUE;
      nSignalSem(mutex);
      return TRUE;
    }
    else {

      nTask izqThread = nEmitTask(buscaSeq4,root->izq, num, termina, mutex);
      nTask derThread = nEmitTask(buscaSeq4,root->der, num, termina, mutex);
      int izqResultado = nWaitTask(izqThread);
      int derResultado = nWaitTask(derThread);
      return izqResultado || derResultado;
    }
  }
  else{
    return *termina;
  }

}
