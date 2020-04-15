/*
 * Emisor.cpp
 *
 *  Created on: 26 mar. 2020
 *      Author: nebur
 */
#include "Emisor.h"

Emisor:: Emisor(){
	carE = 0;
	indice = 0;
	R = NULL;
	f = NULL;
	p = NULL;
}

void Emisor::setReceptor(Receptor* R){
	this->R = R;
}

void Emisor::setFile(File* f){
	this->f = f;
}

void Emisor::setProtocolo(Protocolo* p){
	this->p = p;
}

char Emisor:: getCarE(){
	return carE;
}


void Emisor::Enviar(HANDLE &PuertoCOM){

	if(!p->getProtocolo()){//Si no esta activado el modo protocolo, uso normal

		if(kbhit()){

			carE = getch();

				switch(carE){

					case 0://Tecla de funcion
						carE = getch();
						if(carE == 59){
							teclaF1(PuertoCOM);
						}else if(carE == 60){
							teclaF2(PuertoCOM);
						}else if(carE == 61){
							teclaF3(PuertoCOM);
						}else if(carE == 63){
							teclaF5();
						}
						else if(carE == 64){
							teclaF6(PuertoCOM);
						}
						break;

					case 8://Borrar
						borrar();
						break;

					case 13://Enter
						enter();
						break;

					default:
						escribir();
						break;

				}

		}

	}else{//Si esta activado el modo protocolo
		if(f->getCondition()){
			f->cerrarFichero();
			f->changeCondicion();
		}
		p->printCabecera();
		switch(p->getTipo()){
		case 69://Esclavo
			Esclavo(PuertoCOM);
			break;
		case 77://Maestro
			Maestro(PuertoCOM);
			break;
		}
	}
}


void Emisor::escribir(){
	if(indice < MAXMENSAJE){
		establecerColor(2);
		mensaje[indice] = carE;  //Añade el caracter para mostrarlo cuando se envie
		indice++;
		printf("%c", carE);  //Muestra envio en la pantalla que escribe
	}
}


void Emisor::borrar(){
	if(indice > 0 && mensaje[indice-1] != '\n'){
			indice--;
			mensaje[indice] = ' ';

			printf("\b");
			printf(" ");
			printf("\b");

		}
}


void Emisor::enter(){
	if(indice < MAXMENSAJE){
		mensaje[indice] = '\n';
		printf("\n");
		indice++;
	}
}


void Emisor::teclaF5(){

	if(!f->getCondition()){
		f->changeCondicion();
		f->abrirFichero();
		establecerColor(232);
		printf("\nTodo lo que esciba se escribira en el fichero, tenga cuidado con lo que escribe :)\n");
	}else{
		establecerColor(15);
		f->printString("La funcion de F5 ya esta activa\n");
	}

}

void Emisor::teclaF6(HANDLE &PuertoCOM){

	if(f->getCondition()){
		f->cerrarFichero();
		f->changeCondicion();
	}

	p->printCabecera();

	char opcion;
	bool salir = false;
	establecerColor(12);
	do{
		p->printSeleccion();
		opcion = getch();
	    if(opcion > 50 || (opcion < 49 && opcion != 27)) p->printString("Por favor, seleccione una opcion valida...\n");
	    else if(opcion == 27) salir = true;

	} while((opcion > 50 || opcion < 49) && !salir);

	if(!salir){

		p->setProtocolo(true);//Se activa protocolo

		if(opcion == 49){
			p->setTipo('M');
			p->abrirFichero();
			EnviarCaracter(PuertoCOM, 'E');//La otra estacion sera esclavo
			Maestro(PuertoCOM);
		}else if(opcion == 50){
			p->setTipo('E');
			p->abrirFichero();
			EnviarCaracter(PuertoCOM, 'M');//La otra estacion sera maestro
			Esclavo(PuertoCOM);
		}

	}else{
		establecerColor(15);
		p->setProtocolo(false);//Se cancela protocolo
		//TODO Habria que enviarle algun caracter para que otra pantalla cancele protocolo tb
		p->printString("Se cancela la accion\n");
	}

}

