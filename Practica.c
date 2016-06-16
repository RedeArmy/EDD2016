/*EDER YAFETH GACIA QUIROA - 201212621*/
/*Estructura de Datos - Vacaciones Junio 2016*/
/*PRACTICA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define false 0
#define true 1

typedef int bool;
//enum { false, true };

typedef struct Nodo
{
	int no_caja, no_atendido, no_carreta, no_cliente;
	char estado[25], genero[25];
	int valor, edad, cliente, turno, carreta;
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
GNodo *COnodo;
GNodo *CNnodo;
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
void ReducirTC();
void ReducirTDE();
void Agregar();
void Simulacion();
void pushCO();
void pushCN();
void pushCP();
void pushP1();
void pushP2();
void pushP3();
void pushP4();
void Atender();
int obtenerCarreta();
int Contador();
int ContadorCompras();
int popP(void);
int *popCP(void);
int *popCN(void);
int *popCO(void);
void Extra(int);
void sacarCarreta();
void sacarComprador();
void ExtraC();
void Graficar();

int main(){
	lista = NULL;
	COnodo = NULL;
    CNnodo = NULL;
	CPnodo = NULL;
	p1nodo = NULL;
	p2nodo = NULL;
	p3nodo = NULL;
	p4nodo = NULL;
	circular1 = NULL;
	circular2 = NULL;

	
      int k,r,l,h,z,v;
 
      printf("------- SIMULACIÓN DEL SISTEMA DE SUPERMECADO------- \n");
      
		  printf("Ingresar Cantidad de Carretas \n"); 
		  scanf("%d", &k);
		  int dato = k;
		  srand(time (NULL));
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
									 w = rand() % (90-17+2) + 15;
									 pushCP(i,w, "HOMBRE");
									 break;
									case 2:
									 w = rand() % (90-17+2) + 15;
									 pushCP(i,w, "MUJER");
									 break;
								}
				}
				
	      printf("Ingresar Cantidad de Clientes Comprando \n"); 
		  scanf("%d", &l);
		  srand(time (NULL));
		  	    for(int i = 1; i<=l; i++){
							int o,p,q,r; 
							o = rand() % (100-50+1) + 50;
							p = rand() % (100-50+1) + 50;
							q = rand() % (90-18+1) + 18;
							r = rand() % (5-1+1) + 1;
							InsertarC(o,p,q,r);		 				 
				}
				
		  printf("Ingresar Cantidad de Clientes en Cola de Pagos \n"); 
		  scanf("%d", &z);
		  srand(time (NULL));
		     for(int i = 1; i<=z; i++){
							int o,p,q; 
							o = rand() % (100-50+2) + 50;
							p = rand() % (64-18+1) + 18;
							q = rand() % (100-50+2) + 50;
							pushCN(o,p,q);		 				 
				}
				
		  printf("Ingresar Cantidad de Clientes en Cola de “Ciudadanos de Oro” \n");
		  scanf("%d", &v); 
		  srand(time (NULL)); 
		  	 for(int i = 1; i<=v; i++){
							int x,y,z; 
							x = rand() % (100-50+1) + 50;
							y = rand() % (90-65+1) + 65;
							z = rand() % (90-50+1) + 50;
							pushCO(x,y,z);		 				 
				}
				
		  printf("Ingresar Cantidad de Cajas \n");  
		  scanf("%d", &h);
		        for(int i = 1; i<=h; i++){
							Insertar(i,"LIBRE",0,0,0,0);		 				 
  		}
Graficar();
Agregar(dato); 
}

/*AGREGAR NUEVAS CARRETAS AL SISTEMA*/
void Agregar(int bandera){
	char m;
	int c;
		 while(1){
		  printf("Desea Ingresar Mas Carretas? SI [y], NO [n] o SALIR[s]: ");
		  scanf ("%s", &m);
		  getchar();
		  
		  switch(m){
		  case 'y': printf("\nIngresar Cantidad de Carretas \n"); 
					scanf("%d", &c);
						for(int i = 1; i<=c; i++){
								int j = rand() % (4-1+1) + 1;
										 switch(j){ 
											case 1: 
											 pushP1(i+bandera);
											 break;
											case 2:
											 pushP2(i+bandera);
											 break;
											case 3:
											 pushP3(i+bandera);
											 break;
											case 4: 
											 pushP4(i+bandera);
											 break;
										}
							}
							bandera = bandera + c;	
							printf("\n"); 	
							Simulacion();	
		  break;	  
		  case 'n': 
			Simulacion();
		  break;
		  case 's': exit(0);
		  default: printf("\nERORR! seleccione opccion");
			}
		}
	}
