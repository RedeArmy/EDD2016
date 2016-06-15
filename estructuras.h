#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef struct nodo {
	/*
	 *	Este valor bien puede ser un entero, string, char, etc.
	 *	Es utilizado ya sea como una metrica o un indice, es recomendable
	 *	utilizar un atributo llamado "index", "indice" o "id" para identificar
	 *	a los nodos de EDD como listas.
	 *
	 *	La metrica (valor que se compara para ordenamiento) de preferencia debe
	 *	ser diferente al indice, sin embargo no es necesario, depende de la
	 *	logica del algoritmo.
	*/
	int valor;
	/*
	 *	Se deben crear todos los apuntadores que sean necesarios para la logica
	 *	del algoritmo, este es un ejemplo asi que posee 2 apuntadores
	 *	sin embargo se debe crear un tipo de nodo para cada EDD que se quiera
	 *	utilizar, es decir, para pila, cola y circular se usan nodos con un
	 *	solo apuntador llamado siguiente;
	*/
	struct nodo *siguiente;
	struct nodo *anterior;
} Nodo;

typedef int boolean;

Nodo *pila; // Hace referencia a la EDD Pila (FILO)
Nodo *cola; // Hace referencia a la EDD Cola (FIFO)
Nodo *circular1; // Apuntador al "Inicio" de la lista circular simple
Nodo *circular2; // Apuntador al "FInal" de la lista circular simple
Nodo *doble; // Apuntador al Inicio de la lista doblemente enlazada

Nodo *setNodo(int valor); // Inicializa y devuelve un apuntador de Nodo para una EDD
void pushPila(Nodo *nodo); // Inserta con el algoritmo de pila FILO
void pushCola(Nodo *nodo); // Inserta con el algoritmo de cola FIFO
void pushCircular(Nodo *nodo); // Inserta en una lista circular simple ORDENADA
void pushDoble(Nodo *nodo); // Inserta en una lista doblemente enlazada ORDENADA
void pushDobleNoOrder(Nodo *nodo); // Inserta al FINAL de una lista doblemente enlazada
void pushCircularNoOrder(Nodo *nodo); // Inserta al FINAL de una lista circular simple
Nodo *popPila(); // Devuelve el valor del tope de la pila
Nodo *popCola(); // Devuelve el ultimo valor de la cola
Nodo *getCircularByIndex(int Index); // Obtiene un nodo de la circular simple por medio de un INDICE
Nodo *getDobleByIndex(int Index); // Obtiene un nodo de la doblemente enlazada por medio de un INDICE
boolean deleteDobleByIndex(int Index); // Elimina un nodo de la doblemente enlazada por medio de un INDICE
boolean deleteCircularByIndex(int Index); // Elimina un nodo de la circular simple por medio de un INDICE

/*
*	Este metodo inicializa un nodo para incluirlo en cualquier EDD
*	dependiendo de la logica del algoritmo asi seran los valores
*	que este resiva, siempre devolvera un nodo inicializado
*/
Nodo *setNodo(int valor){
	Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo)); // Preparamos el espacio del nuevo nodo
	nuevo->valor = valor; // Inicializamos todos sus atributos
	nuevo->siguiente = NULL;
	nuevo->anterior = NULL;
	return nuevo; // Devolvemos el apuntador a este nodo
}

void pushPila(Nodo *nodo){
	if(pila == NULL){
		pila = nodo;
	} else {
		nodo->siguiente = pila; // Se mueve el valor del tope de la pila al fondo
		pila = nodo; // Se coloca el nuevo nodo en el tope de la pila
	}
}

void pushCola(Nodo *nodo){
	Nodo *temporal = cola;
	if(cola == NULL){
		cola = nodo;
	} else {
		// Nos ubicamos al final de la cola
		while(temporal->siguiente != NULL){
			temporal = temporal->siguiente;
		}		
		temporal->siguiente = nodo; // El nuevo nodo se coloca al final de la cola
	}
}

