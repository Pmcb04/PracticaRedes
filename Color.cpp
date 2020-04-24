/*
 * Color.cpp
 *
 *  Created on: 5 abr. 2020
 *      Author: nebur
 */
#include "Color.h"

void establecerColor(int color){
	HANDLE Pantalla = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Pantalla, color);
}

// color/16 = colorFondo
// color%16 = colorTexto
//color = colorTexto + colorFondo*16
//void Gestor::establecerColor(int color){
//	HANDLE Pantalla = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(Pantalla, color);
//}
