#ifndef TRAMACONTROL_H
#define TRAMACONTROL_H


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
/*
 * Se trata de una clase que representa uno de los tipos de tramas que continuamente se envian y reciben.
 *
 */
class TramaControl{

	private:
		unsigned char S;  // Sincronismo = SYN = 22
		unsigned char D;  // Direccion= (En principio fijo a ’T’)
		unsigned char C;  // Control = (05 (ENQ), 04 (EOT), 06 (ACK), 21 (NACK))
		unsigned char NT; // Numero de Trama = (En principio fijo a ‘0’)

	public:
		/*
		 * Constructor por defecto de objetos de tipo TramaControl
		 */
		TramaControl();

		/*
		 * Actualiza el valor del atributo -S- con el contenido de la variable "S"
		 */
		void setSincronismo(unsigned char S);

		/*
		 * Actualiza el valor del atributo -D- con el contenido de la variable "D"
		 */
		void setDireccion(unsigned char D);

		/*
		 * Actualiza el valor del atributo -C- con el contenido de la variable "C"
		 */
		void setControl(unsigned char C);

		/*
		 * Actualiza el valor del atributo -NT- con el contenido de la variable "NT"
		 */
		void setNumeroTrama(unsigned char NT);

		/*
		 * Retorna el contenido del atributo -S-
		 */
		unsigned char getSincronismo();

		/*
		 * Retorna el contenido del atributo -D-
		 */
		unsigned char getDireccion();
		/*
		 * Retorna el contenido del atributo -C-
		 */
		unsigned char getControl();

		/*
		 * Retorna el contenido del atributo -NT-
		 */
		unsigned char getNumeroTrama();

		/*
		 * Destructor por defecto
		 */
		~TramaControl();

};

#endif // TRAMACONTROL_H
