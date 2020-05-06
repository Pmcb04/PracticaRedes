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

class Emisor {
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

		// Establece un receptor
		void setReceptor(Receptor* R);

		// Establece un archivo para escribir
		void setFile(File *f);

		// Establece un protocolo
		void setProtocolo(Protocolo* p);

		//Retorna valor de -carE-
		char getCarE();

		// Metodo para enviar informacion
		void Enviar(HANDLE &PuertoCOM);

		// metodo para cuando se escribe
		void escribir();

		// metodo para cuando se borra
		void borrar();

		// metodo para cunado se da a la tecla enter
		void enter();

		void teclaf7(HANDLE &PuertoCOM);

		// metodo para cuando se da a la tecla F6
		void teclaF6(HANDLE &PuertoCOM);

		// metodo para cuando se da a la tecla F5
		void teclaF5();

		// metodo para cuando se da a la tecla F2
		void teclaF2(HANDLE &PuertoCOM);

		// metodo para cuando se da a la tecla F3
		void teclaF3(HANDLE &PuertoCOM);

 		// metodo para cuando se da a la tecla F1
		void teclaF1(HANDLE &PuertoCOM);

		// metodo para enviar fichero
		void enviarFichero(HANDLE &PuertoCOM);

		// metodo que contruye la trama par enviarla
		void construirTrama(int numCaracteres, int &indiceMensaje, char* mensaje);

		// metodo para enviar la trama de control que antes hemos contruido
		void enviarTramaControl(HANDLE &PuertoCOM);

		// metodo para elegir en el protocolo modo sondeo si se acaba el protocolo o no
		void elegirFin(HANDLE &PuertoCOM);

		// metodo para enviar la trama de datos que antes hemos de contruir
		void enviarTramaDatos(HANDLE &PuertoCOM);

		// metodo para que el esclavo espere la respuesta del maestro para ver si acaba el protocolo o no
		void esperarRespuesta(HANDLE &PuertoCOM);

		// copia cadena en cadaux poniendo '\0' al final
		void copiarCadena(char* cadena, int numCaracteres, char* cadaux);

		//Copia el contenido del string s en cadena y pone '\0' al final
		void copiarString(char* cadena, string s);

		// Metodo para el maestro en el protocolo, elige el tipo de
		// operacion a realizar en el protocolo y el modo del maestro (Sondeo o selección)
		void Maestro(HANDLE &PuertoCOM, ifstream &protocolo);

		// Metodo para el escalvo en el protocolo, el modo del esclavo (Sondeo o selección
		void Esclavo(HANDLE &PuertoCOM, ifstream &protocolo);

		// metodo para maestro de modo seleccion
		void maestroSeleccion(HANDLE &PuertoCOM, ifstream &protocolo);

		// metodo para maestro de modo selección
		void maestroSondeo(HANDLE &PuertoCOM, ifstream &protocolo);

		// metodo para esclavo de modo selección
		void esclavoSeleccion(HANDLE &PuertoCOM, ifstream &protocolo);

		// metodo para esclavo de modo sondeo
		void esclavoSondeo(HANDLE &PuertoCOM, ifstream &protocolo);

		// envia una trama de establecimiento (Trama ENQ)
		void enviarTramaEstablecimiento(HANDLE &PuertoCOM);

		// se espera a la espera de una trama de establecimiento (Trama ENQ)
		void esperarTramaEstablecimiento(HANDLE &PuertoCOM);

		// envia una trama de confirmacion (Trama ACK)
		void enviarTramaConfirmacion(HANDLE &PuertoCOM);

		// se espera a la espera de una trama de confirmación (Trama ACK)
		void esperarTramaConfirmacion(HANDLE &PuertoCOM);

		// envia una trama de cierre (Trama EOT)
		void enviarTramaCierre(HANDLE &PuertoCOM);

		// se espera a la espera de una trama de cierre (Trama EOT)
		void esperarTramaCierre(HANDLE &PuertoCOM);

		// se espera a la espera de una trama de datos (Trama STX)
		void esperarTramaDatos(HANDLE &PuertoCOM);

		// envia una trama de negacion (Trama NACK)
		void enviarTramaNegacion(HANDLE &PuertoCOM);

		// envio de la fase de tranferencia (envio del fichero por tramas de STX)
		void enviarFaseTransferencia(HANDLE &PuertoCOM, ifstream &protocolo);

		// recibe la fase de Transferencia (recibo del fichero por tramas de STX)
		void recibirFaseTranseferencia(HANDLE &PuertoCOM);

		// imprime la trama que se va enviando
		void TEimprimir();//para fichero

		// imprime la trama que se va recibiendo y comprueba el BCE
		void TEimprimirTrama();//para fichero


		// Destructor de la clase Emisor
		~Emisor();

};



#endif /* EMISOR_H_ */