/*SISTEMA DE SIMULACION*/
void Simulacion(){
	int id;//<-------valor de carreta 
	int *id1 = (int *)malloc(sizeof(int) * 2);//<-------vector de 2 posiciones, valores de Cliente y Edad
	int *norm = (int *)malloc(sizeof(int) * 2);//<------vector de 2 posiciones, valores de Cliente y Carreta
	int *oro = (int *)malloc(sizeof(int) * 2);//<-------vector de 2 posiciones,valores de Cliente y Carreta
	id = 0;
	
	srand(time (NULL));
	  int q = rand() % (5-1+1) + 1;
	  int z = rand() % (3-1+1) + 1;

			  id = popP();//<------Capta el valor eliminado de la pila
			  id1 = popCP();//<----Capta el valor eliminado de la cola de prioridad 
			  
			  InsertarC(id,id1[0],id1[1],q);//<-----Inserta valores en la lista circular
			  
		/* Verifica si cola de ORO esta visia, sino toma de cola normal*/	  
		GNodo *tempCO = COnodo;
		  if (tempCO==NULL){
			  norm = popCN();
			  Atender(norm[1],norm[0],z);//<---Inserta valores en metodo
		  }
		  else{
			  oro = popCO();
			  Atender(oro[0],oro[1],z);//<---Inserta valores en metodo
		  }
			  sacarComprador();//<---Metodo para sacar compradores y enviarlos a colas
			  sacarCarreta();//<---Metodo para sacar carretas de cajas y enviarlas a pilas
			  Recorrer();//<---Metodo generador en consola
			  Graficar();//<---Metodo generador de grafo
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
void pushCN(int cliente, int edad, int valor){ 
	GNodo *new = (GNodo *)malloc(sizeof(GNodo));
	GNodo *temp = CNnodo;
	new->cliente = cliente;
	new->valor = valor;
	new->edad = edad;
	new->siguiente = NULL;
	
	if(CNnodo == NULL)
		CNnodo = new;
	else {
		while(temp->siguiente != NULL){
			temp = temp->siguiente;
		}	
		temp->siguiente = new;
	}
}

/*COLA CLIENTES ORO*/
void pushCO(int cliente, int edad, int valor){ 
	GNodo *new = (GNodo *)malloc(sizeof(GNodo));
	GNodo *temp = COnodo;
	new->cliente = cliente;
	new->valor = valor;
	new->edad = edad;
	new->siguiente = NULL;
	
	if(COnodo == NULL)
		COnodo = new;
	else {
		while(temp->siguiente != NULL){
			temp = temp->siguiente;
		}	
		temp->siguiente = new;
	}
}

/*LISTA CIRCULAR SIMPLEMENTE ENLAZADA*/
void InsertarC(int valor, int cliente, int edad, int turno){
	GNodo *nuevo = (GNodo *)malloc(sizeof(GNodo));
	nuevo->valor = valor;
	nuevo->cliente = cliente;
	nuevo->edad = edad;
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


/*LISTA DOBLEMENTE ENLAZADA ORDENANDA*/
void Insertar(int no_caja, char *estado, int no_cliente, int no_carreta, int no_atendido, int turno){
	GNodo *nuevo = (GNodo *)malloc(sizeof(GNodo));
		nuevo->no_caja = no_caja;
		nuevo->no_cliente = no_cliente;
		nuevo->no_carreta = no_carreta;
		nuevo->no_atendido = no_atendido;
		nuevo->turno = turno;
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
	        int opc = 1;
	        
			if (p1nodo==NULL && p2nodo==NULL && p3nodo==NULL && p4nodo==NULL){ 
				printf("NO HAY CARRETAS"); return EOF; }
			else{
				do{
					int j = rand() % (4-1+1) + 1;
						switch(j){ 
							case 1:
							if(p1nodo!=NULL){ 
								x = p1nodo->id;
								printf("%d",x);
								p1nodo = p1nodo->before;
								opc = 0;
							}
							else {opc =1;}
							break;
							case 2:
							if(p2nodo!=NULL){ 
								x = p2nodo->id;
								printf("%d",x);
								p2nodo = p2nodo->before;
								opc = 0;
							}
							else {opc =1;}
							break;
							case 3:
							if(p3nodo!=NULL){ 
								x = p3nodo->id;
								printf("%d",x);
								p3nodo = p3nodo->before;
								opc = 0;
							}
							else {opc =1;}				
							break;	
							case 4:
							if(p4nodo!=NULL){ 
								x = p4nodo->id;
								printf("%d",x);
								p4nodo = p4nodo->before;
								opc = 0;
							}
							else {opc =1;}	
							break;
						}			
					} while(opc!=0);
				}					 
      return x;
	  }

/*SACAR COLA DE PRIORIDAD*/
int *popCP(void){
	int *h = (int *)malloc(sizeof(int)*2);
		if (CPnodo==NULL){ 
				printf("NO HAY CLIENTES"); }
			else{
				h[0] = CPnodo->cliente;
				h[1] = CPnodo->edad;
				CPnodo = CPnodo->siguiente;
	}
     return h;		
}

/*SACAR COLA DE ESPERA CLIENTES*/
int *popCN(void){
	int *b = (int *)malloc(sizeof(int)*2);
	
	GNodo *tempCN = CNnodo;
		if (tempCN==NULL){ 
				printf("NO HAY CLIENTES"); }
			else{
				b[0] = tempCN->cliente;
				b[1] = tempCN->edad;
				CNnodo = CNnodo->siguiente;
	}
     return b;		
}

/*SACAR COLA DE ESPERA CLIENTES ORO*/
int *popCO(void){
	int *v = (int *)malloc(sizeof(int)*2);
	
	GNodo *tempCO = COnodo;
		if (tempCO==NULL){ 
				printf("NO HAY CLIENTES"); }
			else{
				v[0] = tempCO->valor;
				v[1] = tempCO->cliente;
				COnodo = COnodo->siguiente;
	}
     return v;		
}


/*SACAR CARRETA DE CAJAS*/
void sacarCarreta(){
	
	ReducirTDE();
	
	int contador = Contador();
	int x = 0;
	while(x < contador){
		
		int carreta = obtenerCarreta();
		
		int j = rand() % (4-1+1) + 1;
			switch(j){ 
				case 1: 
				  pushP1(carreta);
				break;
				case 2:
				  pushP2(carreta);
				break;
				case 3:
				  pushP3(carreta);
				break;
				case 4: 
				  pushP4(carreta);
				break;
			}
		x = x + 1;
	}
}


/*CONTADOR DE CARRETA DE CAJAS*/
int Contador(){
	int contador = 0;
	GNodo *temporal  = lista;
	
	while(temporal->seguente != NULL){
		if(temporal->turno == 0 && temporal->no_carreta !=0){
			contador = contador + 1;
		}
		temporal = temporal->seguente;
	}
	return contador;
}

/*OBTENER DE CARRETA DE CAJAS*/
int obtenerCarreta(){
	int carreta = 0;
	GNodo *temporal  = lista;
	
	while(temporal != NULL){
		if(temporal->no_carreta != 0 && temporal->turno == 0){
			carreta = temporal->no_carreta;
			strcpy(temporal->estado, "LIBRE");
		    temporal->no_carreta = 0;
		    temporal->no_cliente = 0;
		    temporal->no_atendido = temporal->no_atendido + 1;
		    temporal->turno = 0;
		    return carreta;
		}
		temporal = temporal->seguente;
	}
	return carreta;
}


/*DECRECER TURNOS DOBLEMEMTENTE ENLAZADA*/
void ReducirTDE(){
	GNodo *temporal  = lista;
	
	 while (temporal != NULL){
		 
		 if(temporal->turno > 0){
			temporal->turno = temporal->turno - 1;
		}
 		temporal = temporal->seguente;
	 } 
	 
}

/*SACAR CIRCULAR*/
GNodo *getCompras(int turno1){
	if(circular1->turno == turno1) 
		return circular1;
	if(circular2->turno == turno1) 
		return circular2;
	GNodo *temporal = circular1;
	while(temporal!=circular2 && temporal->turno != turno1){ 
		temporal = temporal->siguiente;
	}
	if(temporal->turno == turno1)
		return temporal;
	else 
		return (GNodo *)NULL;
}

/* SACAR COMPRADOR DE LISTA DE COMPRAS*/
void sacarComprador(){
	
	ReducirTC();
	
	int contador = ContadorCompras();
	int x = 0;
	while(x < contador){
		
		GNodo *cliente = getCompras(0);
		Extra(0);
		int carreta = cliente->valor; 
		int cliente1 = cliente->cliente;
		int edad = cliente->edad;
		
		if(edad >= 65){
			pushCO(cliente1,edad,carreta);	
	    }
	    else {
			pushCN(cliente1,edad,carreta);
		}
		
		x = x + 1;
	}
			  	
}

/*DECRECER TURNOS CIRCULAR SIMPLE*/
void ReducirTC(){
	GNodo *tempo = circular1;

	while(tempo != circular2 ) {
		if(tempo->turno > 0){
			tempo->turno = tempo->turno - 1;
		}
 		tempo = tempo->siguiente;
 	}
 	
	if(circular2->turno > 0)
		circular2->turno = circular2->turno - 1;
}


/*CONTADOR DE CLINETES EN COMPRAS*/
int ContadorCompras(){
	int contador = 0;
	GNodo *temp1  = circular1;

	while(temp1->siguiente != circular1 ) {
		if(temp1->turno == 0){
			contador = contador + 1;
		}
 		temp1 = temp1->siguiente;
 	}
	return contador;
}

/*ELIMINAR NODO CIRCULAR*/
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
			//Extra(turno1);
		} else if(circular1->turno == turno1){
			circular2->siguiente = circular1->siguiente;
			circular1 = circular1->siguiente;
			//Extra(turno1);
		} else {
			while(temp != circular2){
				if(temp->turno == turno1){
					anterior->siguiente = temp->siguiente;
					temp = anterior;
					return;
				}
				anterior = temp;
				temp = temp->siguiente;
			}
		}
	}
}

