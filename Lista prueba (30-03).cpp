#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct nodo			//typedef permite dejar de utilizar los struct en el resto del código.
	{
		char *item;
		struct nodo *sig;
	}Libro;					//Variable de tipo nodo
	


Libro *listaLibro(Libro *Lista)		//Función que recibe un apuntador de tipo libro 
	{
		Lista=NULL;			//Creación de la lista. Asigna  un valor nulo y lo regresa
		return Lista;
	}
	
	
//Introducir caracteres. Función que devuelve un apuntador tipo libro.
Libro *agregarLibro(Libro *Lista, char *item)
	{
		Libro *nuevoLibro, *aux; //Nueva variable
		nuevoLibro=(Libro*)malloc(sizeof(Libro)); //Reservando memoria del tamaño de la estructura Libro.
		nuevoLibro->item=item;	//agregar a libro
		nuevoLibro->sig=NULL;	//apuntar a la siguiente estructura
		if (Lista==NULL)		//Verificación de que la lista está vacía y se agrega primer elemento.
			{
				Lista=nuevoLibro;
			}
		else
			{
				aux=Lista;
				while(aux->sig!=NULL)
					{
						aux=aux->sig;
					}
				aux->sig=nuevoLibro;
			}
		return Lista;
	}

int Menu(void);

int caso;
char item[20],Repetir='s';
int main()
	{
		Libro *Lista=listaLibro(Lista);
		caso=Menu();
/*		switch(caso)
	 		{
				case '1': crear();
				break;
				case '2': anexar();
				break;
				case '3': modificar();
				break;
				case '4': eliminar();
				break;
				case '5': reporte();
				break;
				case '6' : exit(1);
  			}
  }
  while(resp!='6');		EN PROCESO*/ 
		do
			{
				printf("Agrega productos");
				scanf("%s",&item);
				Lista=agregarLibro(Lista,item);
				printf("Agregar mas? s/n");
				scanf("%s",&Repetir);
				//strupr(Repetir);
			}
		while(Repetir!='n');
		while(Lista!=NULL)
			{
				printf("%s\n",Lista->item);
				Lista=Lista->sig;		
			}
		return 0;
	}
	
int Menu()
	{
	int opcion;
	printf("\n\n\t\t\t* * * * * BIENVENIDO * * * * *");
    printf("\n\t\t---------------------------------------------------");
    printf("\n\t\t\t      SELECCIONE UNA OPCI%cN   ",162);
    printf("\n\t\t---------------------------------------------------\n\n\n\n");
    printf("\t\t\t\t (1) CREAR INVENTARIO  \n");
    printf("\t\t\t\t (2) EDITAR INVENTARIO     \n");
    printf("\t\t\t\t (3) MODIFICAR DATOS DEL PRODUCTO     \n");
    printf("\t\t\t\t (4) ELIMINAR             \n");
    printf("\t\t\t\t (5) MOSTRAR INVENTARIO              \n");
    printf("\t\t\t\t (6) SALIR  ........        ");
    scanf("%i",&opcion);
    return opcion;
	}
