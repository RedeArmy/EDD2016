#include "estructuras.h"

int main(){
	pila = NULL;
	cola = NULL;
	circular1 = NULL;
	circular2 = NULL;
	doble = NULL;
	pushCircular(setNodo(25));
	pushCircular(setNodo(10));
	pushCircular(setNodo(33));
	pushCircular(setNodo(60));
	pushCircular(setNodo(40));
	pushCircular(setNodo(15));
	Nodo *temporal = circular1;
	int x = 1;
	while(temporal != NULL && x < 21){
		printf("Pos: %d = %d\n", x, temporal->valor);
		temporal = temporal->siguiente;
		x = x + 1;
	}
	return 0;
}