void Emisor::Maestro(HANDLE &PuertoCOM){

	char opcion;
	bool salir = false;
	establecerColor(2);
	p->printString("Ha seleccionado MAESTRO, ");
	do{
		p->printString("seleccione la operacion a realizar:(1-2)\n");
		p->printString("\t1. Seleccion\n");
		p->printString("\t2. Sondeo\n\n");
		opcion = getch();
		if(opcion > 50 || (opcion < 49 && opcion != 27)) p->printString("Por favor, seleccione una opcion valida...\n");
		else if(opcion == 27) salir = true;

	} while((opcion > 50 || opcion < 49) && !salir);

	if(!salir){
		switch(opcion){
			case 49://Seleccion
				p->setOperacion('R');
				maestroSeleccion(PuertoCOM);
				break;
			case 50://Sondeo
				p->setOperacion('T');
				maestroSondeo(PuertoCOM);
				break;
		}


	}else{
		establecerColor(15);
		p->setProtocolo(false);//Se cancela protocolo
		//TODO Habria que enviarle algun caracter para que otra pantalla cancele protocolo tb
		p->printString("Se cancela la accion\n");
	}

}

void Emisor::maestroSeleccion(HANDLE &PuertoCOM){

	establecerColor(1);
	enviarTramaEstablecimiento(PuertoCOM);
	p->printString("E ");//Trama enviada
	TE.imprimir(); TEimprimir();
	esperarTramaConfirmacion(PuertoCOM);
	p->printString("\n");//Acaba fase Establecimiento

	enviarFaseTransferencia(PuertoCOM);
	p->printString("\n");//Acaba fase Transferencia

	establecerColor(11);
	TE.setNumeroTrama('0');
	enviarTramaCierre(PuertoCOM);
	p->printString("E ");//Trama enviada
	TE.imprimir(); TEimprimir();
	esperarTramaConfirmacion(PuertoCOM);


	p->printString("FIN PROTOCOLO\n");
	p->cerrarFichero();
	p->setProtocolo(false);//Se termina el protocolo
}

void Emisor::elegirFin(HANDLE &PuertoCOM){
	establecerColor(11);
	esperarTramaCierre(PuertoCOM);

	char opcion;
	bool salir = false;
	establecerColor(2);
	do{
		p->printString("¿Desea el cierre de la comunicacion?(1-2)\n");
		p->printString("\t1. Si\n");
		p->printString("\t2. No\n\n");
		opcion = getch();
		if(opcion > 50 || (opcion < 49 && opcion != 27)) p->printString("Por favor, seleccione una opcion valida...\n");
		else if(opcion == 27) salir = true;

	} while((opcion > 50 || opcion < 49) && !salir);

	if(!salir){
		establecerColor(11);
		switch(opcion){
			case 49:
				TE.setNumeroTrama(R->getNumeroTrama());
				enviarTramaConfirmacion(PuertoCOM);
				p->printString("E ");//Trama enviada
				TE.imprimir(); //TEimprimir();
				p->setFinSondeo(true);
				break;
			case 50:
				TE.setNumeroTrama(R->getNumeroTrama());
				p->printString("E ");//Trama enviada
				TE.imprimir(); //TEimprimir();
				enviarTramaNegacion(PuertoCOM);
				break;
		}


	}else{
		establecerColor(15);
		p->setProtocolo(false);//Se cancela protocolo
		//TODO Habria que enviarle algun caracter para que otra pantalla cancele protocolo tb
		p->printString("Se cancela la accion\n");
	}

}

