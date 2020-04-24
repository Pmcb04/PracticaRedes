/*
 * Receptor.h
 *
 *  Created on: 26 mar. 2020
 *      Author: Pedro Miguel Carmona & RubÃ©n MarÃ­n Lucas
 */

/*
 * Receptor.h
 *
 *  Created on: 26 mar. 2020
 *      Author: Pedro Miguel Carmona & RubÃ©n MarÃ­n Lucas
 */

#ifndef RECEPTOR_H_
#define RECEPTOR_H_


#include "TramaDatos.h"
#include "File.h"
#include "Protocolo.h"
#include "Gestor.h"


class Receptor{
	char carR;
	int campo;
	TramaDatos TR;
	bool esFichero;
	bool finFichero;
	int linea;
	int color;
	ofstream flujoEscritura;
	string Autores;
	File* f;
	Protocolo* p;
	char NT;//Para que desde esclavo sepamos NT de la ultima trama de maestro
	//TODO este caracter se podria poner mejor en protocolo?
   public:

	Receptor();

	void setProtocolo(Protocolo* p);

	void setFile(File* f);

	char getCarR();

	int getTipoTrama(char c);

	bool getFinFichero();

	char getNumeroTrama();

	int Recibir(HANDLE &PuertoCOM);

	void procesarTramaControl();

	bool procesarTramaDatos();

	void procesarFichero();

	void cerrarFichero();

	void TRimprimir();

	void TRimprimirTrama();//para fichero

	~Receptor();

};



#endif /* RECEPTOR_H_ */
