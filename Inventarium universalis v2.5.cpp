#include <stdio.h>
#include <string.h>				//Función strcmpy y strcat.
#include <stdlib.h>				//Permite usar malloc.
#include <ctype.h>				//toupper.

typedef struct nodo{			//typedef permite simplificar la declaración del nodo en el resto del programa.
	char item[31];				//Nombre del producto en inventario.
	short cantidad;				//Cantidad del producto en inventario.
	float precio;				//Precio del producto en inventario.
	struct nodo *NEXT;			//Referencia Next al siguiente elemento de la lista.
} nodo;

nodo *HEAD = NULL;				//Apuntador al primer (HEAD) y último (TAIL) elemento. Iniciados en NULL pues no existe la lista.
nodo *TAIL = NULL;
								//Funciones del menú.
void Menu();					//Impresión del menú y selección.
void Ayuda(char menu);			//Muestra información relevante del uso del programa.
void InsertarArchivo();			//Permite la lectura de nodos a partir de un archivo creado previamente.
void Buscar();					//Busca un nodo en el inventario y muestra su contenido.
void Insertar();				//Inserta un nuevo nodo al inventario.
void Eliminar();				//Busca un nodo y, de existir, mueve las referencias para "eliminarlo".
void Modificar();				//Busca un nodo y, de existir, es capaz de modificar su contenido.
void Mostrar();					//Muestra el inventario.
void Guardar(char Sobreescribir);//Permite guardar el inventario en un archivo .INVUNI.

char NombreArchivo[50];			//Almacena el nombre del archivo.
char OpcionSobreescribir;		//Auxiliar para mantener el nombre de un archivo.

int main(){
	char Opcion,OpcionArchivo,r='1';			//Auxiliares para la selección en los menús.
	printf("%cBienvenid@!\n\n",173);
	while(r=='1')										//Condición para repetir el menú en caso de opción no valida. Tras ejecutarse una acción se rompe el ciclo.
		{
			printf("Seleccione una opci%cn:\nA-Crear nuevo inventario.\nB-Cargar inventario.\nC-Salir.\nD-Ayuda.",162);
			scanf("%s",&OpcionArchivo);
			OpcionArchivo=toupper(OpcionArchivo);		//Permite quitar sensibilidad de minúsculas.
			switch(OpcionArchivo)
				{
					case 'A':							//No se abre aún el archivo para evitar uso innecesario de memoria
						printf("\nSe crear%c un nuevo archivo\n\n",160);
						r=0;
						break;
					case 'B':
						InsertarArchivo(); 
						r='0';
						break;
					case 'C':
						Opcion='F';						//Con esto se evita que el siguiente ciclo se realice.
						r='0';
						break;
					case 'D':
						Opcion='0';
						Ayuda(Opcion);
						r='1';
						break;
					default:
						printf("\n\nOpci%cn no v%clida.\nPor favor ingrese una letra del men%c.\n\n",162,160,163);
						r='1';						//Se tuvo que revalidar para evitar malfuncionamiento del programa.
				}
		}
	while(Opcion != 'F')								//Permite realizar múltiples tareas sobre el inventario antes de guardar.
		{
			Menu();
			scanf("%s", &Opcion);
			Opcion=toupper(Opcion);						//Permite quitar sensibilidad de minúsculas.
			switch(Opcion)
				{
					case 'A':
						printf("\n\n");
						Insertar();
						printf("\n\n");
						break;
					case 'B':
						printf("\n\n");
						Buscar();
						printf("\n\n");
						break;	
					case 'C':
						printf("\n\n");
						Modificar();
						printf("\n\n");
						break;
					case 'D':
						printf("\n\n");
						Eliminar();
						printf("\n\n");
						break;
					case 'E':
						printf("\n\n");	
						Mostrar();
						printf("\n\n");
						break;
					case 'F':
						break;
					case 'G':
						printf("\n\n");
						if (OpcionArchivo=='B') 		//Sólo se pregunta si se ha cargado un inventario.
							{
								printf("Si desea guardar el inventario con el mismo nombre, presione 1.\nNOTA: el inventario que cargaste inicialmente ser%c reemplazado por el inventario actual.",160);
								scanf("%s",&OpcionSobreescribir);
							}
						Guardar(OpcionSobreescribir);
						break;
					case 'H':
						printf("\n\n");	
						Ayuda(Opcion);
						Opcion='0';
						printf("\n\n");
						break;
					default:
						printf("\n\nOpci%cn no v%clida\nPor favor ingrese una letra del men%c.\n\n",162,160,163);
						Opcion='0';
				}
		}
	printf("\n\n\n\nGracias por usar el programa...");
	getchar();
	return 0;
}

