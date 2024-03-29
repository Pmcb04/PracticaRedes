/*
 * Receptor.cpp
 *
 *  Created on: 26 mar. 2020
 *      Author: Pedro Miguel Carmona & Rubén Marín Lucas
 */
#include "Receptor.h"

Receptor::Receptor(){
	carR = 0;
	campo = 1;
	linea = 0;
	finFichero = false;
	esFichero = false;
	color = 0;
	NT = 0;
	f = NULL;
	p = NULL;
}

void Receptor::setFile(File* f){
	this->f = f;
}

void Receptor::setProtocolo(Protocolo* p){
	this->p = p;
}

int Receptor::getTipoTrama(char c){
	int tipoTrama;
	switch(c){
	case 02://STX
		tipoTrama = 1;
		break;
	case 04://EOT
		tipoTrama = 2;
		break;
	case 05://ENQ
		tipoTrama = 3;
		break;
	case 06://ACK
		tipoTrama = 4;
		break;
	case 21://NACK
		tipoTrama = 5;
		break;
	}
	return tipoTrama;
}


char Receptor::getNumeroTrama(){
	return NT;
}


char Receptor::getCarR(){
	return carR;
}


int Receptor::Recibir(HANDLE &PuertoCOM){

	int tipoTrama = 0;

		carR = RecibirCaracter(PuertoCOM);

		if(carR != 0){

			switch(campo){
				case 1:
					if(carR == 22){
						TR.setSincronismo(carR);
						campo++;
					}else if(carR == 27){
						establecerColor(15);
						printf("Se cancela la accion\n");
						if(!esFichero){
							p->cerrarFichero();
						    p->setProtocolo(false);
						}

					}else if(carR == '{'){//comienzo de recepcion de fichero
						esFichero = true;
						finFichero = false;
						p->setFinFichero(false);
						linea = 0;
					}else if(carR == '}'){//fin de repcepcion de fichero
							cerrarFichero();
						if(!p->getProtocolo()){
							establecerColor(color);
							f->printString("Fichero recibido\n");
						}else establecerColor(8);
						esFichero = false;
						finFichero = true;
						p->setFinFichero(true);
					}else if(carR == 'M'){
						p->setProtocolo(true);//Se activa protocolo
						p->setTipo('M');
						p->abrirFichero();
						p->printCabecera(); p->printCabeceraFichero();
					}else if(carR == 'E'){
						p->setProtocolo(true);//Se activa protocolo
						p->setTipo('E');
						p->abrirFichero();
						p->printCabecera(); p->printCabeceraFichero();
					}
					break;

				case 2:
					TR.setDireccion(carR);
					campo++;
					break;

				case 3:
					TR.setControl(carR);
					campo++;
					break;

				case 4:
					TR.setNumeroTrama(carR);
					if(TR.getControl() != 02){
						if(p->getProtocolo()){//si esta activo el protocolo
							tipoTrama = getTipoTrama(TR.getControl());
							NT = TR.getNumeroTrama();
							p->setOperacion(TR.getDireccion());//Sabemos la operacion por el campo direccion
							imprimir();
						}else{//sino esta activo el protocolo
							procesarTramaControl();
						}
						campo = 1;
					}else{
						campo++;
					}
					break;

				case 5:
					TR.setLongitud(carR);
					campo++;

				case 6:
					vDatos datos;
					RecibirCadena(PuertoCOM, datos, TR.getLongitud());
					TR.insertarDatos(datos, TR.getLongitud());
					campo++;
					break;

				case 7:
				   bool tramaCorrecta = procesarTramaDatos();
				   campo = 1;

					if(tramaCorrecta){

						if(esFichero){
							 procesarFichero();
						}else if(finFichero){
							numBytes = TR.toString();
							establecerColor(color);
							if(p->getProtocolo()) establecerColor(8);
							else{
								f->printString("El fichero recibido tiene un tamano de ");
								f->printString(numBytes);
								f->printString(" bytes\n");
							}
							finFichero = false;
							linea = 0;
						}else{//mensaje normal
							establecerColor(6);
							string datos = TR.toString();
							f->printString(datos);
						}

						if(p->getProtocolo()){
							tipoTrama = getTipoTrama(TR.getControl());
							NT = TR.getNumeroTrama();
							imprimirTrama();
						}

					}else{//trama incorrecta
						if(esFichero){
							if(!p->getProtocolo()) f->printString("Error en la recepcion de la trama del fichero no protocolo\n");
							else{ // procesamos error en la trama y la mostramos
								establecerColor(2);
								tipoTrama = getTipoTrama(TR.getControl());
								NT = TR.getNumeroTrama();
								imprimirTrama();

								if(kbhit()){//Si se pulsa una tecla
									if(getch() == 27){
										p->setProtocolo(false);//Se cancela protocolo
										p->cerrarFichero();
										EnviarCaracter(PuertoCOM, 27);
										establecerColor(15);
										f->printString("Se cancela la accion");
									}
								}
							}
						}else{
							if(!p->getProtocolo()) f->printString("Error en la trama recibida no protocolo\n");
							else p->printString("Error en la trama recibida protocolo\n");

						}
					}
					break;
			}
		}

		return tipoTrama;

}


