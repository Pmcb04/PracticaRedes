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
  ```C++
  Trama de control a enviar:
   -  1: Trama ENQ.
   -  2: Trama EOT.
   -  3: Trama ACK.
   -  4: Trama NACK.
  ```
Solo a través de la pulsación de **1, 2, 3 o 4** se enviará la trama de control seleccionada.
En otro caso **no se enviará nada** y se informará al usuario que tiene que pulsar la
opción adecuada.

### :four: Recepción de tramas de control.
- Para comprobar qué tipo de trama se recibirá (trama de datos o de control), se debe
  chequear el campo “control” y verificar que contiene un valor distinto de **02** (valor
  reservado para tramas de datos). En este caso sabremos que recibiremos una trama de
  control.
- Al recibir una trama de control se deberá distinguir qué tipo de trama es e indicar un
  mensaje informativo dependiendo de si es ENQ, EOT, ACK o NACK.
  Ejemplo: ``` “Se ha recibido una trama ACK”.```
  
  ```C++
  carR = RecibirCaracter(PuertoCOM)
  Si (carR != 0) //Comprobamos si hay datos que recibir
    Inicio
        Caso de (campo) //Campo es una variable que pasamos por parámetro para indicar el campo que se va recibiendo
            1://Posible carácter de sincronismo
              Si (carR == 22)
                Almacenarlo en TDR
                Campo++;
            2://Carácter de dirección
                Almacenarlo en TDR
                Campo++;
            3://Carácter de control
                Almacenarlo en TDR
                Campo++;
            4://Número de trama
                Almacenarlo en TDR
                Campo=1;
                Mostrar un mensaje que indique el tipo de trama de control recibida, por ejemplo:
                “Se ha recibido una trama ACK”
            En otro caso:
                Haremos algo distinto
    Fin
  ```
  
### :five: Control de fin de aplicación (ESC).
En todo momento, el usuario puede poner fin a la aplicación mediante la
pulsación de la tecla **ESCAPE.** En el caso de estar realizando alguna acción mientras se
pulsa esta tecla, se cancelará dicha acción.

# Entrega 3
### :one: Construcción de tramas de datos.
Las tramas de datos estarán compuestas por los siguientes campos:

```C++
struct TramaDatos
{
  unsigned char S; // Sincronismo = SYN =22;
  unsigned char D; // Direccion=’T’;
  unsigned char C; // Control = STX = 02;
  unsigned char N; // NumTrama = (En principio fijo a ‘0’);
  unsigned char L; // Long (Longitud del campo de datos);
  char Datos[255]; // Datos[255];
  unsigned char BCE; // (Siempre debe tomar siempre valores entre 1 y 254);
};
```

En un principio la trama de datos se construirá de la manera expresada anteriormente.
En las sesiones sucesivas se explicará como irá cambiando.
### :two: Cálculo del BCE:
Para calcular el valor del campo BCE de una trama se debe hacer la operación lógica XOR dos a dos entre todos
los caracteres del campo de datos de la trama.

Es decir se hará (DATOS[0] XOR DATOS[1]) XOR DATOS[2]) XOR DATOS[3]) ... XOR DATOS[Long-1]).

- Si al calcular el **BCE** obtenemos un valor **0** o un valor **255**, lo cambiaremos
  siempre por **1**.

### :three: Envío de mensajes con tramas de datos.
- Los mensajes de datos serán como máximo de 800 caracteres.
- Los mensajes se trocearán en bloques de 254 caracteres (ya que la última posición la
  reservaremos para el ‘\0’). El bloque de datos se almacenará en el campo Datos de la
  trama de datos. El campo long es el carácter que resulta de expresar la longitud total
  del campo de datos (valor decimal de un carácter comprendido entre 1 y 254). Se
  calculará el BCE para cada bloque de datos y se almacenará en el campo BCE. Para
  cada bloque se enviará una trama de datos completa.
-  Se enviarán tantas tramas de datos como número de bloques de datos se hayan
  extraído del mensaje.
-  Al final de la última trama de datos se almacenará un salto de línea (‘\n’), de esta
  forma se imprimirá un salto de línea al final de cada mensaje en el receptor. (Si ya se
  hizo en la primera entrega con F1 al enviar el mensaje, debe mantenerse).
- **El envío y la recepción nunca deben excluirse mutuamente.**

### :four: Recepción de mensajes con tramas de datos.
- **La trama de datos se procesará solo cuando se reciba completa**
- Procesar la trama de datos consiste en, una vez recibida la trama completa, calcular
  el BCE del campo Datos de la trama recibida y compararlo con el campo BCE de
  dicha trama; si tienen el mismo valor, la trama será correcta y, por lo tanto, habrá que
  mostrar por pantalla el campo **Datos**. Si, por el contrario, no tienen el mismo valor,
  habrá que mostrar un mensaje por pantalla informando que se ha producido un error
  (``“Error al recibir la trama”``) y esa trama se descartaría, por tanto, en este caso no
  habría que mostrar el campo **Datos.**
  
