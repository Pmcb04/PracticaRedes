/*
 * Protocolo.h
 *
 *  Created on: 5 abr. 2020
 *      Author: nebur
 */

#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

#include "Gestor.h"

class Protocolo {
	bool protocolo;//Si se pusa f6 se activa
	char mE;// 'M' maestro | 'E' esclavo
	char operacion; // 'R' Seleccion | 'T' Sondeo
	bool finFichero; //Para controlar la recepcion
	bool finSondeo;
	char datos[800]; //Para mostrar en pantalla TODO creo que con 254 va que chuta
	ofstream maestro; //Para escribir en fichero
	ofstream esclavo;

     /*
	 * imprime los datos procesados
	 */
	 void printDatos();

public:

	// construcctor por defecto de la clase protocolo
	Protocolo();

	// establece el tipo de protocolo
	void setTipo(char c);

	// establece si el protocolo esta activo o no
	void setProtocolo(bool b);

	// establece el tipo de operacion (Seleccion o sondeo) para el protocolo
	void setOperacion(char c);

	// establece si se a terminado de escribir en el fichero
	void setFinFichero(bool b);

	// establece si se a llegado al final de la operacion de sondeo
	void setFinSondeo(bool s);

	// devuelve el tipo de protocolo
	char getTipo();

	// devuelve si el protocolo esta activo o no
	bool getProtocolo();

	// devuelve si la operacion sondeo a terminado o no
	bool getFinSondeo();

	// devuelve el tipo de operacion del protocolo
	char getOperacion();

	// devuevle si si a llegado a terminar de escribir en el fichero
	bool getFinFichero();

	// abre el fichero
	void abrirFichero();

	// cierra el fichero
	void cerrarFichero();

	// imprime por pantalla y en fichero s
	void printString(string s);

	// imprime en pantalla y en fichero la cabezera del protocolo
	void printCabecera();

	//imprime el caracter especial de la cabezera cont veces por pantalla
	void printCaracterCabecera(int cont);

	// imprime el menu de seleccion de maestro esclavo
	void printSeleccion();

	// imprime en fichero s
	void printStringFichero(string s);

	// imprime en fichero c
	void printCharFichero(char c);

	// imprime el caracter especial de la cabezera cont veces por fichero
	void printCharCabecera(int cont);

	//imprime en fichero n
	void printIntFichero(int n);

	// imprime c en fichero
	void printCharPunteroFichero(char* c, int longitud);

	// destructor de la clase Protocolo
	~Protocolo();



};


#endif /* PROTOCOLO_H_ */