void pushDoble(Nodo *nodo){
	Nodo *temporal = doble;
	Nodo *anterior = NULL;
	Nodo *siguiente = NULL;
	if(doble == NULL){
		doble = nodo;
	} else {
		if(nodo->valor < doble->valor){ // Si el nuevo valor es menor al inicio, se cambia el apuntador
			nodo->siguiente = doble;
			doble->anterior = nodo;
			doble = nodo;
		} else { // de lo contrario buscamos el lugar que corresponde e insertamos el nodo
			anterior = doble;
			while(temporal->siguiente != NULL && temporal->valor < nodo->valor){
				anterior = temporal;
				temporal = temporal->siguiente;
			}
			if(temporal->valor < nodo->valor){
				nodo->siguiente = temporal->siguiente;
				temporal->siguiente = nodo;
				nodo->anterior = temporal;
			} else if (temporal->valor > nodo->valor){
				anterior->siguiente = nodo;
				nodo->siguiente = temporal;
				nodo->anterior = anterior;
				temporal->anterior = nodo;
			} else {
				temporal->siguiente = nodo;
				nodo->anterior = temporal;
			}
		}
	}
}

void pushDobleNoOrder(Nodo *nodo){
	Nodo *temporal = doble;
	while(temporal->siguiente != NULL){ // Recorremos la lista doble hasta el final
		temporal = temporal->siguiente;
	}
	// Enlazamos el nuevo nodo con el final de la lista
	nodo->anterior = temporal;
	temporal->siguiente = nodo;
}

void pushCircular(Nodo *nodo){
	Nodo *temporal = NULL;
	Nodo *anterior = NULL;
	if(circular1 == NULL) {
		circular1 = circular2 = nodo;
	} else {
		if(nodo->valor < circular1->valor){ // Si el nuevo valor es menor al inicio, se cambia el apuntador
			nodo->siguiente = circular1;
			circular1 = nodo;
		} else { // de lo contrario buscamos el lugar que corresponde
			temporal = circular1;
			while(temporal != circular2 && temporal->valor < nodo->valor){
				anterior = temporal;
				temporal = temporal->siguiente;
			}
			if(temporal == circular2 && temporal->valor < nodo->valor){
				nodo->siguiente = circular1;
				circular2->siguiente = nodo;
				circular2 = nodo;
			} else {
				anterior->siguiente = nodo;
				nodo->siguiente = temporal;
			}
		}
	}
}

void pushCircularNoOrder(Nodo *nodo){
	nodo->siguiente = circular1; // Apuntamos el nuevo nodo al "Inicio" de la lista
	circular2->siguiente = nodo; // Apuntamos el "Final" de la lista circular al nuevo nodo
	circular2 = nodo; // Cambiamos el "Final" de la lista hacia el nuevo nodo
}

Nodo *getCircularByIndex(int Index){
	if(circular1->valor == Index) // Se calcula el caso especial en que el valor esta en el "inicio" de la circular
		return circular1;
	if(circular2->valor == Index) // Se calcula el caso especial en que el valor esta en el "final" de la circular
		return circular2;
	Nodo *temporal = circular1;
	while(temporal!=circular2 && temporal->valor != Index){ // Recorremos toda la circular buscando el valor
		temporal = temporal->siguiente;
	}
	if(temporal->valor == Index) // Si lo encontramos regresamos el temporal
		return temporal;
	else // De lo contrario nulo
		return NULL;
}

Nodo *getDobleByIndex(int Index){
	Nodo *temporal = doble;
	while(temporal->siguiente != NULL && temporal->valor != Index){ // Recorremos la doblemente enlazada buscando el valor
		temporal = temporal->siguiente;
	}
	if(temporal->valor == Index) // Comprobamos si el Indice es el correcto y retornamos el temporal
		return temporal;
	else // Si no existe retornamos nulo
		return NULL;
}

Nodo *popPila(){
	if(pila == NULL) // Verificamos que haya algo en la pila
		return NULL; // Retornamos nulo en caso de estar vacia
	Nodo *temporal = pila; // Tomamos el valor en el tope de la pila
	pila = pila->siguiente; // Movemos el tope hacia el siguiente nodo
	return temporal; // Regresamos el nuevo tope
}