void Buscar(){
	int x,BusquedaCompleta;								//Auxiliar para función strcmpy y el estado de la búsqueda.
	char r='1',itemBuscado[30];									//Guarda el nodo buscado.
	while (r=='1')											//Permite repetir el proceso hasta que el usuario decida.
		{
			nodo *actual = (nodo*) malloc(sizeof(nodo));	//Creación de un apuntador para recorrer la lista.
			actual = HEAD;									//Se inicia por HEAD.
			BusquedaCompleta=0;								//Inicia el estado de la búsqueda en "no encontrado".				 			
			printf("Ingrese el item a Buscar: ");
			scanf("%s", &itemBuscado);
			if(HEAD!=NULL)									//Comprobación de que la lista no esté vacía.
				{											
					while(actual!=NULL&&BusquedaCompleta!=1)//Recorre hasta el TAIL y espera que la búsqueda sea exitosa.
						{
							x=strcmp(actual->item,itemBuscado);
							if(x == 0)						//Verificación que el item sea parte de un nodo.
								{
									printf("\nNodo encontrado.\nProducto: %s\nCantidad: %i\nPrecio: $%f", itemBuscado,actual->cantidad,actual->precio);
									BusquedaCompleta = 1;	//Al asignar a encontrado 1, se "notifica" que la búsqueda está completa exitosamente.
								}
				
							actual = actual->NEXT;			//Se recorre al siguiente elemento.
						}
					if(BusquedaCompleta == 0)				//Cuando se llega a TAIL y la búsqueda está completa pero no exitosamente.
						{
							printf("\nNodo no encontrado.\n\n");
						}
				}
			else
				{
					printf("\nLa lista se encuentra vac%ca\n\n",161);
				}
			printf("\n\nB%csqueda terminada.\n\nSi desea realizar otra b%csqueda, presione 1. De lo contrario, presione cualquier tecla.\n",163,163);
			scanf("%s",&r);									//Verifica la repetición del bucle.
		}
}

void Insertar(){
	char r='1';
	while (r=='1')											//Permite repetir el proceso hasta que el usuario decida.
		{
			nodo *nuevo = (nodo*) malloc(sizeof(nodo));		//Asigna dinámicamente el espacio para un nodo nuevo mediante un apuntador.
			printf("Ingrese el producto, cantidad y precio (separados con ENTER):\n");
			scanf("%s%i%f", &nuevo->item,&nuevo->cantidad,&nuevo->precio);//Se asignan los items a cada miembro de la estructura
			if(HEAD==NULL)									//Comprueba si la lista está vacía mediante la referencia HEAD
				{
					HEAD = nuevo;							//HEAD apunta al primer elemento
					HEAD->NEXT = NULL;						//El último elemento apunta a NULL. Al ser el primero, será este.
					TAIL = nuevo;							//TAIL también será el primer elemento.
				}
			else
				{
					TAIL->NEXT = nuevo;						//el nodo pasado ahora apunta al nodo insertado.
					nuevo->NEXT = NULL;						//la referencia NEXT del nuevo nodo apunta a NULL porque es el último ahora.
					TAIL = nuevo;
				}
			printf("\nNodo ingresado con %cxito\n\nSi desea agregar otro nodo, presione 1. De lo contrario, presione cualquier tecla.\n",130);
			scanf("%s",&r);									//Verifica la repetición del bucle.
		}
	}

