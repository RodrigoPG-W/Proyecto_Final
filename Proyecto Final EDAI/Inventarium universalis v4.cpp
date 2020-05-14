#include <stdio.h>
#include <string.h>				//Funci�n strcmpy y strcat.
#include <stdlib.h>				//Permite usar malloc.
#include <ctype.h>				//toupper.
#include <windows.h>			//Funci�n cls y goto.

typedef struct nodo{			//typedef permite simplificar la declaraci�n del nodo en el resto del programa.
	char item[21];				//Nombre del producto en inventario.
	int cantidad;				//Cantidad del producto en inventario.
	float precio;				//Precio del producto en inventario.
	struct nodo *NEXT;			//Referencia Next al siguiente elemento de la lista.
} nodo;

nodo *HEAD;						//Apuntador al primer (HEAD) y �ltimo (TAIL) elemento. Iniciados en NULL pues no existe la lista.
nodo *TAIL;
								//Funciones del men�.
void Menu();					//Impresi�n del men� y selecci�n.
void Ayuda(char menu);			//Muestra informaci�n relevante del uso del programa.
void InsertarArchivo();			//Permite la lectura de nodos a partir de un archivo creado previamente.
void Buscar();					//Busca un nodo en el inventario y muestra su contenido.
void Insertar();				//Inserta un nuevo nodo al inventario.
void Eliminar();				//Busca un nodo y, de existir, mueve las referencias para "eliminarlo".
void Modificar();				//Busca un nodo y, de existir, es capaz de modificar su contenido.
void Mostrar();					//Muestra el inventario.
void Guardar(char Sobreescribir);//Permite guardar el inventario en un archivo .INVUNI.
void gotoxy(int xc, int yc);	//Permite indicar coordenadas en la pantalla

char r, NombreArchivo[50], OpcionSobreescribir, itemBuscado[21];
int BusquedaCompleta;		//Permite repetir, Almacena el nombre del archivo, Auxiliar para mantener el nombre de un archivo, Almacena par�metro de b�squeda, Auxiliar para verificaci�n de estado de b�squeda

int main(){
	char Iniciar='1';					//Auxiliar para repetir el programa
	char Opcion,OpcionArchivo;			//Auxiliares para la selecci�n en los men�s.
	while (Iniciar=='1')
		{
		HEAD = NULL;						//Inicia la lista. En caso de repetir, reinicia.
		TAIL = NULL;
		r='1';								//Auxiliar para repetici�n.
		printf("%cBienvenid@!\n\n",173);
		while(r=='1')										//Condici�n para repetir el men� en caso de opci�n no valida. Tras ejecutarse una acci�n se rompe el ciclo.
			{
				printf("Seleccione una opci%cn:\nA-Crear nuevo inventario.\nB-Cargar inventario.\nC-Salir.\nD-Ayuda.\n",162);
				scanf("%s",&OpcionArchivo);
				OpcionArchivo=toupper(OpcionArchivo);		//Permite quitar sensibilidad de min�sculas.
				switch(OpcionArchivo)
					{
						case 'A':							//No se abre a�n el archivo para evitar uso innecesario de memoria
							printf("\nSe crear%c un nuevo archivo\n\n",160);
							r='0';
							Sleep(2000);
							break;
						case 'B':
							InsertarArchivo(); 
							r='0';
							Sleep(2000);
							break;
						case 'C':
							Opcion='F';						//Con esto se evita que el siguiente ciclo se realice.
							r='0';
							break;
						case 'D':
							Opcion='0';
							system("cls");
							Ayuda(Opcion);					//Muestra ayuda dependiendo del men� en el que se encuentre.
							r='1';
							break;
						default:
							system("cls");
							printf("\n\nOpci%cn no v%clida.\nPor favor ingrese una letra del men%c.\n\n",162,160,163);
							r='1';							//Se tuvo que revalidar para evitar malfuncionamiento del programa.
					}
			}
		system("cls");
		while(Opcion != 'F')								//Permite realizar m�ltiples tareas sobre el inventario antes de guardar.
			{
				gotoxy(5,1);								//Desplaza y mantiene el men� en una sola coordenada
				Menu();
				scanf("%s", &Opcion);
				Opcion=toupper(Opcion);						//Permite quitar sensibilidad de min�sculas.
				switch(Opcion)
					{
						case 'A':
							printf("\n\n");
							Insertar();
							system("cls");
							break;
						case 'B':
							Buscar();
							system("cls");
							break;	
						case 'C':
							printf("\n\n");
							Modificar();
							system("cls");
							break;
						case 'D':
							printf("\n\n");
							Eliminar();
							system("cls");
							break;
						case 'E':
							printf("\n\n");	
							Mostrar();
							system("cls");
							break;
						case 'F':
							system("cls");
							break;
						case 'G':
							printf("\n\n");
							if (OpcionArchivo=='B') 		//Verifica si se ha cargado un inventario.
								{
									printf("Si desea guardar el inventario con el mismo nombre, presione 1.\nNOTA: el inventario que cargaste inicialmente ser%c reemplazado por el inventario actual.\n",160);
									scanf("%s",&OpcionSobreescribir);
								}
							Guardar(OpcionSobreescribir);
							system("cls");
							break;
						case 'H':
							printf("\n\n");	
							Ayuda(Opcion);
							Opcion='0';
							printf("\n\n");
							system("cls");
							break;
						default:
							printf("\n\nOpci%cn no v%clida\nPor favor ingrese una letra del men%c.\n\n",162,160,163);
							Opcion='0';
					}
				system("cls");
			}
		Opcion='0';
		printf("\n\n\n\nGracias por usar el programa...\n\nSi desea abrir otro inventario, presione 1\n\nDe lo contrario, presione cualquier tecla para salir.");
		scanf("%s",&Iniciar);				//Confirma que se desee repetir para trabajar sobre un nuevo inventario
		system("cls");
		}
	getchar();
	return 0;
}

