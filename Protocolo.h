/*
 * Protocolo.h
 *
 *  Created on: 5 abr. 2020
 *      Author: nebur
 */

#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

#include "Color.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;

class Protocolo{
	bool protocolo;//Si se pusa f6 se activa
	char mE;// 'M' maestro | 'E' esclavo
	char operacion; // 'R' Seleccion | 'T' Sondeo
	bool finFichero; //Para controlar la recepcion
	char datos[800]; //Para mostrar en pantalla TODO creo que con 254 va que chuta
	ofstream maestro; //Para escribir en fichero
	ofstream esclavo;

     /*
	 * imprime los datos procesados
	 */
	 void printDatos();

public:
	Protocolo();

	void setTipo(char c);

	void setProtocolo(bool b);

	void setOperacion(char c);

	void setFinFichero(bool b);

	char getTipo();

	bool getProtocolo();

	char getOperacion();

	bool getFinFichero();

	/*
	*  Abre el fichero
	*/
	void abrirFichero();

	/*
	* Cierra el fichero
	*/
	void cerrarFichero();

	void printString(string s);

	void printCabecera();

	void printSeleccion();

	void printStringFichero(string s);

	void printCharFichero(char c);

	void printIntFichero(int n);

	void printCharPunteroFichero(char* c, int longitud);

	~Protocolo();



};


#endif /* PROTOCOLO_H_ */