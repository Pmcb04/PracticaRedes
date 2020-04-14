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

char Protocolo::getTipo(){
	return mE;
}

bool Protocolo::getProtocolo(){
	return protocolo;
}

bool Protocolo::getFinFichero(){
	return finFichero;
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

void Protocolo::printCabecera(){
	printStringFichero("===================================================\n");
	printStringFichero("===================================================\n");
	printStringFichero("-----------{ ");
	printStringFichero("PROTOCOLO MAESTRO-ESCLAVO");
	printStringFichero(" }-----------\n");
	printStringFichero("===================================================\n");
	printStringFichero("===================================================\n\n");
}

void Protocolo::printSeleccion(){
	printStringFichero("Seleccione maestro o esclavo:(1-2)\n");
	printStringFichero("\t1. Mestro\n");
	printStringFichero("\t2. Esclavo\n\n");
}

Protocolo::~Protocolo(){


}