void Emisor::maestroSondeo(HANDLE &PuertoCOM){

	establecerColor(1);
	enviarTramaEstablecimiento(PuertoCOM);
	p->printString("E ");//Trama enviada
	TE.imprimir(); TEimprimir();
	esperarTramaConfirmacion(PuertoCOM);
	p->printString("\n");//Acaba fase Establecimiento

	recibirFaseTranseferencia(PuertoCOM);
	p->printString("\n");//Acaba fase Transferencia

	while(!p->getFinSondeo()){
		elegirFin(PuertoCOM);
		p->printString("\n");
	}

	p->printString("FIN PROTOCOLO\n");
	p->cerrarFichero();
	p->setProtocolo(false);//Se termina el protocolo
	p->setFinSondeo(false);//Preparado para futura comunicacion
}


void Emisor::Esclavo(HANDLE &PuertoCOM){
	establecerColor(2);
	p->printString("Ha seleccionado ESCLAVO\n\n");

	establecerColor(1);//Para la trama ENQ que recibimos
	esperarTramaEstablecimiento(PuertoCOM);//Esperar llamada | Trama ENQ

	char operacion = p->getOperacion();
	switch(operacion){
	case 82:
		p->setOperacion('R');
		esclavoSeleccion(PuertoCOM);
		break;
	case 84:
		p->setOperacion('T');
		esclavoSondeo(PuertoCOM);
		break;
	}
}

void Emisor::esclavoSeleccion(HANDLE &PuertoCOM){

	enviarTramaConfirmacion(PuertoCOM);
	p->printString("E ");//Trama enviada
	TE.imprimir(); TEimprimir();
	p->printString("\n");//Acaba fase Establecimiento

	recibirFaseTranseferencia(PuertoCOM);
	p->printString("\n");//Acaba fase Transferencia

	establecerColor(11);
	esperarTramaCierre(PuertoCOM);

	if(R->getNumeroTrama() == '1') TE.setNumeroTrama('1');
	else TE.setNumeroTrama('0');
	enviarTramaConfirmacion(PuertoCOM);
	p->printString("E ");//Trama enviada
	TE.imprimir(); TEimprimir();

	p->printString("FIN PROTOCOLO\n");
	p->cerrarFichero();
	p->setProtocolo(false);//Se termina el protocolo
}


void Emisor::esclavoSondeo(HANDLE &PuertoCOM){

	enviarTramaConfirmacion(PuertoCOM);
	p->printString("E ");//Trama enviada
	TE.imprimir(); TEimprimir();
	p->printString("\n");//Acaba fase Establecimiento

	enviarFaseTransferencia(PuertoCOM);
	p->printString("\n");//Acaba fase Transferencia


	establecerColor(11);
	TE.setNumeroTrama('0');
	enviarTramaCierre(PuertoCOM);
	p->printString("E ");//Trama enviada
	TE.imprimir(); TEimprimir();


	int i = 1;
	while(!p->getFinSondeo()){
		establecerColor(11);
		esperarRespuesta(PuertoCOM);
		p->printString("\n");
		if(!p->getFinSondeo()){
			if(i%2 == 0) TE.setNumeroTrama('0');
			else TE.setNumeroTrama('1');
			enviarTramaCierre(PuertoCOM);
			p->printString("E ");//Trama enviada
			TE.imprimir(); TEimprimir();
			i++;
		}
	}

	p->printString("\n");//Acaba fase Cierre

	p->printString("FIN PROTOCOLO\n");
	p->cerrarFichero();
	p->setProtocolo(false);//Se termina el protocolo
	p->setFinSondeo(false);//Preparado para futura comunicacion

}

void Emisor::enviarTramaEstablecimiento(HANDLE &PuertoCOM){
	char D = p->getOperacion();
	TE.setDireccion(D);
	TE.setControl(05);//Trama ENQ

	EnviarCaracter(PuertoCOM, TE.getSincronismo());
	EnviarCaracter(PuertoCOM, TE.getDireccion());
	EnviarCaracter(PuertoCOM, TE.getControl());
	EnviarCaracter(PuertoCOM, TE.getNumeroTrama());
}

