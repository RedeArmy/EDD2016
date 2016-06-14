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
	int valor, edad, cliente, turno;
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

	pushC(12);
	pushC(4);
	pushC(25);

	
      int k,r,t,h,c;
 
      printf("------- SIMULACIÓN DEL SISTEMA DE SUPERMECADO------- \n");
      
		  printf("Ingresar Cantidad de Carretas \n"); 
		  scanf("%d", &k);
		  
			for(int i = 1; i<=k; i++){
					int j = rand() % (4-1+1) + 1;
							 switch(j){ 
								case 1: 
								 pushP1(i);
								 break;
								case 2:
								 pushP2(i);
								 break;
								case 3:
								 pushP3(i);
								 break;
								case 4: 
								 pushP4(i);
								 break;
							}
				}
				
		  printf("Ingresar Cantidad de Clientes en Cola de Espera \n"), 
		  scanf("%d", &r);
		  
			  for(int i = 1; i<=r; i++){
						int j = rand() % (2-1+1) + 1;
								 switch(j){ 
									int w;
									case 1: 
									 w = rand() % (80-15+1) + 15;
									 pushCP(i,w, "HOMBRE");
									 break;
									case 2:
									 w = rand() % (80-15+1) + 15;
									 pushCP(i,w, "MUJER");
									 break;
								}
				}
				
	      printf("Ingresar Cantidad de Clientes Comprando \n"); 
		  scanf("%d", &t);
		  	    for(int i = 1; i<=t; i++){
							int o,p,q; 
							o = rand() % (100-50+1) + 50;
							p = rand() % (100-50+1) + 50;
							q = rand() % (5-1+1) + 1;
							InsertarC(o,p,q);		 				 
				}
				
		  printf("Ingresar Cantidad de Cajas \n");  
		  scanf("%d", &h);
		        for(int i = 1; i<=h; i++){
							Insertar(i,"LIBRE",0,0,0);		 				 
				}
		  
Recorrer(); 
		  /*
		  printf("Ingresar Cantidad de Clientes en Cola de Pagos \n"); 
		  scanf("%d", &y);
		  printf("Ingresar Cantidad de Clientes en Cola de “Ciudadanos de Oro” \n");
		  scanf("%d", &i);  
*/
      
		  while(1){
		  printf("Desea Ingresar Mas Carretas? SI [y], NO [n] o SALIR[s]: ");
		  char m=getchar();
		  getchar();
		  
		  switch(m){
		  case 'y': printf("\nIngresar Cantidad de Carretas \n"); 
					scanf("%d", &c);
						for(int i = k; i<=c; i++){
								int j = rand() % (4-1+1) + 1;
										 switch(j){ 
											case 1: 
											 pushP1(i);
											 break;
											case 2:
											 pushP2(i);
											 break;
											case 3:
											 pushP3(i);
											 break;
											case 4: 
											 pushP4(i);
											 break;
										}
							}					
		  break;	  
		  case 'n': Recorrer();  
		  break;
		  case 's': exit(0);
		  default: printf("\nSaliendo del programa...");
		  return 0;
			}
		}
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
void pushCP(int cliente, int edad, char *genero){ 
	GNodo *actual = (GNodo *)malloc(sizeof(GNodo));
	GNodo *nuevo = (GNodo *)malloc(sizeof(GNodo));
	nuevo->cliente = cliente;
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

/*COLA CLIENTES NORMALES*/
void pushC(int cliente){ 
	GNodo *presente = (GNodo *)malloc(sizeof(GNodo));
	GNodo *new = (GNodo *)malloc(sizeof(GNodo));
	new->cliente = cliente;

	new->siguiente = NULL;
	presente->siguiente = NULL;

	while(new->siguiente != NULL)
		cnodo=cnodo->siguiente;

	new->siguiente = NULL;
	new->siguiente = cnodo;
	new = cnodo;
}

/*LISTA CIRCULAR SIMPLEMENTE ENLAZADA*/
void InsertarC(int valor, int cliente, int turno){
	GNodo *nuevo = (GNodo *)malloc(sizeof(GNodo));
	nuevo->valor = valor;
	nuevo->cliente = cliente;
	nuevo->turno = turno;
	
	
	if(circular1 == NULL) {
		circular1 = circular2 = nuevo;
	} else {
		GNodo *temp = circular2;
		nuevo->siguiente = circular1;
		temp->siguiente = nuevo;
		circular2 = nuevo;
	}
	
}


/* Eliminar de la lista doblemente enlazada */
void Eliminar(int no_caja){
	GNodo *temporal = lista;
	GNodo *anterior = NULL;
	while(temporal->no_caja != no_caja && temporal->seguente !=NULL) {
		anterior = temporal;
		temporal = temporal->seguente;
	}
	if(temporal->no_caja == no_caja){
		
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
void Extra(int turno1){
	GNodo *anterior = circular1;
	GNodo *temp = circular1;
	if(circular1 == circular2){
		circular1 = circular2 = NULL;
	}
	else {
		if(circular2->turno == turno1){
			while(temp != circular2){
				anterior = temp;
				temp = temp->siguiente;
			}
			anterior->siguiente = circular1;
			circular2 = anterior;
			Extra(turno1);
		} else if(circular1->turno == turno1){
			circular2->siguiente = circular1->siguiente;
			circular1 = circular1->siguiente;
			Extra(turno1);
		} else {
			while(temp != circular2){
				if(temp->turno == turno1){
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
			
	GNodo *tempPila = p4nodo;		
			while(tempPila!=NULL)
			{
				printf("Número de Carreta: %d\n ", tempPila->id);
				tempPila = tempPila->before;
			}
			printf("\n");
			
	GNodo *temp = CPnodo;
		while(temp!=NULL)
			{
				printf("No. Cliente: %d\n Edad Cliente: %d\n Genero Cliente: %s\n\n ", temp->cliente, temp->edad, temp->genero);
				temp = temp->siguiente;
			}
			printf("\n");

	GNodo *tempC = circular1;		
			while(tempC != circular2)
			{
				printf("No Carreta: %d\n No. Cliente: %d\n Turno: %d\n\n", tempC->valor, tempC->cliente, tempC->turno);
				tempC = tempC->siguiente;
			}
			printf("No Carreta: %d\n No. Cliente: %d\n Turno: %d\n\n", tempC->valor, tempC->cliente, tempC->turno);
			printf("\n");

	GNodo *temporal = lista;
	
	while(temporal->seguente!=NULL){
		printf("No Caja: %d\n Estado: %s\n Cliente Atendido: %d\n Número de Carreta: %d\n Número de Clientes Atendidos: %d\n\n ", temporal->no_caja, temporal->estado, temporal->no_cliente, temporal->no_carreta, temporal->no_atendido);
		temporal = temporal->seguente;
	}
	
	printf("No Caja: %d\n Estado: %s\n Cliente Atendido: %d\n Número de Carreta: %d\n Número de Clientes Atendidos: %d\n\n ", temporal->no_caja, temporal->estado, temporal->no_cliente, temporal->no_carreta, temporal->no_atendido);
			
			
	  GNodo *tempCOLA = cnodo;		
		while(tempCOLA!=NULL)
			{
				printf("Número de Cliente: %d\n ", tempCOLA->cliente);
				tempCOLA = tempCOLA->siguiente;
			}
			printf("\n");
			
}
