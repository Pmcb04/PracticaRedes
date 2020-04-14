/*
 * Gestor.cpp
 *
 *  Created on: 27 mar. 2020
 *      Author: nebur
 */
#include "Gestor.h"

Gestor::Gestor(){
	vTrans = 0;
	f = NULL;
}

void Gestor::setFile(File* f){
	this->f = f;
}

// color/16 = colorFondo
// color%16 = colorTexto
//color = colorTexto + colorFondo*16
//void Gestor::establecerColor(int color){
//	HANDLE Pantalla = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(Pantalla, color);
//}

int Gestor::getVTrans(){
	return vTrans;
}

void Gestor::copiarPSerie(char* cadaux){
	for(int i = 0; i<5; i++){
		cadaux[i] = PSerie[i];
	}
}

void Gestor::encabezado(){
		establecerColor(12);
	    f->printString("============================================================================\n");
	    establecerColor(10);
	    f->printString("----------- ");
	    establecerColor(15);
	    f->printString("PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES ");
	    establecerColor(10);
	    f->printString("------------\n");
	    f->printString("---------------------------- ");
	    establecerColor(15);
	    f->printString(	"CURSO 2019/20");
	    establecerColor(10);
	    f->printString(" ---------------------------------\n");
	    f->printString("----------------------------- ");
	    establecerColor(15);
	    f->printString("SESION1.CPP");
	    establecerColor(10);
	    f->printString(" ----------------------------------\n");
	    establecerColor(12);
	    f->printString("============================================================================\n\n");
}


void Gestor::elegirCOM(){

		establecerColor(15);
		   char opcion;
		   bool salir = false;

		  do{
				f->printString("Seleccionar el puerto a utilizar:(1-4)\n");
				f->printString("\t1. COM1\n");
				f->printString("\t2. COM2\n");
				f->printString("\t3. COM3\n");
				f->printString("\t4. COM4\n");
				opcion = getch();
				if(opcion > 52 || (opcion < 49 && opcion != 27)) f->printString("Por favor, seleccione una opcion valida...\n");
				else if(opcion == 27) salir = true;

		  }while((opcion > 52 || opcion < 49) && !salir);

		    switch (opcion) {
				case 49:
					 strcpy (PSerie, "COM1");
					 f->printString("Puerto COM1 seleccionado\n");
					break;

				case 50:
					 strcpy (PSerie,"COM2");
					 f->printString("Puerto COM2 seleccionado\n");
					 break;

				case 51:
					 strcpy (PSerie,"COM3");
					 f->printString("Puerto COM3 seleccionado\n");
					 break;

				case 52:
					 strcpy (PSerie,"COM4");
					 f->printString("Puerto COM4 seleccionado\n");
					 break;

				default:
					break;
			}
}


void Gestor::elegirVelocidad(){

	establecerColor(15);
	char opcion;
	bool salir = false;
		  do{
		       f->printString("Seleccionar la velocidad de transmision:(1-5)\n");
		       f->printString("\t1. 1200\n");
		       f->printString("\t2. 2400\n");
		       f->printString("\t3. 4800\n");
		       f->printString("\t4. 9600\n");
		       f->printString("\t5. 19200\n");
		       opcion = getch();
			   if(opcion > 53 || (opcion < 49 && opcion != 27)) f->printString("Por favor, seleccione una opcion valida...\n");
			   else if(opcion == 27) salir = true;

		   } while((opcion > 53 || opcion < 49) && !salir);

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

		   	f->printString("Velocidad seleccionada:" + to_string(vTrans) + "\n");
}

//Esto es para que quede toda esta inicialización en un método y en cualquier momento se
//pueda pulsar ESC y salir directamente
int Gestor::IniciarPuerto(HANDLE &PuertoCOM){

	establecerColor(15);
	   char opcion; char PSerie[5];
	   bool salir0 = false;

	  do{
			f->printString("Seleccionar el puerto a utilizar:(1-4)\n");
			f->printString("\t1. COM1\n");
			f->printString("\t2. COM2\n");
			f->printString("\t3. COM3\n");
			f->printString("\t4. COM4\n");
			opcion = getch();
			if(opcion > 52 || (opcion < 49 && opcion != 27)) f->printString("Por favor, seleccione una opcion valida...\n");
			else if(opcion == 27) salir0 = true;

	  }while((opcion > 52 || opcion < 49) && !salir0);

		switch (opcion) {
			case 49:
				 strcpy (PSerie, "COM1");
				 f->printString("Puerto COM1 seleccionado\n");
				break;

			case 50:
				 strcpy (PSerie,"COM2");
				 f->printString("Puerto COM2 seleccionado\n");
				 break;

			case 51:
				 strcpy (PSerie,"COM3");
				 f->printString("Puerto COM3 seleccionado\n");
				 break;

			case 52:
				 strcpy (PSerie,"COM4");
				 f->printString("Puerto COM4 seleccionado\n");
				 break;

			default:
				break;
		}

		if(!salir0){

			bool salir1 = false;
			int vTrans;

			do{
				   f->printString("Seleccionar la velocidad de transmision:(1-5)\n");
				   f->printString("\t1. 1200\n");
				   f->printString("\t2. 2400\n");
				   f->printString("\t3. 4800\n");
				   f->printString("\t4. 9600\n");
				   f->printString("\t5. 19200\n");
				   opcion = getch();
				   if(opcion > 53 || (opcion < 49 && opcion != 27)) f->printString("Por favor, seleccione una opcion valida...\n");
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
				f->printString("Velocidad seleccionada:" + to_string(vTrans) + "\n");

				PuertoCOM = AbrirPuerto(PSerie, vTrans, 8, 0, 1);

			}

		}

		if(PuertoCOM == NULL)
		{

			f->printString("Error al abrir el puerto ");
			f->printCharPuntero(PSerie, 5);
			f->printString("\n");
			//getch(); TODO Si se quita esto sirve lo que he hecho, sino da igual
			return (1);
		}
		else{
			 f->printString("Puerto ");
			 f->printCharPuntero(PSerie, 5);
			 f->printString(" abierto correctamente\n");
			 return (0);
		}

}

Gestor::~Gestor(){//TODO
	//delete f;
}
