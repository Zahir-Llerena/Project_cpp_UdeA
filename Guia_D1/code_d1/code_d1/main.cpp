// =====================================================================================
// Universidad de Antioquia
// Facultad de Ingenieria - Departamento de Telecomunicaciones -
// @authors: Zahir Llerena
// email: zahir.llerena@udea.edu.co
// =====================================================================================
// Librerias principales a invocar:
// Las librerías son como cajas de herramientas especializadas que traemos al taller
// para poder realizar tareas complejas sin tener que fabricar cada tornillo desde cero.

// (Input/Output Stream): Es la herramienta de comunicación.
// Función: Permite que el programa muestre texto en la pantalla (std::cout) y que
// nosotros podamos escribir datos con el teclado (std::cin).
#include <iostream>

// (C Standard Integer): Es la herramienta de precisión matemática.
// Función: Define tipos de números con un tamaño exacto de bits (como uint64_t).
// En el Tetris: La usamos para crear el board_t. Nos asegura que cada fila del tablero
// tenga exactamente 64 espacios (bits) para colocar bloques. Es lo que nos permite tener
// un tablero de hasta 64 columnas de ancho.
#include <cstdlib>

// (C Time): Es la herramienta del reloj del sistema.
// Función: Permite acceder a la hora y fecha actual del computador.
// En el Tetris: Aunque en el código actual el azar se maneja con <random>,
// tradicionalmente se usa el tiempo del reloj para que definir una semilla
// para definir la extraccion de piezas de manera aleatoia.
#include <ctime>

// (Random Number Generation): Es la herramienta de eleatoriedad controlada.
// Función: Proporciona motores matemáticos avanzados para generar números al azar.
// En el Tetris: Es el motor detrás de la función obtenerPiezaAleatoria().
// Se encarga de que nunca se sepa cuál será la próxima pieza que va a caer.
#include <random>

// (C Standard Library)
// Es la herramienta de control del sistema.
// Función: Contiene funciones generales para interactuar con el sistema operativo.
// En el Tetris: La usamos principalmente por la instrucción system("clear || cls") dentro
// de la función renderizar. Esto sirve para "limpiar el tablero" de la consola antes de
// dibujar el siguiente movimiento de la pieza.
// Necesario para uint64_t (Soporta hasta 64 columnas)
#include <cstdint>
// Inicio ---------------------------------------------------------------------------
/*
BLOQUE 1: DEFINICIONES DE DATOS ---
Aquí definimos "qué" información vamos a manejar.

Usamos 'uint64_t' para que cada fila sea un número de 64 bits (64 espacios).

typedef: Es la abreviatura de Type Definition (Definición de Tipo). Su función es crear
un "alias" o un apodo para un tipo de dato que ya existe.
 
uint64_t: Es un tipo de dato que proviene de la librería <cstdint>.

u: Significa unsigned (sin signo). Solo guarda números positivos (del 0 en adelante).

int: Significa integer (entero). No permite decimales.
 
64: Es el tamaño exacto en bits.
 
_t: Es una convención de C++ para indicar que es un "tipo" (type).
*/

typedef uint64_t board_t;

// Es como decir: "A partir de ahora, cada vez que yo diga board_t, el computador
// debe entender que me refiero a un uint64_t".

/*
¿Por qué usamos 64 bits exactamente?

En nuestro Tetris, cada fila del tablero es un solo número de este tipo.
Al ser de 64 bits, tenemos 64 interruptores (0 o 1) alineados en una sola fila.
 
- Si el usuario define un ancho de 10, usamos los primeros 10 bits. El maximo es de
   columnas 64

- Esto es mucho más eficiente que crear 64 variables pequeñas; aquí,
  una sola variable contiene toda la información de una fila horizontal.
 
¿Por qué no usar simplemente uint64_t en todo el código?
Usar board_t tiene ventajas para un programador:

- Claridad Semántica: Cuando se lee board_t fila; se entiende que esa
  variable pertenece al tablero de juego. Si leyera uint64_t fila;, solo sabría
  que es un número grande, pero no para qué sirve.
 
- Facilidad de Cambio: Si mañana queremos que el Tetris sea gigante
  y soporte 128 columnas. En lugar de buscar y cambiar uint64_t en las 200
  líneas de código, solo cambiamos la definición inicial a un tipo más grande,
  y todo el programa se actualiza automáticamente.
*/

