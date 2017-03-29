# CC4302-1-Sistemas-Operativos
###### Repositorio de la asignatura CC4302-1 Sistemas Operativos de mi Doctorado en Ciencias


## Auxiliar 01 

Para dar inicio a esta auxiliar debe tener corriendo nSystem en su computador, si usted tiene Linux solo debe descargar el archivo desde aquí [nSystem](http://users.dcc.uchile.cl/~lmateu/CC41B/download/nsystem64-beta2.tgz). Una vez descomprimido debe seguir las instrucciones del archivo README. Si usted tiene otro sistema operativo o si no quiere instalarlo directamente en su Linux también puede usar la receta Docker que esta en el directorio *Herramientas*. 

Una vez ha logrado hacer correr nSystem en su computador es hora de iniciar a desarrollar.


### Aspectos básicos de nSystem 

Lo primero es crear un programa muy simple que utilice las funciones de creación de tareas de nSystem. Para esto vamos a escribir un programa principal, el handler de programa principal es **nMain** con la siguiente firma `int nMain()` tiene el mismo comportamiento que `main` en la mayoría de los lenguajes de programación. 

El método nMain es el punto de entrada de una aplicación de consola de nSystem.  Cuando se inicia la aplicación, el método nMain es el primer método que se invoca. En un programa de C para nSystem, sólo puede haber un punto de entrada.

```
#include "nSystem.h" 

int escritor(int num, int espera);

int nMain() {
	
	Task tareas[3];
	int i;
	for (i=0; i<3; ++i)
	{
		tareas[i] = nEmitTask(escritor, i, i * 200); // Crea las tareas 
	}
	
	for (i=0; i<3; ++i)
	{
		nWaitTask(tareas[i]); // Espera que finalicen las tareas
	}
	
	nPrintf("Fin ejemplo\n");
	
}
// Metodo que es invocado por cada Tarea creada. 
int escritor(int num, int espera)
{
	int i = 5;
	while ( i > 0)
	{
		nPrintf(Thread %d: %d\n", num, i);
		nSleep( espera); // Pone a dormir a un Thread dentro de nSystem. 
		--i;
	}
}

``` 

Las funciones que vamos a utilizar en este ejercicio son `nEmitTask` que nos permite lanzar un thread independiente, al ejecutarlo nos devuelve un descriptor del Thread creado con el cual podemos ejecutar la función de espera (la cual es bloqueante) `nWaitTask` esta función nos permite esperar hasta que el Thread descripto por el descriptor de la tarea finalice, cuando la tarea finaliza `nWaitTask` devuelve el valor que la función enviada como parámetro a `nEmitTask` retorne. 
Dentro del sistema operativo nSystem existen varias funciones re definidas como por ejemplo **nPrintf, nSleep, nOpen, Close, nFprintf, nMalloc**, etc. Cada una de estas funciones se encuentran re escritas ya que son la API de nuestro nuevo sistema operativo, si por alguna razón utilizamos sin darnos cuenta `sleep` en vez de `nSleep` tendremos un efecto no deseado dado que dormiríamos al proceso nSystem el cual simula todo nuestro nuevo sistema operativo y no al thread actual simulado por nSystem. 

## Compilación del ejemplo 
 
Para realizar la compilación de este código de ejemplo se debe crear una variable de ambiente llamada ***NSYSTEM*** con la ubicación absoluta de nSystem `export NSYSTEM=/usr/src/nsystem64-beta2`. 
Luego es posible realizar la compilación por medio de los siguientes comandos: 

```
> gcc -c ejemplo01.c -I$NSYSTEM/include
> gcc ejemplo01.o #NSYSTEM/lib/libnSys.a -o ejemplo01
```
> Para compilar nSystem en un Linux de 64 bits se debe agregar la opción -m32 a las variables `CFLAGS` y `LFLAGS` del archivo *Make*. Además dependiendo de la distribución, requerirá tener instalada la librería `glic-devel` o `libc6-dev`. Actualmente se encuentra disponible la versión nativa de 64 bits de nSystem en la pagina del curso [http://users.dcc.uchile.cl/~lmateu/CC41B/](http://users.dcc.uchile.cl/~lmateu/CC41B/)


### Búsqueda en un árbol 

El desafiado este ejercicio es poder escribir un algoritmo de búsqueda (simple, muy simple) en un árbol binario con la siguiente estructura. 

```
typedef struct Nodo {
	int valor;
	struct Nodo* izq;
	struct Nodo* der;
} Nodo; 
```

Para esta estructura se deben implementar los siguientes métodos de búsqueda 

- `int buscarSeq1( Nodo *node, int num)` Busca num en el árbol haciendo un recorrido en profundidad. 
- `int buscarSeq2( Nodo *nodo, int num)` Busca num en árbol haciendo un recorrido simultáneo en cada rama creando tantos thread como nodos del árbol. 
- `int buscarSeq2( Nodo *node, int num)` Búsqueda igual que el anterior pero con la optimización que la ejecución de todas las tareas termina cuando alguna encuentra el elemento buscado. 

### Ejemplo de I/O 

Ahora nos introduciremos en el ejemplo de poder realizar operaciones de entrada salida dentro de nSystem. Para esto debemos implementar un programa que lee desde la entrada estándar un número n y luego escribe n archivos en *paralelo* con una cantidad de lineas variable. 
 