void Emisor::enviarTramaCierre(HANDLE &PuertoCOM){
	char D = p->getOperacion();
	TE.setDireccion(D);
	TE.setControl(04);//Trama EOT

	EnviarCaracter(PuertoCOM, TE.getSincronismo());
	EnviarCaracter(PuertoCOM, TE.getDireccion());
	EnviarCaracter(PuertoCOM, TE.getControl());
	EnviarCaracter(PuertoCOM, TE.getNumeroTrama());
}

void Emisor::enviarTramaConfirmacion(HANDLE &PuertoCOM){
	char D = p->getOperacion();
	TE.setDireccion(D);
	TE.setControl(06);//Trama ACK

	EnviarCaracter(PuertoCOM, TE.getSincronismo());
	EnviarCaracter(PuertoCOM, TE.getDireccion());
	EnviarCaracter(PuertoCOM, TE.getControl());
	EnviarCaracter(PuertoCOM, TE.getNumeroTrama());
}

void Emisor::enviarTramaNegacion(HANDLE &PuertoCOM){
	char D = p->getOperacion();
	TE.setDireccion(D);
	TE.setControl(21);//Trama NACK

	EnviarCaracter(PuertoCOM, TE.getSincronismo());
	EnviarCaracter(PuertoCOM, TE.getDireccion());
	EnviarCaracter(PuertoCOM, TE.getControl());
	EnviarCaracter(PuertoCOM, TE.getNumeroTrama());
}

void Emisor::esperarTramaEstablecimiento(HANDLE &PuertoCOM){
	while(R->Recibir(PuertoCOM) != 3);//Esperar trama ENQ
}

void Emisor::esperarTramaConfirmacion(HANDLE &PuertoCOM){
	while(R->Recibir(PuertoCOM) != 4);//Esperar trama ACK
}

void Emisor::esperarTramaCierre(HANDLE &PuertoCOM){
	while(R->Recibir(PuertoCOM) != 2);//Esperar trama EOT
}

void Emisor::esperarTramaDatos(HANDLE &PuertoCOM){
	while(R->Recibir(PuertoCOM) != 1);//Esperar trama STX
}

void Emisor::esperarRespuesta(HANDLE &PuertoCOM){
	int n = 0;
	while((n = R->Recibir(PuertoCOM)) < 3);

	if(n == 4) p->setFinSondeo(true);
}

void Emisor::recibirFaseTranseferencia(HANDLE &PuertoCOM){
	while(!p->getFinFichero()){
		esperarTramaDatos(PuertoCOM);//Hasta que no reciba trama no puede confirmar

		if(R->getNumeroTrama() == '1') TE.setNumeroTrama('1');
		else TE.setNumeroTrama('0');
		enviarTramaConfirmacion(PuertoCOM);
		p->printString("E ");
		TE.imprimirTrama(); TEimprimir();
		printf("\n");
	}
	p->setFinFichero(false);
}