// --------------------------------------------------------------------------------------
/*
¿Qué es una struct? (El Contenedor)
 
Una 'struct' es una forma de agrupar diferentes tipos de datos bajo un
mismo nombre para representar un objeto de la vida real.
 
En el código, el nombre del elemento que agrupa todo se llama "Pieza".

board_t filas[4]; (El Cuerpo): Es un requisito interno de una sola pieza.
                               "Cada pieza que fabricamos debe tener 4 espacios de memoria
                                para sus filas".

- filas[4]: Es un arreglo (una lista) de 4 elementos. Como cada elemento es un board_t
  (Un número de 64 bits), la pieza tiene 4 renglones de "memoria" para dibujarse.
 
- Aunque haya piezas pequeña (como un cuadrado de 2x2), le damos un espacio de 4x4 para
  que tenga margen de maniobra cuando la hagamos rotar.
 
int ancho; e int alto; (Las Dimensiones)
 
- ancho: Guarda cuántas columnas ocupa la figura real dentro de esos 64 bits.
 
- alto: Guarda cuántas filas ocupa hacia abajo.

Sin estos datos, el juego no sabría si una pieza ya tocó la pared derecha o el suelo.
Es la información que usamos para que la pieza "sienta" los límites del tablero.
*/

struct Pieza {
    board_t filas[4];
    int ancho;
    int alto;
};

// --------------------------------------------------------------------------------------
/*
Esta función es la "Fábrica de Azar" de nuestro videojuego.

El Motor de Azar

- static: Le dice al computador: "Crea un algoritmo de azar una sola vez
          y mantenlo encendida mientras el juego funcione".
 
- mt19937: Nombre de un motor matemático que genera números
           impredecibles. Es un macanismo que revuelve los números.
 
- uniform_int_distribution<>(0, 6): Obliga al algoritmo a darnos solo
                                    numeros entre 0 y 6, ya que solo tenemos
                                    7 piezas disponibles.

El Catálogo de Piezas (El Estante)

En C++, cuando trabajamos con los procesadores y el dibujo de piezas
de Tetris, necesitamos hablar en Binario.
 
El Prefijo como Traductor (0b)

0: Indica que vamos a usar una notación especial.
b: Viene de Binario.

Al escribir 0b011, le estamos ordenando al compilador: "No leas esto como el
número once (lectura de derecha a izquierda); léelo como una serie de
interruptores: Apagado-Encendido-Encendido".
 
- Barra (I): {{0b1111, 0, 0, 0}, 4, 1}
             Línea horizontal de 4 bloques. Ancho 4, Alto 1.
 
- Cuadrado (O): {{0b11, 0b11, 0, 0}, 2, 2}
                Un bloque sólido de 2x2. Ancho 2, Alto 2.

- "T" (T): {{0b010, 0b111, 0, 0}, 3, 2}
           Un bloque sobre una fila de tres. Ancho 3, Alto 2.
 
- Zig-Zag (S): {{0b011, 0b110, 0, 0}, 3, 2}
               Dos bloques a la derecha sobre dos bloques a la izquierda.
               Ancho 3, Alto 2.
 
- Zig-Zag Invertido (Z): {{0b110, 0b011, 0, 0}, 3, 2}
                         Dos bloques a la izquierda sobre dos bloques a la
                         derecha. Ancho 3, Alto 2.
 
- "L" Invertida (J): {{0b100, 0b111, 0, 0}, 3, 2}
                     Un bloque en la esquina superior izquierda sobre una
                     fila de tres. Ancho 3, Alto 2.
 
- "L" (L): {{0b001, 0b111, 0, 0}, 3, 2}
           Un bloque en la esquina superior derecha sobre una
           fila de tres. Ancho 3, Alto 2.
 
Aunque el tablero sea de 64 columnas, cada pieza vive en su propia "celda" de 4x4.
Esta cuadrícula es el lienzo donde el algoritmo de rotación y dibujo trabaja antes
de proyectarlo.
 
- En el código: El bit más pequeño (la derecha) es el primero que el computador procesa.
 
- En la práctica: Si escribimos 0b0001, el bloque "#" aparecerá en la esquina derecha de ese
  cuadrado de 4x4.
 
- La fila 0: Es, efectivamente, el "techo" de la pieza.
 
"Imaginen que cada pieza es un edificio de 4 pisos (filas 0 a 3).
 Empezamos a construir desde arriba (Fila 0) hacia abajo (Fila 3).
 Y en cada piso, colocamos los ladrillos comenzando desde la ventana de
 la derecha hacia la izquierda".
 
Plantilla que le dice al computador: "Si quieres crear una pieza de Tetris,
tiene que tener 3 elementos: un arreglo de 4 filas, un ancho y un alto".
 
La función obtenerPiezaAleatoria() actúa como un selector que trabaja sobre un arreglo
de instancias de tipo Pieza. No modifica el tipo Pieza (el molde), sino que accede
a las posiciones de memoria del arreglo piezas para devolver una copia de una de esas
instancias.
 
En la funcion: obtenerPiezaAleatoria(), se tiene la escritura en la definicion
Pieza obtenerPiezaAleatoria().

El hecho de que la palabra 'Pieza' aparezca antes del nombre de la función indica el
Tipo de Retorno.
 
"Voy a crear una función llamada obtenerPiezaAleatoria que, cuando termine de ejecutarse,
 me va a devolver un objeto completo de tipo Pieza".
*/