/*ATENDER CAJA*/
void Atender(int carreta, int cliente, int turno){
 	GNodo *temporal = lista;
	while(strcmp(temporal->estado,"LIBRE") != 0  && temporal->seguente !=NULL) {
 		temporal = temporal->seguente;
 	}
	if(strcmp(temporal->estado,"LIBRE") == 0){
		strcpy(temporal->estado, "OCUPADO");
		temporal->no_carreta = carreta;
		temporal->no_cliente = cliente;
		temporal->turno = turno;
	}
 }

/*MOSTRAR ESTRUCTURAS*/
void Recorrer(){
	
	GNodo *temp1 = p1nodo;		
			while(temp1!=NULL)
			{
				printf("Número de Carreta pila1: %d\n ", temp1->id);
				temp1 = temp1->before;
			}
			printf("\n");
			
	GNodo *temp2 = p2nodo;		
			while(temp2!=NULL)
			{
				printf("Número de Carreta pila2: %d\n ", temp2->id);
				temp2 = temp2->before;
			}
			printf("\n");
			
	GNodo *temp3 = p3nodo;
			while(temp3!=NULL)
			{
				printf("Número de Carreta pila3: %d\n ", temp3 ->id);
				temp3  = temp3->before;
			}
			printf("\n");
			
	GNodo *tempPila = p4nodo;		
			while(tempPila!=NULL)
			{
				printf("Número de Carreta pila4: %d\n ", tempPila->id);
				tempPila = tempPila->before;
			}
			printf("\n");
			
	GNodo *tempM = CPnodo;
		while(tempM!=NULL)
			{
				printf("No. Cliente: %d\n Edad Cliente: %d\n Genero Cliente: %s\n\n ", tempM->cliente, tempM->edad, tempM->genero);
				tempM = tempM->siguiente;
			}
			printf("\n");

	 GNodo *tempC = circular1;		
			while(tempC != circular2)
			{
				printf("No Carreta: %d\n No. Cliente: %d\n Edad: %d\n Turno: %d\n\n", tempC->valor, tempC->cliente, tempC->edad, tempC->turno);
				tempC = tempC->siguiente;
			}
			printf("No Carreta: %d\n No. Cliente: %d\n Edad: %d\n Turno: %d\n\n", tempC->valor, tempC->cliente, tempC->edad, tempC->turno);
			printf("\n");
			
	  GNodo *tempCN = COnodo;		
		while(tempCN!=NULL)
			{
				printf("Número de Cliente: %d\n Edad: %d\n úmero de Carreta: %d\n\n ", tempCN->cliente, tempCN->edad, tempCN->valor);
				tempCN = tempCN->siguiente;
			}
			printf("\n");
			
	  GNodo *tempCO = CNnodo;		
		while(tempCO!=NULL)
			{
				printf("Número de Cliente: %d\n Edad: %d\n Número de Carreta: %d\n\n ", tempCO->cliente, tempCO->edad, tempCO->valor);
				tempCO = tempCO->siguiente;
			}
			printf("\n");

		GNodo *temporal = lista;
		
		while(temporal->seguente!=NULL){
			printf("No Caja: %d\n Estado: %s\n Cliente Atendido: %d\n Número de Carreta: %d\n Número de Clientes Atendidos: %d\n Turnos: %d\n\n ", temporal->no_caja, temporal->estado, temporal->no_cliente, temporal->no_carreta, temporal->no_atendido, temporal->turno);
			temporal = temporal->seguente;
		}
		
		printf("No Caja: %d\n Estado: %s\n Cliente Atendido: %d\n Número de Carreta: %d\n Número de Clientes Atendidos: %d\n Turnos: %d\n\n ", temporal->no_caja, temporal->estado, temporal->no_cliente, temporal->no_carreta, temporal->no_atendido, temporal->turno);
				
}