Nodo *popCola(){
	Nodo *temporal = cola;
	Nodo *anterior = NULL;
	if(cola == NULL) // Verificamos que haya algo en la cola
		return NULL; // Retornamos nulo en caso de estar vacia
	if(cola->siguiente == NULL){
		/*
		* Veriicamos si solo existe un nodo en la cola
		* de ser asi eliminamos la cola y regresamos el temporal
		* que actualmente contiene el valor de la cola
		*/
		cola = NULL;
		return temporal;
	}
	while(temporal->siguiente != NULL){ // Recorremos la cola hasta llegar al final
		anterior = temporal; // Guardamos el penultimo nodo
		temporal = temporal->siguiente;
	}
	anterior->siguiente = NULL; // Apuntamos ese penultimo nodo a nulo convirtiendolo en el nuevo final
	return temporal; // Regresamos el temporal, siendo el ulitmo nodo y el primero que entro a la cola
}

boolean deleteDobleByIndex(int Index){
	if(doble == NULL)
		return FALSE;
	Nodo *temporal = doble;
	Nodo *anterior = NULL;
	while(temporal->siguiente != NULL && temporal->valor != Index){ // Buscamos el indice proporcionado
		anterior = temporal; // Guardamos el anterior
		temporal = temporal->siguiente;
	}
	if(anterior == NULL && temporal->valor == Index){ // Si el anterior es nulo y encontramos el valor, borramos la cabeza de la doble
		doble = doble->siguiente; // Avanzamos la cabeza de la doble un nodo
		return TRUE;
	} else {
		if(temporal->valor == Index){ // Si encontramos el valor buscado y no es caso especial
			anterior->siguiente = temporal->siguiente; // borramos el temporal
			return TRUE;
		} else {
			return FALSE;
		}
	}
}

boolean deleteCircularByIndex(int Index){
	Nodo *temporal = circular1;
	Nodo *anterior = NULL;
	if(circular1 == NULL)
		return FALSE;
	if(circular1->valor == Index){ // Caso especial en que el Indice es el "primer" nodo de la circular.
		if(circular1->siguiente == circular2){ // Caso especial en que de 2 quedara un solo nodo
			circular1 = circular2; // Igualamos los nodos
			circular2->siguiente = circular1->siguiente = NULL; // Apuntamos los siguientes a nulos
		} else {
			circular2->siguiente = circular1->siguiente; // Apuntamos el "final" de la lista al siguiente del "inicio"
			circular1 = circular1->siguiente; // convertimos el siguiente del "inicio" en el nuevo "inicio"
		}
		return TRUE;
	}
	if(circular2->valor == Index){ // Caso especial en que el Indice es el "ultimo" nodo de la circular.
		if(circular1->siguiente == circular2){ // Caso especial en que de 2 quedara un solo nodo
			circular2 = circular1; // Igualamos los nodos
			circular2->siguiente = circular1->siguiente = NULL; // Apuntamos los siguientes a nulos
			return TRUE;
		}
	}
	if(circular1 == circular2 && circular1->valor == Index) {
		circular1 = circular2 = NULL; // Comprobamos si hay solo un nodo, de ser asi lo eliminamos
		return TRUE; // Retornamos verdadero
	} else {
		while(temporal->siguiente != circular2 && temporal->valor != Index){ // Buscamos el indice en la circular
			anterior = temporal; // Guardamos el anterior
			temporal = temporal->siguiente;
		}
		if(temporal->valor == Index){ // Comprobamos que hayamos encontrado el valor buscado
			if(temporal == circular2){ // Si estamos en el "final" de la circular
				circular2 = anterior; // Cambiamos ese apuntador
				circular2->siguiente = temporal->siguiente; // Y apuntamos el cambio al "inicio"
			} else {
				anterior->siguiente = temporal->siguiente; // Apuntamos el anterior al siguiente del temporal
			}
			return TRUE;
		} else {
			return FALSE;
		}
	}
}