void Buscar(){
	int x;									//Auxiliar para funci�n strcmpy.
	r='1';									//Permite repetir el proceso hasta que el usuario decida.
	while (r=='1')											
		{
			nodo *actual = (nodo*) malloc(sizeof(nodo));	//Creaci�n de un apuntador para recorrer la lista.
			actual = HEAD;									//Se inicia por HEAD.
			BusquedaCompleta=0;								//Inicia el estado de la b�squeda en "no encontrado".				 			
			printf("Ingrese el producto a Buscar: ");
			scanf("%s", &itemBuscado);
			if(HEAD!=NULL)									//Comprobaci�n de que la lista no est� vac�a.
				{											
					while(actual!=NULL&&BusquedaCompleta!=1)//Recorre hasta el TAIL y espera que la b�squeda sea exitosa.
						{
							x=strcmp(actual->item,itemBuscado);
							if(x == 0)						//Verificaci�n que el item sea parte de un nodo.
								{
									printf("\nNodo encontrado.\nProducto: %s\nCantidad: %i\nPrecio: $%.2f", itemBuscado,actual->cantidad,actual->precio);
									BusquedaCompleta = 1;	//Al asignar a encontrado 1, se "notifica" que la b�squeda est� completa exitosamente.
								}
				
							actual = actual->NEXT;			//Se recorre al siguiente elemento.
						}
					if(BusquedaCompleta == 0)				//Cuando se llega a TAIL y la b�squeda est� completa pero no exitosamente.
						{
							printf("\nNodo no encontrado.\n\n");
						}
				}
			else
				{
					printf("\nLa lista se encuentra vac%ca",161);
				}
			printf("\n\nB%csqueda terminada.\n\nSi desea realizar otra b%csqueda, presione 1. De lo contrario, presione cualquier tecla.\n",163,163);
			scanf("%s",&r);									//Verifica la repetici�n del bucle.
		}
}

void Insertar(){
	r='1';
	while (r=='1')											//Permite repetir el proceso hasta que el usuario decida.
		{
			nodo *nuevo = (nodo*) malloc(sizeof(nodo));		//Asigna din�micamente el espacio para un nodo nuevo mediante un apuntador.
			printf("Ingrese el producto, cantidad y precio (separados con ENTER).\n");
			scanf("%s%i%f", &nuevo->item,&nuevo->cantidad,&nuevo->precio);//Se asignan los elementos a cada miembro de la estructura.
			if(HEAD==NULL)									//Comprueba si la lista est� vac�a mediante la referencia HEAD
				{
					HEAD = nuevo;							//HEAD apunta al primer elemento
					HEAD->NEXT = NULL;						//El �ltimo elemento apunta a NULL. Al ser el primero, ser� este.
					TAIL = nuevo;							//TAIL tambi�n ser� el primer elemento.
				}
			else
				{
					TAIL->NEXT = nuevo;						//el nodo pasado ahora apunta al nodo insertado.
					nuevo->NEXT = NULL;						//la referencia NEXT del nuevo nodo apunta a NULL porque es el �ltimo ahora.
					TAIL = nuevo;
				}
			printf("\nNodo ingresado con %cxito\n\nSi desea agregar otro nodo, presione 1. De lo contrario, presione cualquier tecla.\n",130);
			scanf("%s",&r);									//Verifica la repetici�n del bucle.
		}
	}