- En ningún momento deberán mostrarse los campos de la trama que no se pidan expresamente.

```C++
carR = RecibirCaracter(PuertoCOM)
Si (carR != 0) //Comprobamos si hay datos que recibir
  Inicio
    Caso de (campo) //Campo es una variable utilizada para indicar el campo que se va recibiendo
      1://Carácter de sincronismo
        Si (caracter == 22)
           Inicializar_Trama (TDR);
           Almacenarlo en TDR
           Campo++
           Break
        Else //Estas dos líneas se eliminarán ya del código, ya que el
          printf(“%c’,carR) //mensaje se recibe en forma de tramas de datos
      2://Carácter de dirección
          Almacenarlo en TDR
          Campo++
          Break
      3://Carácter de control
          Almacenarlo en TDR
          Campo++
          Break
      4://Número de trama
          Almacenarlo en TDR
          Si (Carácter_control es distinto de 02, es decir, que no es trama de datos)
            Campo = 1 //Esta trama es de control y el siguiente campo será de una trama nueva
            Procesar_Trama_Control (TDR)
          Si no (Sería una trama de datos)
            Campo++ //Seguiremos recibiendo el resto de campos de una trama de datos
             Break
      5://Longitud
          Almacenarlo en TDR
           Campo++;
           ¡Cuidado, no ponemos Break para que entre en el siguiente campo!
      6://Datos
         //Recibimos los datos completos de una vez y los almacenamos en el campo datos de la trama
          RecibirCadena (PuertoCOM, Campo_Datos, Campo_Longitud);
          Campo_Datos[Campo_Longitud] = '\0'; //Añadimos el final de cadena al campo datos de la trama
          Campo++
          Break
      7://BCE
          Almacenarlo en TDR
          Campo = 1
          Procesar_Trama_Datos (TDR)
          Break
  Fin
```

### :five: Utilización de diferentes colores para diferenciar mensaje enviados y recibidos.
Para diferenciar los mensajes que se envíen de los que se reciban, es obligatorio
hacer uso de colores. Para ello deberemos utilizar Windows.h.
- Tendremos que declarar un manejador (Pantalla) para controlar el color.
  ```C++ 
  HANDLE Pantalla //HANDLE está declarado en Windows.h
  ```
- Mediante la función GetStdHandle() se podrá manipular el dispositivo estándar de salida para mostrar el color.
  ```C++ 
  Pantalla = GetStdHandle(STD_OUTPUT_HANDLE)
   ```
- Tendremos que usar una variable color que contendrá el valor con el cual
  indicaremos el color de texto y color de fondo deseado. 
    ```C++ 
   int color
   ```
- El color se calculará a través de la siguiente fórmula: 
  **color de texto + color de fondo*16**
  
- Los colores que se podrán utilizar son 15 y se identifican con los siguientes valores enteros:
    ```C++ 
  0 = Negro
  1 = Azul
  2 = Verde
  3 = Azul verdoso
  4 = Marrón
  5 = Morado
  6 = Verde mostaza
  7 = Gris claro
  8 = Gris oscuro
  9 = Azul eléctrico
  10 = Verde fluorescente
  11 = Cian
  12 = Rojo
  13 = Fucsia
  14 = Amarillo
  15 = Blanco
   ```
- Si se quisiera imprimir texto rojo (12) con fondo blanco (15), la variable color
  tendría que almacenar el siguiente valo
  ```C++ 
  color = 12 + 15*16 //(Valdría 252)
  ```
  Cuando la variable color tome el valor de 252, se mostrará esa combinación. 
  
 Ejemplo de código para uso de color: Muestra de un mensaje en gris claro con  fondo azul verdoso y de otro mensaje en
 azul celeste con fondo negro.
   ```C++ 
  #include <iostream>
  #include <conio.h>
  #include <windows.h>
  using namespace std;
  int main()
  {
      HANDLE Pantalla;
      int color;
      Pantalla = GetStdHandle (STD_OUTPUT_HANDLE);
      color = 7 + 3*16; //Letras en gris claro y fondo azul verdoso. (El fondo hay que multiplicarlo por 16).
      SetConsoleTextAttribute (Pantalla, color);
      printf ("Prueba de color 1\n");
      color = 11 + 0*16; //Letras en azul celeste y fondo negro. (El fondo hay que multiplicarlo por 16).
      SetConsoleTextAttribute (Pantalla, color);
      printf ("Prueba de color 2\n");
      getch();
  }
  ```
  Se deberán usar colores que no impidan una visión cómoda de la información.
 