Pieza obtenerPiezaAleatoria() {
    static std::random_device rd;  // Semilla rd. Pide al 'Sistema operativo' uno y solo un numero aleatorio por 'static'
    static std::mt19937 gen(rd()); // Toma la semilla rd() y la usa para empezar a generar una
                                   // cadena infinita de números aparentemente al azar.
    std::uniform_int_distribution<> dis(0, 6); // Los números que genera gen son grandes.
                                               // Esta línea actúa como un "filtro" y toma del 0 al 6

    // Definición de las 7 piezas clásicas con bits
    // Si 'Pieza' es el molde, piezas[7] es el estante que contiene 7 de esos
    // moldes fabricados y listos para usar.
    Pieza piezas[7] = {
        {{0b1111,0,0,0}, 4, 1}, {{0b11,0b11,0,0}, 2, 2}, {{0b010,0b111,0,0}, 3, 2},
        {{0b011,0b110,0,0}, 3, 2}, {{0b110,0b011,0,0}, 3, 2}, {{0b100,0b111,0,0}, 3, 2},
        {{0b001,0b111,0,0}, 3, 2}
    };
    return piezas[dis(gen)];
}

/*
Función sin uso de librerías STL
Pieza obtenerPiezaAleatoria() {
     // Definimos el catálogo de piezas como 'static'.
     // Esto evita que el arreglo se cree de nuevo cada vez que la función es llamada,
     // ahorrando tiempo de procesamiento y memoria.
     static const Pieza catalogo[7] = {
         {{0b1111,0,0,0}, 4, 1}, {{0b11,0b11,0,0}, 2, 2}, {{0b010,0b111,0,0}, 3, 2},
         {{0b011,0b110,0,0}, 3, 2}, {{0b110,0b011,0,0}, 3, 2}, {{0b100,0b111,0,0}, 3, 2},
         {{0b001,0b111,0,0}, 3, 2}
     };

     // rand() es una función de la librería <cstdlib> (C estándar, no STL).
     // El operador '%' (módulo) asegura que el resultado esté siempre entre 0 y 6.
     int indice = rand() % 7;
     
     return catalogo[indice];
 }
 
 Para que esto funcione, debes poner esta línea en la primera línea de tu main():
 
 srand(time(NULL)); // Inicializa el generador con el tiempo actual
*/