void Eliminar(){
	int x, BusquedaCompleta;								//Auxiliar para función strcmpy el estado de la búsqueda.
	char r='1',itemBuscado[16];								//Guarda el nodo buscado.
	while (r=='1')											//Permite repetir el proceso hasta que el usuario decida.
		{
			nodo *actual = (nodo*) malloc(sizeof(nodo));	//Creación de un apuntador para recorrer la lista.
			nodo *anterior = (nodo*) malloc(sizeof(nodo));	//Creación de un apuntador anterior para la lista.
			actual = HEAD;									//Se inicia por HEAD.
			anterior = NULL;								//Al no haber algo antes de HEAD, se inicia en NULL.
			BusquedaCompleta=0;								//Inicia el estado de la búsqueda en "no encontrado".
			printf("Ingrese el item del nodo a Eliminar: ");
			scanf("%s", &itemBuscado);
			if(HEAD!=NULL)									//Comprobación de que la lista no esté vacía.
				{
					while(actual!=NULL&&BusquedaCompleta!=1)//Recorre hasta el TAIL y espera que la búsqueda sea exitosa.
						{			
							x=strcmp(actual->item,itemBuscado);
							if(x == 0)						//Verificación que el item sea parte de un nodo.
								{							//Selección de los posibles casos a eliminar:				
									if(actual == HEAD)		//	>Primer nodo:
										{					//Se actualiza su apuntador primero al siguiente nodo.
											HEAD = HEAD->NEXT;	
										}
									else if(actual == TAIL)	//	>Último nodo:
											{				//El miembro apuntador siguiente del nodo anterior pasa a NULL
												anterior->NEXT = NULL;
												TAIL = anterior;//Se actualiza su apuntador último al anterior.
											}
										else				//	>Otro nodo:
											{				//El miembro apuntador siguiente del nodo anterior se actualiza por el miembro apuntador siguiente del nodo actual.
												anterior->NEXT = actual->NEXT;	
											}
									printf("\nNodo eliminado con %cxito",130);
									BusquedaCompleta = 1;
								}
							anterior = actual;				//El apuntador anterior pasa a ser el actual.
							actual = actual->NEXT;			//Se recorre al siguiente elemento.
						}
					if(BusquedaCompleta == 0)				//Cuando se llega a TAIL y la búsqueda está completa pero no exitosamente.
						{
							printf("\nNodo no encontrado.\n\n");
						}
					else
						{
							free(anterior);					//Libera memoria del apuntador auxiliar anterior.
						}
				}
			else
				{
					printf("\nLa lista se encuentra vac%ca.\n\n",161);
				}
			printf("\n\nProceso terminado.\n\nSi desea eliminar otro item, presione 1. De lo contrario, presione cualquier tecla.\n",162);
			scanf("%s",&r);									//Verifica la repetición del bucle.
		}
}

