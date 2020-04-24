//============================================================================
// ----------- PRÃ�CTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2019/20 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================


#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "PuertoSerie.h"
#include "TramaDatos.h"
#include "File.h"
#include "Emisor.h"
#include "Protocolo.h"

using namespace std;

HANDLE PuertoCOM;


//Abrimos el puerto. Para ello necesitamos indicar los siguientes parÃ¯Â¿Â½metros:
// - Nombre del puerto a abrir: ("COM1", "COM2", "COM3", ...).
// - Velocidad: (1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200).
// - NÃ¯Â¿Â½mero de bits en cada byte enviado o recibido: (4, 5, 6, 7, 8).
// - Paridad: (0=sin paridad, 1=impar, 2=par, 3=marca, 4=espacio).
// - Bits de stop: (0=1 bit, 1=1.5 bits, 2=2 bits).

int main()
{
	File* f = new File();
	Protocolo* p = new Protocolo();

	Receptor *R = new Receptor();  R->setFile(f); R->setProtocolo(p);
	Emisor* E = new Emisor();  E->setReceptor(R);  E->setFile(f); E->setProtocolo(p);
	Gestor* G = new Gestor();  G->setFile(f);

  	TramaDatos TD, TC;
    char PSerie[5];

	G->encabezado();
	//int i = G.IniciarPuerto(PuertoCOM, f);
	G->elegirCOM();
	G->copiarPSerie(PSerie);
	G->elegirVelocidad();
	int vTrans = G->getVTrans();
    PuertoCOM = AbrirPuerto(PSerie, vTrans, 8, 0, 1);

    //Abrimos el puerto COM1 (en la sala siempre abrimos el COM1)
  	    if(PuertoCOM == NULL)
  	    {

  	        f->printString("Error al abrir el puerto ");
  	        f->printCharPuntero(PSerie, 5);
  	        f->printString("\n");
  	        getch();
  	        return (1);
  	    }
  	    else{
  	    	 f->printString("Puerto ");
  	         f->printCharPuntero(PSerie, 5);
		     f->printString(" abierto correctamente\n");
  	    }


    // Lectura y escritura simultÃ¡nea de caracteres:
	//if(i == 0){
		while( E->getCarE() != 27){
			R->Recibir(PuertoCOM);
			E->Enviar(PuertoCOM);
		}
	//}

// Cerramos el puerto:
	 f->cerrarFichero();

	 delete p; delete f;  delete R;//TODO
	 delete E;  delete G;

   CerrarPuerto(PuertoCOM);

   return 0;
}
