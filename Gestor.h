/*
 * Gestor.h
 *
 *  Created on: 27 mar. 2020
 *      Author: Pedro Miguel Carmona & Rubén Marín Lucas
 */

#ifndef GESTOR_H_
#define GESTOR_H_

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "PuertoSerie.h"
#include "File.h"
//#include "Protocolo.h"
#include "Color.h"

class Gestor{
	char PSerie[5];
	int vTrans;
	File* f;

	public:
	Gestor();

	void setFile(File* f);

	//Retorna el valor de -vTrans-
	int getVTrans();

	//Copia el contenido de -PSerie- en cadaux
	void copiarPSerie(char* cadaux);

	//Muestra el encabezado de la práctica
	void encabezado();

	//Elige el PuertoCOM
	void elegirCOM();

	//Elige la velocidad del puerto
	void elegirVelocidad();

	//A partir de "color" establece el color del texto y el fondo en la pantalla
	//void establecerColor(int color);

	//Este método era para hacer que si a la hora de elegir COM o velocidad,
	//es decir, antes de abrir el puerto pulso ESC, para salirme directamente
	//y no tener que pulsar otra tecla, pero no se si se puede hacer...Hay que
	//preguntar a Mar
	int IniciarPuerto(HANDLE &PuertoCOM);


	~Gestor();
};



#endif /* GESTOR_H_ */
