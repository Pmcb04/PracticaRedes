/*
 * Gestor.cpp
 *
 *  Created on: 27 mar. 2020
 *      Author: nebur
 */
#include "Gestor.h"


void establecerColor(int color){
	HANDLE Pantalla = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Pantalla, color);
}


void encabezado(){
		establecerColor(12);
	    printf("============================================================================\n");
	    establecerColor(10);
	    printf("----------- ");
	    establecerColor(15);
	    printf("PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES");
	    establecerColor(10);
	    printf("------------\n");
	    printf("---------------------------- ");
	    establecerColor(15);
	    printf(	"CURSO 2019/20");
	    establecerColor(10);
	    printf(" ---------------------------------\n");
	    printf("----------------------------- ");
	    establecerColor(15);
	    printf("SESION1.CPP");
	    establecerColor(10);
	    printf(" ----------------------------------\n");
	    establecerColor(12);
	    printf("============================================================================\n\n");
}


int IniciarPuerto(HANDLE &PuertoCOM){

	establecerColor(15);
	   char opcion; char PSerie[5];
	   bool salir0 = false;

	  do{
			  printf("Seleccionar el puerto a utilizar:(1-4)\n");
			  printf("\t1. COM1\n");
			  printf("\t2. COM2\n");
			  printf("\t3. COM3\n");
			  printf("\t4. COM4\n");
			opcion = getch();
			if(opcion > 52 || (opcion < 49 && opcion != 27)) printf("Por favor, seleccione una opcion valida...\n");
			else if(opcion == 27) salir0 = true;

	  }while((opcion > 52 || opcion < 49) && !salir0);

		switch (opcion) {
			case 49:
				 strcpy (PSerie, "COM1");
				 printf("Puerto COM1 seleccionado\n");
				break;

			case 50:
				 strcpy (PSerie,"COM2");
				 printf("Puerto COM2 seleccionado\n");
				 break;

			case 51:
				 strcpy (PSerie,"COM3");
				 printf("Puerto COM3 seleccionado\n");
				 break;

			case 52:
				 strcpy (PSerie,"COM4");
				 printf("Puerto COM4 seleccionado\n");
				 break;

			default:
				break;
		}

		if(!salir0){

			bool salir1 = false;
			int vTrans;

			do{
					printf("Seleccionar la velocidad de transmision:(1-5)\n");
					printf("\t1. 1200\n");
					printf("\t2. 2400\n");
					printf("\t3. 4800\n");
					printf("\t4. 9600\n");
					printf("\t5. 19200\n");
				   opcion = getch();
				   if(opcion > 53 || (opcion < 49 && opcion != 27)) printf("Por favor, seleccione una opcion valida...\n");
				   else if(opcion == 27) salir1 = true;

			   } while((opcion > 53 || opcion < 49) && !salir1);

				   switch (opcion) {
					case 49:
						vTrans = 1200;
						break;
					case 50:
						vTrans = 2400;
						break;

					case 51:
						vTrans = 4800;
						break;

					case 52:
						vTrans = 9600;
						break;

					case 53:
						vTrans = 19200;
						break;

					default:
						break;
				}


			if(!salir1){

				string s = to_string(vTrans);
				char velocidad[s.length()];
				strcpy(velocidad, s.c_str());
				printf("Velocidad seleccionada: %s\n", velocidad);
				PuertoCOM = AbrirPuerto(PSerie, vTrans, 8, 0, 1);

			}

		}

		if(PuertoCOM == NULL)
		{

			printf("Error al abrir el puerto ");
			printf(PSerie, 5);
			printf("\n");
			getch();
			return (1);
		}
		else{
			 printf("Puerto ");
			 printf(PSerie, 5);
			 printf(" abierto correctamente\n");
			 return (0);
		}

}
