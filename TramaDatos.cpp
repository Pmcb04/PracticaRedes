#include "TramaDatos.h"


TramaDatos :: TramaDatos(){
	setControl(02);
	L = 0;
	BCE = 1;
}


void TramaDatos::setLongitud(unsigned char L) {
	this->L = L;
}

void TramaDatos::setDato(int pos, char c) {
	this->Datos[pos] = c;
}

void TramaDatos::setDatos(char* datos, int longitud){
	 for (int i = 0; i < longitud; i++)
		   Datos[i] = datos[i];
	  Datos[longitud] = '\0';
}

void TramaDatos::setBCE(unsigned char BCE) {
	this->BCE = BCE;
}

unsigned char TramaDatos::getLongitud() {
	return L;
}

char TramaDatos::getDato(int pos){
	return Datos[pos];
}

char* TramaDatos::getDatos(){
	return &Datos[0];
}

unsigned char TramaDatos::getBCE() {
	return BCE;
}


void TramaDatos::insertarDatos(vDatos datos, int pos){
	for(int i = 0; i < pos; i++){
		Datos[i] = datos[i];
	}
}

void TramaDatos::copiarDatos(vDatos &datos){
	for(int i = 0; i < L; i++){
		datos[i] = Datos[i];
	}
	datos[L] = '\0';
}

string TramaDatos::toString(){
	string s = "";
	for(int i = 0; i < L; i++){
			s = s + Datos[i];
	}
	return s;
}

unsigned char TramaDatos::calcularBCE(){
	unsigned char BCE = Datos[0];

	for(int i = 1; i < L; i++){
		BCE ^= Datos[i];
	}

	if(BCE == 0 || BCE == 255) BCE = 1;

	return BCE;
}

void TramaDatos::imprimirDatos(){
	for (int i = 0; i < L; ++i) {
		printf("%c", Datos[i]);
	}
}

void TramaDatos::imprimir(){
	printf("%c ", getDireccion());
	char control[5];
	switch(getControl()){
	case 02:
		strcpy (control, "STX");
		control[3] = '\0';
		break;
	case 04:
		strcpy (control, "EOT");
		control[3] = '\0';
		break;
	case 05:
		strcpy (control, "ENQ");
		control[3] = '\0';
		break;
	case 06:
		strcpy (control, "ACK");
		control[3] = '\0';
		break;
	case 21:
		strcpy (control, "NACK");
		control[4] = '\0';
		break;
	}

	printf("%s ", control);
	printf("%c\n", getNumeroTrama());
}

void TramaDatos::imprimirTrama(){
	printf("%c ", getDireccion());
	char control[5];
	switch(getControl()){
	case 02:
		strcpy (control, "STX");
		control[3] = '\0';
		break;
	case 04:
		strcpy (control, "EOT");
		control[3] = '\0';
		break;
	case 05:
		strcpy (control, "ENQ");
		control[3] = '\0';
		break;
	case 06:
		strcpy (control, "ACK");
		control[3] = '\0';
		break;
	case 21:
		strcpy (control, "NACK");
		control[4] = '\0';
		break;
	}

	printf("%s ", control);
	printf("%c ", getNumeroTrama());
	printf("%d ", BCE);
}

TramaDatos :: ~TramaDatos(){

}