void Receptor::cerrarFichero(){
	flujoEscritura.close();
}

void Receptor::procesarFichero(){




	if(linea == 0){

	  Autores = TR.toString();
	  if(p->getProtocolo()) establecerColor(12);//linea de cabecera

	  linea++;

	}else if(linea == 1){

		string colores = TR.toString();
		color = atoi(colores.c_str());
		if(p->getProtocolo()) establecerColor(12);//linea de cabecera

		linea++;

	}else if(linea == 2){

		string fichero = TR.toString();
		flujoEscritura.open(fichero);
		establecerColor(color);
		if(!p->getProtocolo()){
			f->printString("Recibiendo fichero por ");
			f->printString(Autores);
			f->printString("\n");
		}else{
			establecerColor(12);//linea de cabecera
		}

		linea++;

	}else{//Viene el cuerpo del fichero
		vDatos datos;
		TR.copiarDatos(datos);

		for(int i = 0; i<TR.getLongitud(); i++){
			flujoEscritura.put(datos[i]);
		}

		if(p->getProtocolo()){
			if(linea == 3){
				establecerColor(color);
				p->printString("\n");
				p->printString("Recibiendo fichero por ");
				p->printString(Autores);
				p->printString("\n\n");
			}
			establecerColor(2);//cuerpo de fichero
		}

		linea++;
	}

}

void Receptor::imprimirProtocolo(){
	establecerColor(color);
	p->printString("\nFichero recibido\n");
	p->printString("El fichero recibido tiene un tamano de ");
	p->printString(numBytes);
	p->printString(" bytes\n");
}


void Receptor::TRimprimir(){
	p->printCharFichero(TR.getDireccion()); p->printCharFichero(' ');

	int longitud = 5;
	char control[longitud];

	switch(TR.getControl()){
	case 02:
		strcpy (control, "STX");
		longitud = longitud - 2;
		break;
	case 04:
		strcpy (control, "EOT");
		longitud = longitud - 2;
		break;
	case 05:
		strcpy (control, "ENQ");
		longitud = longitud - 2;
		break;
	case 06:
		strcpy (control, "ACK");
		longitud = longitud - 2;
		break;
	case 21:
		strcpy (control, "NACK");
		longitud--;
		break;
	}

	control[longitud] = '\0';

	p->printCharPunteroFichero(control, longitud); p->printCharFichero(' ');
	p->printCharFichero(TR.getNumeroTrama());
}

void Receptor::TRimprimirTrama(){
	p->printCharFichero(TR.getDireccion()); p->printCharFichero(' ');

	int longitud = 5;
	char control[longitud];

	switch(TR.getControl()){
	case 02:
		strcpy (control, "STX");
		longitud = longitud - 2;
		break;
	case 04:
		strcpy (control, "EOT");
		longitud = longitud - 2;
		break;
	case 05:
		strcpy (control, "ENQ");
		longitud = longitud - 2;
		break;
	case 06:
		strcpy (control, "ACK");
		longitud = longitud - 2;
		break;
	case 21:
		strcpy (control, "NACK");
		longitud--;
		break;
	}

	control[longitud] = '\0';

	p->printCharPunteroFichero(control, longitud); p->printCharFichero(' ');
	p->printCharFichero(TR.getNumeroTrama()); p->printCharFichero(' ');

	int BCE = (int) TR.getBCE();
	p->printIntFichero(BCE);

}

void Receptor::procesarTramaControl(){

	if(TR.getControl() == 04){
		establecerColor(159);
		f->printString("Se ha recibido una trama EOT\n");
	}else if(TR.getControl() == 05){
		establecerColor(95);
		f->printString("Se ha recibido una trama ENQ\n");
	}else if(TR.getControl() == 06){
		establecerColor(223);
		f->printString("Se ha recibido una trama ACK\n");
	}else if(TR.getControl() == 21){
		establecerColor(63);
		f->printString("Se ha recibido una trama NACK\n");
	}
}


bool Receptor::procesarTramaDatos(){
	bool correcto = false;

	unsigned char BCE = TR.calcularBCE();

	TR.setBCE((unsigned char) carR);

	if(TR.getBCE() == BCE) correcto = true;

	return correcto;
}


void Receptor::imprimir(){
	p->printString("R ");//Trama enviada
	TR.imprimir(); // imprimimos en pantalla sin bce
	TRimprimir(); // imprimimos en fichero sin bce
	p->printString("\n"); // impimimos el salto de carro para los dos
}

void Receptor::imprimirTrama(){
	p->printString("R ");//Trama enviada
	TR.imprimirTrama(); // imprimimos en pantalla con bce
	TRimprimirTrama(); // imprimimos en fichero con bce
	int BCE = TR.calcularBCE();
	printf("%d", BCE);		// imprimimos el bce que nos ha llegado
	p->printString(" ");
	p->printIntFichero(BCE);
	p->printString("\n"); // impimimos el salto de carro para los dos
}



Receptor::~Receptor(){//TODO
 //delete f;
}
