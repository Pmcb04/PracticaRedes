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
	Protocolo();

	void setTipo(char c);

	void setProtocolo(bool b);

	void setOperacion(char c);

	void setFinFichero(bool b);

	void setFinSondeo(bool s);

	char getTipo();

	bool getProtocolo();

	bool getFinSondeo();

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

	void printCaracterCabecera(int cont);

	void printSeleccion();

	void printStringFichero(string s);

	void printCharFichero(char c);

	void printCharCabecera(int cont);

	void printIntFichero(int n);

	void printCharPunteroFichero(char* c, int longitud);

	~Protocolo();



};


#endif /* PROTOCOLO_H_ */
