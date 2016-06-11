/*EDER YAFETH GACIA QUIROA - 201212621*/
/*Estructura de Datos - Vacaciones Junio 2016*/
/*PRACTICA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false 0
#define true 1

typedef int bool;
//enum { false, true };

typedef struct Nodo
{
	int no_caja, no_atendido, no_carreta, no_cliente;
	char estado[25], genero[25];
	int valor, edad;
	int id;
	bool gestando;
	struct Nodo *seguente;
	struct Nodo *precedente;
	struct Nodo *empleado;
	struct Nodo *siguiente;
	struct Nodo *anterior;
	struct Nodo *documento;
	struct Nodo *before;
		
}GNodo;

GNodo *lista;
GNodo *colaP;
GNodo *cnodo;
GNodo *CPnodo;
GNodo *p1nodo;
GNodo *p2nodo;
GNodo *p3nodo;
GNodo *p4nodo;
GNodo *circular1;
GNodo *circular2;


void Insertar();
void InsertarC();
void Recorrer();
void pushC();
void pushCP();
void pushP1();
void pushP2();
void pushP3();
void pushP4();
int popP(void);
void Extra(int);

int main(){
	lista = NULL;
	cnodo = NULL;
	CPnodo = NULL;
	p1nodo = NULL;
	p2nodo = NULL;
	p3nodo = NULL;
	p4nodo = NULL;
	circular1 = NULL;
	circular2 = NULL;
	
	Insertar(3,"LIBRE",6,7,3);
	Insertar(1,"OCUPADO",7,2,6);
	
	InsertarC(4);
	InsertarC(0);
	InsertarC(0);
	InsertarC(0);
	InsertarC(7);

	
	pushCP(12, "HOMBRE");
	pushCP(18, "HOMBRE");

	pushP1(50);
	pushP1(1);
	
	pushP2(25);
	pushP2(7);
	pushP2(2);
	
	  char m,c;
      int k,r,t,y,i,h,f;
      printf("------- SIMULACION DEL SISTEMA SUPERMECADO------- \n");
      
		  printf("1) Ingresar Número de Carretas \n"); 
		  printf("2) Ingresar Número de Clientes en Cola de Espera \n"), 
		  printf("3) Cantidad de clientes comprando \n");  
		  printf("4) Salir [s] \n");
      
		  while(1){
		  printf("[a], [e], [m] o [s]: ");
		  m=getchar();
		  getchar();
		  
		  switch(m){
		  case 'a': printf("Introduzca Número de Departamento: ");
					scanf("%d", &k); getchar(); 
					printf("Introduzca Nombre del departamento: ");
					scanf("%s", &c); getchar(); 
					printf("Introduzca Número de empleados libres: ");
					scanf("%d", &r); getchar(); 
					printf("Introduzca Número de empleados ocupados: ");
					scanf("%d", &t); getchar(); 
					printf("Introduzca Número de clientes que están siendo atendidos: ");
					scanf("%d", &y); getchar(); 
					printf("Introduzca Número de clientes que han atendido: ");
					scanf("%d", &i); getchar(); 
					printf("Introduzca Número de empleados que pertenecen a este departamento: ");
					scanf("%d", &h); getchar(); 
					printf("Introduzca Cantidad de documentos procesados en total: ");
					scanf("%d", &f); getchar(); 
					
					Insertar(k); 		
					Recorrer(); 
		  break;
		  case 'e': 
		  /*popP();*/
		  Extra(0); 
		  Recorrer();  
		  break;
		  case 'm': Recorrer();  
		  break;
		  case 's': exit(0);
		  default: printf("\nSaliendo del programa...");
		  return 0;
			}
		}
	return 0;
}

/*PILA 1*/
void pushP1(int id){ 
	GNodo *nuovo = (GNodo *)malloc(sizeof(GNodo));
	nuovo->id = id;
	
	nuovo->before = p1nodo;
    nuovo->id = id;
	p1nodo = nuovo;
}

/*PILA 2*/
void pushP2(int id){ 
	GNodo *nuovo = (GNodo *)malloc(sizeof(GNodo));
	nuovo->id = id;
	
	nuovo->before = p2nodo;
    nuovo->id = id;
	p2nodo = nuovo;
}

/*PILA 3*/
void pushP3(int id){ 
	GNodo *nuovo = (GNodo *)malloc(sizeof(GNodo));
	nuovo->id = id;
	
	nuovo->before = p3nodo;
    nuovo->id = id;
	p3nodo = nuovo;
}

/*PILA 4*/
void pushP4(int id){ 
	GNodo *nuovo = (GNodo *)malloc(sizeof(GNodo));
	nuovo->id = id;
	
	nuovo->before = p4nodo;
    nuovo->id = id;
	p4nodo = nuovo;
}

/*COLA DE PRIORIDAD*/
void pushCP(int edad, char *genero){ 
	GNodo *actual = (GNodo *)malloc(sizeof(GNodo));
	GNodo *nuevo = (GNodo *)malloc(sizeof(GNodo));
	nuevo->edad = edad;
	strcpy(nuevo->genero, genero);

		    nuevo->siguiente = NULL;
			actual->siguiente = NULL;
			GNodo *temp = CPnodo;
			
			if(CPnodo==NULL) {
				CPnodo = nuevo;
			} else {
				if (nuevo->edad >= 65) {
					if(temp->edad < 65) {
						nuevo->siguiente = CPnodo;
						CPnodo = nuevo;
					} else {
						while(temp->siguiente != NULL && temp->edad >= 65){
							actual = temp;
							temp = temp->siguiente;
						}
						if(temp->siguiente == NULL) temp->siguiente = nuevo;
						else {
							actual->siguiente = nuevo;
							nuevo->siguiente = temp;
						}
					}
				} else {
					while(temp->siguiente != NULL){
						temp = temp->siguiente;
					}
					temp->siguiente = nuevo;
				}
			}
}