// --------------------------------------------------------------------------------------
/*
 - Stack (Pila): Es la memoria de acceso rápido y automático. Aquí viven las variables
                 locales (como int i, board_t filaVisual) y los parámetros quepasas
                 por valor. Se libera sola en cuanto la función llega a su llave de cierre.
 
 - Heap: Es la memoria dinámica. Aquí viven los datos que creas con new.
         En el Tetris, el tablero (board_t* t) vive aquí porque su tamaño puede ser
         cambiar de acuerdo al ANCHO y ALTO que deterina el usuario.

BLOQUE 2: LAS HERRAMIENTAS (FUNCIONES) ---

Tarea: Girar la pieza 90 grados.

Usamos '&p' (Referencia): Estamos recibiendo la pieza original (Pieza)
y la modificaremos directamente en su lugar de memoria. (Paso por referencia)
Cualquier cambio que se hagas a 'p' dentro de esta función, se refleja en la pieza original.

Usar el símbolo '&' es como dar esa llave: permitimos que nuestras funciones operen
directamente sobre la ("Pieza") que vive en la RAM.

Utilizamos 'PASO POR REFERENCIA' (&p) para evitar crear copias innecesarias de la
estructura completa en cada ROTACION, lo que optimiza el uso de memoria.

 - Stack: Es la memoria de acceso rápido y automático. Aquí viven las variables
          locales (como int i, board_t filaVisual) y los parámetros quepasas
                 por valor. Se libera sola en cuanto la función llega a su llave de cierre.
 
 - Heap: Es la memoria dinámica. Aquí viven los datos que creas con new.
         En el Tetris, el tablero (board_t* t) vive aquí porque su tamaño puede ser
         cambiar de acuerdo al ANCHO y ALTO que deterina el usuario.
 
MEMORIA: Esta función trabaja principalmente en el Stack, pero recibe una Referencia (&).
Al recibir Pieza &p, no estamos creando una copia de la pieza en el Stack; estamos
pasando una "dirección" a la pieza original. Sin embargo, la variable 'Pieza nueva'
que creamos dentro de la función vive en el Stack.
 
Al ser 'const', garantizamos a la memoria que solo vamos a leer del Heap, no a escribir.
*/

void rotarPieza(Pieza &p) {
    // - Creamos un como 'tablero nuevo'.
    // En nuestro nuevo espacio de memoria, todas las filas estén "apagadas" e
    // intercambiamos alto por ancho, porque al girar 90° de 3x2 -> 2x3
    // ancho = p.alto, alto = p.ancho (El intercambio de medidas)
    // Creamos un 'lienzo nuevo' (Destino) vacío y limpio. ("El borrador")
    Pieza nueva = {{0,0,0,0}, p.alto, p.ancho};

    // - Escaneamos la pieza fuente 'p' (La original) para solo leer sus datos (No alteramos nada en ella).
    // El Bucle Externo (j - Columnas):
    // Construye la nueva configuración fila por fila".
    // Estamos preparando una fila limpia para ser rellenada.
    for (int j = 0; j < p.ancho; j++) {
        board_t nuevaFila = 0; // Esta variable construirá la nueva fila bit a bit.
        
        // El Bucle Interno (i - Filas):
        // Este bucle es el "lector de bits".
        // Es el que recorre cada fila de la pieza original para ver si hay un
        // bloque (1) en la posición actual.
        for (int i = 0; i < p.alto; i++) {
            
            // - ¿Hay un bloque aquí?
            //   'p.filas[i] >> j' mueve el bit de la columna j hasta la posición 0.
            //   '& 1' es nuestra "lupa" para ver si ese bit es 1 (hay bloque) o 0 (vacío).
            if ((p.filas[i] >> j) & 1) {
                
                // - La rotación:
                // Calculamos la nueva posición. El nuevo bit se coloca en una posición calculada
                // mediante 'p.alto - 1 - i'. Esto es lo que realiza el giro.
                // |= se llama Operador de Asignación con OR a nivel de bits.
                // Compara dos números bit a bit. Si cualquiera de los dos bits es 1, el resultado es 1.
                // Solo es 0 si ambos bits son 0.

                // El << i: Es el "Movimiento" (Traslación)
                // Vuelta i = 0: (board_t)1 << 0 -> 0000...0001
                // Vuelta i = 1: (board_t)1 << 1 -> 0000...0010
                // Vuelta i = 2: (board_t)1 << 2 -> 0000...0100

                nuevaFila |= ((board_t)1 << (p.alto - 1 - i));
            }
        }
        // Guardamos la fila ya rotada en nuestro lienzo nuevo.
        // El código usa la pieza nueva (nueva) como un destino de resultados.
        nueva.filas[j] = nuevaFila;
    }
    // - Sobrescribimos la pieza original con la nueva configuración.
    p = nueva;
}

