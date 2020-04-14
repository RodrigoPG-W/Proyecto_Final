#include <stdio.h>
#include <string.h>				//Función strcmpy.
#include <stdlib.h>				//Permite usar malloc.

typedef struct nodo{				//typedef permite simplificar la declaración del nodo en el resto del programa.
	char item[16];
	short cantidad;
	struct nodo *NEXT;
} nodo;

nodo *HEAD = NULL;				//Apuntador al primer (HEAD) y último (TAIL) elemento.
nodo *TAIL = NULL;

int Menu();					//Impresión del menú y selección.
//void InsertarArchivo();			//Funciones del menú.
void Buscar();					//Método para buscar nodos aplicado en otras funciones.
void Insertar();				//Ingresa nodos.
void Eliminar();				//Tras una búsqueda, se cambian las referencias del nodo anterior para "eliminarlo"
void Modificar();				//Tras una búsqueda, permite modificar los datos del nodo.
void Mostrar();					//Imprime el conjunto de nodos (inventario).

int main(){
	int Opcion;
	do
		{
			Opcion=Menu();
			switch(Opcion)
				{
					case 1:
						printf("\n\n");
						Insertar();
						break;
					case 2:
						printf("\n\n");
						Buscar();
						break;	
					case 3:
						printf("\n\n");
						Modificar();
						break;
					case 4:
						printf("\n\n");
						Eliminar();
						break;
					case 5:
						printf("\n\n");	
						Mostrar();
						break;
					case 6:
						printf("\n\nGracias por usar el programa...");
						break;
					default:
						printf("\n\nOpci%cn no v%clida\nPor favor ingrese un n%cmero del men%c.\n\n",162,160,163,163);	
				}
		}
	while(Opcion != 6);
	return 0;
}

void Buscar(){
	int r=1,x,BusquedaCompleta;								//Auxiliar para función strcmpy y el estado de la búsqueda.
	char itemBuscado[16];									//Guarda el nodo buscado.
	while (r==1)										//Permite repetir el proceso hasta que el usuario decida.
		{
			nodo *actual = (nodo*) malloc(sizeof(nodo));	//Creación de un apuntador para recorrer la lista.
			actual = HEAD;								//Se inicia por HEAD.
			BusquedaCompleta=0;							//Inicia el estado de la búsqueda en "no encontrado".				 			
			printf("Ingrese el item a Buscar: ");
			scanf("%s", &itemBuscado);
			if(HEAD!=NULL)								//Comprobación de que la lista no esté vacía.
				{											
					while(actual!=NULL&&BusquedaCompleta!=1)//Recorre hasta el TAIL y espera que la búsqueda sea exitosa.
						{
							x=strcmp(actual->item,itemBuscado);
							if(x == 0)				//Verificación que el item sea parte de un nodo.
								{
									printf("\nEl nodo con el item ( %s ) Encontrado\n\n", itemBuscado);
									BusquedaCompleta = 1;	//Al asignar a encontrado 1, se "notifica" que la búsqueda está completa exitosamente.
								}
				
							actual = actual->NEXT;			//Se recorre al siguiente elemento.
						}
					if(BusquedaCompleta == 0)				//Cuando se llega a TAIL y la búsqueda está completa pero no exitosamente.
						{
							printf("\nNodo no encontrado\n\n");
						}
				}
			else
				{
					printf("\nLa lista se encuentra vac%ca\n\n",161);
				}
			printf("\nB%csqueda terminada.\n\nSi desea realizar otra b%csqueda, presione 1.\n",163,163);
			scanf("%i",&r);								//Verifica la repetición del bucle.
		}
}

void Insertar(){
	int r=1;
	while (r==1)							//Permite repetir el proceso hasta que el usuario decida.
		{
			nodo *nuevo = (nodo*) malloc(sizeof(nodo));	//Asigna dinámicamente el espacio para un nodo nuevo mediante un apuntador.
			printf("Ingrese el item que contendra el nuevo Nodo y la cantidad (separados con ENTER): ");
			scanf("%s%i", &nuevo->item,&nuevo->cantidad);	//Se asignan los items a cada miembro de la estructura
			if(HEAD==NULL)					//Comprueba si la lista está vacía mediante la referencia HEAD
				{
					HEAD = nuevo;			//HEAD apunta al primer elemento
					HEAD->NEXT = NULL;		//El último elemento apunta a NULL. Al ser el primero, será este.
					TAIL = nuevo;			//TAIL también será el primer elemento.
				}
			else
				{
					TAIL->NEXT = nuevo;		//el nodo pasado ahora apunta al nodo insertado.
					nuevo->NEXT = NULL;		//la referencia NEXT del nuevo nodo apunta a NULL porque es el último ahora.
					TAIL = nuevo;
				}
			printf("\nNodo ingresado con %cxito\n\nSi desea agregar otro nodo, presione 1.\n",130);
			scanf("%i",&r);					//Verifica la repetición del bucle.
		}
	}

