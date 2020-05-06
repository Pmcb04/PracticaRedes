/*
 * Gestor.h
 *
 *  Created on: 27 mar. 2020
 *      Author: Pedro Miguel Carmona & Rub�n Mar�n Lucas
 */

#ifndef GESTOR_H_
#define GESTOR_H_

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "PuertoSerie.h"

/*
 *  0 = Negro
 * 	1 = Azul
 *	2 = Verde
 *	3 = Azul verdoso
 *	4 = Marron
 *	5 = Morado
 *	6 = Verde mostaza
 * 	7 = Gris claro
 * 	8 = Gris oscuro
 *	9 = Azul electrico
 *	10 = Verde fluorescente
 *	11 = Cian
 *	12 = Rojo
 *	13 = Fucsia
 *	14 = Amarillo
 *	15 = Blanco
 */

	//A partir de "color" establece el color del texto y el fondo en la pantalla
	void establecerColor(int color);


	//Muestra el encabezado de la práctica
	void encabezado();

	// metodo para sellecionar el puerto a utilizar y la velocidad a utilizar
	int IniciarPuerto(HANDLE &PuertoCOM);



#endif /* GESTOR_H_ */