/*
"¿Por qué utilizaron 'Pieza &p en lugar de Pieza *p (puntero)?":
Usamos &p porque queremos modificar la pieza original (el giro es permanente)
y tenemos la certeza de que siempre habrá una pieza para rotar.
Además, mejora la legibilidad del código al permitirme usar
el operador punto (.) en lugar de la flecha (->).

No puede ser nula. Siempre existe.
Es más "limpia" y segura en el Stack. Le dice al compilador: "Usa este objeto directamente".

Puntero: Es más flexible para gestionar el Heap. Nos permite navegar por estructuras
complejas y manejar la ausencia de objetos (el estado "nada").
 
- Con respecto al bucle: que hace en realidad?
El doble bucle implementa una transformación de coordenadas matricial.
El bucle externo recorre las dimensiones de la pieza original para remapear sus bits
en una estructura temporal (nueva), la cual inicializo en cero para asegurar la
integridad de los datos y evitar contaminación con residuos de memoria (valores basura).
Este enfoque es eficiente porque realiza la rotación mediante manipulación de bits
directa.
*/

// --------------------------------------------------------------------------------------
/*
Tarea: Detectar si la pieza toca un muro, el suelo o bloques ya fijos.
'const board_t* t': Usamos un puntero 'const' al tablero. Esto es vital:
le dice al compilador: "Solo voy a mirar el tablero, no voy a alterarlo".
 
 - const board_t* t:
   ¿Qué es?: Un puntero constante al tablero principal del juego.
   Función: Contiene el estado actual de los bloques ya fijados.
   El const: le asegura que mientras estemos "revisando" el tablero para detectar colisiones,
   no lo modificaremos accidentalmente. Solo estamos leyendo.

 - int ALTO, int ANCHO:
   ¿Qué es?: Las dimensiones dinámicas del tablero que el usuario definió al inicio.
   Función: Son nuestras "reglas de medir". Sin estos valores, la función no sabría
   dónde están las fronteras (muros) del juego.
 
 - const Pieza* p:
   ¿Qué es?: Un puntero a la estructura Pieza que queremos evaluar.
   Función: Es la "pieza". Queremos saber si esa pieza específica puede
   existir en las coordenadas px, py que le estamos proponiendo.
 
 - int px, int py:
   ¿Qué es?: Las coordenadas (posición en X y Y) del lugar donde "queremos" colocar la pieza.
   Función: Es la "hipótesis" del movimiento. El juego le pregunta a esta función: "Oye, si
   pongo la pieza en esta coordenada exacta, ¿chocaría con algo?".

 Plano cartesiano:
 * El origen (0,0) está en la esquina SUPERIOR IZQUIERDA.
 * Eje X: Crece de izquierda a derecha (esto sí es igual al cartesiano).
 * Eje Y: Crece de arriba hacia abajo.
 
 - Stack: Es la memoria de acceso rápido y automático. Aquí viven las variables
          locales (como int i, board_t filaVisual) y los parámetros quepasas
          por valor. Se libera sola en cuanto la función llega a su llave de cierre.
 
 - Heap: Es la memoria dinámica. Aquí viven los datos que creas con new.
         En el Tetris, el tablero (board_t* t) vive aquí porque su tamaño puede ser
         cambiar de acuerdo al ANCHO y ALTO que deterina el usuario.
 
 MEMORIA: Uso de Punteros (*) para acceder al Heap.
 El tablero t es un puntero. Esto significa que la función no "carga" todo el
 tablero en el Stack (lo cual sería lento), sino que solo recibe la dirección
 de dónde está el tablero en el Heap.
  
*/
bool hayColision(const board_t* t, int ALTO, int ANCHO, const Pieza* p, int px, int py) {
    // Recorremos fila por fila la pieza que intenta moverse.
    // p->alto: En la dirección de memoria p, busca el valor guardado en el campo 'alto' de la Pieza.
    
    for (int i = 0; i < p->alto; i++) {
        // Cuando i = 0, estás analizando la primera fila de la pieza (la parte superior).
        // Cuando i aumenta, estás bajando por las filas de la pieza.
        // i cuantifica cuántos renglones bajamos desde el ancla (py).
        // Calculamos la fila absoluta en el tablero.
        // Cuando yCoord aumenta, estás bajando en el tablero (acercándote a ALTO).
        int yCoord = py + i;

        // - REGLA IMPORTANTE (Límites físicos)
        //   ¿La pieza se sale por abajo? (yCoord >= ALTO)
        if (yCoord >= ALTO) return true;
        // ¿La pieza se sale por izquierda o derecha?
        if (px < 0 || (px + p->ancho) > ANCHO) return true;

        // Declaramos una variable 'piezaEnPos' que es de tipo 'board_t'
        // Esta variable actuará como una máscara de bits para realizar la comparativa de
        // colisión para la fila actual 'i'.
        // Realizamos una traslación horizontal de los bits mediante el operador '<<'.
        // La fórmula (ANCHO - p->ancho - px) mapea las coordenadas locales de la pieza
        // al sistema global del tablero, alineando la geometría de la pieza en la columna 'px'.
        // ANCHO - p->ancho: Esto nos dice cuánto espacio vacío hay en total a la derecha.
        // - px: Esto "quita" el espacio de la derecha que no necesitamos, empujando la pieza
        //       hacia la izquierda hasta que su borde toque la columna px deseada.
        board_t piezaEnPos = p->filas[i] << (ANCHO - p->ancho - px);
        if ((t[yCoord] & piezaEnPos) != 0) return true;

        // - EL DETECTOR DE COLISIÓN (AND lógico)
        // Al usar un puntero (board_t* t): Pasas solo la referencia, pasas una dirección
        // de memoria 8 bytes.
        // Cuando accedes a t[yCoord], el programa hace lo siguiente:
        // Va a la dirección de memoria guardada en t, Salta 'yCoord' posiciones hacia adelante.
        
        // Comparamos el tablero ('t[yCoord]') con nuestra pieza alineada ('piezaEnPos').
        // Si el resultado es distinto de 0, significa que hay un 1 en la pieza
        // y un 1 en el tablero en la MISMA posición: Colisión.
                    
    }
    
    // Si terminamos de recorrer toda la pieza y no chocamos con nada, es un movimiento válido.
    return false;
}
// --------------------------------------------------------------------------------------
/*
Tarea: Soldar la pieza al tablero cuando ya no puede bajar más.
Aquí ya no usamos 'const' en board_t* t, porque ahora SÍ vamos a modificar el tablero.
 
 - Stack: Es la memoria de acceso rápido y automático. Aquí viven las variables
          locales (como int i, board_t filaVisual) y los parámetros quepasas
          por valor. Se libera sola en cuanto la función llega a su llave de cierre.
 
 - Heap: Es la memoria dinámica. Aquí viven los datos que creas con new.
         En el Tetris, el tablero (board_t* t) vive aquí porque su tamaño puede ser
         cambiar de acuerdo al ANCHO y ALTO que deterina el usuario.
 
MEMORIA: Modificación directa en el Heap.
Recibe la dirección del tablero en el Heap. La gran diferencia es que aquí no es const.

La función usa el Stack para calcular el desplazamiento (<<), pero el resultado final
se escribe permanentemente en la memoria del Heap.
*/