void Emisor::enviarFaseTransferencia(HANDLE &PuertoCOM){

	char cadaux[255]; //char salir;
	int numBytes = 0; //bool fin = false;

	ifstream flujoFichero;
	flujoFichero.open("EProtoc.txt");

		if(!flujoFichero.fail()){

				EnviarCaracter(PuertoCOM, '{');//Enviamos caracter {

				int i = 0, indiceMensaje, numCaracteres;

				while(i<3){//Envio de 3 primeras lineas

					indiceMensaje = 0;

					flujoFichero.getline(cadaux, 70);//Lee 69 caracteres o hasta que encuentre \n

					numCaracteres = (int) strlen(cadaux);//casting porque strlen te devuelve unsigned

					if(i%2 != 0) TE.setNumeroTrama('1');//Numero de trama 1 intercaladamente
					else TE.setNumeroTrama('0');
					construirTrama(numCaracteres, indiceMensaje, cadaux);

					enviarTramaDatos(PuertoCOM);//se envia la trama una vez construida
					establecerColor(12);
					p->printString("E ");//Trama enviada
					TE.imprimirTrama(); TEimprimirTrama();
					p->printString("\n");

					esperarTramaConfirmacion(PuertoCOM);//Cada vez que envia Trama STX, espera trama ACK

					i++;
				}


				while(!flujoFichero.eof()){

					flujoFichero.read(cadaux, 254);

					indiceMensaje = 0;//Quiero que empiece desde el principio siempre, porque son cadenas distintas

					if(flujoFichero.gcount() > 0){

						numBytes += flujoFichero.gcount();

						cadaux[flujoFichero.gcount()] = '\0';
						numCaracteres = flujoFichero.gcount();
						if(i%2 != 0) TE.setNumeroTrama('1');//Numero de trama 1 intercaladamente
						else TE.setNumeroTrama('0');
						construirTrama(numCaracteres, indiceMensaje, cadaux);

						enviarTramaDatos(PuertoCOM);//se envia la trama una vez construida
						establecerColor(3);
						p->printString("E ");//Trama enviada
						TE.imprimirTrama(); TEimprimirTrama();
						p->printString("\n");

						esperarTramaConfirmacion(PuertoCOM);//Cada vez que envia Trama STX, espera trama ACK

						i++;
					}

				}

				EnviarCaracter(PuertoCOM, '}');//Enviamos caracter }

				string num = to_string(numBytes);
				numCaracteres = num.size();
				copiarString(cadaux, num);
				if(i%2 != 0) TE.setNumeroTrama('1');//Numero de trama 1 intercaladamente
				else TE.setNumeroTrama('0');
				indiceMensaje = 0;
				construirTrama(numCaracteres, indiceMensaje, cadaux);


				enviarTramaDatos(PuertoCOM);//se envia la trama una vez construida
				establecerColor(8);
				p->printString("E ");//Trama enviada
				TE.imprimirTrama(); TEimprimirTrama();
				p->printString("\n");

				esperarTramaConfirmacion(PuertoCOM);//Cada vez que envia Trama STX, espera trama ACK

		}else{

			establecerColor(15);
			p->printString("ERROR: El fichero EProtoc.txt no existe\n");

		}

		flujoFichero.close();
}


void Emisor::teclaF3(HANDLE &PuertoCOM){
	enviarFichero(PuertoCOM);
}

void Emisor::teclaF2(HANDLE &PuertoCOM){
	enviarTramaControl(PuertoCOM);
}

void Emisor::teclaF1(HANDLE &PuertoCOM){

	mensaje[indice] = '\n';
	indice++;
	mensaje[indice] = '\0';

	f->printMensaje(mensaje, indice-1);

	bool fin = false; char salir;
	int numEnvios, numRestante = indice % 254;

	if(numRestante == 0) numEnvios = indice / 254;
	else numEnvios = (indice / 254) + 1;

	int indiceMensaje = 0;
	for(int i = 0; i < numEnvios && !fin; i++){//Cambiar por while

			if(i == numEnvios-1 && numRestante != 0){//Si el ultimo envio no es de 254 caracteres

				construirTrama(numRestante, indiceMensaje, mensaje);

			}else{//mensaje de 254 caracteres

				construirTrama(254, indiceMensaje, mensaje);

			}

			if(kbhit()){//Si se pulsa una tecla
				salir = getch();
				if(salir == 27){
					f->printString("Se cancela la accion\n");
					fin = true;
				}

			}
			enviarTramaDatos(PuertoCOM);//se envia la trama una vez construida

			R->Recibir(PuertoCOM);

	}

	indice = 0;
	f->printString("\n");
}


