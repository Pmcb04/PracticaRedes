/*
 *
 * Emisor.h
 *
 *  Created on: 26 mar. 2020
 *      Author: Pedro Miguel Carmona & Rubén Marín Lucas
 */

#ifndef EMISOR_H_
#define EMISOR_H_

#include "Receptor.h"
#include "Protocolo.h"


const int MAXMENSAJE = 800;

class Emisor{
	char carE;
	char mensaje[MAXMENSAJE+2];
	int indice;
	TramaDatos TE;
	Receptor* R;
	File* f;
	Protocolo* p;

   public:
	//Constructor de objetos de tipo Emisor
	Emisor();

	void setReceptor(Receptor* R);

	void setFile(File *f);

	void setProtocolo(Protocolo* p);

	//Retorna valor de -carE-
	char getCarE();

	void Enviar(HANDLE &PuertoCOM);

	void escribir();

	void borrar();

	void enter();

	void teclaF6(HANDLE &PuertoCOM);

	void teclaF5();

	void teclaF2(HANDLE &PuertoCOM);

	void teclaF3(HANDLE &PuertoCOM);

	void teclaF1(HANDLE &PuertoCOM);

	void enviarFichero(HANDLE &PuertoCOM);

	void construirTrama(int numCaracteres, int &indiceMensaje, char* mensaje);

	void enviarTramaControl(HANDLE &PuertoCOM);

	void elegirFin(HANDLE &PuertoCOM);

	void enviarTramaDatos(HANDLE &PuertoCOM);

	void esperarRespuesta(HANDLE &PuertoCOM);

	void copiarCadena(char* cadena, int numCaracteres, char* cadaux);

	void copiarString(char* cadena, string s);

	void Maestro(HANDLE &PuertoCOM);

	void Esclavo(HANDLE &PuertoCOM);

	void maestroSeleccion(HANDLE &PuertoCOM);

	void maestroSondeo(HANDLE &PuertoCOM);

	void esclavoSeleccion(HANDLE &PuertoCOM);

	void esclavoSondeo(HANDLE &PuertoCOM);

	void enviarTramaEstablecimiento(HANDLE &PuertoCOM);

	void esperarTramaEstablecimiento(HANDLE &PuertoCOM);

	void enviarTramaConfirmacion(HANDLE &PuertoCOM);

	void esperarTramaConfirmacion(HANDLE &PuertoCOM);

	void enviarTramaCierre(HANDLE &PuertoCOM);

	void esperarTramaCierre(HANDLE &PuertoCOM);

	void esperarTramaDatos(HANDLE &PuertoCOM);

	void enviarTramaNegacion(HANDLE &PuertoCOM);

	void enviarFaseTransferencia(HANDLE &PuertoCOM);

	void recibirFaseTranseferencia(HANDLE &PuertoCOM);

	void TEimprimir();//para fichero

	void TEimprimirTrama();//para fichero

	~Emisor();

};



#endif /* EMISOR_H_ */