void Eliminar(){
	int r=1;
	int x, BusquedaCompleta;					//Auxiliar para función strcmpy el estado de la búsqueda.
	char itemBuscado[16];						//Guarda el nodo buscado.
	while (r==1)							//Permite repetir el proceso hasta que el usuario decida.
		{
			nodo *actual = (nodo*) malloc(sizeof(nodo));	//Creación de un apuntador para recorrer la lista.
			nodo *anterior = (nodo*) malloc(sizeof(nodo));	//Creación de un apuntador anterior para la lista.
			actual = HEAD;					//Se inicia por HEAD.
			anterior = NULL;				//Al no haber algo antes de HEAD, se inicia en NULL.
			BusquedaCompleta=0;				//Inicia el estado de la búsqueda en "no encontrado".
			printf("Ingrese el item del nodo a Eliminar: ");
			scanf("%s", &itemBuscado);
			if(HEAD!=NULL)					//Comprobación de que la lista no esté vacía.
				{
					while(actual!=NULL&&BusquedaCompleta!=1)//Recorre hasta el TAIL y espera que la búsqueda sea exitosa.
						{			
							x=strcmp(actual->item,itemBuscado);
							if(x == 0)	//Verificación que el item sea parte de un nodo.
								{					//Selección de los posibles casos a eliminar:				
									if(actual == HEAD)		//	>Primer nodo:
										{			//Se actualiza su apuntador primero al siguiente nodo.
											HEAD = HEAD->NEXT;	
										}
									else if(actual == TAIL)		//	>Último nodo:
											{		//El miembro apuntador siguiente del nodo anterior pasa a NULL
												anterior->NEXT = NULL;
												TAIL = anterior;//Se actualiza su apuntador último al anterior.
											}
										else			//	>Otro nodo:
											{		//El miembro apuntador siguiente del nodo anterior se actualiza por el miembro apuntador siguiente del nodo actual.
												anterior->NEXT = actual->NEXT;	
											}
									printf("\nNodo eliminado con %cxito",130);
									BusquedaCompleta = 1;
								}
							anterior = actual;				//El apuntador anterior pasa a ser el actual.
							actual = actual->NEXT;				//Se recorre al siguiente elemento.
						}
					if(BusquedaCompleta == 0)					//Cuando se llega a TAIL y la búsqueda está completa pero no exitosamente.
						{
							printf("\nNodo no encontrado\n\n");
						}
					else
						{
							free(anterior);		//Libera memoria del apuntador auxiliar anterior.
						}
				}
			else
				{
					printf("\nLa lista se encuentra vac%ca\n\n",161);
				}
			printf("\nEliminaci%cn terminada.\n\nSi desea eliminar otro item, presione 1.\n",162);
			scanf("%i",&r);						//Verifica la repetición del bucle.
		}
}

void Modificar(){
	int r=1;
	int x, BusquedaCompleta;								//Auxiliar para función strcmpy el estado de la búsqueda.
	char itemBuscado[16];									//Guarda el nodo buscado.
	while (r==1)										//Permite repetir el proceso hasta que el usuario decida.
		{
			nodo *actual = (nodo*) malloc(sizeof(nodo));				//Creación de un apuntador para recorrer la lista.
			actual = HEAD;								//Se inicia por HEAD.
			BusquedaCompleta=0;							//Inicia el estado de la búsqueda en "no encontrado" (álgebra booleana).
			printf("Ingrese el item del nodo a Buscar para Modificar: ");
			scanf("%s", &itemBuscado);
			if(HEAD!=NULL)								//Comprobación de que la lista no esté vacía.
				{
					while(actual!=NULL&&BusquedaCompleta!=1)//Recorre hasta el TAIL y espera que la búsqueda sea exitosa.
						{
							x=strcmp(actual->item,itemBuscado);
							if(x == 0)				//Verificación que el item sea parte de un nodo.
								{
									printf("\nEl nodo con el item ( %s ) Encontrado", itemBuscado);
									/*REALIZAR 3 CONDICIONALES PARA MÁS OPTIMIZACIÓN*/
									printf("\nIngrese los nuevos valores para este Nodo (separados con ENTER): ");//Tras encontrarse el nodo, se cambian los items del mismo.
									scanf("%s%i", &actual->item,&actual->cantidad);
									printf("\nNodo modificado con %cxito\n\n",130);
									BusquedaCompleta = 1;	//Al asignar a encontrado 1, se "notifica" que la búsqueda está completa exitosamente.
								}
							actual = actual->NEXT;			//Se recorre al siguiente elemento.
						}
					if(BusquedaCompleta == 0)				//Cuando se llega a TAIL y la búsqueda está completa pero no exitosamente.
						{
							printf("\nNodo no encontrado\n\n");
						}
				}
			else
				{
					printf("\nLa lista se encuentra vac%ca\n\n",161);
				}
			printf("\nModificaci%cn terminada.\n\nSi desea realizar otra modificaci%cn, presione 1.\n",162,162);
			scanf("%i",&r);								//Verifica la repetición del bucle.
		}
}

void Mostrar(){
	nodo *actual = (nodo*) malloc(sizeof(nodo));			//Creación de un apuntador para recorrer la lista.
	actual = HEAD;							//Se inicia por HEAD.
	if(HEAD!=NULL)							//Comprobación de que la lista no esté vacía.
		{
			printf("\n PRODUCTO:		CANTIDAD:");
			while(actual != NULL)				//Condición para recorrer hasta el TAIL de la lista.
				{
					printf("\n %s			[%i]", actual->item,actual->cantidad);
					actual = actual->NEXT;
				}
		}
	else
		{
			printf("\nLa lista se encuentra vac%ca\n\n",161);
		}
}

int Menu(){
	int z;
	printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
	printf("\n|                  |  %c INVENTARIO %c  |                   |",178,178);
	printf("\n*------------------*------------------*-------------------*");
	printf("\n| 1.Insertar item  | 3.Modificar item | 5.Mostrar         |");//Opción de guardar en 5.
	printf("\n*------------------*------------------*-------------------*");
	printf("\n| 2.Buscar item    | 4.Eliminar item  | 6. Salir          |");
	printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
	printf("\n\n %cQu%c desea hacer sobre su inventario?: ",168,130);
	scanf("%d", &z);
	return z;
}