void Emisor::enviarFichero(HANDLE &PuertoCOM){
	char cadaux[255]; char autores[100]; char salir;
	int numBytes = 0, caracteres;
	bool fin = false;

	ifstream flujoFichero;
	flujoFichero.open("fichero-e.txt");

	if(!flujoFichero.fail()){

			EnviarCaracter(PuertoCOM, '{');//Enviamos caracter {

			int i = 0, indiceMensaje = 0, numCaracteres;

			while(i<3){//Envio de 3 primeras lineas

				flujoFichero.getline(cadaux, 70);//Lee 69 caracteres o hasta que encuentre \n

				numCaracteres = (int) strlen(cadaux);//casting porque strlen te devuelve unsigned
				if(i == 0){
					copiarCadena(cadaux, numCaracteres, autores);//copio lo leido en cadaux, en Autores
					caracteres = numCaracteres;
				}

				construirTrama(numCaracteres, indiceMensaje, cadaux);
				indiceMensaje = 0;//Quiero que empiece desde el principio siempre, porqeu son cadenas distintas
				enviarTramaDatos(PuertoCOM);//se envia la trama una vez construida

				i++;
			}
			establecerColor(9);
			f->printString("Enviando fichero por ");
			f->printCharPuntero(autores, caracteres);
			f->printString("\n");

			while(!flujoFichero.eof() && !fin){

				flujoFichero.read(cadaux, 254);

				if(flujoFichero.gcount() > 0){

					numBytes += flujoFichero.gcount();

					cadaux[flujoFichero.gcount()] = '\0';
					numCaracteres = flujoFichero.gcount();
					construirTrama(numCaracteres, indiceMensaje, cadaux);
					indiceMensaje = 0;//Quiero que empiece desde el principio siempre, porque son cadenas distintas

					if(kbhit()){//Si se pulsa una tecla
						salir = getch();
						if(salir == 27){
							printf("Se cancela la accion\n");
							fin = true;
						}

					}

					enviarTramaDatos(PuertoCOM);//se envia la trama una vez construida

					R->Recibir(PuertoCOM);
				}

			}

			EnviarCaracter(PuertoCOM, '}');//Enviamos caracter }

			string num = to_string(numBytes);
			numCaracteres = num.size();
			copiarString(cadaux, num);
			construirTrama(numCaracteres, indiceMensaje, cadaux);
			indiceMensaje = 0;

			enviarTramaDatos(PuertoCOM);//se envia la trama una vez construida

			establecerColor(9);
			f->printString("Fichero enviado\n");

		}else{

			establecerColor(15);
			f->printString("ERROR: El fichero fichero-e.txt no existe\n");

		}
		flujoFichero.close();
}


void Emisor::copiarCadena(char* cadena, int numCaracteres, char* cadaux){
	for(int i = 0; i < numCaracteres; i++){
			cadaux[i] = cadena[i];
		}
		cadaux[numCaracteres] = '\0';
}


//Copia el contenido del string s en cadena y pone '\0' al final
void Emisor::copiarString(char *cadena, string s){
	for(unsigned int i = 0; i < s.size(); i++){
		cadena[i] = s[i];
	}
	cadena[s.size()] = '\0';
}

void Emisor::construirTrama(int numCaracteres, int &indiceMensaje, char* mensaje){
		if(p->getProtocolo()) TE.setDireccion(p->getOperacion());
		else TE.setDireccion('T');
		if(!p->getProtocolo()) TE.setNumeroTrama('0');
		TE.setControl(02);//es trama de datos
		TE.setLongitud(numCaracteres);

		for(int j = 0; j < numCaracteres; j++){
			TE.setDato(j, mensaje[indiceMensaje]);
			indiceMensaje++;
		}
		unsigned char BCE = TE.calcularBCE();

		TE.setBCE(BCE);
		TE.setDato(numCaracteres, '\0');//Añadir \0 al final del vector
}


void Emisor::enviarTramaDatos(HANDLE &PuertoCOM){
	char datos[255];
	EnviarCaracter(PuertoCOM, TE.getSincronismo());
	EnviarCaracter(PuertoCOM, TE.getDireccion());
	EnviarCaracter(PuertoCOM, TE.getControl());
	EnviarCaracter(PuertoCOM, TE.getNumeroTrama());
	EnviarCaracter(PuertoCOM, TE.getLongitud());
	TE.copiarDatos(datos);
	int longitud = TE.getLongitud();
	EnviarCadena(PuertoCOM, datos, longitud);
	EnviarCaracter(PuertoCOM, TE.getBCE());
}


