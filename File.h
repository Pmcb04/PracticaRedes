/*
 * File.h
 *
 *  Created on: 23 mar. 2020
 *      Author: Pedro Miguel Carmona & Rubén Marín Lucas
 */

#ifndef __FILE_H_
#define __FILE_H_

#include <fstream>
#include <string.h>
#include <iostream>
using namespace std;

const int MAX_FILE = 802;
typedef char Datos[MAX_FILE];


class File{

	private:
		bool f5;
		ofstream fichero;
		Datos datos;

	public:

		/*
		* Constructor por defecto de objetos de tipo File
		*/
		File();

		/*
		*  Abre el fichero
		*/
		void abrirFichero();

		/*
		* Cierra el fichero
		*/
		void cerrarFichero();

		/*
		* Imprimie en fichero si f5 = true, siempre imprime por consola
		*/
		void printCharPuntero(char* s, int longitud);


		/*
		* Imprime en fichero si f5 = true
		*/
		void printMensaje(char* s, int longitud);

		/*
		* Imprimie en fichero si f5 = true, siempre imprime por consola
		*/
		void printString(string s);

		/*
		* Imprimie en fichero si f5 = true, siempre imprime por consola
		*/
		void printChar(char s);

		/*
		* Cambia la variable de f5 para poder o no escribir en el fichero
		*/
		void changeCondicion();

		/*
		* Devuelve el estado de la variable f5
		*/
		bool getCondition();

		/*
		* Destructor por defecto
		*/
		~File();

	private:

		/*
		* imprime los datos procesados
		*/
		void printDatos();



};
#endif
