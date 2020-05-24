Proceso Principal
	Definir OpcionSobreescribir,Iniciar,r,OpcionArchivo,Opcion Como Caracter
	Definir cantidad,xc,yc,BusquedaCompleta Como Entero
	Definir precio Como Real
	Definir item,NombreArchivo,itemBuscado Como Caracter
	// Definir HEAD,TAIL,HEAD_NEXT,TAIL_NEXT,actual,anterior,actual_NEXT,anterior_NEXT,NULL Como APUNTADORES
	Iniciar <- '1'
	Mientras Iniciar='1' Hacer
		HEAD <- NULL
		TAIL <- NULL
		r <- '1'
		Escribir 'Bienvenid@!'
		Mientras r='1' Hacer
			Escribir 'Seleccione una opción: A-Crear nuevo inventario | B-Cargar inventario | C-Salir | D-Ayuda'
			Leer OpcionArchivo
			Segun OpcionArchivo  Hacer
				'A':
					Escribir 'Se creará un nuevo archivo'
					r <- '0'
				'B':
					InsertarArchivo()
					r <- '0'
				'C':
					Opcion <- 'F'
					r <- '0'
				'D':
					Opcion <- '0'
					Ayuda(Opcion)
				De Otro Modo:
					Escribir 'Opción no válida'
			FinSegun
		FinMientras
		Mientras Opcion<>'F' Hacer
			Menu()
			Leer Opcion
			Segun Opcion  Hacer
				'A':
					Insertar()
				'B':
					Buscar()
				'C':
					Modificar()
				'D':
					Eliminar()
				'E':
					Escribir ()
				'F':
				'G':
					Si OpcionArchivo='B' Entonces
						Escribir 'Si desea guardar el inventario con el mismo nombre, presione 1'
						Leer OpcionSobreescribir
					FinSi
					Guardar(OpcionSobreescribir)
				'H':
					Ayuda(Opcion)
					Opcion <- '0'
				De Otro Modo:
					Escribir 'Opción no válida'
			FinSegun
		FinMientras
		Opcion <- '0'
		Escribir 'Gracias por usar el programa. Si desea abrir otro inventario, presione 1'
		Leer Iniciar
	FinMientras
FinProceso

SubProceso InsertarArchivo ()
	Definir rIA Como Caracter
	rIA <- '1'
	// DEFINIR A como apuntador
	Mientras rIA='1' Hacer
		Escribir 'Ingrese el nombre del archivo (inventario)'
		Leer NombreArchivo
		// Se buscará un archivo y se almacenará el resultado en A
		Si A=NULL Entonces
			Escribir 'No existe el archivo. Para volver a buscar presione 1'
			Leer rIA
		SiNo
			Mientras A=0 Hacer // Se leerá todo el documento
				// DEFINIR nuevo COMO APUNTADOR NODO 
				Leer item,cantidad,precio // almacenar en nuevo
				Si HEAD=NULL Entonces
					HEAD <- nuevo
					HEAD_NEXT <- NULL
					TAIL <- nuevo
				SiNo
					TAIL_NEXT <- nuevo
					nuevo_NEXT <- NULL
					TAIL <- nuevo
				FinSi
			FinMientras
			rIA <- '2'
		FinSi
	FinMientras
	Escribir 'Inventario cargado correctamente'
FinSubProceso

SubProceso Ayuda(menuayuda)
	Definir auxiliarparar Como Caracter
	Si menuayuda='0' Entonces
		Escribir '[Ayuda de manejo de archivos]'
	SiNo
		Escribir '[Ayuda de funciones en el inventario]'
		Leer auxiliarparar
	FinSi
FinSubProceso

SubProceso Menu()
	Escribir 'A.Insertar | B.Buscar | C.Modificar | D.Eliminar | E.Mostrar | F.Cerrar | G.Guardar | H.Ayuda | ¿Qué desea hacer?'
FinSubProceso

SubProceso Insertar()
	r <- '1'
	Mientras r='1' Hacer
		// DEFINIR nuevo COMO APUNTADOR NODO
		Escribir 'Ingrese el producto, cantidad y precio'
		Leer item,cantidad,precio // almacenar en nuevo
		Si HEAD=NULL Entonces
			HEAD <- nuevo
			HEAD_NEXT <- NULL
			TAIL <- nuevo
		SiNo
			TAIL_NEXT <- nuevo
			nuevo_NEXT <- NULL
			TAIL <- nuevo
		FinSi
		Escribir 'Nodo ingresado con éxito. Si desea agregar otro nodo, presione 1'
		Leer r
	FinMientras
FinSubProceso

SubProceso Buscar()
	Definir x Como Entero
	r <- '1'
	Mientras r='1' Hacer
		// DEFINIR actual COMO APUNTADOR NODO
		actual <- HEAD
		BusquedaCompleta <- 0
		Escribir 'Ingrese el producto a buscar'
		Leer itemBuscado
		Si HEAD<>NULL Entonces
			Mientras actual<>NULL Y BusquedaCompleta<>1 Hacer
				// Comparar item del nodo actual con itemBuscado, y se almacena en x
				Si item=itemBuscado Entonces
					Escribir 'Nodo encontrado:',item,cantidad,precio
					BusquedaCompleta <- 1
				FinSi
				actual <- actual_NEXT
			FinMientras
			Si BusquedaCompleta=0 Entonces
				Escribir 'Nodo no encontrado'
			FinSi
		SiNo
			Escribir 'La lista se encuentra vacía'
		FinSi
		Escribir 'Búsqueda terminada.Si desea realizar otra búsqueda, presione 1.'
		Leer r
	FinMientras
