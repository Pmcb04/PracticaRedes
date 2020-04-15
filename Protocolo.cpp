/*
 * Protocolo.cpp
 *
 *  Created on: 5 abr. 2020
 *      Author: nebur
 */

#include "Protocolo.h"

Protocolo::Protocolo(){
	mE = 0;
	protocolo = false;
	operacion = 0;
	finFichero = false;
	finSondeo = false;

}

void Protocolo::setTipo(char c){
	mE = c;
}

void Protocolo::setProtocolo(bool b){
	protocolo = b;
}

void Protocolo::setOperacion(char c){
	operacion = c;
}

void Protocolo::setFinFichero(bool b){
	finFichero = b;
}

void Protocolo::setFinSondeo(bool s){
	finSondeo = s;
}

char Protocolo::getTipo(){
	return mE;
}

bool Protocolo::getProtocolo(){
	return protocolo;
}

bool Protocolo::getFinFichero(){
	return finFichero;
}

bool Protocolo::getFinSondeo(){
	return finSondeo;
}
char Protocolo::getOperacion(){
	return operacion;
}


void Protocolo::printDatos(){
	printf("%s", datos);
}


void Protocolo::abrirFichero(){
	if(protocolo){
		if((mE == 'M') && !maestro.is_open()) maestro.open("Prolog-m.txt");
		else if((mE == 'E') && !esclavo.is_open()) esclavo.open("Prolog-e.txt");
	}
}

void Protocolo::cerrarFichero(){
	if(protocolo){
		if(maestro.is_open()) maestro.close();
		else esclavo.close();
	}
}

void Protocolo::printString(string s){
	for (unsigned int i = 0; i < s.length(); i++) datos[i] = s[i];

    datos[s.length()] = '\0';
    printDatos();

    if(mE == 'M'){
    	for (unsigned int i = 0; i < s.length(); i++) maestro.put(s[i]);
    }else{
    	for (unsigned int i = 0; i < s.length(); i++) esclavo.put(s[i]);
    }
}

void Protocolo::printStringFichero(string s){
	if(mE == 'M'){
		for (unsigned int i = 0; i < s.length(); i++) maestro.put(s[i]);
	}else{
		for (unsigned int i = 0; i < s.length(); i++) esclavo.put(s[i]);
	}
}

void Protocolo::printCharFichero(char c){
	if(mE == 'M')  maestro.put(c);
	else esclavo.put(c);
}

void Protocolo::printIntFichero(int n){
	if(mE == 'M')  maestro << n;
	else esclavo << n;
}

void Protocolo::printCharPunteroFichero(char* c, int longitud){
	if(mE == 'M'){
		for(int i = 0; i < longitud; i++) maestro.put(c[i]);
	}else{
		for(int i = 0; i < longitud; i++) esclavo.put(c[i]);
	}
}

void printCaracterCabecera(int cont){
	for ( int i = 0; i < cont; i++) {
		printf("%c", 176);
	}
}

void Protocolo::printCabecera(){
	establecerColor(11);
	printCaracterCabecera(39);
	printf("\n");
	printCaracterCabecera(6);
	printf(" PROTOCOLO MAESTRO-ESCLAVO ");
	printCaracterCabecera(6);
	printf("\n");
	printCaracterCabecera(39);
	printf("\n");
	printf("\n");
}

void Protocolo::printSeleccion(){
	printString("Seleccione maestro o esclavo:(1-2)\n");
	printString("\t1. Maestro\n");
	printString("\t2. Esclavo\n\n");
}

Protocolo::~Protocolo(){


}