void Eliminar(){
	int x;													//Auxiliar para funci�n strcmpy.
	r='1';													
	while (r=='1')											//Permite repetir el proceso hasta que el usuario decida.
		{
			nodo *actual = (nodo*) malloc(sizeof(nodo));	//Creaci�n de un apuntador para recorrer la lista.
			nodo *anterior = (nodo*) malloc(sizeof(nodo));	//Creaci�n de un apuntador anterior para la lista.
			actual = HEAD;									//Se inicia por HEAD.
			anterior = NULL;								//Al no haber algo antes de HEAD, se inicia en NULL.
			BusquedaCompleta=0;								//Inicia el estado de la b�squeda en "no encontrado".
			printf("Ingrese el producto del nodo a Eliminar: ");
			scanf("%s", &itemBuscado);
			if(HEAD!=NULL)									//Comprobaci�n de que la lista no est� vac�a.
				{
					while(actual!=NULL&&BusquedaCompleta!=1)//Recorre hasta el TAIL y espera que la b�squeda sea exitosa.
						{			
							x=strcmp(actual->item,itemBuscado);
							if(x == 0)						//Verificaci�n que el item sea parte de un nodo.
								{							//Selecci�n de los posibles casos a eliminar:				
									if(actual == HEAD)		//	>Primer nodo:
										{					//Se actualiza su apuntador primero al siguiente nodo.
											HEAD = HEAD->NEXT;	
										}
									else if(actual == TAIL)	//	>�ltimo nodo:
											{				//El miembro apuntador siguiente del nodo anterior pasa a NULL
												anterior->NEXT = NULL;
												TAIL = anterior;//Se actualiza su apuntador �ltimo al anterior.
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
					if(BusquedaCompleta == 0)				//Cuando se llega a TAIL y la b�squeda est� completa pero no exitosamente.
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
					printf("\nLa lista se encuentra vac%ca.",161);
				}
			printf("\n\nProceso terminado.\n\nSi desea eliminar otro item, presione 1. De lo contrario, presione cualquier tecla.\n",162);
			scanf("%s",&r);									//Verifica la repetici�n del bucle.
		}
}

void Modificar(){
	int x;													//Auxiliar para funci�n strcmpy.
	char r='1',r2,OpcionM;									//Auxiliares para elecciones de modificaci�n.
	while (r=='1')											//Permite repetir el proceso hasta que el usuario decida.
		{
			nodo *actual = (nodo*) malloc(sizeof(nodo));	//Creaci�n de un apuntador para recorrer la lista.
			actual = HEAD;									//Se inicia por HEAD.
			BusquedaCompleta=0;								//Inicia el estado de la b�squeda en "no encontrado".
			printf("Ingrese el producto del nodo a buscar para modificar: ");
			scanf("%s", &itemBuscado);
			if(HEAD!=NULL)									//Comprobaci�n de que la lista no est� vac�a.
				{
					while(actual!=NULL&&BusquedaCompleta!=1)//Recorre hasta el TAIL y espera que la b�squeda sea exitosa.
						{
							x=strcmp(actual->item,itemBuscado);
							if(x == 0)						//Verificaci�n que el item sea parte de un nodo.
								{
									printf("\nNodo encontrado.\nProducto: %s\nCantidad: %i\nPrecio: %.2f", itemBuscado,actual->cantidad,actual->precio);
									r2='1';					//En caso de repetir la modificaci�n, revalida el ciclo al encontrar el item.
									while (r2=='1')
										{
											printf("\n\n\n%cQu%c elemento deseas modificar?:\nA.Producto\tB.Cantidad\tC.Precio\tD.Todos",168,130);
											scanf("%s",&OpcionM);//Tras encontrarse el nodo, se cambian los valores del mismo que el usuario elija.
											OpcionM=toupper(OpcionM);//Permite quitar sensibilidad de min�sculas.
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
														printf("\nIngrese los nuevos valores para este Nodo (Producto, cantidad y precio separados con ENTER): ");
														scanf("%s%i%f", &actual->item,&actual->cantidad,&actual->precio);
													break;
													default:
														printf("\n\nOpci%cn no v%clida.\nPor favor ingrese una letra del men%c.\n\n",162,160,163);
														r2='1';//Se tuvo que revalidar para evitar malfuncionamiento del programa.
												}
											printf("\nNodo modificado con %cxito\nSi desea modificar otro elemento del nodo, preione 1. De lo contrario, presiona cualquier tecla.\n",130);
											scanf("%s",&r2);
										}
									BusquedaCompleta = 1;	//Al asignar a encontrado 1, se "notifica" que la b�squeda est� completa exitosamente.
								}
							actual = actual->NEXT;			//Se recorre al siguiente elemento.
						}
					if(BusquedaCompleta == 0)				//Cuando se llega a TAIL y la b�squeda est� completa pero no exitosamente.
						{
							printf("\nProducto no encontrado.\n\n");
						}
				}
			else
				{
					printf("\nLa lista se encuentra vac%ca.",161);
				}
			printf("\n\nModificaci%cn terminada.\n\nSi desea realizar otra modificaci%cn, presione 1. De lo contrario, presione cualquier tecla.\n",162,162);
			scanf("%s",&r);									//Verifica la repetici�n del bucle.
		}
}

void Mostrar(){
	char auxiliarparar;										//Auxuiliar para dejar la lista en pantalla.
	int puntosMenos,i,longitudM;							//Auxiliares para la impresi�n
	nodo *actual = (nodo*) malloc(sizeof(nodo));			//Creaci�n de un apuntador para recorrer la lista.
	actual = HEAD;											//Se inicia por HEAD.
	if(HEAD!=NULL)											//Comprobaci�n de que la lista no est� vac�a.
		{
			printf("\n PRODUCTO:           CANTIDAD:            PRECIO:");
			while(actual != NULL)							//Condici�n para recorrer hasta el TAIL de la lista.
				{
					puntosMenos=0;							//Inicializa en 0 para cada repetici�n del ciclo, pues se imprimen n productos.
					printf("\n %s",actual->item);			//Muestra producto.
					longitudM=strlen(actual->item);			//Obtiene la longitud del producto para reservar el espacio.
					for (i=1;i<=(20-longitudM);i++)			//Tiene predefinido imprimir 20 espacios, a los cuales les ser� restado la cantidad reservada.
						{									//Imprimiendo puntos en su lugar para mantener la est�tica.
							printf(".");	
						}
					printf("[%i]",actual->cantidad);		//Muestra producto entre corchetes.
					longitudM = actual->cantidad;
					if (longitudM<0)
						{
							puntosMenos++;					//Si el inventario contiene un n�mero negativo, reserva el espacio.
						}
					while ((longitudM/10)!=0)
						{
							longitudM=(longitudM/10);		//Divide entre 10 para conocer el tama�o del n�mero, pues al llegar al cero implica que...
							puntosMenos++;					//se han reservado suficientes espacios, pues se le suma uno en cada repetici�n.
						}
					for (i=1;i<=(18-puntosMenos);i++)		//20-2 = 18 debido al par de corchetes.
						{
							printf(".");	
						}
					printf("$ %.2f",actual->precio);
					actual = actual->NEXT;
				}
		}
	else
		{
			printf("\nLa lista se encuentra vac%ca\n\n",161);
		}
	printf("\n\nPara volver al men%c, presione cualquier tecla",163);
	scanf("%s",&auxiliarparar);
}

void Guardar(char Sobreescribir){
	FILE *B;												//Permite crear el archivo.
	nodo *actual = (nodo*) malloc(sizeof(nodo));			//Creaci�n de un apuntador para recorrer la lista.
	actual = HEAD;											//Se inicia por HEAD.
	if (Sobreescribir!='1')									//Verifica que el usuario quiera sobreescribir un inventario existente.
		{
			printf("\nIngrese el nombre que desea asignarle a su archivo:\n");
			scanf("%s",&NombreArchivo);						//Se ingresa el nombre del archivo de salida.
			strcat(NombreArchivo,".invuni");				//Agrega la extensi�n del programa.
		}
	B=fopen(NombreArchivo,"w+t");							//Se abre el archivo en modo de "sobreescrituta". Si existe un archivo de nombre hom�nimo, se borrar�.
	if(HEAD!=NULL)											//Comprobaci�n de que la lista no est� vac�a.
		{
			while(actual != NULL)							//Condici�n para recorrer hasta el TAIL de la lista.
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
	fclose(B);												//Cierra el archivo y limpia el b�ffer.
	fflush(stdin);
	Sleep(2000);
}

void InsertarArchivo(){
	char R='1';
	while(R=='1')														//Permite repetir en caso de error humano.
		{
			FILE *A;													//Apuntador auxiliar para abrir el archivo.
			printf("\nIngrese el nombre del archivo (inventario):\n");
			scanf("%s",&NombreArchivo);
			system("cls");
			strcat(NombreArchivo,".invuni");							//Agrega la extensi�n del programa.
			if ((A=fopen(NombreArchivo,"r"))==NULL)						//Permite comprobar la existencia del archivo.
				{
					printf("\nNo existe el archivo.\nSi desea rectificar o cargar un inventario v%clido, presione 1.\nSi desea continuar abriendo un nuevo inventario, presione cualquier tecla.",160);
					scanf("%s",&R);										//Verifica la repetici�n del bucle.
				}
			else
				{
					while(feof(A)==0)									//Instrucci�n que permite leer hasta el final del archivo.
						{
							nodo *nuevo = (nodo*) malloc(sizeof(nodo));	//Asigna din�micamente el espacio para un nodo nuevo mediante un apuntador.
							fscanf(A,"%s %i %f\n",&nuevo->item,&nuevo->cantidad,&nuevo->precio);//Se asignan los valores a cada miembro de la estructura a partir del archivo.
							if(HEAD==NULL)								//Comprueba si la lista est� vac�a mediante la referencia HEAD.
								{
									HEAD = nuevo;						//HEAD apunta al primer elemento.
									HEAD->NEXT = NULL;					//El �ltimo elemento apunta a NULL. Al ser el primero, ser� este.
									TAIL = nuevo;						//TAIL tambi�n ser� el primer elemento.
								}
							else
								{
									TAIL->NEXT = nuevo;					//el nodo pasado ahora apunta al nodo insertado.
									nuevo->NEXT = NULL;					//la referencia NEXT del nuevo nodo apunta a NULL porque es el �ltimo ahora.
									TAIL = nuevo;
								}
						}
					R='2';												//Rompe el ciclo pues ya se carg� el inventario.
				}
			fclose(A);													//Cierra el archivo y limpia el b�ffer.
			fflush(stdin);
		}
	printf("\nInventario cargado correctamente.\n\n");
}	

void Menu(){
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
	printf("\n%c                  %c     %c INVENTARIUM UNIVERSALIS %c     %c                  %c",186,186,178,178,186,186);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185);
	printf("\n%c A.Insertar       %c C.Modificar      %c E.Mostrar        %c G.Guardar        %c",186,186,186,186,186);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",204,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,185);
	printf("\n%c B.Buscar         %c D.Eliminar       %c F.Cerrar         %c H.Ayuda          %c",186,186,186,186,186);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
	printf("\n\n%cQu%c desea hacer?: ",168,130);
}

void Ayuda(char menuayuda){
	char auxiliarparar;
	if (menuayuda=='0')
		{
			printf("\nA) Si desea empezar un inventario nuevo, eliga esta opci%cn. Al terminar de modificar podr%c asignarle un nombre.\n\n",162,160);
			printf("B) Permite elegir un archivo generado previamente para cargar los nodos del mismo, poniendo el nombre del archivo (sin extensi%cn). El archivo debe estar en la misma ubicaci�n que su programa.\n\n",162);
			printf("C) Cierra el programa.\n\n");
		}
	else
		{
			printf("El programa es sensible a may%csculas y min%csculas. De no seguir las instrucciones, pueden provocarse errores en el programa.\n\n",163,163);
			printf("Se entiende por nodo la unidad m%cnima de almacenamiento de datos, comprendido por un producto, una cantidad y un precio.\n\n",161);
			printf("A) Inserta un nuevo nodo al inventario. El nombre no debe tener espacios y no debe tener m%cs de 30 caracteres.\n\n",160);
			printf("B) Busca en el inventario a partir del nombre del producto y muestra su contenido.\n\n");
			printf("C) Busca en el inventario a partir del nombre del producto y puede modificar cada miembro su contenido.\n\n");
			printf("D) Busca en el inventario a partir del nombre del producto y lo elimina del inventario.\n\n");
			printf("E) Muestra el inventario completo en forma descendente (se muestran en el orden en el que fueron agregados).\n\n");
			printf("F) Cierra el programa.\n\n");
			printf("G) Almacena el inventario en su estado actual en un archivo. Puede asignarse un nombre o conservar el mismo si fue cargado y desea actualizarlo.\n\n");
			printf("\n\nPara continuar, presione cualquier tecla",163);
			scanf("%s",&auxiliarparar);	
		}
}

void gotoxy(int xc, int yc){			//Funci�n impartida en clase de Fundamentos de Programaci�n por Cintia Quezada.
	COORD coord;						//Asigna coordenadas en pantalla para la impresi�n (sin embargo, la coordenada x no funciona correctamente en el SO Windows 10).
	coord.X=xc;							
	coord.Y=yc;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
