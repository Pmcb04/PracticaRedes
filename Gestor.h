/*
 * Gestor.h
 *
 *  Created on: 27 mar. 2020
 *      Author: Pedro Miguel Carmona & RubÃ©n MarÃ­n Lucas
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
#include "Color.h"

class Gestor{
	File* f;

	public:
	Gestor();

	void setFile(File* f);

	//Muestra el encabezado de la prÃ¡ctica
	void encabezado();

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