void Emisor::enviarTramaControl(HANDLE &PuertoCOM){
	establecerColor(15);
	char opcion;
	bool salir = false;

		 do{
			   f->printString("Seleccionar la trama de control a enviar:(1-4)\n");
			   f->printString("\t1. Trama EOT\n");
			   f->printString("\t2. Trama ENQ\n");
			   f->printString("\t3. Trama ACK\n");
			   f->printString("\t4. Trama NACK\n");
			   opcion = getch();
			   if(opcion > 52 || (opcion < 49 && opcion != 27)) f->printString("Por favor, seleccione una opcion valida...\n");
			   else if(opcion == 27) salir = true;

		 } while((opcion > 52 || opcion < 49) && !salir);

		 if(!salir){

		 	 EnviarCaracter(PuertoCOM, TE.getSincronismo());
		 	 EnviarCaracter(PuertoCOM, TE.getDireccion());

		 	 if(opcion == 49) TE.setControl(04);
		 	 else if(opcion == 50) TE.setControl(05);
		 	 else if(opcion == 51) TE.setControl(06);
		 	 else if(opcion == 52) TE.setControl(21);

		 	 EnviarCaracter(PuertoCOM, TE.getControl());
		 	 EnviarCaracter(PuertoCOM, TE.getNumeroTrama());

		 	 if(opcion == 49){
		 		establecerColor(159);
		 		f->printString("Trama EOT enviada\n");
		 	 }else if(opcion == 50){
		 		establecerColor(95);
		 		 f->printString("Trama ENQ enviada\n");
		 	 }else if(opcion == 51){
		 		establecerColor(223);
		 		 f->printString("Trama ACK enviada\n");
		 	 }else if(opcion == 52){
		 		establecerColor(63);
		 		 f->printString("Trama NACK enviada\n");
		 	 }

		 }else{
			f->printString("\nSe cancela el envio de la trama de control\n");
		 }
}

void Emisor::TEimprimir(){

	p->printCharFichero(TE.getDireccion()); p->printCharFichero(' ');

	int longitud = 5;
	char control[longitud];

	switch(TE.getControl()){
	case 02:
		strcpy (control, "STX");
		longitud = longitud - 2;
		break;
	case 04:
		strcpy (control, "EOT");
		longitud = longitud - 2;
		break;
	case 05:
		strcpy (control, "ENQ");
		longitud = longitud - 2;
		break;
	case 06:
		strcpy (control, "ACK");
		longitud = longitud - 2;
		break;
	case 21:
		strcpy (control, "NACK");
		longitud--;
		break;
	}

	control[longitud] = '\0';

	p->printCharPunteroFichero(control, longitud); p->printCharFichero(' ');
	p->printCharFichero(TE.getNumeroTrama()); p->printCharFichero('\n');
}

void Emisor::TEimprimirTrama(){
	p->printCharFichero(TE.getDireccion()); p->printCharFichero(' ');

	int longitud = 5;
	char control[longitud];

	switch(TE.getControl()){
	case 02:
		strcpy (control, "STX");
		longitud = longitud - 2;
		break;
	case 04:
		strcpy (control, "EOT");
		longitud = longitud - 2;
		break;
	case 05:
		strcpy (control, "ENQ");
		longitud = longitud - 2;
		break;
	case 06:
		strcpy (control, "ACK");
		longitud = longitud - 2;
		break;
	case 21:
		strcpy (control, "NACK");
		longitud--;
		break;
	}

	control[longitud] = '\0';

	p->printCharPunteroFichero(control, longitud); p->printCharFichero(' ');
	p->printCharFichero(TE.getNumeroTrama()); p->printCharFichero(' ');

	int BCE = (int) TE.getBCE();
	p->printIntFichero(BCE); //p->printCharFichero('\n');

}


Emisor :: ~Emisor(){//TODO
//	delete R;
//	delete f;
}