void Modificar(){
	int x, BusquedaCompleta;								//Auxiliar para función strcmpy y el estado de la búsqueda.
	char r='1',r2,itemBuscado[16],OpcionM;					//Guarda el nodo buscado y permite elecciones de modificación.
	while (r=='1')											//Permite repetir el proceso hasta que el usuario decida.
		{
			nodo *actual = (nodo*) malloc(sizeof(nodo));	//Creación de un apuntador para recorrer la lista.
			actual = HEAD;									//Se inicia por HEAD.
			BusquedaCompleta=0;								//Inicia el estado de la búsqueda en "no encontrado" (álgebra booleana).
			printf("Ingrese el producto del nodo a buscar para modificar: ");
			scanf("%s", &itemBuscado);
			if(HEAD!=NULL)									//Comprobación de que la lista no esté vacía.
				{
					while(actual!=NULL&&BusquedaCompleta!=1)//Recorre hasta el TAIL y espera que la búsqueda sea exitosa.
						{
							x=strcmp(actual->item,itemBuscado);
							if(x == 0)						//Verificación que el item sea parte de un nodo.
								{
									printf("\nNodo encontrado.\nProducto: %s\nCantidad: %i\nPrecio: %f", itemBuscado,actual->cantidad,actual->precio);
									r2='1';					//En caso de repetir la modificación, revalida el ciclo al encontrar el item.
									while (r2=='1')
										{
											printf("\n\n\n%cQu%c elemento deseas modificar?:\nA.Producto\tB.Cantidad\tC.Precio\tD.Todos",168,130);
											scanf("%s",&OpcionM);//Tras encontrarse el nodo, se cambian los valores del mismo.
											OpcionM=toupper(OpcionM);//Permite quitar sensibilidad de minúsculas.
											switch(OpcionM)
												{
													case 'A':
														printf("\nIngresa el nuevo producto: ");
														scanf("%s", &actual->item);
													break;
													case 'B':
														printf("\nIngresa la nueva cantidad: ");
														scanf("%i", &actual->cantidad);
													break;
													case 'C':
														printf("\nIngresa el nuevo precio: ");
														scanf("%f", &actual->precio);
													break;
													case 'D':
														printf("\nIngrese los nuevos valores para este Nodo (separados con ENTER): ");
														scanf("%s%i%f", &actual->item,&actual->cantidad,&actual->precio);
													break;
													default:
														printf("\n\nOpci%cn no v%clida.\nPor favor ingrese una letra del men%c.\n\n",162,160,163);
														r2='1';//Se tuvo que revalidar para evitar malfuncionamiento del programa.
												}
											printf("\nNodo modificado con %cxito\nSi desea modificar otro elemento del nodo, preione 1. De lo contrario, presiona cualquier tecla.\n",130);
											scanf("%s",&r2);
										}
									BusquedaCompleta = 1;	//Al asignar a encontrado 1, se "notifica" que la búsqueda está completa exitosamente.
								}
							actual = actual->NEXT;			//Se recorre al siguiente elemento.
						}
					if(BusquedaCompleta == 0)				//Cuando se llega a TAIL y la búsqueda está completa pero no exitosamente.
						{
							printf("\nProducto no encontrado.\n\n");
						}
				}
			else
				{
					printf("\nLa lista se encuentra vac%ca.\n\n",161);
				}
			printf("\n\nModificaci%cn terminada.\n\nSi desea realizar otra modificaci%cn, presione 1. De lo contrario, presione cualquier tecla.\n",162,162);
			scanf("%s",&r);									//Verifica la repetición del bucle.
		}
}

void Mostrar(){
	nodo *actual = (nodo*) malloc(sizeof(nodo));			//Creación de un apuntador para recorrer la lista.
	actual = HEAD;											//Se inicia por HEAD.
	if(HEAD!=NULL)											//Comprobación de que la lista no esté vacía.
		{
			printf("\n PRODUCTO:\t\tCANTIDAD:\t\tPRECIO:");
			while(actual != NULL)							//Condición para recorrer hasta el TAIL de la lista.
				{
					printf("\n %s\t\t[%i]\t\t$%f", actual->item,actual->cantidad,actual->precio);
					actual = actual->NEXT;
				}
		}
	else
		{
			printf("\nLa lista se encuentra vac%ca\n\n",161);
		}
}

void Guardar(char Sobreescribir){
	FILE *B;												//Permite crear el archivo.
	nodo *actual = (nodo*) malloc(sizeof(nodo));			//Creación de un apuntador para recorrer la lista.
	actual = HEAD;											//Se inicia por HEAD.
	if (Sobreescribir!='1')									//Verifica que el usuario quiera sobreescribir un inventario existente.
		{
			printf("\nIngrese el nombre que desea asignarle a su archivo:\n");
			scanf("%s",&NombreArchivo);					//Se ingresa el nombre del archivo de salida.
			strcat(NombreArchivo,".invuni");				//Agrega la extensión del programa.
		}
	B=fopen(NombreArchivo,"w+t");							//Se abre el archivo en modo de "sobreescrituta". Si existe un archivo de nombre homónimo, se borrará.
	if(HEAD!=NULL)											//Comprobación de que la lista no esté vacía.
		{
			while(actual != NULL)							//Condición para recorrer hasta el TAIL de la lista.
				{
					fprintf(B,"%s %i %f\n", actual->item,actual->cantidad,actual->precio);
					actual = actual->NEXT;
				}
		}
	else
		{
			printf("\nLa lista se encuentra vac%ca\n\n",161);
		}
	printf("\n\nProceso completado con %cxito.\n\n",130);
	fclose(B);												//Cierra el archivo y limpia el búffer.
	fflush(stdin);
}