void Graficar(){
	
	
	FILE* grafico = fopen("Grafico.dot","w+");

	fprintf(grafico,"digraph {\n");
	
		fprintf(grafico, "subgraph cluster_1{");
		fprintf(grafico,"style = filled;");
	    fprintf(grafico,"node[shape=record,rankdir=LR]; \n");
        fprintf(grafico,"node1 [label = \"{Pila 1 \n");
        
		GNodo *tempG1 = p1nodo;		
			while(tempG1!=NULL)
			{
				fprintf(grafico,"|Carreta: %d\n ", tempG1->id);
				tempG1 = tempG1->before;
			}

		fprintf(grafico, "}\"];");
		fprintf(grafico,"\n}");//<-----grafica pila1
		
		fprintf(grafico, "subgraph cluster_2{");
		fprintf(grafico,"style = filled;");
	    fprintf(grafico,"node[shape=record,rankdir=LR]; \n");
        fprintf(grafico,"node2 [label = \"{Pila 2 \n");
        
		GNodo *tempG2 = p2nodo;		
			while(tempG2!=NULL)
			{
				fprintf(grafico,"|Carreta: %d\n ", tempG2->id);
				tempG2 = tempG2->before;
			}

		fprintf(grafico, "}\"];");
		fprintf(grafico,"\n}");//<-----grafica pila2

		fprintf(grafico, "subgraph cluster_3{");
		fprintf(grafico,"style = filled;");
	    fprintf(grafico,"node[shape=record,rankdir=LR]; \n");
        fprintf(grafico,"node3 [label = \"{Pila 3 \n");
        
		GNodo *tempG3 = p3nodo;		
			while(tempG3!=NULL)
			{
				fprintf(grafico,"|Carreta: %d\n ", tempG3->id);
				tempG3 = tempG3->before;
			}

		fprintf(grafico, "}\"];");
		fprintf(grafico,"\n}");//<-----grafica pila3

		fprintf(grafico, "subgraph cluster_4{");
		fprintf(grafico,"style = filled;");
	    fprintf(grafico,"node[shape=record,rankdir=LR]; \n");
        fprintf(grafico,"node4 [label = \"{Pila 4 \n");
        
		GNodo *tempG4 = p4nodo;		
			while(tempG4!=NULL)
			{
				fprintf(grafico,"|Carreta: %d\n ", tempG4->id);
				tempG4 = tempG4->before;
			}

		fprintf(grafico, "}\"];");
		fprintf(grafico,"\n}");//<-----grafica pila4	
	
			//Grafica de cola de prioridad
			fprintf(grafico, "subgraph cluster_0{");
			fprintf(grafico, "style=filled;");
			fprintf(grafico, "label=\"COLA DE PRIORIDAD\";");
			fprintf(grafico, "node [ shape = record; rankdir=TB;];");
			fprintf(grafico, "node0 [ label = \" ");
			
		GNodo *temp = CPnodo;
		while(temp!=NULL)
			{
				fprintf(grafico,"| Cliente:%d\\nEdad:%d\\nGenero:%s ", temp->cliente, temp->edad, temp->genero);
				temp = temp->siguiente;
			}
			
		   fprintf(grafico,"\n \"];");
		   fprintf(grafico,"\n}");//<-----termina grafica cola 
			
			//Grafica de cola de espera normal
			fprintf(grafico, "subgraph cluster_5{");
			fprintf(grafico, "style=filled;");
			fprintf(grafico, "label=\"COLA DE ESPERA NORMAL\";");
			fprintf(grafico, "node [ shape = record; rankdir=TB;];");
			fprintf(grafico, "node5 [ label = \" ");
			
	  GNodo *tempCN = CNnodo;		
		while(tempCN!=NULL)
			{
				fprintf(grafico,"|Cliente: %d\\nEdad: %d\\nCarreta: %d ", tempCN->cliente, tempCN->edad, tempCN->valor);
				tempCN = tempCN->siguiente;
			}
			
		   fprintf(grafico,"\n \"];");
		   fprintf(grafico,"\n}");//<-----termina grafica cola 


			//Grafica de cola de espera oro
			fprintf(grafico, "subgraph cluster_6{");
			fprintf(grafico, "style=filled;");
			fprintf(grafico, "label=\"COLA DE ESPERA ORO\";");
			fprintf(grafico, "node [ shape = record; rankdir=TB;];");
			fprintf(grafico, "node6 [ label = \" ");
			
	  GNodo *tempCO = COnodo;		
		while(tempCO!=NULL)
			{
				fprintf(grafico,"|Cliente: %d\\nEdad: %d\\nCarreta: %d ", tempCO->cliente, tempCO->edad, tempCO->valor);
				tempCO= tempCO->siguiente;
			}
			
		   fprintf(grafico,"\n \"];");
		   fprintf(grafico,"\n}");//<-----termina grafica cola 

		   //Grafica de lista circular
	       fprintf(grafico, "subgraph cluster_7{");
           fprintf(grafico,"\nlabel = \"Lista Simple\";");
           fprintf(grafico,"\ncolor = lightgrey;\n");
           fprintf(grafico,"node[shape=box, color=lightblue, style=filled];\n");
           


			GNodo *tempC = circular1;
			int nodoGrafico = 100;
			
			while(tempC->siguiente != circular1)
			{
				fprintf(grafico, "node%d [ label = \" ",nodoGrafico);
				fprintf(grafico,"Carreta: %d\\nCliente: %d\\nEdad: %d\\nTurno: %d", tempC->valor, tempC->cliente, tempC->edad, tempC->turno);
				fprintf(grafico,"\"]; \n ");
				tempC = tempC->siguiente;
				nodoGrafico = nodoGrafico + 1;
			}
				fprintf(grafico, "node%d [ label = \" ",nodoGrafico);
				fprintf(grafico,"Carreta: %d\\nCliente: %d\\nEdad: %d\\nTurno: %d", tempC->valor, tempC->cliente, tempC->edad, tempC->turno);
				fprintf(grafico," \"]; \n");
			//fprintf(grafico, "No Carreta: %d\n No. Cliente: %d\n Edad: %d\n Turno: %d\n\n", tempC->valor, tempC->cliente, tempC->edad, tempC->turno);
			nodoGrafico = 100;
			tempC = circular1;
			while(tempC->siguiente != circular1)
			{
				fprintf(grafico, "node%d -> node%d;", nodoGrafico, nodoGrafico + 1);
				tempC = tempC->siguiente;
				nodoGrafico = nodoGrafico + 1;
			}
			fprintf(grafico, "node%d -> node%d;", nodoGrafico, 100);
           
		   fprintf(grafico,"\n}");//<-----termina grafica lista circular



			fprintf(grafico,"\n}");
			            fclose(grafico);
			            system("dot -Tjpg Grafico.dot -o Practica1.jpg");
			            system("gnome-open Practica1.jpg");
}

