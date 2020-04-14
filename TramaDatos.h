#ifndef TRAMADATOS_H
#define TRAMADATOS_H

#include "TramaControl.h"
#include "PuertoSerie.h"

const int MAX = 255;
typedef char vDatos[MAX];

/*
 * Clase que representa uno de los tipos de trama que continuamente se envian y reciben. Hereda de la clase TramaControl todos sus atributos
 * y metodos
 *
 */
class TramaDatos : public TramaControl
{

	private:
    	unsigned char L; //Longitud del campo datos
    	vDatos Datos; //Datos[255]
    	unsigned char BCE; //valores entre [1,254]

	public:
    	/*
		 * Constructor por defecto de objetos de tipo TramaDatos
		 */
        TramaDatos();

		/*
		 * Actualiza el valor del atributo -L- con el contenido de la variable "L"
		 */
        void setLongitud(unsigned char L);

		/*
		 * En la posicion "pos" introduce el caracter "c" en el atributo C
		 */
        void setDato(int pos, char c);

		/*
		 * Introduce datos en la trama de control
		 */
        void setDatos(vDatos datos, int longitud);

		/*
		 * Actualiza el valor del atributo -BCE- con el contenido de la variable "BCE"
		 */
        void setBCE(unsigned char BCE);

		/*
		 * Retorna el contenido del atributo -L-
		 */
        unsigned char getLongitud();

		/*
		 *	Retorna el contenido del vector -Datos- de la posicion "pos"
		 */
        char getDato(int pos);

		/*
		 *	Retorna el contenido del vector -Datos- de la posicion "pos"
		 */
        char* getDatos();

		/*
		 * Retorna el contenido del atributo -BCE-
		 */
        unsigned char getBCE();

		/*
		 * Se copia el contenido del atributo -Datos- en el vector "datos" que será devuevuelto por parametro
		 */
        void copiarDatos(vDatos &datos);


        string toString();

        unsigned char calcularBCE();


		/*
		 *	Inserta los caracteres almacenados en el vector "datos" en el atributo -Datos- hasta la posicion "pos"
		 */
        void insertarDatos(vDatos datos, int pos);

		/*
		 *	Imprime por pantalla el contenido del atributo -Datos-
		 */
        void imprimirDatos();

        void imprimir();

        void imprimirTrama();

        /*
		 * Destructor por defecto
		 */
        ~TramaDatos();

};

#endif // TRAMADATOS_H