/*LISTA CIRCULAR SIMPLEMENTE ENLAZADA*/
void InsertarC(int valor){
	GNodo *nuevo = (GNodo *)malloc(sizeof(GNodo));
	nuevo->valor = valor;
	if(circular1 == NULL) {
		circular1 = circular2 = nuevo;
	} else {
		GNodo *temp = circular2;
		nuevo->siguiente = circular1;
		temp->siguiente = nuevo;
		circular2 = nuevo;
	}
	
}



/*LISTA DOBLEMENTE ENLAZADA ORDENANDA*/
void Insertar(int no_caja, char *estado, int no_cliente, int no_carreta, int no_atendido){
	GNodo *nuevo = (GNodo *)malloc(sizeof(GNodo));
		nuevo->no_caja = no_caja;
		nuevo->no_cliente = no_cliente;
		nuevo->no_carreta = no_carreta;
		nuevo->no_atendido = no_atendido;
		strcpy(nuevo->estado, estado);
		
			nuevo->seguente = NULL;
			nuevo->precedente = NULL;
			GNodo *temporal = lista;
			
			if(lista==NULL){
				lista = nuevo;
			} else {
				if(no_caja < temporal->no_caja){
					nuevo->seguente = temporal;
					lista = nuevo;
				} else {
					GNodo *anterior = temporal;
					while(no_caja > temporal->no_caja && temporal->seguente != NULL){
						anterior = temporal;
						temporal = temporal->seguente;
					}			
					if(temporal->no_caja < no_caja){
						nuevo->seguente = temporal->seguente;
						temporal->seguente = nuevo;
						nuevo->precedente = temporal;
					} else if(temporal->no_caja > no_caja){				
						anterior->seguente = nuevo;
						nuevo->seguente = temporal;
						nuevo->precedente = temporal->precedente;
						temporal->precedente = nuevo;
					} else {
						temporal->seguente = nuevo;
						nuevo->precedente = temporal;
					}
				}
		}
}

/*SACAR PILA*/
int popP(void){ 
			int x;
			if (p1nodo==NULL){ 
				printf("Lista vacia"); return EOF; }
			else{
				x = p1nodo->id;
				p1nodo = p1nodo->before;
      return x;
	  }
    }

/*SACAR CIRCULAR*/
void Extra(int turno){
	GNodo *anterior = circular1;
	GNodo *temp = circular1;
	if(circular1 == circular2){
		circular1 = circular2 = NULL;
		printf("Nada\n");
	}
	else {
		if(circular2->valor == turno){
			while(temp != circular2){
				anterior = temp;
				temp = temp->siguiente;
			}
			anterior->siguiente = circular1;
			circular2 = anterior;
			Extra(turno);
		} else if(circular1->valor == turno){
			circular2->siguiente = circular1->siguiente;
			circular1 = circular1->siguiente;
			//printf("Llamada recursiva\n");
			Extra(turno);
		} else {
			//printf("Llamada recursiva --\n");
			while(temp != circular2){
				if(temp->valor == turno){
					anterior->siguiente = temp->siguiente;
					temp = anterior;
				}
				anterior = temp;
				temp = temp->siguiente;
			}
		}
	}
}



/*MOSTRAR ESTRUCTURAS*/
void Recorrer(){
	GNodo *temporal = lista;
	
	while(temporal->seguente!=NULL){
		printf("No Caja: %d\n Estado: %s\n Cliente Atendido: %d\n Número de Carreta: %d\n Número de Clientes Atendidos: %d\n\n ", temporal->no_caja, temporal->estado, temporal->no_cliente, temporal->no_carreta, temporal->no_atendido);
		temporal = temporal->seguente;
	}
	
	printf("No Caja: %d\n Estado: %s\n Cliente Atendido: %d\n Número de Carreta: %d\n Número de Clientes Atendidos: %d\n\n ", temporal->no_caja, temporal->estado, temporal->no_cliente, temporal->no_carreta, temporal->no_atendido);
	
	GNodo *temp = CPnodo;
		while(temp!=NULL)
			{
				printf("Edad Cliente: %d\n Genero Cliente: %s\n\n ", temp->edad, temp->genero);
				temp = temp->siguiente;
			}
			printf("\n");

	GNodo *temp1 = p1nodo;		
			while(temp1!=NULL)
			{
				printf("Número de Carreta: %d\n ", temp1->id);
				temp1 = temp1->before;
			}
			printf("\n");
			
	GNodo *temp2 = p2nodo;		
			while(temp2!=NULL)
			{
				printf("Número de Carreta: %d\n ", temp2->id);
				temp2 = temp2->before;
			}
			printf("\n");
			
	GNodo *temp3 = p3nodo;
			while(temp3!=NULL)
			{
				printf("Número de Carreta: %d\n ", temp3 ->id);
				temp3  = temp3->before;
			}
			printf("\n");
			
	GNodo *temp4 = p4nodo;		
			while(temp4!=NULL)
			{
				printf("Número de Carreta: %d\n ", temp4->id);
				temp4 = temp4->before;
			}
			printf("\n");
			
	GNodo *tempC = circular1;		
			while(tempC != circular2)
			{
				printf("Comprador: %d\n ", tempC->valor);
				tempC = tempC->siguiente;
			}
			printf("Comprador: %d\n ", tempC->valor);
			printf("\n");
			
}
