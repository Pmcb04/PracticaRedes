#include "File.h"


File::File(){
  f5 = false;
}

void File::abrirFichero(){
	if (f5 && !fichero.is_open()) fichero.open("log.txt");
}

void File::cerrarFichero(){
	if(fichero.is_open()) fichero.close();
}

void File::setCondicion(bool b){
	f5 = b;
}

bool File::getCondicion(){
	return f5;
}

void File::printDatos(){
	printf("%s", datos);
}

void File::printCharPuntero(char* c, int longitud){

 for (int i = 0; i < longitud; i++) datos[i] = c[i];

 datos[longitud] = '\0';
  printDatos();

  if(f5) for(int i = 0; i < longitud; i++) fichero.put(c[i]);

}

void File::printMensaje(char* c, int longitud){

  if(f5) for(int i = 0; i < longitud; i++) fichero.put(c[i]);

}


void File::printString(string s){

  for (unsigned int i = 0; i < s.length(); i++) datos[i] = s[i];

  datos[s.length()] = '\0';
  printDatos();

  if(f5) for (unsigned int i = 0; i < s.length(); i++) fichero.put(s[i]);

}

void File::printChar(char s){

  datos[0] = s;
  datos[1] = '\0';
  printDatos();
  if(f5) fichero.put(s);

}

File::~File(){


}
