# Entrega 1
### :one: Objetivos.
Las primeras sesiones prácticas de la asignatura, tienen como objetivo la
familiarización con una librería de control del puerto RS-232. La mayoría de sistemas
operativos de propósito general actuales incluyen controladores para los puertos serie
disponibles en el ordenador. Para evitar la incorporación de instrucciones de acceso
directo al hardware, se proporciona la librería **PuertoSerie** que hace uso de la librería
**Windows.h.** Con ella se construirá una aplicación que permita controlar de forma
precisa todos los circuitos de un puerto RS-232C.

### :two: Elección del puerto y velocidad de transmisión.
Al iniciar la aplicación se deberá permitir al usuario seleccionar el puerto serie que
será utilizado por la aplicación, permitiendo elegir entre COM1, COM2, COM3 y COM4 de
la siguiente manera:

```
Seleccionar el puerto a utilizar:
1. COM1
2. COM2
3. COM3
4. COM4
```
Una vez seleccionado el puerto, se deberá mostrar al usuario la posibilidad de elegir la
velocidad de transmisión de entre las siguientes opciones:

```
Seleccionar la velocidad de transmisión:
1. 1200
2. 2400
3. 4800
4. 9600
5. 19200
```

A continuación, el puerto se abrirá usando el resto de parámetros por defecto comentados en
clase (8 bits de datos, sin paridad, 1 bit de stop).

### :three: Envío y recepción de datos.
- Se debe permitir escribir un mensaje en pantalla de hasta 800 caracteres como
máximo bloqueando la escritura de cualquier carácter más, a partir de ese
número.
- Se debe hacer un eco en pantalla de los caracteres que se van escribiendo.
- El mensaje podrá estar compuesto por:
  - Caracteres en general: el mensaje podrá estar compuesto por cualquier
carácter exceptuando aquellos relacionados con las teclas de función (**F1,
F2,** …).
  - Carácter de retroceso: pulsando este carácter el cursor deberá retroceder una
posición, borrando el carácter anterior.
 - Retorno de carro: pulsando este carácter el cursor deberá posicionarse al
inicio de la línea siguiente.
- Una vez construido el mensaje, éste **solo** se enviará a través del puerto serie
pulsando la tecla de función **F1**.
- El receptor recibirá cualquier mensaje enviado por el emisor.
- **El envío y la recepción nunca deben excluirse mutuamente.**

### :four: Control de fin de aplicación (ESC).
En todo momento, el usuario puede poner fin a la aplicación mediante la
pulsación de la tecla **ESCAPE.** En el caso de estar realizando alguna acción mientras se
pulsa esta tecla, se cancelará dicha acción.

# Entrega 2
### :one: Tipos de tramas de control.
- En esta entrega empezaremos a trabajar con el nivel de enlace. Para enviar
información y controlar la comunicación entre dos estaciones de trabajo utilizaremos
tramas de datos y tramas de control. Ambas tramas se diferencian principalmente en
el campo **control**. Las tramas de datos tienen siempre un valor **02** en dicho campo y
las tramas de control un valor diferente dependiendo de la trama, el cual se verá a
continuación. En esta sesión nos centraremos en las tramas de control.
- Como se ha comentado, las tramas de control se usarán para controlar la
comunicación entre dos estaciones y estarán formadas por 4 campos:
  - Campo 1: Sincronismo (**SYN**).
  - Campo 2: Dirección (**‘T’** ó **‘R’**).
  - Campo 3: Control (**ENQ, EOT, ACK, NACK**).
  - Campo 4: Número de trama (**‘0’** ó **‘1’**).

- Tendremos 4 tipos de tramas de control (dependiendo de campo de control):
  - Tramas de órdenes:
    - ENQ: Para sondear o seleccionar a la estación esclava.
    - EOT: Para liberrar la comunicación o petición de liberación
  - Tramas de repuestas
    - ACK: Aceptar (asentir) la trama recibida
    - NACK: Rechazar la trama recibida
    
- El valor del campo **Sincronismo** (SYN) es el 22
- El valor del campo **Dirección** será 'T' o 'R', dependerá de si se hace una operación de selección o de sondeo. En     principio lo fijaremos a 'T'
- El valor del campo **Control**, dependerá del tipo de trama de control que se vaya a construir
  - Trama ENQ: Valor 05.
  - Trama EOT: Valor 04.
  - Trama ACK: Valor 06.
  - Trama NACK: Valor 21.
- El campo **Numero de Trama** oscilará entre los valores '0' y '1'. En principio se fijará a '0'.

### :two: Contrucción de tramas de control
- Las tramas de control se construirán de la siguiente manera:
```C++
 struct TramaControl
 {
 unsigned char S; // Sincronismo = SYN = 22
 unsigned char D; // Direccion= (En principio fijo a ’T’)
 unsigned char C; // Control = (05 (ENQ), 04 (EOT), 06 (ACK), 21 (NACK))
 unsigned char NT; // Numero de Trama = (En principio fijo a ‘0’)
 };
 ```

### :three: Envío tramas de control.
- Para enviar tramas de control se añadirá una nueva opción a la práctica mediante la
pulsación de **F2**.
- Posteriormente el usuario mostrará un menú al usuario para que seleccione el tipo de
trama de control que se enviará:

Trama de control a enviar:
  -  1: Trama ENQ.
  -  2: Trama EOT.
  -  3: Trama ACK.
  - 4: Trama NACK.
  
-  Solo a través de la pulsación de **1, 2, 3 o 4** se enviará la trama de control seleccionada.
En otro caso **no se enviará nada** y se informará al usuario que tiene que pulsar la
opción adecuada.