void InsertarArchivo(){
	char r='1';
	while(r=='1')
		{
			FILE *A;													//Apuntador auxiliar para abrir el archivo.
			printf("\nIngrese el nombre del archivo (inventario):\n  ");
			scanf("%s",&NombreArchivo);
			strcat(NombreArchivo,".invuni");							//Agrega la extensión del programa.
			if ((A=fopen(NombreArchivo,"r"))==NULL)						//Permite comprobar la existencia del archivo.
				{
					printf("\nNo existe el archivo.\nSi desea rectificar o cargar un inventario v%clido, presione 1.\nSi desea continuar abriendo un nuevo inventario, presione cualquier tecla.",160);
					scanf("%s",&r);										//Verifica la repetición del bucle.
				}
			else
				{
					while(feof(A)==0)									//Instrucción que permite leer hasta el final del archivo.
						{
							nodo *nuevo = (nodo*) malloc(sizeof(nodo));	//Asigna dinámicamente el espacio para un nodo nuevo mediante un apuntador.
							fscanf(A,"%s %i %f\n",&nuevo->item,&nuevo->cantidad,&nuevo->precio);//Se asignan los valores a cada miembro de la estructura a partir del archivo.
							if(HEAD==NULL)								//Comprueba si la lista está vacía mediante la referencia HEAD.
								{
									HEAD = nuevo;						//HEAD apunta al primer elemento.
									HEAD->NEXT = NULL;					//El último elemento apunta a NULL. Al ser el primero, será este.
									TAIL = nuevo;						//TAIL también será el primer elemento.
								}
							else
								{
									TAIL->NEXT = nuevo;					//el nodo pasado ahora apunta al nodo insertado.
									nuevo->NEXT = NULL;					//la referencia NEXT del nuevo nodo apunta a NULL porque es el último ahora.
									TAIL = nuevo;
								}
						}
					r='2';												//Rompe el ciclo pues ya se cargó el inventario.
				}
			fclose(A);													//Cierra el archivo y limpia el búffer.
			fflush(stdin);
		}
}	

void Menu(){
	printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
	printf("\n|                  |  %c INVENTARIO %c  |                   |",178,178);
	printf("\n*------------------*------------------*-------------------*");
	printf("\n| A.Insertar item  | C.Modificar item | E.Mostrar         |");
	printf("\n*------------------*------------------*-------------------*");
	printf("\n| B.Buscar item    | D.Eliminar item  | F. Salir          |");
	printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
	printf("\n  G.Guardar inventario		H.Ayuda ");
	printf("\n\n %cQu%c desea hacer sobre su inventario?: ",168,130);
}

void Ayuda(char menu){
	if (menu=='0')
		{
			printf("A) Si desea empezar un inventario nuevo, eliga esta opci%cn. Al terminar de modificar podr%c asignarle un nombre.\n\n",162,160);
			printf("B) Permite elegir un archivo generado previamente para cargar los nodos del mismo, poniendo el nombre del archivo (sin extensi%cn).\n\n",162);
			printf("C) Cierra el programa.\n\n");
		}
	else
		{
			printf("A) Inserta un nuevo nodo al inventario. El nombre no debe tener espacios y no debe tener m%cs de 30 caracteres.\n\n",162,160);
			printf("B) Busca un nodo en el inventario a partir del nombre del producto (sensible a may%cs/min%cs) y muestra su contenido.\n\n",163,163);
			printf("C) Busca un nodo en el inventario a partir del nombre del producto (sensible a may%cs/min%cs) y puede modificar cada miembro su contenido.\n\n",163,163);
			printf("D) Busca un nodo en el inventario a partir del nombre del producto (sensible a may%cs/min%cs) y lo elimina del inventario.\n\n",163,163);
			printf("E) Muestra el inventario completo en forma descendente (se muestran en el orden en el que fueron agregados).\n\n");
			printf("F) Cierra el programa.\n\n");
			printf("G) Almacena el inventario en su estado actual en un archivo. Puede asignarse un nombre o conservar el mismo si fue cargado y desea actualizarlo.\n\n");		
		} 
}
