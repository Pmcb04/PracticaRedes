//============================================================================
// ----------- PRÁCTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2019/20 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================


#include "Emisor.h"

using namespace std;

HANDLE PuertoCOM;


//Abrimos el puerto. Para ello necesitamos indicar los siguientes parámetros:
// - Nombre del puerto a abrir: ("COM1", "COM2", "COM3", ...).
// - Velocidad: (1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200).
// - Número de bits en cada byte enviado o recibido: (4, 5, 6, 7, 8).
// - Paridad: (0=sin paridad, 1=impar, 2=par, 3=marca, 4=espacio).
// - Bits de stop: (0=1 bit, 1=1.5 bits, 2=2 bits).

int main()
{
	File* f = new File();
	Protocolo* p = new Protocolo();

	Receptor *R = new Receptor();  R->setFile(f); R->setProtocolo(p);
	Emisor* E = new Emisor();  E->setReceptor(R);  E->setFile(f); E->setProtocolo(p);

	encabezado();
	int i = IniciarPuerto(PuertoCOM);


    // Lectura y escritura simultánea de caracteres:
	  if(i == 0){//Si i == 0 es que se aha abierto el puerto correctamente
		while( E->getCarE() != 27){
			R->Recibir(PuertoCOM);
			E->Enviar(PuertoCOM);
		}
	  }

// Cerramos el puerto:
	 f->cerrarFichero();//TODO mirarse donde cerrar eso

	 delete p; delete f;
	 delete R;
	 delete E;

   CerrarPuerto(PuertoCOM);

   return 0;
}
