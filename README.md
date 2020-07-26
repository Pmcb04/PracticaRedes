<a name ="top"></a>

# :books: Realizado por: 
  - :computer: [Pedro Miguel Carmona Broncano](https://github.com/Pmcb04)
  - :computer: [Rubén Marín Lucas](https://github.com/Pr0t0n9)
  - :date: Curso 2019/2020
  - :office: [Universidad de Extremadura](https://www.unex.es)



# **INDICE**
  - :one: [ENTREGA 1. ENVÍO Y RECEPCIÓN DE DATOS](#ent1)
    - [Objetivos](#e11)
    - [Elección de puerto y velocidad de trasmisión](#e12)
    - [Envío y recepción de datos](#e13)
    - [Control de fin de aplicación](#e14)
  - :two: [ENTREGA 2. ENVÍO Y RECEPCIÓN DE TRAMAS DE CONTROL (NIVEL ENLCE)](#ent2)
    - [Tipos de trama de control](#e21)
    - [Construcción de tramas de control](#e22)
    - [Envio de tramas de control](#e23)
    - [Recepción de tramas de control](#e24)
    - [Control de fin de aplicación](#e25)
  - :three: [ENTREGA 3. ENVÍO Y RECEPCIÓN DE MENSAJES CON TRAMAS DE DATOS](#ent3)
    - [Construcción de tramas de datos](#e31)
    - [Cálculo del BCE](#e32)
    - [Envío de mensajes de tramas de datos](#e33)
    - [Recepción de mensajes con tramas de datos](#e34)
    - [Utilización de diferentes colores para diferenciar mensajes enviados y recibidos](#e35)
    - [Control de fin de aplicación(ESC)](#e36)
  - :four: [ENTREGA 4. ENVÍO Y RECEPCIÓN DE FICHEROS CON TRAMAS](#ent4)
    - [Construcción de tramas de datos](#e41)
    - [Envío y repección de ficheros con tramas de datos](#e42)
    - [Ejemplo de fichero de texto](#e43)
    - [Volcado de pantalla a fichero log.txt](#e44)
    - [Control de fin de aplicación(ESC)](#e45)
  - :five: [ENTREGA 5. PROTOCOLO MAESTRO-ESCLAVO](#ent5)
    - [Funcionamiento del protocolo](#e51)
    - [Tipos de tramas empleadas](#e52)
    - [Fases de la operación de Selección](#e53)
    - [Fases de la operación de Sondeo](#e54)
    - [Volcado de pantalla a fichero Prolog-m.txt y Prolog-e.txt](#e55)
    - [Control de fin de aplicación(ESC)](#e56)
  - :six: [ENTREGA 6. PROTOCOLO MAESTRO-ESCLAVO CON ERRORES](#ent6)
    - [Funcionamiento del protocolo Maestro-Esclavo sensible a errores](#e61)
    - [Fases de la operación de Selección con control de errores](#e62)
    - [Fases de la operación de Sondeo con control de errores](#e63)
    - [Puntos a incluir en la documentación externa](#e64)
    
 
  ## :computer: PROGRAMAS UTILIZADOS
   - [Eclipse](https://www.eclipse.org/)
   - Virtual Serial Port Emulator
   - Libreria *Windows.h*
   - Libreria *PuertoSerie.h* (Proporcionada por profesores)





<a name ="ent1"></a>
# ENTREGA 1. ENVÍO Y RECEPCIÓN DE DATOS
<a name ="e11"></a>
### :one: Objetivos.
Las primeras sesiones prácticas de la asignatura, tienen como objetivo la
familiarización con una librería de control del puerto RS-232. La mayoría de sistemas
operativos de propósito general actuales incluyen controladores para los puertos serie
disponibles en el ordenador. Para evitar la incorporación de instrucciones de acceso
directo al hardware, se proporciona la librería **PuertoSerie** que hace uso de la librería
**Windows.h.** Con ella se construirá una aplicación que permita controlar de forma
precisa todos los circuitos de un puerto RS-232C.
<a name ="e12"></a>
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
<a name ="e13"></a>
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
<a name ="e14"></a>
### :four: Control de fin de aplicación (ESC).
En todo momento, el usuario puede poner fin a la aplicación mediante la
pulsación de la tecla **ESCAPE.** En el caso de estar realizando alguna acción mientras se
pulsa esta tecla, se cancelará dicha acción.
[:top:](#top)
<a name ="ent2"></a>
# ENTREGA 2. ENVÍO Y RECEPCIÓN DE TRAMAS DE CONTROL (NIVEL ENLCE)
<a name ="e21"></a>
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
  - *Tramas de órdenes*:
    - ENQ: Para sondear o seleccionar a la estación esclava.
    - ![Entrega 2.1](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%202.1.jpg)
    
    - EOT: Para liberrar la comunicación o petición de liberación
    - ![Entrega 2.2](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%202.2.jpg)
    
  - *Tramas de repuestas*
    - ACK: Aceptar (asentir) la trama recibida
    - ![Entrega 2.3](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%202.3.jpg)

    - NACK: Rechazar la trama recibida
    - ![Entrega 2.4](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%202.4.jpg)


- El valor del campo **Sincronismo** (SYN) es el 22
- El valor del campo **Dirección** será 'T' o 'R', dependerá de si se hace una operación de selección o de sondeo. En     principio lo fijaremos a 'T'
- El valor del campo **Control**, dependerá del tipo de trama de control que se vaya a construir
  - Trama ENQ: Valor 05.
  - Trama EOT: Valor 04.
  - Trama ACK: Valor 06.
  - Trama NACK: Valor 21.
- El campo **Numero de Trama** oscilará entre los valores '0' y '1'. En principio se fijará a '0'.
<a name ="e22"></a>
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
<a name ="e23"></a>
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
<a name ="e24"></a>
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
<a name ="e25"></a>
### :five: Control de fin de aplicación (ESC).
En todo momento, el usuario puede poner fin a la aplicación mediante la
pulsación de la tecla **ESCAPE.** En el caso de estar realizando alguna acción mientras se
pulsa esta tecla, se cancelará dicha acción.
[:top:](#top)

<a name ="ent3"></a>
# ENTREGA 3. ENVÍO Y RECEPCIÓN DE MENSAJES CON TRAMAS DE DATOS
<a name ="e31"></a>
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

 ![Entrega 3.1](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%203.1.jpg)
- En un principio la trama de datos se construirá de la manera expresada anteriormente.
En las sesiones sucesivas se explicará como irá cambiando.
<a name ="e32"></a>
### :two: Cálculo del BCE:
Para calcular el valor del campo BCE de una trama se debe hacer la operación lógica XOR dos a dos entre todos
los caracteres del campo de datos de la trama. Por ejemplo, para calcular el BCE de
una trama de datos que transporta los caracteres "HOLA" se haría:


 ![Entrega 3.2](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%203.2.jpg)

- Si al calcular el **BCE** obtenemos un valor **0** o un valor **255**, lo cambiaremos
  siempre por **1**.
  
<a name ="e33"></a>
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

<a name ="e34"></a>
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
<a name ="e35"></a>
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
<a name ="e36"></a>
### :six: Control de fin de aplicación (ESC).
En todo momento, el usuario puede poner fin a la aplicación mediante la pulsación
de la tecla **ESCAPE.** En el caso de estar realizando alguna acción mientras se pulsa esta
tecla, se cancelará dicha acción.
[:top:](#top)

<a name ="ent4"></a>
# ENTREGA 4. ENVÍO Y RECEPCIÓN DE FICHEROS CON TRAMAS
<a name ="e41"></a>
### :one: Construcción de tramas de datos.
Como ya se explicó anteriormente, las tramas de datos están compuestas por los
siguientes campos:


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

![Entrega 4.1](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%204.1.jpg)


En un principio, como se explicó en la entrega 3, la trama de datos se construirá de la
manera expresada anteriormente. En la entrega 5 se explicará como cambiará.
<a name ="e42"></a>
### :two: Envío y recepción de ficheros con tramas de datos.
- Previamente se creará un fichero de texto llamado **“fichero-e.txt”** con el bloc de notas
  y se almacenará en el directorio de trabajo. El tamaño del fichero será como mínimo
  de 100 KB.
- El fichero constará primero de tres líneas de cabecera y a continuación aparecerá el
  cuerpo del fichero.
- Las líneas de cabecera contendrán:
  - Línea 1: Nombre y apellidos de los autores de la práctica separados por & (Ej: Clara Santos & Olivia Becerra).
  - Línea 2: Color cabecera (texto y fondo). Se expresará con un valor entero.
  - Línea 3: Nombre y extensión del fichero en el equipo receptor.
  
 ![Entrega 4.2](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%204.2.jpg)

  
- Mediante la tecla F3 se iniciará el envío del fichero de texto. Pasos a seguir:
  1. Se intentará abrir el fichero **“fichero-e.txt”.** Si existe dicho fichero, se
  enviará el carácter ‘{’ al receptor para indicarle que recibirá un fichero. Si
  no existe, se deberá mostrar el mensaje pertinente y no se enviará
  información alguna.
  2. Se extraerá de la primera línea de cabecera el nombre y apellidos de los
  autores de la práctica. Posteriormente esta información se enviará al equipo
  receptor mediante una trama de datos.
  3. Se extraerá de la segunda línea de cabecera el color de texto y fondo con el
  que se mostrará la información referente al fichero en el receptor.
  Posteriormente esta información se enviará al equipo receptor mediante una
  trama de datos.
  4. Se extraerá de la tercera línea de cabecera el nombre del fichero que tendrá
  en el equipo receptor. Este nombre de fichero se enviará al equipo receptor
  mediante una trama de datos; en el equipo receptor se creará un fichero con
  dicho nombre. Posteriormente, se enviará el cuerpo del fichero (resto de
  líneas del fichero sin las tres líneas de cabecera).
  5. A la vez que se va enviando el cuerpo del fichero mediante tramas de datos
  se irá calculando el tamaño de ese fichero.
  6. Una vez finalizado el envío del fichero, se mandará el carácter ‘}’ para
  indicar al receptor que el envío terminó.
  7. Por último, se enviará el número de caracteres de los que constará el fichero
  enviado mediante una trama de datos.

- **El fichero debe llegar íntegro.**
- NO SE DEBE MOSTRAR en ningún momento el cuerpo del fichero por pantalla, ni
  en el emisor, ni en el receptor.
- Toda la información mostrada en el equipo receptor referente al fichero, se mostrará en
  el color (texto y fondo) indicado por la segunda línea de cabecera recibida.
- Las tramas de datos recibidas en el equipo receptor (pertenecientes al cuerpo del
  fichero), serán procesadas tal y como se explica a continuación. El campo datos de las
  tramas recibidas, se irá almacenando en el fichero siempre y cuando éstas sean
  correctas (proceso que se explicó en la entrega anterior). Si alguna trama fuese correcta,
  se mostrará el mensaje en pantalla de **“Error en la recepción de la trama del fichero”**
  y la trama se descartará. Como no se contemplan errores de transmisión, las tramas
  deben llegar siempre correctas para que la entrega se pueda considerar APTA.
  Recordar: en el fichero receptor, solo se almacenarán las tramas de datos perteneciente
  al cuerpo del fichero enviado, no las líneas de cabecera.

- Cuando el emisor comience a enviar el fichero, mostrará un mensaje informativo de
  ``“Enviando fichero por Autores”`` y cuando termine, mostrará un mensaje indicando
  que el fichero ya se ha enviado, ``“Fichero enviado”``. Autores será el nombre y apellidos
  de los autores de la práctica separados por & y se extraerá de la primera línea de
  cabecera del fichero de envío.
- En el receptor se mostrará un mensaje informativo indicando cuando comienza a
  recibirse un fichero, ``“Recibiendo fichero por Autores”`` y otro para indicar cuando
  termina la recepción de dicho fichero, ``“Fichero recibido”.`` La información de
  “Autores” la habrá recibido el receptor previamente.
- Una vez terminada la recepción del fichero, se mostrará el mensaje: ``“El fichero``
  ``recibido tiene un tamaño de xxxx bytes”``, siendo xxxx el número de caracteres del
  fichero y que previamente envió el emisor.
- Para realizar el envío, el fichero se irá troceando en bloques de 254 caracteres. Cada
  bloque se almacenará en el campo Datos de la trama de datos. Para enviar el fichero se
  harán tantos envíos como bloques de 254 caracteres se pueda dividir el fichero. Para
  cada envío se deberá enviar la trama de datos completa.
- **MUY IMPORTANTE:** Nunca se debe excluir el envío de la recepción, es decir, se puede
  y se debe “enviar y recibir a la vez”. Las posibilidades que tendríamos serían las
  siguientes:
  - **Enviar mensaje datos / recibir mensaje datos.**
  Se podrán enviar mensajes de datos (con F1) y recibir mensajes del equipo
  receptor (que envió con F1).
  - **Enviar mensaje datos / recibir fichero.**
  Se podrán enviar mensajes de datos (con F1) y recibir un fichero de texto
  (por parte del equipo receptor).
  - **Enviar fichero / recibir mensaje datos.**
  Se podrá enviar un fichero y recibir mensajes del equipo receptor (que envió
  con F1).
  
   ![Entrega 4.3](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%204.3.jpg)

  - Para que se pueda enviar un fichero de 100 kb a la vez que se reciba el mensaje de 800
  caracteres, se debería usar como velocidad de transmisión 4800 bits por segundo, de esta  
  manera dará tiempo a enviar el fichero y a recibir las 4 tramas del mensaje de 800 caracteres.
  En caso de utilizar una velocidad más alta, habría que ampliar el tamaño del fichero de texto
  para que diese tiempo a enviar y a recibir toda la información. Se recuerda que cuando se cree
  el puerto virtual con el emulador de puerto serie, se debe activar la emulación de la velocidad,
  tal y como está descrito en el manual de uso del virtualizador subido al campus.

  - **Enviar fichero / recibir fichero. (OPCIONAL).**
  Este apartado es opcional. Se podrá implementar desde ahora hasta la
  entrega 6. Se podrá enviar y recibir un fichero de 100 kb de forma
  simultánea. El realizar este apartado incrementará la nota de la práctica en
  1 punto.
<a name ="e43"></a>
### :three: Envio de ficheros con tramas de datos

A continuación, se muestra un pseudocódigo para enviar el fichero, a modo de ayuda,
para que podáis pensar en una solución válida. Como recomendación, no utilicéis la
función trocer_trama() que implementasteis en la entrega 3 para el envío del fichero.

```C++
  Abrir_Fichero_Envío();
  si (Apertura correcta del fichero)
    EnviarCaracter(PuertoCOM, '{'); //Comienzo de envío de fichero
    EnviarLineasCabecera ();
    printf("Enviando fichero por %s.\n", Autores); //Autores contendrá los autores del fichero de envío.
    Información que se encuentra en la primera línea de cabecera.
    Mientras (No fin de fichero) //Envío del cuerpo del fichero
      Leer del fichero ();
      Si (se ha leído algo del fichero)
        Construir_trama();
        Enviar_trama();
    Cerrar_fichero ();
    EnviarCaracter(PuertoCOM, '}');//Fin envío de fichero
    EnviarNumCaracteresFichero() // Enviar mediante trama de datos
    printf("Fichero enviado.\n");
  sino
    printf("ERROR: El fichero fichero-e.txt no existe.\n")
 ```

En el emisor,**NO SE DEBE MOSTRAR** en ningún momento el cuerpo del fichero por pantalla.
<a name ="e44"></a>
### :four: Volcado de pantalla a fichero log.txt.
Para comprobar en un momento determinado de forma detallada todo lo que ocurre en
la aplicación, se podrá volcar toda la activad mostrada en pantalla a un fichero llamado **log.txt**
utilizando para ello la tecla de función F5. Una vez pulsada F5 toda la información que se
muestre en pantalla a partir de ese momento en un equipo determinado (emisor o receptor) se
volcará al fichero log.txt hasta finalizar la ejecución de la aplicación.
<a name ="e45"></a>
### :five: Control de fin de aplicación (ESC).
En todo momento, el usuario puede poner fin a la aplicación mediante la pulsación de
la tecla **ESCAPE.** En el caso de estar realizando alguna acción mientras se pulsa esta tecla, se
cancelará dicha acción.
[:top:](#top)
<a name ="ent5"></a>
# ENTREGA 5. PROTOCOLO MAESTRO-ESCLAVO
<a name ="e51"></a>
### :one: Funcionamiento del protocolo MAESTRO-EXCLAVO
El protocolo Maestro-Esclavo se activará **únicamente** en una de las dos estaciones mediante la
pulsación de la tecla **F6**. Una vez activado el protocolo, una estación tomará el roll de
Maestro y la otra de Esclavo, teniendo en cuenta que ambas no podrán ser Maestras o Esclavas al
mismo tiempo. La estación que pulse **F6** tendrá el control para elegir el roll que desee. Una vez que
dicha estación seleccione dicho roll, automáticamente la otra estación adquirirá el roll que quedase
libre.

 - Activación del protocolo mediante pulsación de **F6**

   ![Entrega 5.1](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%205.1.jpg)


 - Selección de roll de maestro en una estación y automáticamente la otra estación se convierte en esclava.

   ![Entrega 5.2](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%205.2.jpg)

- Sólo el PC Maestro tiene capacidad para iniciar una comunicación mediante una llamada al
  Esclavo, mientras que éste sólo estará dedicado a esperar una posible llamada del equipo Maestro
  para contestarla.
  
- El Maestro podrá iniciar una llamada para realizar una operación de Selección o de Sondeo. Se
  deberá preguntar al usuario de la estación Maestra (figura 2 - izquierda) qué operación desea relizar.
  Si la operación es de Selección, el Maestro enviará un fichero de texto fraccionado en tramas de
  datos al Esclavo y si es de Sondeo, el Maestro hará que el Esclavo le envíe un fichero, también
  fraccionado en tramas de datos. El intercambio de datos será unidireccional.

- Si la operación es de Selección se empleará el valor ``'R'`` en el campo Dirección de todas las
  tramas. Si es de Sondeo se empleará el valor ``'T'`` en dicho campo.

- El campo Número de Trama de las tramas de datos tomará los valores ``‘0’ o ‘1’`` de forma cíclica,
  es decir, la trama siguiente a la ``‘0’`` será la ``‘1’``, y la siguiente a ésta, la ``‘0’`` y así sucesivamente.

- Para cada trama recibida se deberá devolver una confirmación de recepción o ACK (siempre y
  cuando la trama recibida sea correcta). Si la operación es de Selección, para cada trama de datos
  que reciba el esclavo, si ésta es correcta, éste deberá devolver una trama ACK. Cuando ésta sea
  recibida por el Maestro, éste podrá enviar la siguiente trama de datos al esclavo. Al recibir cualquier
  trama de datos siempre se deberá comprobar si los BCEs coinciden, aunque como no hay errores de
  transmisión, los BCEs de las tramas de datos siempre deberían coincidir. Si en cambio, la operación
  es de Sondeo, para cada trama de datos que reciba el Maestro éste deberá devolver un ACK si la
  trama es correcta. Cuando el ACK sea recibido por el Esclavo, éste podrá enviar la siguiente trama
  de datos al Maestro. Se deberá realizar la misma comprobación del BCE que se hizo con la operación
  de Selección. Tanto en selección, como en sondeo, en el momento en que, para alguna trama
  recibida, los BCEs no coincidieran, no se podría confirmar dicha trama con ACK, por lo que el
  protocolo se quedaría parado y dejaría de funcionar; sería un fallo cometido por nosotros y
  deberíamos corregirlo. Si los BCEs coincidieran, antes de enviar la trama ACK, el campo datos de
  la trama recibida se almacenará en el fichero del receptor

- El Esclavo nunca podrá dar órdenes. En caso de que la operación sea de sondeo, la estación
  Esclava solicitará a la Maestra la liberación de la comunicación cuando termine de enviar el fichero
  de texto, pero no la podrá liberar hasta que la estación Maestra se lo confirme. Dicho de otro modo,
  cuando la estación Maestra reciba una solicitud de cierre de la Esclava (figura 3), preguntará al
  usuario si quiere terminar la llamada. Si el usuario la rechaza, se enviará una negación (trama
  NACK) a la estación Esclava, que volverá a solicitar el cierre. Este proceso continuará hasta que el
  usuario de la estación Maestra confirme el cierre (envía una trama ACK). Si en cambio la operación
  era de Selección, el Maestro iniciará la liberación de la comunicación automáticamente al terminar
  de enviar el fichero y el Esclavo la aceptará directamente.
  
     ![Entrega 5.3](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%205.3.jpg)

- El fichero a enviar en la fase de transferencia se llamará “EProtoc.txt”. Al igual que en la
práctica anterior, el fichero constará primero de tres líneas de cabecera y a continuación aparecerá
el cuerpo del fichero. Las líneas de cabecera contendrán:
  - **Línea 1:** Nombre y apellidos de los autores de la práctica separados por & (Ej: Clara
    Santos & Olivia Becerra).
  - **Línea 2:** Color cabecera (texto y fondo). Se expresará con un valor entero.
  - **Línea 3:** Nombre y extensión del fichero en el equipo receptor.

- El nombre del fichero que se enviará en la fase de transferencia se llamará EProtoc.txt. El
modo de proceder del fichero será igual que en la práctica anterior. Debe tenerse en cuenta que
después de enviar el fichero completo, se enviará una trama de datos con el tamaño en bytes del
fichero.
<a name ="e52"></a>
### :two: Tipos de tramas empleadas.
Como ya sabemos, existen dos tipos de tramas: tramas de control (órdenes y respuestas) y tramas
de datos. Se debe mostrar por pantalla cada trama de control que se envíe o que se reciba. En el caso
de tramas de datos, las cuales se procesan de manera transparente al usuario, creándose el fichero
correspondiente, se mostrarán también en pantalla, tanto si son enviadas como si son recibidas.

Ejemplo de los tipos de operaciones y tramas que se emplearán en las distintas fases:

 ![Entrega 5.4](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%205.4.jpg)

<a name ="e53"></a>
### :three: Fases de la operación de Selección.

En la siguiente figura se muestra cómo se realiza la comunicación cuando la operación es de
Selección, es decir, el maestro envía el fichero de texto al esclavo:

 ![Entrega 5.5](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%205.5.jpg)


Al comienzo de cada fase de operación, el número de
trama será ‘0’. Dentro de cada fase, se irá alternando entre ‘0’ y ‘1’.

Cuando la operación es de Selección, es decir, el maestro envía el fichero de texto al esclavo

Se deberá mostrar en todo momento TODAS las tramas (control y datos) que se envían y que se reciban durante las tres fases de la comunicación (establecimiento, transferencia y liberación), tanto en el equipo emisor como en el equipo receptor

De cada trama SOLO se mostrará la información estrictamente necesaria que se indica a continuación.
Para la estación maestra se mostrará (en orden de aparición):
- **E** si la trama es enviada o **R** si la trama es recibida.
- **R**, que indica que el tipo de operación que estamos realizando es de Selección.
- La descripción del campo de control (**ENQ, ACK, NACK, EOT o STX** (si es trama
  de datos).
- El número de trama, que se corresponderá con **0 o 1.**
- El **BCE** de la trama que se envía. El valor que se muestre deberá ser un valor
  numérico, no se admitirá un carácter como representación en pantalla.

Para la estación esclava se mostrará (en orden de aparición):
- **E** si la trama es enviada o **R** si la trama es recibida.
- **R**, que indica que el tipo de operación que estamos realizando es de Selección.
- La descripción del campo de control **(ENQ, ACK, NACK, EOT o STX** (si es trama
  de datos).
- El número de trama, que se corresponderá con **0 o 1.**
-  El **BCE** que se recibe de la trama (el BCE que le llega al receptor). El valor que se
   muestre deberá ser un valor numérico, no se admitirá un carácter como representación
   en pantalla.
- El **BCE** que se calcula de la trama recibida. El valor que se muestre deberá ser un
  valor numérico, no se admitirá un carácter como representación en pantalla.

La información referente a las tramas de la fase de establecimiento se deberá mostrar en azul. La
información de la fase de transferencia se mostrará: las correspondientes a las líneas de cabecera en
rojo, las tramas del cuerpo del fichero se mostrarán en verde y las correspondientes al tamaño del
fichero se mostrarán en gris. La información relacionada con las tramas de la fase de cierre, se
mostrarán en cyan.

A continuación, se muestra un ejemplo correspondiente al envío de un fichero + el tamaño del
fichero, compuesto por 3 tramas de datos correspondientes a las líneas de cabecera, 3 tramas
referentes al cuerpo del fichero y 1 trama con la información del tamaño del fichero.  

 ![Entrega 5.6](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%205.6.jpg)

<a name ="e54"></a>
### :four: Fases de la operación de Sondeo

En la siguiente figura se muestra cómo se realiza la comunicación cuando la operación es de
Sondeo, es decir, el maestro le pide al esclavo que le envíe el fichero de texto:

 ![Entrega 5.7](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%205.7.jpg)

El número de trama será ‘0’. Dentro de cada fase, se irá alternando entre ‘0’ y ‘1’. Para cada cierre o liberación solicitada
a la estación maestra, también se alternará el número de trama.

Cuando la operación es de Sondeo, es decir, el maestro le pide al esclavo que le envíe el fichero de texto.

Para comprobar el funcionamiento de la práctica, se deberá mostrar en todo momento TODAS las
tramas (control y datos) que se envían y que se reciben durante las tres fases (establecimiento,
transferencia y liberación), tanto en el equipo emisor como en el receptor. De cada trama solo se mostrará la
información estrictamente necesaria que se indica a continuación:

Para la estación maestra se mostrará (en orden de aparición):
- **E** si la trama es enviada o **R** si la trama es recibida.
- **T**, que indica que el tipo de operación que estamos realizando es de Sondeo.
- La descripción del campo de control (ENQ, ACK, NACK, EOT o STX (si es trama
  de datos).
- El número de trama, que se corresponderá con **0 o 1.**
- El **BCE** que se recibe de la trama (el BCE que le llega). El valor que se muestre deberá
ser un valor numérico, no se admitirá un carácter como representación en pantalla.
- El **BCE** que se calcula de la trama recibida. El valor que se muestre deberá ser un
valor numérico, no se admitirá un carácter como representación en pantalla.

Para la estación esclava se mostrará (en orden de aparición):
- **E** si la trama es enviada o **R** si la trama es recibida.
- **T**, que indica que el tipo de operación que estamos realizando es de Sondeo.
- La descripción del campo de control **(ENQ, ACK, NACK, EOT o STX*** (si es trama
  de datos).
- El número de trama, que se corresponderá con **0 o 1.**
- El **BCE** de la trama que se envía. El valor que se muestre deberá ser un valor
  numérico, no se admitirá un carácter como representación en pantalla.

La información referente a las tramas de la fase de establecimiento se deberá mostrar en azul. La
información de la fase de transferencia se mostrará: las correspondientes a las líneas de cabecera en
rojo, las tramas del cuerpo del fichero se mostrarán en verde y las correspondientes al tamaño del
fichero se mostrarán en gris. La información relacionada con las tramas de la fase de cierre, se
mostrarán en cyan.

A continuación, se muestra un ejemplo correspondiente al envío de un fichero + tamaño del fichero,
compuesto por 3 tramas de datos correspondientes a las líneas de cabecera, 2 tramas correspondiente
al cuerpo del fichero y una trama con la información del tamaño del fichero. En este ejemplo, al
solicitar el esclavo el cierre de la comunicación, el maestro rechazó el primer cierre y aceptó el
segundo

 ![Entrega 5.8](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%205.8.jpg)


<a name ="e55"></a>
### :five: Volcado de pantalla a fichero Prolog-m.txt y Prolog-e.txt
Para comprobar lo que ha podido ocurrir durante la ejecución del protocolo, toda la actividad
mostrada en pantalla se volcará a dos ficheros distintos. La información mostrada en pantalla en el equipo
maestro, se volcará a un fichero llamado **Prolog-m.txt** y la mostrada en el equipo esclavo a un fichero
llamado **Prolog-e.txt**.

 ![Entrega 5.9](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%205.9.jpg)

En caso de haber activado previamente el volcado de información al fichero **log.txt** (mediante F5),
ese fichero se cerrará una vez hayamos entrado en modo protocolo, es decir, al pulsar F6.

<a name ="e56"></a>
### :six: Control de fin de aplicación (ESC)
En este momento de la práctica, la tecla escape debería funcionar perfectamente en la mayoría de
los casos. Al pulsar escape en el programa principal, el usuario pondría fin a la ejecución de la aplicación.
En caso de estar realizando alguna acción mientras se pulse dicha tecla, por ejemplo, enviando fichero,
enviando trama de control, enviando fichero mediante protocolo, … en lugar de abandonar la aplicación,
se debería cancelar dicha acción y volver a la situación anterior, de modo que la práctica no termine de
manera drástica. En el caso de estar recibiendo, tanto si estamos o no en modo protocolo, podría omitirse
la pulsación del escape, ya que el abandonar el receptor la aplicación, provocaría que el emisor se quedara
enviando información sin que nadie la recibiera (no sería muy lógico). Siempre se debe pensar en utilizar
el escape de la manera más lógica y coherente posible
[:top:](#top)

<a name ="ent6"></a>
# Entrega 6
<a name ="e61"></a>
### :one: Funcionamiento del protocolo sensible a errores

- En esta entrega se parte de la práctica anterior, el protocolo maestro-esclavo. El protocolo
seguirá funcionando como hasta ahora (incluyendo los ficheros log de maestro y esclavo),
simplemente se le añadirá una nueva funcionalidad, la cual será complementaria.

- En esta sesión la aplicación deberá controlar y corregir la posible alteración de las tramas de
datos por interferencias externas o ruido sobre la línea. En realidad, se trata sólo de una simulación,
ya que en nuestro caso la transmisión es virtual.

- Para la generación de ruido se empleará una función de inserción de errores, una vez que las
tramas hayan sido construidas y se haya calculado su BCE, de forma que, desde el punto de vista
del receptor, se producirá el mismo efecto que si el error se hubiera introducido durante la
transmisión de las tramas por el medio.

- La pulsación de la tecla **F7** simulará errores en una trama. Esta tecla solo se podrá pulsar cuando
se esté ejecutando la opción Maestro/esclavo (**F6**). Solo tendrá efecto en el emisor durante el envío
del fichero, y provocará que la siguiente trama a enviar se vea alterada con errores.

- Para ello, después de calcular y rellenar el campo BCE, se va a sustituir el primer carácter del
campo datos por ‘ç’ (CampoDatos [0] = ’ç’). Esto simulará el caso de que, después de ser enviada
la trama, ésta se vea alterada por algún tipo de ruido durante la transmisión, cambiándose el primer
carácter del campo datos por el valor ‘ç’.

- Cada vez que se pulse **F7** se introducirá error en una trama diferente. No se podrá introducir
errores en la misma trama y, por tanto, tampoco se podrán introducir errores en la retrasmisión de
una trama. (La trama enviada y su retransmisión se consideran solo una trama).

- Se puede pulsar **F7** tantas veces como dure el envío del cuerpo del fichero (en otras secciones
de la práctica no debe tener efecto). Esto significa que solo se van a poder introducir errores en las
tramas referentes al cuerpo del fichero.

- Se deberá poder enviar errores consecutivos, es decir, enviar errores en tramas consecutivas.
Para probar este caso de forma sencilla, se puede usar el fichero de 10 tramas (campus virtual)
empleando la velocidad del puerto más baja, 1200 bps.

- En el receptor, se debe calcular el BCE de cada trama de datos recibida (como siempre se ha
hecho), para luego comparar el valor obtenido con el del campo BCE de la trama recibida.
- Si los BCEs coinciden, se devolverá una trama **ACK** (como se ha hecho en la entrega anterior),
informando que todo es correcto.

- Si los datos fueron alterados después de rellenar el BCE (en el emisor), el receptor detectará
que los BCEs no coinciden y devolverá una trama **NACK**, indicando de esta manera al emisor que
retransmita de nuevo la trama.

<a name ="e62"></a>
### :two: Fases de la operación de Selección con control de errores

En la siguiente figura se muestra cómo se realiza la comunicación cuando la operación es de
Selección con control de errores. En este ejemplo se detecta un error en la segunda trama de datos
que envía el maestro al esclavo. Éste contesta con una trama NACK y el maestro retransmite la
misma trama, la cual ya llega sin errores, por lo que el esclavo responde con una ACK.

 ![Entrega 6.1](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%206.1.jpg)


Como se puede observar, los números de trama de la trama errónea y de la trama retransmitida son
los mismos, ya que se trata de la misma trama.

Se puede comprobar en la figura 1, que, al comienzo de cada fase de operación, el número de trama
será ‘0’. Dentro de cada fase, se irá alternando entre ‘0’ y ‘1’.

Para comprobar el funcionamiento de la práctica, se deberá mostrar en todo momento **TODAS** las
tramas (control y datos) que se envían y que se reciban durante las tres fases de la comunicación
(establecimiento, transferencia y liberación), tanto en el equipo emisor como en el equipo receptor,
de la misma manera que se hizo en la práctica anterior, así como en los colores empleados en dicha
práctica. En caso de no mostrar todas las tramas la práctica será considerada NO APTA.

A continuación, se muestra un ejemplo correspondiente al envío de un fichero + el tamaño del
fichero, compuesto por 3 tramas de datos correspondientes a las líneas de cabecera, 3 tramas
referentes al cuerpo del fichero (siendo la segunda de ellas incorrecta por lo que se vuelve a
retransmitir) y 1 trama con la información del tamaño del fichero.

 ![Entrega 6.2](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%206.2.jpg)

<a name ="e63"></a>
### :three: Fases de la operación de Sondeo con control de errores

En la siguiente figura se muestra cómo se realiza la comunicación cuando la operación es de
Sondeo con control de errores. En este ejemplo se detecta un error en la segunda trama de datos que
envía el esclavo al maestro. Éste contesta con una trama NACK y el esclavo retransmite la misma
trama, la cual ya llega sin errores, por lo que el maestro responderá con una ACK. Al final el esclavo
pide liberación, pero es el maestro el que la concede o no, y como se observa en el ejemplo en la
primera petición ésta es denegada.

 ![Entrega 6.3](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%206.3.jpg)

Como se puede observar, los números de trama de la trama errónea y de la trama retransmitida son
los mismos, ya que se trata de la misma trama.

Se puede comprobar en la figura 3, que, al comienzo de cada fase de operación, el número de trama
será ‘0’. Dentro de cada fase, se irá alternando entre ‘0’ y ‘1’. Para cada cierre o liberación solicitada
a la estación maestra, también se alternará el número de trama.

Para comprobar el funcionamiento de la práctica, se deberá mostrar en todo momento **TODAS** las
tramas (control y datos) que se envían y que se reciban durante las tres fases de la comunicación
(establecimiento, transferencia y liberación), tanto en el equipo emisor como en el equipo receptor,
de la misma manera que se hizo en la práctica anterior, así como en los colores empleados en dicha
práctica. En caso de no mostrar todas las tramas la práctica será considerada NO APTA.

A continuación, se muestra un ejemplo correspondiente al envío de un fichero + tamaño del fichero,
compuesto por 3 tramas de datos correspondientes a las líneas de cabecera, 3 tramas referentes al
cuerpo del fichero (siendo la tercera trama incorrecta por lo que se vuelve a retransmitir) y una trama
con la información del tamaño del fichero. En este ejemplo, al solicitar el esclavo el cierre de la
comunicación, el maestro rechazó el primer cierre y aceptó el segundo.


 ![Entrega 6.4](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%206.4.jpg)

<a name ="e64"></a>
### :four: Puntos a incluir en la documentación externa

 ![Entrega doc](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%20doc.jpg)

 ![Entrega doc 2](https://github.com/Pmcb04/PracticaRedes/blob/master/images/Entrega%20doc%202.jpg)
 
 [:top:](#top)
