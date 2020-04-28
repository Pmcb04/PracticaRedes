/*
 * Receptor.h
 *
 *  Created on: 26 mar. 2020
 *      Author: Pedro Miguel Carmona & Rubén Marín Lucas
 */

#ifndef RECEPTOR_H_
#define RECEPTOR_H_


#include "TramaDatos.h"
#include "File.h"
#include "Protocolo.h"
#include "Gestor.h"


class Receptor{
	char carR;
	int campo;
	TramaDatos TR;
	bool esFichero;
	bool finFichero;
	int linea;
	int color;
	ofstream flujoEscritura;
	string Autores;
	string numBytes;
	File* f;
	Protocolo* p;
	char NT;//Para que desde esclavo sepamos NT de la ultima trama de maestro
	//TODO este caracter se podria poner mejor en protocolo?
   public:

			// Contructor de la clase receptor
			Receptor();

			// establece el protocolo
			void setProtocolo(Protocolo* p);

			// establece file
			void setFile(File* f);

			// devuelve el caracter recibido
			char getCarR();

			// devueve el tipo de trama
			int getTipoTrama(char c);

			// devuelve si se a llegado a dejar de escribir en fichero
			bool getFinFichero();

			// devuelve el numero de trama
			char getNumeroTrama();

			// metodo para recibir, devuelve el tipo de trama recibida
			int Recibir(HANDLE &PuertoCOM);

			// imprime por pantalla el tipo de trama de control recibida
			void procesarTramaControl();

			// comprueba si la trama de datos recibida es correcta por su BCE
			bool procesarTramaDatos();

			// procesa el fichero recibido
			void procesarFichero();

			// cierra el fichero
			void cerrarFichero();

			// imprime los mensajes de "Fichero recibido..." y "El fichero recibido tiene un tamano de..." cuando esta activado el modo protocolo
			void imprimirProtocolo();

			// imprime la trama que se va enviando
			void TRimprimir();

			// imprime la trama que se va enviando y comprueba el BCE
			void TRimprimirTrama();//para fichero

			// destructor de la clase receptors
			~Receptor();

};



#endif /* RECEPTOR_H_ */
