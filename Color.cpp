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