FinSubProceso

SubProceso Modificar ()
	Definir x Como Entero
	Definir r2,OpcionM Como Caracter
	r <- '1'
	Mientras r='1' Hacer
		// DEFINIR actual COMO APUNTADOR NODO
		actual <- HEAD
		BusquedaCompleta <- 0
		Escribir 'Ingrese el producto a modificar'
		Leer itemBuscado
		Si HEAD<>NULL Entonces
			Mientras actual<>NULL Y BusquedaCompleta<>1 Hacer
				// Comparar item del nodo actual con itemBuscado, y se almacena en x
				Si item=itemBuscado Entonces
					Escribir 'Nodo encontrado:',item,cantidad,precio
					r2 <- '1'
					Mientras r2='1' Hacer
						Escribir 'Qué elemento deseas modificar?: A.Producto | B.Cantidad | C.Precio | D.Todos'
						Leer OpcionM
						Segun OpcionM  Hacer
							'A':
								Escribir 'Ingresa el nuevo producto:'
								Leer item // almacenar en actual
							'B':
								Escribir 'Ingresa la nueva cantidad:'
								Leer cantidad // almacenar en actual
							'C':
								Escribir 'Ingresa el nuevo precio:'
								Leer precio // almacenar en actual
							'D':
								Escribir 'Ingrese los nuevos valores para este Nodo'
								Leer item,cantidad,precio // almacenar en actual
							De Otro Modo:
								Escribir 'Opción no válida'
						FinSegun
						Escribir 'Nodo modificado con éxito. Si desea modificar otro elemento del nodo, preione 1'
						Leer r2
					FinMientras
					BusquedaCompleta <- 1
				FinSi
				actual <- actual_NEXT
			FinMientras
			Si BusquedaCompleta=0 Entonces
				Escribir 'Nodo no encontrado'
			FinSi
		SiNo
			Escribir 'La lista se encuentra vacía'
		FinSi
		Escribir 'Modificación terminada.Si desea realizar otra modificación, presione 1.'
		Leer r
	FinMientras
FinSubProceso

SubProceso Eliminar ()
	Definir x Como Entero
	r <- '1'
	Mientras r='1' Hacer
		// DEFINIR actual, anterior COMO APUNTADOR NODO
		actual <- HEAD
		anterior <- NULL
		BusquedaCompleta <- 0
		Escribir 'Ingrese el producto del nodo a Eliminar'
		Leer itemBuscado
		Si HEAD<>NULL Entonces
			Mientras actual<>NULL Y BusquedaCompleta<>1 Hacer
				// Comparar item del nodo actual con itemBuscado, y se almacena en x
				Si item=itemBuscado Entonces
					Si actual=HEAD Entonces
						HEAD <- HEAD_NEXT
					SiNo
						Si actual=TAIL Entonces
							anterior_NEXT <- NULL
							TAIL <- anterior
						SiNo
							anterior_NEXT <- actual_NEXT
						FinSi
					FinSi
					Escribir 'Nodo eliminado con éxito'
					BusquedaCompleta <- 1
				FinSi
				anterior <- actual
				actual <- actual_NEXT
			FinMientras
			Si BusquedaCompleta=0 Entonces
				Escribir 'Nodo no encontrado'
			SiNo
				// Liberar anterior
			FinSi
		SiNo
			Escribir 'La lista se encuentra vacía'
		FinSi
		Escribir 'Búsqueda terminada.Si desea realizar otra búsqueda, presione 1.'
		Leer r
	FinMientras
FinSubProceso

SubProceso Mostrar ()
	Definir auxiliarparar Como Caracter
	Definir puntosMenos,longitudM,i Como Entero
	// Definir actual como APUNTADOR NODO
	actual <- HEAD
	Si HEAD<>NULL Entonces
		Escribir 'PRODUCTO:           CANTIDAD:            PRECIO:'
		Mientras actual<>NULL Hacer
			puntosMenos <- 0
			Escribir item
			// Se obtiene la longitud de item y se almacena en longitudM
			Para i<-1 Hasta 20-longitudM Hacer
				Escribir '.'
			FinPara
			Escribir '[',cantidad,']'
			longitudM <- cantidad
			Si longitudM<0 Entonces
				puntosMenos <- puntosMenos+1
			FinSi
			Mientras longitudM/10<>0 Hacer
				longitudM <- longitudM/10
				puntosMenos <- puntosMenos+1
			FinMientras
			Para i<-1 Hasta 18-puntosMenos Hacer
				Escribir '.'
			FinPara
			Escribir '$',precio
			actual <- actual_NEXT
		FinMientras
	SiNo
		Escribir 'La lista se encuentra vacía'
	FinSi
	Escribir 'Para volver al menú, presione cualquier tecla'
	Leer auxiliarparar
FinSubProceso

SubProceso Guardar (Sobreescribir)
	// DEFINIR actual como APUNTADOR NODO
	actual <- HEAD
	Si Sobreescribir<>'1' Entonces
		Escribir 'Ingrese el nombre que desea asignarle a su archivo:'
		Leer NombreArchivo
	FinSi
	// Se abrirá un archivo llamado NombreArchivo
	Si HEAD<>NULL Entonces
		Mientras actual<>NULL Hacer
			Escribir item,cantidad,precio // Se escribe en el archivo
			actual <- actual_NEXT
		FinMientras
	SiNo
		Escribir 'La lista se encuentra vacía'
	FinSi
	Escribir 'Proceso completado con éxito'
FinSubProceso