// Tarea: Soldar la pieza al tablero cuando ya no puede bajar más.
// Aquí ya no usamos 'const' en board_t* t, porque ahora SÍ vamos a modificar el tablero.

void fijarPieza(board_t* t, int ANCHO, const Pieza* p, int px, int py) {
    // - Escaneamos la pieza (fila por fila).
    //   El bucle recorre la pieza de arriba hacia abajo (fila 0, 1, 2, hasta alto el fondo).
    for (int i = 0; i < p->alto; i++) {
        
        // - 't[py + i]': Elegimos la fila específica del tablero donde la pieza va a quedar.
        // - '|= ' : El operador OR de soldadura.
        // - '(p->filas[i] << ...)' : La pieza ya alineada y lista para estamparse.
        t[py + i] |= (p->filas[i] << (ANCHO - p->ancho - px));
    }
}

/*
La funcion del bucle es realizar la proyección fila a fila de la geometría de la pieza
hacia las coordenadas del tablero.
Al iterar sobre la altura de la pieza y aplicar una operación de unión lógica (OR),
logra integrar la pieza al mapa de bits del juego, transformando una entidad
'flotante' en un obstáculo estático dentro del tablero."
*/
// --------------------------------------------------------------------------------------
/*
Escanea el tablero en busca de filas completas y gestiona su eliminación.
Aplica un algoritmo de desplazamiento para reordenar las filas superiores
tras eliminar una fila llena, manteniendo la integridad de los bloques fijos.
- t Puntero al tablero (se modifica para reflejar la eliminación).
- ALTO, ANCHO Dimensiones actuales del tablero.

 - Stack: Es la memoria de acceso rápido y automático. Aquí viven las variables
          locales (como int i, board_t filaVisual) y los parámetros quepasas
          por valor. Se libera sola en cuanto la función llega a su llave de cierre.
 
 - Heap: Es la memoria dinámica. Aquí viven los datos que creas con new.
         En el Tetris, el tablero (board_t* t) vive aquí porque su tamaño puede ser
         cambiar de acuerdo al ANCHO y ALTO que deterina el usuario.
 
MEMORIA: Reordenamiento de bloques de memoria en el Heap.
El hecho de mover renglones en el objeto 't', se esta moviendo datos de una celda de
memoria a otra dentro del montón (Heap).
*/
void limpiarFilas(board_t* t, int ALTO, int ANCHO) {
    // - Crear Máscara de Comparación:
    // Construimos una "fila perfecta" (todos los bits en 1) según el ancho definido.
    // Definicmos un Acumulador.
    board_t filaLlena = 0;
    // El bucle va encendiendo cada bit,uno por uno, de derecha a izquierda,
    // por ejemplo: 0000, 0001, 0011, 0111, 1111. Si ANCHO = 4
    // (board_t)1, es una manera de hacer entender a C++ que el 1 se desplace por
    // los espacios del tablero de un solo renglón siendo este con 64 espacios como máximo.
    // El << i: Es el "Movimiento" (Traslación)
    
    // Vuelta i=0: (board_t)1 << 0 -> 0000...0001
    // Vuelta i=1: (board_t)1 << 1 -> 0000...0010
    // Vuelta i=2: (board_t)1 << 2 -> 0000...0100
    for(int i = 0; i < ANCHO; i++) filaLlena |= ((board_t)1 << i);

    // - Escaneo y Reordenamiento:
    for (int i = 0; i < ALTO; i++) {
        // ¿La fila actual está llena? Comparamos bit a bit contra la máscara.
        if (t[i] == filaLlena) {
            
            // - Desplazamiento (Efecto Gravedad):
            // Si la fila está llena, movemos todas las filas superiores un nivel hacia abajo.
            // Iteramos hacia atrás para sobreescribir fila por fila.
            for (int k = i; k > 0; k--) t[k] = t[k - 1];
            
            // - Limpieza del espacio superior:
            // La fila superior siempre queda vacía tras el desplazamiento.
            t[0] = 0;
        }
    }
}
// --------------------------------------------------------------------------------------
/*
 Dibuja en la consola el estado actual del juego.
 Esta función actúa como el "monitor" del juego: toma los datos lógicos (bits)
 y los traduce a caracteres visuales (# y .) para el usuario.
 
 - Stack: Es la memoria de acceso rápido y automático. Aquí viven las variables
          locales (como int i, board_t filaVisual) y los parámetros quepasas
          por valor. Se libera sola en cuanto la función llega a su llave de cierre.
 
 - Heap: Es la memoria dinámica. Aquí viven los datos que creas con new.
         En el Tetris, el tablero (board_t* t) vive aquí porque su tamaño puede ser
         cambiar de acuerdo al ANCHO y ALTO que deterina el usuario.
 
MEMORIA: La variable board_t filaVisual. Esta variable vive en el Stack.
*/
void renderizar(const board_t* t, int ALTO, int ANCHO, const Pieza* p, int px, int py) {
    // Limpiamos la pantalla para eliminar el rastro del fotograma anterior.
    // 'clear' para Mac, 'cls' para Windows.
    system("clear || cls");

    // Recorremos el tablero fila por fila, desde la parte superior hasta la inferior.
    for (int i = 0; i < ALTO; i++) {
        
        // - PREPARAR LA (Capa de Fondo) ---
        // 'filaVisual' es nuestra copia temporal. Trabajamos sobre una copia
        // para no alterar los datos reales del tablero 't[i]'.
        board_t filaVisual = t[i];

        // - SUPERPONER LA PIEZA (Capa Activa) ---
        // Si existe una pieza activa ('p') y estamos en la fila donde debe estar ('py'),
        // dibujamos la pieza encima del tablero temporalmente.
        
        // "Si tengo una pieza cargada (p), Y ADEMÁS estoy dentro del rango vertical de la pieza:
        // i >= py && i < py + p->alto"
        if (p && i >= py && i < py + p->alto) {
            // Aplicamos la máscara: movemos la pieza a la columna horizontal (px)
            // y la fusionamos con el fondo usando OR ('|=').
            filaVisual |= (p->filas[i - py] << (ANCHO - p->ancho - px));
        }
        // - DIBUJAR LA FILA ---
        // Imprimimos el borde izquierdo del tablero.
        std::cout << "|";
        
        // Recorremos la fila de derecha a izquierda (desde el bit más significativo).
        for (int j = ANCHO - 1; j >= 0; j--) {
            
            // "Decodificador de bits":
            // Movemos el bit j hasta la posición 0 ('>> j') y comparamos con 1 ('& 1').
            // Si el resultado es 1, hay un bloque (#). Si es 0, hay un espacio vacío (.).
            if ((filaVisual >> j) & 1) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
        }
        
        // Imprimimos el borde derecho y saltamos a la siguiente línea.
        std::cout << "|\n";
    }
}
// --------------------------------------------------------------------------------------
/*
BLOQUE: Lógica de Control (Main Loop)
Esta función leva acabo la tarea de darle vida al juego: Configuración, Ejecución y Limpieza.
*/
int main() {
    // - CONFIGURACIÓN DEL ENTORNO: Validación de parámetros
    int anchoUser, altoUser;
    std::cout << "--- CONFIGURACION DINAMICA ---" << std::endl;
    std::cout << "Ancho (multiplo de 8, max 64): ";
    std::cin >> anchoUser;
    std::cout << "Alto (minimo 8): ";
    std::cin >> altoUser;

    // Filtro de seguridad: Evitamos estados inválidos del sistema.
    if (anchoUser < 8 || anchoUser % 8 != 0 || anchoUser > 64 || altoUser < 8) {
        std::cout << "Error: Configuración fuera de rango." << std::endl;
        return 1;
    }
    // - RESERVA DE MEMORIA: Asignación dinámica.
    // Usamos el Heap para que el tablero persista independientemente del tamaño elegido.
    board_t* tablero = new board_t[altoUser];
    for (int i = 0; i < altoUser; i++) tablero[i] = 0; // Inicialización del estado a vacío.

    bool jugando = true;
    while (jugando) {
        // - GENERACIÓN DE ENTIDAD: Nueva pieza para el turno actual.
        Pieza piezaActual = obtenerPiezaAleatoria();
        int px = (anchoUser / 2) - (piezaActual.ancho / 2);
        int py = 0;

        // Comprobación de fin de partida (Estado 'Game Over'):
        // Si al aparecer la pieza ya colisiona, el tablero está saturado.
        if (hayColision(tablero, altoUser, anchoUser, &piezaActual, px, py)) {
            renderizar(tablero, altoUser, anchoUser, nullptr, 0, 0);
            std::cout << "--- GAME OVER ---" << std::endl;
            break;
        }

        bool turnoPieza = true;
        while (turnoPieza) {
            // - CICLO DE DIBUJADO: Visualización del estado actual.
            renderizar(tablero, altoUser, anchoUser, &piezaActual, px, py);

            char accion;
            std::cout << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";
            std::cin >> accion;

            if (accion == 'q' || accion == 'Q') { jugando = false; break; }

            // - LÓGICA DE MOVIMIENTO (Transformaciones):
            // Creamos copias auxiliares para validar el movimiento 'antes' de aplicarlo.
            int n_px = px, n_py = py;
            Pieza p_aux = piezaActual;

            if (accion == 'a' || accion == 'A') n_px--;
            else if (accion == 'd' || accion == 'D') n_px++;
            else if (accion == 's' || accion == 'S') n_py++;
            else if (accion == 'w' || accion == 'W') rotarPieza(p_aux);

            // - VALIDACIÓN DE ESTADO (HayColision):
            // Si el movimiento es seguro, actualizamos las coordenadas globales.
            if (!hayColision(tablero, altoUser, anchoUser, &p_aux, n_px, n_py)) {
                px = n_px; py = n_py; piezaActual = p_aux;
            }
            // - CONSOLIDACIÓN DE ESTADO (Fijar y Limpiar):
            // Si el usuario intentó bajar pero chocó, la pieza se 'suelda' al tablero.
            else if (accion == 's' || accion == 'S') {
                fijarPieza(tablero, anchoUser, &piezaActual, px, py);
                limpiarFilas(tablero, altoUser, anchoUser); // Verificación de progreso.
                turnoPieza = false; // Finaliza el control de esta pieza.
            }
        }
    }

    // - LIBERACIÓN DE RECURSOS: Prevención de fugas de memoria.
    delete[] tablero;
    return 0;
}
// The End ------------------------------------------------------------------------------
