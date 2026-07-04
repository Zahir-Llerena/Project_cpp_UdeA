// =====================================================================================
// Universidad de Antioquia
// Facultad de Ingenieria - Departamento de Telecomunicaciones -
// @authors: Zahir Llerena
// email: zahir.llerena@udea.edu.co
// =====================================================================================

// Libreria principar a invocar:
#include <iostream>

// ======================================================================================
// DEFINICIÓN DE FUNCIONES (Ejercicios)
// Al definir las funciones antes del main(), el compilador ya conoce los
// elementos (variables, objetos y funciones) a invocar y permite ejecucion
// eficiente.
// ======================================================================================

// DEFINICIÓN DE LA FUNCIÓN
// 'void': Indica al compilador que esta subrutina ejecutará instrucciones
// pero NO retornará ningún valor numérico al finalizar (similar a un procedimiento).
// Las llaves { ... } delimitan el "ámbito" o vida de la función.
// Todo lo que nazca aquí { (variables, objetos y funciones), morirá al llegar
// a la llave de cierre }.

// ======================================================================================

void ejercicio_1_1() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite dos numeros A y B e imprima en pantalla el
    // residuo de la division A/B.
    // Por ejemplo, si se ingresan A = 8 y B = 3 se debe imprimir:
    // "El residuo de la division 8/3 es: 2"
    // ----------------------------------------------------------------------------------

    // 1. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.1 ---\n";

    // 2. DECLARACION DE VARIABLES (Gestion de Memoria)
    // A diferencia de Python (dinamico), C++ es de TIPADO ESTATICO.
    // Debemos decirle al sistema operativo QUE tipo de dato guardaremos antes de usarlo.
    // 'int': Reserva 4 bytes (32 bits) en la memoria RAM para numeros ENTEROS.
    int A;
    int B;

    // 3. INTERACCION CON EL USUARIO (Input)
    // Primero, enviamos un mensaje a la pantalla para guiar al usuario.
    std::cout << "Ingresa el primer numero (A): ";

    // 'std::cin': Significa "Entrada Estandar de Caracteres" (el teclado).
    // '>>': Operador de EXTRACCION. La flecha apunta a la variable.
    // "Extrae el dato DEL teclado y guardalo DENTRO de A".
    // El programa se pausa aqui esperando que el usuario presione Enter.
    std::cin >> A;

    std::cout << "Ingresa el segundo numero (B): ";
    std::cin >> B;

    // 4. PROCESAMIENTO MATEMATICO (ALU)
    // Declaramos una nueva variable 'residuo' de tipo entero.
    // El operador '%' (modulo) calcula lo que sobra de una division entera.
    // Ejemplo: 8 / 3 = 2, y sobran 2. Ese '2' es el modulo.
    int residuo = A % B;

    // 5. SALIDA CONCATENADA
    // En Python usamos f-strings (f"Texto {variable}").
    // En C++ "encadenamos" el flujo de salida usando multiples operadores '<<'.
    // Es como un tren de vagones: Texto -> Variable -> Texto -> Variable -> Fin.
    std::cout << "El residuo de la division " << A << "/" << B << " es: " << residuo << "\n";

} // FIN DE LA FUNCION: Aqui se libera la memoria de A, B y residuo automaticamente.

// ======================================================================================

void ejercicio_1_3() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite dos numeros A y B e imprima en pantalla el
    // mayor entre ellos.
    // Por ejemplo, si se ingresan 7 y 3 se debe imprimir: "El mayor es 7".
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.3 ---\n";

    // 1. DECLARACION Y ENTRADA DE DATOS
    // En C++, las variables son "cajas" de tamano fijo.
    // 'int' define que la caja solo aceptara numeros enteros.
    // C++ es de TIPADO ESTATICO. Debemos decirle al sistema operativo QUE tipo de dato
    // guardaremos antes de usarlo. 'int': Reserva 4 bytes (32 bits) en la memoria RAM
    // para numeros ENTEROS.
    // Es buena practica declarar las variables justo antes de usarlas o al inicio del bloque.
    int A;
    int B;

    // Interaccion Usuario-Maquina:
    // Flujo de Salida (<<): La maquina "habla" a la pantalla.
    std::cout << "Ingresa el primer numero (A): ";

    // Flujo de Entrada (>>): La maquina "escucha" del teclado y guarda en A.
    std::cin >> A;

    std::cout << "Ingresa el segundo numero (B): ";
    std::cin >> B;

    // 2. LOGICA CONDICIONAL (El Cerebro del Programa)
    // DIFERENCIA CLAVE CON PYTHON:
    // En Python usamos ':' y la indentacion (sangria) para agrupar codigo.
    // En C++, la condicion DEBE ir entre parentesis (...) y el bloque de codigo
    // que se ejecuta DEBE estar delimitado por llaves { ... }.

    if (A > B) {
        // Bloque VERDADERO para la primera condicion.
        // Solo entramos aqui si A es estrictamente mayor que B.
        // La indentacion aqui es visual (para nosotros), las llaves son obligatorias (para el compilador).
        std::cout << "El mayor es " << A << "\n";
    }
    else if (B > A) {
        // Bloque ALTERNATIVO CONDICIONAL.
        // OJO: En Python se escribe 'elif'. En C++ se escribe separado: 'else if'.
        // Si la primera fallo, evaluamos esta nueva pregunta.
        std::cout << "El mayor es " << B << "\n";
    }
    else {
        // Bloque POR DEFECTO (Default).
        // Si no fue A > B, y tampoco fue B > A, la unica opcion logica/matematica
        // que queda es que sean iguales.
        // No lleva condicion entre parentesis.
        std::cout << "Ambos numeros son iguales\n";
    }

} // Fin de la funcion. Las variables A y B se destruyen aqui para liberar RAM.

// ======================================================================================

void ejercicio_1_5() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite dos numeros A y B e imprima en pantalla la
    // division A/B con redondeo.
    // Por ejemplo, si se ingresan 8 y 3, se debe imprimir: 8/3 = 3 (porque es 2.66...)
    // Si se ingresan 7 y 3 se debe imprimir: 7/3 = 2 (porque es 2.33...)
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.5 ---\n";

    // 1. ENTRADA DE DATOS
    // C++ es de TIPADO ESTATICO. Debemos decirle al sistema operativo QUE tipo de dato
    // guardaremos antes de usarlo. 'int': Reserva 4 bytes (32 bits) en la memoria RAM
    // para numeros ENTEROS.
    // Declaramos variables enteras. El usuario ingresara numeros sin punto decimal.
    int A;
    int B;

    std::cout << "Ingresa el primer numero (A): ";
    std::cin >> A;

    std::cout << "Ingresa el segundo numero (B): ";
    std::cin >> B;

    // 2. PROCESAMIENTO: "Casting" y Aritmetica de Tipos
    // PROBLEMA: En C++, la division entre dos 'int' SIEMPRE devuelve un 'int'.
    // El compilador trunca (corta) los decimales. Ejemplo: 7/3 da 2, no 2.33.

    // SOLUCION (Casting): Anteponemos (float) a la variable A.
    // Esto le dice al procesador: "Trata temporalmente a A como si tuviera decimales".
    // Al dividir un float entre un int, el resultado se "promueve" a float automaticamente.
    float division_exacta = (float)A / B;

    // 3. ARTIFICIO MATEMATICO DE REDONDEO
    // Python tiene la funcion round(). En C++ base, para no cargar la libreria <cmath>,
    // aplicamos una tecnica de ingenieria clasica para numeros positivos:
    // Sumamos 0.5 al valor original.

    // CASO A (Redondear hacia arriba): 2.6 + 0.5 = 3.1. Al volverlo entero (int), queda 3.
    // CASO B (Redondear hacia abajo):  2.3 + 0.5 = 2.8. Al volverlo entero (int), queda 2.

    // (int)(...) fuerza la conversion del resultado final de vuelta a entero,
    // eliminando la parte decimal sobrante.
    int resultado = (int)(division_exacta + 0.5);

    // 4. SALIDA
    std::cout << "El resultado redondeado de " << A << "/" << B << " es: " << resultado << "\n";

} // Fin de la funcion.


// ======================================================================================

void ejercicio_1_7() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite un numero N e imprima en pantalla la suma de
    // todos los numeros entre 0 y N, incluyendo N.
    // Por ejemplo, si se ingresa 5: (1 + 2 + 3 + 4 + 5 = 15), se debe imprimir:
    // "La sumatoria desde 0 hasta 5 es: 15"
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.7 ---\n";

    // 1. ENTRADA DE DATOS
    // C++ es de TIPADO ESTATICO. Debemos decirle al sistema operativo QUE tipo de dato
    // guardaremos antes de usarlo. 'int': Reserva 4 bytes (32 bits) en la memoria RAM
    // para numeros ENTEROS.
    // Declaramos la variable N (limite superior).
    // Recuerde: En C++, si no inicializamos una variable, esta contiene "basura"
    // de la memoria RAM hasta que le asignemos un valor.
    int N;

    std::cout << "Ingresa un numero (N): ";
    std::cin >> N;

    // 2. PATRON DE ACUMULACION (El "Balde Vacio")
    // Declaramos una variable para ir guardando la suma progresiva.
    // ES CRITICO inicializarla en 0. Si no lo hacemos, C++ podria sumar
    // sobre un valor aleatorio de memoria preexistente.
    int suma_total = 0;

    // 3. PROCESO: EL CICLO 'FOR' (La Maquina de 3 Pasos)
    // DIFERENCIA CLAVE CON PYTHON:
    // Python: for x in range(N + 1):  <-- Oculta la mecanica interna.
    // C++: Nos exige definir manualmente el control del ciclo en 3 partes separadas por ';':

    // Parte A (Inicializacion): int numero = 0  -> Arranca el contador.
    // Parte B (Condicion):      numero <= N     -> Mientras esto sea VERDAD, repite.
    // Parte C (Actualizacion):  numero++ -> Al terminar la vuelta, incrementa 1.

    // Nota: 'numero++' es una abreviatura de alta eficiencia para 'numero = numero + 1'.

    for (int numero = 0; numero <= N; numero++) {

        // CUERPO DEL CICLO:
        // En cada vuelta, tomamos el valor actual de 'numero' y ingresa al ciclo para ser
        // sumado con suma_total.
        // suma_total acumula el valor anterior + el nuevo numero.
        suma_total = suma_total + numero;

        // (Aqui termina la vuelta, el programa salta a la Parte C: numero++,
        //  luego verifica la Parte B, y si cumple, entra de nuevo).
    }

    // 4. SALIDA
    // Al romperse la condicion (cuando numero sea N + 1), el flujo continua aqui.
    std::cout << "La sumatoria desde 0 hasta " << N << " es: " << suma_total << "\n";

} // Fin de la funcion.


// ======================================================================================

void ejercicio_1_9() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite un numero N (radio) e imprima en pantalla el
    // perimetro y el area de un circulo. Use 3.1416 como aproximacion de PI.
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.9 ---\n";

    // 1. ENTRADA DE DATOS (Tipos de Punto Flotante)
    // En fisica y geometria, las medidas no suelen ser enteros perfectos.
    // 'float': Reserva 4 bytes para guardar numeros con decimales (precision simple).
    // Nota: Existe 'double' (8 bytes), pero para este ejercicio 'float' es mas
    // eficiente en memoria.
    float N;

    std::cout << "Ingresa el radio del circulo (N): ";
    std::cin >> N;

    // 2. DEFINICION DE CONSTANTES (Inmutabilidad)
    // DIFERENCIA CLAVE CON PYTHON:
    // Python: PI = 3.1416 (Es una variable, podria cambiar por error mas adelante).
    // C++: 'const' convierte la variable en SOLO LECTURA.
    // Si intentamos hacer 'PI = 4;' mas adelante, el compilador lanzara un ERROR y no
    // dejara crear el programa.

    // El sufijo 'f' (3.1416f) es una buena practica de ingenieria: le confirma al
    // compilador que ese numero es un 'float' y no un 'double', evitando conversiones
    // innecesarias.
    const float PI = 3.1416f;

    // 3. PROCESAMIENTO (Optimizacion Aritmetica)

    // CALCULO DEL PERIMETRO: Formula P = 2 * pi * r
    // C++ respeta la jerarquia de operaciones matematicas estandar.
    float perimetro = 2 * PI * N;

    // CALCULO DEL AREA: Formula A = pi * r^2
    // En Python usariamos: area = PI * (N ** 2)
    // En C++, la potencia requiere la libreria externa <cmath> (funcion pow).
    // SOLUCION DE INGENIERIA: Multiplicar N * N es mas rapido para el procesador
    // que llamar a una funcion compleja de potencias.
    // Es una solucion "nativa" y eficiente.
    float area = PI * (N * N);

    // 4. SALIDA DE RESULTADOS
    // Imprimimos las variables calculadas.
    std::cout << "Perimetro: " << perimetro << "\n";
    std::cout << "Area: " << area << "\n";

} // Fin de la funcion.


// ======================================================================================

void ejercicio_1_11() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite un numero N e imprima en pantalla
    // su tabla de multiplicar hasta 10 x N.
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.11 ---\n";

    // 1. ENTRADA DE DATOS
    // C++ es de TIPADO ESTATICO. Debemos decirle al sistema operativo QUE tipo de dato
    // guardaremos antes de usarlo. 'int': Reserva 4 bytes (32 bits) en la memoria RAM
    // para numeros ENTEROS.
    // Declaramos la variable 'N' que servira como la base de la tabla.
    int N;

    std::cout << "Ingresa un numero para calcular su tabla (N): ";
    std::cin >> N;

    // 2. CICLO FOR (Control de Intervalos)
    // DIFERENCIA CLAVE CON PYTHON:
    // Python: range(1, 11). El '11' nunca se toca (intervalo semi-abierto [1, 11) ).
    // C++: Nosotros escribimos la CONDICION LOGICA de parada manualmente.
    // 'iterador <= 10' significa que el 10 SI se incluye (intervalo cerrado [1, 10]).

    // Desglose del ciclo:
    // A) int iterador = 1;  -> Nace la variable contadora en 1.
    // B) iterador <= 10;    -> Pregunta: "¿Sigo dentro del rango?".
    // C) iterador++;        -> Incremento: "Suma 1 al terminar la vuelta".
    //    iterador++ -> iterador = iterador + 1

    for (int iterador = 1; iterador <= 10; iterador++) {

        // 3. AMBITO DE VARIABLES (Scope / Vida de la variable)
        // Declaramos 'resultado' DENTRO de las llaves del for.
        // EFICIENCIA DE MEMORIA:
        // Esta variable "nace" al inicio de la vuelta y "muere" (se borra de RAM)
        // al llegar a la llave de cierre '}'.
        // En Python, las variables del ciclo suelen "fugarse" y seguir existiendo fuera.
        // En C++, esta variable es PRIVADA de este bloque.
        int resultado = iterador * N;

        // 4. SALIDA FORMATEADA
        // Construimos la frase visualmente uniendo pedazos de texto y numeros.
        // iterador (int) -> "x" (texto) -> N (int) -> " = " (texto) -> resultado (int)
        std::cout << iterador << "x" << N << " = " << resultado << "\n";

    } // Aqui muere 'resultado'. En la siguiente vuelta, se crea una nueva y limpia.

} // Fin de la funcion.


// ======================================================================================

void ejercicio_1_13() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite un numero N e imprima todos los divisores de N.
    // Por ejemplo, si se ingresa 4 se debe imprimir: "1, 2, 4"
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.13 ---\n";

    // 1. ENTRADA DE DATOS
    // C++ es de TIPADO ESTATICO. Debemos decirle al sistema operativo QUE tipo de dato
    // guardaremos antes de usarlo. 'int': Reserva 4 bytes (32 bits) en la memoria RAM
    // para numeros ENTEROS.
    // Declaramos la variable N. 'int' es suficiente para teoria de numeros basica.
    int N;

    std::cout << "Ingresa un numero (N): ";
    std::cin >> N;

    // 2. SALIDA PREVIA
    // Imprimimos el encabezado antes de entrar al ciclo de calculo.
    std::cout << "Los divisores de " << N << " son:\n";

    // 3. PROCESO: BARRIDO SECUENCIAL (Fuerza Bruta)
    // El objetivo es probar TODOS los numeros enteros desde 1 hasta N.
    // Python: for candidato in range(1, N + 1):
    // C++:    for (int candidato = 1; candidato <= N; candidato++)

    // Configuración del Ciclo:
    // A) Inicio: candidato = 1 (Porque dividir por 0 es ilegal matematicamente).
    // B) Fin:    candidato <= N (Incluimos al mismo numero, pues todo numero es divisible por si mismo).
    // C) Paso:   candidato++ (Probamos de uno en uno).

    for (int candidato = 1; candidato <= N; candidato++) {

        // 4. FILTRO DE DIVISIBILIDAD (Bloque Anidado)
        // Dentro de cada vuelta del ciclo, hacemos una pregunta logica.
        // Operador Modulo (%): Devuelve el residuo de la division.
        // Si (N % candidato == 0) significa que la division es exacta (sin decimales).

        if (N % candidato == 0) {

            // Si la condicion es VERDADERA, entramos a este sub-bloque.
            // Imprimimos el candidato porque demostró ser un divisor.
            std::cout << candidato << "\n";
        }

        // Si la condicion es FALSA, el programa ignora el 'cout' y salta aqui.
        // Luego, sube al 'candidato++' para probar el siguiente numero.
    }

} // Fin de la funcion.


// ======================================================================================

void ejercicio_1_15() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite al usuario que ingrese numeros.
    // Una vez se ingrese el numero cero (0), se debe imprimir la suma total.
    // El 0 funciona como "Centinela" (señal de parada).
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.15 ---\n";

    // 1. INICIALIZACION DEL ACUMULADOR
    // Es vital que empiece en 0. Si no lo inicializamos, sumaria sobre "basura" de la RAM.
    int suma_total = 0;

    // 2. LECTURA DE PREPARACION ("Priming Read")
    // Declaramos la variable 'numero' para almacenar temporalmente cada entrada.
    // C++ es de TIPADO ESTATICO. Debemos decirle al sistema operativo QUE tipo de dato
    // guardaremos antes de usarlo. 'int': Reserva 4 bytes (32 bits) en la memoria RAM
    // para numeros ENTEROS.
    int numero;

    // Antes de entrar al ciclo, debemos pedir el dato por PRIMERA vez.
    // Esto es necesario para que la condicion del 'while' tenga algo que evaluar.
    std::cout << "Ingresa un numero (0 para terminar): ";
    std::cin >> numero;

    // 3. CICLO 'WHILE' (Iteracion Indefinida)
    // DIFERENCIA CLAVE CON 'FOR':
    // El 'for' se usa cuando sabemos que vamos por ejemplo de 1 a 10, definidos los limites!.
    // El 'while' se usa cuando dependemos del usuario (podria ingresar 1 numero o 1000).

    // Condicion Logica: (numero != 0)
    // "!=" significa DISTINTO DE. Mientras el numero NO sea cero, el ciclo continua.

    while (numero != 0) {

        // A) ACUMULACION:
        // Sumamos el numero actual a nuestra bolsa total.
        suma_total = suma_total + numero;

        // B) ACTUALIZACION DE LA VARIABLE DE CONTROL
        // --- PUNTO CRITICO DE INGENIERIA ---
        // Debemos volver a pedir el dato DENTRO del ciclo.
        // Si olvidamos estas lineas, la variable 'numero' nunca cambiaria,
        // la condicion (numero != 0) seria siempre VERDADERA, y creariamos
        // un BUCLE INFINITO que colgaria el programa.

        std::cout << "Ingresa un numero (0 para terminar): ";
        std::cin >> numero;

        // El programa regresa arriba a evaluar el 'while' con el nuevo valor.
    }

    // 4. SALIDA
    // El flujo solo llega aqui cuando el usuario ingresa 0 y el ciclo se rompe.
    std::cout << "El resultado de la sumatoria es: " << suma_total << "\n";

} // Fin de la funcion.


// ======================================================================================

void ejercicio_1_17() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite al usuario ingresar varios numeros.
    // Una vez se ingrese el cero (0), se debe imprimir el MAYOR de todos.
    // El 0 es el centinela (fin) y no cuenta como dato a comparar.
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.17 ---\n";

    // 1. LECTURA INICIAL (Priming Read)
    // Necesitamos el primer numero ANTES de entrar al ciclo por dos razones:
    // a) Para evaluar si entramos al while (si es 0, no entramos).
    // b) Para establecer el "record" inicial.
    int numero;

    std::cout << "Ingresa un numero (0 para terminar): ";
    std::cin >> numero;

    // 2. INICIALIZACION DEL ESTADO (Punto Critico de Ingenieria)
    // ERROR COMUN: Hacer 'int mayor = 0;'.
    // ¿Por que esta mal? Si ingresamos: -5, -8, -2, 0... el mayor seria -2.
    // Si hubieramos puesto 'mayor = 0', el programa diria 0 (falso, el 0 no estaba en la lista).

    // SOLUCION CORRECTA: Asumimos que el PRIMER numero leido es el mayor provisional.
    // Al asignar 'mayor = numero', establecemos la base de comparación con el primer dato real.
    // Matematicamente, en un conjunto de un solo elemento, ese elemento es el maximo.
    int mayor = numero;

    // 3. CICLO CONDICIONAL (While)
    // Mientras el numero ingresado no sea el centinela (0)...
    while (numero != 0) {

        // A) EVALUACION (El Retador)
        // Comparamos el 'valor actual' (mayor) con el 'retador' (numero).
        // Si el retador es mas grande, toma el titulo.
        if (numero > mayor) {
            mayor = numero; // Actualizacion de memoria (Sobreescritura).
        }

        // B) ACTUALIZACION DEL FLUJO
        // Solicitamos el SIGUIENTE numero.
        // Sin esta línea, el valor de 'numero' nunca cambiaría y tendríamos un "Bucle Infinito".
        // Importante: Esto debe ir al final del ciclo.
        // Al leer aqui, el ciclo vuelve arriba y evalua si este nuevo numero es 0.
        std::cout << "Ingresa un numero (0 para terminar): ";
        std::cin >> numero;

    } // El flujo regresa al 'while' para la evaluación lógica.

    // 4. SALIDA
    // Si el primer numero fue 0, el bucle nunca corrio y 'mayor' es 0.
    // Si hubo datos, 'mayor' contiene el maximo encontrado.

    // Condicion de borde visual: Si el usuario ingreso 0 de inmediato.
    if (mayor == 0) {
        std::cout << "No se ingresaron datos validos para comparar.\n";
    } else {
        std::cout << "El numero mayor fue: " << mayor << "\n";
    }

} // Fin de la funcion.


// ======================================================================================

void ejercicio_1_19() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite un numero N e imprima si es o no un numero primo.
    // Ejemplo: 7 -> "7 es un numero primo."
    // Ejemplo: 8 -> "8 NO es un numero primo."
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.19 ---\n";

    // 1. ENTRADA DE DATOS
    // C++ es de TIPADO ESTATICO. Debemos decirle al sistema operativo QUE tipo de dato
    // guardaremos antes de usarlo. 'int': Reserva 4 bytes (32 bits) en la memoria RAM
    // para numeros ENTEROS.
    int N;
    std::cout << "Ingresa un numero (N): ";
    std::cin >> N;

    // 2. ESTADO INICIAL (Variable de Bandera / Flag)
    // DIFERENCIA CLAVE CON PYTHON:
    // Python: usa 'True' y 'False' (Capitalizados).
    // C++:    usa 'true' y 'false' (Minu sculas estrictas).
    // El tipo de dato es 'bool' (ocupa 1 byte usualmente).

    // HIPOTESIS: "Inocente hasta demostrar lo contrario".
    // Asumimos que el numero SI es primo. Si encontramos un divisor, bajamos esta bandera.
    bool es_primo = true;

    // 3. PROCESO DE VERIFICACION (Fuerza Bruta)
    // Definicion Matematica: Un primo solo es divisible por 1 y por si mismo.
    // Por tanto, buscamos divisores en el rango intermedio [2, N-1].

    // Configuracion del Ciclo:
    // Inicio: 2 (Primer divisor posible).
    // Fin:    candidato < N (ESTRICTAMENTE MENOR).
    //         Si pusieramos <= N, N se dividiria por si mismo y diria que no es primo (error).

    for (int candidato = 2; candidato < N; candidato++) {

        // Validacion de Divisibilidad:
        // Si el residuo es 0, significa que N es divisible por 'candidato'.
        if (N % candidato == 0) {

            // Si entra aqui, nuestra hipotesis original era falsa.
            // Cambiamos el estado de la variable booleana.
            es_primo = false;

            // NOTA DE EFICIENCIA DE INGENIERIA:
            // En un entorno real, aqui agregariamos la instruccion 'break;'.
            // ¿Por que? Si probamos el numero 1,000,000 y vemos que es divisible por 2,
            // ya sabemos que no es primo. No hace falta probar el 3, 4, 5... hasta el 999,999.
            // Por simplicidad pedagogica actual, dejamos que el ciclo termine solo.
        }
    }

    // 4. EVALUACION FINAL Y SALIDA
    // Una vez terminado el interrogatorio (ciclo), vemos como quedo la bandera.

    // Lógica Compuesta:
    // a) (es_primo == true): Que no hayamos encontrado divisores.
    // b) (N > 1): El numero 1 NO se considera primo por definicion matematica.
    //             El ciclo for (2 a 1) no corre, asi que 'es_primo' seguiria true sin esta correccion.

    // DIFERENCIA DE SINTAXIS:
    // Python: if es_primo and N > 1:
    // C++:    El operador 'and' se escribe como doble ampersand '&&'.

    if (es_primo == true && N > 1) {
        std::cout << N << " es un numero primo.\n";
    } else {
        std::cout << N << " NO es un numero primo.\n";
    }

} // Fin de la funcion.

// ======================================================================================

void ejercicio_1_21() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite un caracter C.
    // Si es una letra, invierta su caso (Mayuscula <-> Minuscula) e imprimala.
    // Ejemplo: 'B' -> 'b', 'k' -> 'K'.
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.21 ---\n";

    // 1. ENTRADA DE DATOS (El Tipo 'char')
    // DIFERENCIA CRITICA DE SINTAXIS:
    // En C++, las comillas SIMPLES ('A') se usan para un solo caracter (char).
    // Las comillas DOBLES ("A") se usan para texto (string). NO son intercambiables.

    // 'char': Reserva 1 byte (8 bits) en memoria.
    // Internamente, la computadora guarda un numero del 0 al 255 (Codigo ASCII).
    char C;

    std::cout << "Ingresa una letra (C): ";
    std::cin >> C;

    // 2. EVALUACION LOGICA (Matematica de Conjuntos)
    // Como 'C' es un numero en el fondo, podemos usar operadores de comparacion (>=, <=).
    // 'A' vale 65, 'Z' vale 90.
    // 'a' vale 97, 'z' vale 122.

    // Rango Mayusculas: [65, 90]
    bool es_mayuscula = (C >= 'A' && C <= 'Z');

    // Rango Minusculas: [97, 122]
    bool es_minuscula = (C >= 'a' && C <= 'z');

    // CONDICIONAL COMPUESTA (OR):
    // Usamos el operador "||" (doble barra vertical) que significa "O".
    // "Si es mayuscula O es minuscula, entonces es una letra valida".

    if (es_mayuscula || es_minuscula) {

        char convertida;

        // 3. PROCESO DE TRANSFORMACION (Aritmetica ASCII)
        // La distancia entre una mayuscula y su minuscula en ASCII es siempre 32.
        // Diferencia: 'a' (97) - 'A' (65) = 32.

        if (es_mayuscula) {
            // Si el usuario ingresa una mayúscula, estamos en el rango bajo (65-90).
            // Para llegar a su versión minúscula, debemos "bajar" en la tabla.
            // Matemáticamente, sumamos la distancia que las separa.

            // De Mayuscula a Minuscula: SUMAMOS 32 para "bajar" en la tabla.
            // (char) + (int) = (int). Al guardarlo en 'convertida' (char),
            // C++ lo traduce de nuevo a letra automaticamente.
            convertida = C + 32;
        }
        else {
            // Si el usuario ingresa una minúscula, estamos en el rango alto (97-122).
            // Para obtener la versión "superior" o mayúscula, debemos "subir" en la
            // tabla restando esa misma distancia:
            // De Minuscula a Mayuscula: RESTAMOS 32 para "subir" en la tabla.
            convertida = C - 32;
        }

        // 4. SALIDA
        std::cout << "Letra convertida: " << convertida << "\n";

    } else {
        // RUTA DE ERROR (Validacion de Entrada)
        // Si el usuario ingresa '5', '@' o un espacio, entra aqui.
        std::cout << "Error: El caracter ingresado no es una letra del alfabeto.\n";
    }

} // Fin de la funcion.

// ======================================================================================

void ejercicio_1_23() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que pida dos numeros A y B e imprima el MCM.
    // Ejemplo: 4 y 6 -> "El MCM de 4 y 6 es: 12"
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.23 ---\n";

    // 1. ENTRADA DE DATOS
    // C++ es de TIPADO ESTATICO. Debemos decirle al sistema operativo QUE tipo de dato
    // guardaremos antes de usarlo. 'int': Reserva 4 bytes (32 bits) en la memoria RAM
    // para numeros ENTEROS.
    int A;
    int B;

    std::cout << "Ingresa el primer numero (A): ";
    std::cin >> A;

    std::cout << "Ingresa el segundo numero (B): ";
    std::cin >> B;

    // 2. OPTIMIZACION MATEMATICA (Punto de Partida)
    // El MCM de dos numeros NUNCA puede ser menor que el mas grande de los dos.
    // Por lo tanto, empezar a buscar desde 1 seria un desperdicio de ciclos de CPU.
    // Empezamos la busqueda desde el mayor (MAX).

    int mayor;

    // Estructura condicional para hallar el maximo.
    if (A > B) {
        mayor = A;
    } else {
        mayor = B;
    }

    // Inicializamos nuestra variable 'candidato' (mcm) en ese maximo.
    int mcm = mayor;

    // 3. CICLO DE BUSQUEDA (Fuerza Bruta)
    // Buscamos el primer numero que satisfaga AMBAS divisibilidades.
    // Por tanto, el ciclo debe CONTINUAR mientras FALTE alguna de las dos.

    // LOGICA DE DE MORGAN:
    // Queremos detenernos cuando: (mcm % A == 0) AND (mcm % B == 0).
    // Por tanto, debemos continuar mientras: (mcm % A != 0) OR (mcm % B != 0).

    // DIFERENCIA DE SINTAXIS:
    // Python: while ... or ...
    // C++:    El operador 'O' es la doble barra vertical '||'.

    while ((mcm % A != 0) || (mcm % B != 0)) {

        // Si entramos aqui, es porque el numero actual fallo al menos una prueba.
        // Incrementamos en 1 para probar el siguiente entero.
        // mcm = mcm + 1;  <-- Forma clasica.
        mcm++;          // <-- Forma idiomatica de C++ (mas elegante).

    } // El ciclo se repite hasta que ambas condiciones sean falsas
      // (es decir, ambas divisibilidades sean verdaderas).

    // 4. SALIDA
    // El flujo solo llega aqui cuando encontramos el numero magico.
    std::cout << "El MCM de " << A << " y " << B << " es: " << mcm << "\n";

} // Fin de la funcion.


// ======================================================================================

void ejercicio_1_25() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite un numero N e imprima la cantidad de digitos.
    // Ejemplo: 1234 -> "1234 tiene 4 digitos."
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.25 ---\n";

    // 1. ENTRADA DE DATOS
    // C++ es de TIPADO ESTATICO. Debemos decirle al sistema operativo QUE tipo de dato
    // guardaremos antes de usarlo. 'int': Reserva 4 bytes (32 bits) en la memoria RAM
    // para numeros ENTEROS.
    int N;
    std::cout << "Ingresa un numero (N): ";
    std::cin >> N;

    // 2. PRESERVACION DE DATOS (Copia de Seguridad)
    // CRITICO: Vamos a usar un algoritmo de "descomposicion destructiva".
    // Si usaramos 'N' directamente en el ciclo, al final N valdria 0.
    // Por eso creamos 'temp' (temporal) para trabajar, dejando 'N' intacto para el mensaje final.
    int temp = N;

    // 3. VALOR ABSOLUTO (Manual)
    // Python: abs(N).
    // C++ Base: Implementamos la logica matematica. Si es negativo, lo multiplicamos por -1.
    // Esto asegura que el conteo funcione igual para -1234 que para 1234.
    if (temp < 0) {
        temp = -temp;
    }

    // Inicializamos el contador.
    int cantidad_digitos = 0;

    // 4. PROCESO: ALGORITMO DE DESCOMPOSICION DECADICA

    // CASO BORDE (El Cero):
    // Matematicamente, el 0 es un caso especial. El ciclo while(temp > 0) no correria para 0.
    // Por definicion, decimos que tiene 1 digito.
    if (temp == 0) {
        cantidad_digitos = 1;
    }
    else {
        // CICLO WHILE (Mientras quede numero por procesar)
        // Logica: "Cortar" el ultimo digito una y otra vez hasta que no quede nada.

        while (temp > 0) {

            // A) Contamos el digito actual.
            cantidad_digitos = cantidad_digitos + 1; // O: cantidad_digitos++;

            // B) CORTAMOS EL ULTIMO DIGITO (Division Entera)
            // DIFERENCIA CLAVE CON PYTHON:
            // Python: temp / 10 da decimales (123.4). Se requiere temp // 10.
            // C++:    Entre enteros ('int'), la division (/) SIEMPRE trunca los decimales.
            //         1234 / 10 = 123.
            //         123  / 10 = 12.
            //         1    / 10 = 0 (Aqui se rompe el ciclo).

            temp = temp / 10;
        }
    }

    // 5. SALIDA
    // Gracias a que usamos 'temp', la variable 'N' sigue valiendo lo que ingreso el usuario.
    std::cout << N << " tiene " << cantidad_digitos << " digitos.\n";

} // Fin de la funcion.

// ======================================================================================

void ejercicio_1_27() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que actue como una calculadora simple (+, -, *, /).
    // El usuario ingresa operandos y operador.
    // Ejemplo: 3, +, 5 -> "3 + 5 = 8"
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.27 ---\n";

    // 1. ENTRADA DE DATOS (Mezcla de Tipos)
    // 'float': Reserva 4 bytes para guardar numeros con decimales (precision simple).
    // Nota: Existe 'double' (8 bytes), pero para este ejercicio 'float' es mas
    // eficiente en memoria.
    // Usamos 'float' porque una calculadora debe soportar decimales (Ej: 2.5 * 4).
    float A;
    float B;

    // DIFERENCIA CRITICA DE SINTAXIS:
    // 'char': Variable de 1 byte para UN solo simbolo.
    // Usamos comillas SIMPLES ('+') para inicializar o comparar caracteres.
    // Las comillas DOBLES ("+") son para texto (string), y no caben en un 'char'.
    char operacion;

    std::cout << "Ingresa el primer numero: ";
    std::cin >> A;

    std::cout << "Ingresa la operacion (+, -, *, /): ";
    // El flujo 'cin' leera el siguiente caracter visible, ignorando espacios en blanco previos.
    std::cin >> operacion;

    std::cout << "Ingresa el segundo numero: ";
    std::cin >> B;

    // 2. LOGICA DE SELECCION MULTIPLE (La Escalera If-Else-If)
    // Evaluamos el caracter ingresado contra constantes literales ('+').
    // Nota: Es importante comparar usando == (igualdad) y no = (asignacion).

    float resultado;

    // CASO SUMA
    if (operacion == '+') {
        resultado = A + B;
        std::cout << A << " + " << B << " = " << resultado << "\n";
    }
    // CASO RESTA (Si no fue suma, preguntamos si es resta)
    else if (operacion == '-') {
        resultado = A - B;
        std::cout << A << " - " << B << " = " << resultado << "\n";
    }
    // CASO MULTIPLICACION
    else if (operacion == '*') {
        resultado = A * B;
        std::cout << A << " * " << B << " = " << resultado << "\n";
    }
    // CASO DIVISION (Requiere Validacion Adicional)
    else if (operacion == '/') {

        // VALIDACION DE INGENIERIA (Division por Cero):
        // Antes de calcular, verificamos si el denominador B es 0.
        // En Python esto lanzaria una excepcion (ZeroDivisionError).
        // En C++, dividir float por 0 puede dar 'inf' (infinito) o 'nan' (not a number),
        // pero es mejor practica controlarlo manualmente.

        if (B == 0) {
            std::cout << "Error analitico: La division por cero no esta definida.\n";
        }
        else {
            // Solo dividimos si es seguro.
            resultado = A / B;
            std::cout << A << " / " << B << " = " << resultado << "\n";
        }
    }
    // CASO POR DEFECTO (Error de Capa 8 / Usuario)
    else {
        // Si llegamos aqui, el usuario ingreso algo invalido (ej: '%', '$', 'k').
        std::cout << "Error logico: Operador '" << operacion << "' no reconocido.\n";
    }

} // Fin de la funcion.


// ======================================================================================

void ejercicio_1_29() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que adivine un numero secreto (entre 0 y 100).
    // El usuario da pistas: '>' (Tu numero es muy grande), '<' (Tu numero es muy peuqeño).
    // El programa tiene maximo 7 intentos (Logica de Busqueda Binaria).
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 1.29 (Busqueda Binaria) ---\n";

    // 1. INICIALIZACION DEL ESPACIO DE BUSQUEDA
    // Definimos los limites del intervalo matematico [0, 100].
    int limite_inferior = 0;
    int limite_superior = 100;

    // Contador de iteraciones.
    // Teoria de la Informacion: Para un rango de 100, log2(100) = 6.64.
    // Por eso, 7 intentos son matematicamente suficientes para garantizar el exito.
    int intento_actual = 1;

    // Bandera logica (Flag) para controlar si ganamos antes de tiempo.
    bool acertado = false;

    // Instrucciones para el usuario (Interfaz Humana)
    std::cout << "Piensa en un numero entre 0 y 100.\n";
    std::cout << "OJO con la regla:\n";
    std::cout << " Escribe '>' si MI numero (maquina) es MAYOR que el tuyo.\n";
    std::cout << " Escribe '<' si MI numero (maquina) es MENOR que el tuyo.\n";
    std::cout << " Escribe '=' si acerte.\n";
    std::cout << "----------------------------------------\n";

    // 2. CICLO DE CONVERGENCIA (While)
    // El algoritmo se ejecuta mientras tengamos intentos disponibles (<= 7).
    while (intento_actual <= 7) {

        // --- DEFENSA DE INTEGRIDAD (Defensive Programming) ---
        // Si el usuario miente en las pistas, los limites pueden cruzarse (min > max).
        // Esto es matematicamente imposible. Detectamos la contradiccion y abortamos.
        if (limite_inferior > limite_superior) {
            std::cout << "Error logico: Las pistas se contradicen. El numero ha desaparecido del rango.\n";
            break; // Salimos del ciclo de emergencia.
        }

        // 3. CALCULO DEL PIVOTE (La Mitad)
        // La estrategia optima es siempre dividir el problema por la mitad.
        // En C++, la division entera (/) trunca los decimales automaticamente.
        // Ejemplo: (0 + 100) / 2 = 50.
        int B = (limite_inferior + limite_superior) / 2;

        // Interaccion: Mostramos nuestra "adivinanza" (B).
        char respuesta;
        std::cout << "Intento " << intento_actual << ": Mi numero es " << B << ". Como es? (>, <, =): ";
        std::cin >> respuesta;

        // 4. EVALUACION Y REDUCCION DEL RANGO
        // Dependiendo de la pista, descartamos la mitad inservible del arreglo.

        if (respuesta == '=') {
            // CASO DE EXITO
            std::cout << "¡Exito! Adivine el numero " << B << ".\n";
            acertado = true;
            break; // Rompemos el ciclo inmediatamente.
        }
        else if (respuesta == '>') {
            // PISTA: "Tu numero es MAYOR que el mio".
            // Significado: El numero secreto esta ABAJO.
            // Accion: Movemos el techo (limite superior) justo debajo de nuestra apuesta.
            // El '-1' es CRITICO para evitar bucles infinitos.
            limite_superior = B - 1;

            // Solo gastamos un intento si la respuesta fue valida.
            intento_actual++;
        }
        else if (respuesta == '<') {
            // PISTA: "Tu numero es MENOR que el mio".
            // Significado: El numero secreto esta ARRIBA.
            // Accion: Movemos el piso (limite inferior) justo encima de nuestra apuesta.
            limite_inferior = B + 1;

            intento_actual++;
        }
        else {
            // CASO DE ERROR DE CAPA 8 (Usuario tecleo otra cosa)
            // No incrementamos 'intento_actual', le damos otra oportunidad de escribir bien.
            std::cout << "Simbolo invalido. Usa solo >, < o =.\n";
        }

    } // Fin del While

    // 5. SALIDA DE FRACASO
    // Si salimos del ciclo y la bandera 'acertado' sigue en falso...
    // Nota: (acertado == false) es equivalente a (!acertado).
    if (acertado == false && limite_inferior <= limite_superior) {
        std::cout << "Agote mis 7 intentos matematicos sin lograrlo. ¿Hiciste trampa?\n";
    }

} // Fin de la funcion.

// ======================================================================================
// Segundo bloque de ejericicios
// ======================================================================================

void ejercicio_2_1() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que identifique si un caracter es vocal, consonante o nada.
    // Ejemplo: '@' -> No es letra.
    // Ejemplo: 'a' -> Vocal.
    // Ejemplo: 'C' -> Consonante.
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 2.1 ---\n";

    // 1. ENTRADA DE DATOS
    // 'char': Variable de 1 byte.
    // Recordatorio: Las comillas simples (' ') son obligatorias para caracteres literales.
    char caracter;
    std::cout << "Ingresa un caracter: ";
    std::cin >> caracter;

    // 2. FILTRO PRIMARIO (¿Es una letra?)
    // Antes de preguntar si es vocal, debemos saber si siquiera es una letra.
    // Usamos el Algebra de Boole y los rangos ASCII numericos.

    // Rango [65, 90]
    bool es_mayuscula = (caracter >= 'A' && caracter <= 'Z');
    // Rango [97, 122]
    bool es_minuscula = (caracter >= 'a' && caracter <= 'z');

    // UNION DE CONJUNTOS (OR):
    // Si esta en el grupo de las mayusculas O en el de las minusculas, procedemos.
    if (es_mayuscula || es_minuscula) {

        // 3. NORMALIZACION DE DATOS (Tecnica de Ingenieria)
        // Para no tener que preguntar: ¿Es 'A' o 'a' o 'E' o 'e'...? (10 comparaciones),
        // creamos una variable temporal y convertimos todo a minusculas.
        // Asi solo haremos 5 comparaciones.

        char temp = caracter; // Copia de seguridad (No tocamos la variable original).

        if (es_mayuscula) {
            // Transformacion Lineal: Sumamos 32 para "movernos" a la zona de minusculas en ASCII.
            temp = temp + 32;
        }

        // 4. EVALUACION DEL SUBCONJUNTO (Vocales)
        // DIFERENCIA CRITICA CON PYTHON:
        // Python: if temp in ['a', 'e', 'i', 'o', 'u']:
        // C++:    NO existe el operador "in". Debemos comparar uno por uno.

        // ERROR COMUN DE PRINCIPIANTE: if (temp == 'a' || 'e' || 'i'...)
        // Eso es incorrecto porque 'e' se evalua como verdadero (distinto de 0).
        // Correcto: (temp == 'a') || (temp == 'e') ... Repetir la variable siempre.

        if (temp == 'a' || temp == 'e' || temp == 'i' || temp == 'o' || temp == 'u') {
            std::cout << caracter << " es una vocal\n";
        }
        else {
            // 5. LOGICA DE DESCARTE (Complemento)
            // Si sabemos que ES una letra (estamos dentro del primer if),
            // y sabemos que NO es vocal (fallo el if anterior),
            // por definicion axiomatica, TIENE que ser consonante.
            std::cout << caracter << " es una consonante\n";
        }

    } else {
        // El caracter cayo fuera de los rangos alfabeticos (ej: '@', '1', '#').
        std::cout << caracter << " no es una letra\n";
    }

} // Fin de la funcion.

// ======================================================================================

#include <string> // Necesario para usar variables de texto (strings) de forma sencilla

void ejercicio_2_3() {
    // ----------------------------------------------------------------------------------
    // 1. ENTRADA DE DATOS
    // Solicitamos dos numeros enteros al usuario. No sabemos aun cual es el dia y cual el mes.
    // ----------------------------------------------------------------------------------
    int N1, N2;
    std::cout << "\n--- Ejecutando Ejercicio 2.3 (Validacion de Fechas) ---\n";
    std::cout << "Ingresa el primer numero: ";
    std::cin >> N1;
    std::cout << "Ingresa el segundo numero: ";
    std::cin >> N2;

    std::cout << "\n--- Analisis de Datos Conjuntos ---\n";

    // ==============================================================================
    // PERMUTACION A: Asumimos que N1 es el MES y N2 es el DIA (Formato Mes/Dia)
    // ==============================================================================
    int mes_A = N1;
    int dia_A = N2;

    // Declaramos una variable de texto para guardar el veredicto.
    // "std::string" es como una palabra en Python: facil de leer y cambiar.
    // Por defecto, asumimos que la fecha no sirve (invalida).
    std::string estado_A = "invalida";

    // ARBOL DE DECISION:
    // Primero: ¿Es el mes un numero entre 1 y 12?
    if (mes_A >= 1 && mes_A <= 12) {

        // Si el mes es FEBRERO (2)
        if (mes_A == 2) {
            if (dia_A == 29) {
                estado_A = "valida en ano bisiesto";
            } else if (dia_A >= 1 && dia_A <= 28) {
                estado_A = "valida";
            }
        }
        // Si el mes tiene 30 dias (Abril, Junio, Septiembre, Noviembre)
        // El simbolo '||' significa "O". Basta que uno sea cierto.
        else if (mes_A == 4 || mes_A == 6 || mes_A == 9 || mes_A == 11) {
            if (dia_A >= 1 && dia_A <= 30) {
                estado_A = "valida";
            }
        }
        // Para todos los demas meses (que tienen 31 dias)
        else {
            if (dia_A >= 1 && dia_A <= 31) {
                estado_A = "valida";
            }
        }
    }
    // Mostramos el resultado de la primera interpretacion
    std::cout << mes_A << "/" << dia_A << " es una fecha (mes/dia) " << estado_A << ".\n";


    // ==============================================================================
    // PERMUTACION B: Asumimos que N2 es el MES y N1 es el DIA (Formato Dia/Mes)
    // ==============================================================================
    int mes_B = N2;
    int dia_B = N1;
    std::string estado_B = "invalida"; // Reiniciamos el estado para el nuevo analisis

    // Repetimos la misma logica pero con los numeros invertidos
    if (mes_B >= 1 && mes_B <= 12) {
        if (mes_B == 2) {
            if (dia_B == 29) {
                estado_B = "valida en ano bisiesto";
            } else if (dia_B >= 1 && dia_B <= 28) {
                estado_B = "valida";
            }
        }
        else if (mes_B == 4 || mes_B == 6 || mes_B == 9 || mes_B == 11) {
            if (dia_B >= 1 && dia_B <= 30) {
                estado_B = "valida";
            }
        }
        else {
            if (dia_B >= 1 && dia_B <= 31) {
                estado_B = "valida";
            }
        }
    }
    // Mostramos el resultado de la segunda interpretacion
    std::cout << dia_B << "/" << mes_B << " es una fecha (dia/mes) " << estado_B << ".\n";
}

// ======================================================================================

void ejercicio_2_5() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que reciba un numero impar (N) e imprima un patron de diamante.
    // Ejemplo (N = 7):
    // 1: *
    // 3: ***
    // 5: *****
    // 7: ******* (Centro)
    // 5: *****
    // 3: ***
    // 1: *
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 2.5 (Patrones y Ciclos Anidados) ---\n";

    // 1. ENTRADA DE DATOS
    int N;
    std::cout << "Ingresa un numero impar para el centro del patron (N): ";
    std::cin >> N;

    // 2. VALIDACION DE INTEGRIDAD (Filtro Par/Impar)
    // El patron es simetrico y requiere un centro unico. Los numeros pares no tienen centro entero.
    // Usamos el modulo (% 2). Si el residuo es 0, es par.
    if (N % 2 == 0) {
        std::cout << "Error logico: El patron simetrico requiere un numero impar.\n";
    }
    else {
        // 3. CONSTRUCCION GEOMETRICA (Algoritmo de Impresion)

        // DIFERENCIA CRITICA CON PYTHON:
        // Python: print("*" * 5)  <-- Operacion de alto nivel (String Multiplication).
        // C++: No podemos multiplicar texto. Debemos iterar.

        // --- FASE 1: CRECIENTE (Triangulo Superior + Centro) ---
        // Logica: 1, 3, 5... hasta N.
        // Control del Ciclo Externo (Filas):
        // Inicio: 1. Fin: N. Paso: Aumentar de 2 en 2 (i += 2).

        for (int i = 1; i <= N; i += 2) {

            // CICLO ANIDADO (Columnas / "Cabezal de Impresion"):
            // Este ciclo es el responsable de dibujar la linea horizontal.
            // Se repite 'i' veces. Si i=3, imprime 3 asteriscos uno al lado del otro.
            for (int j = 0; j < i; j++) {
                std::cout << "*";
                // Nota: 'cout' NO salta de linea automaticamente. El cursor sigue a la derecha.
            }

            // Una vez terminada la fila de asteriscos, ordenamos el salto de carro.
            std::cout << "\n";
        }

        // --- FASE 2: DECRECIENTE (Triangulo Inferior) ---
        // Logica: N-2, N-4... hasta 1.

        // Configuracion del Ciclo:
        // Inicio: N - 2. (Si N=7, empezamos en 5 para no repetir la fila central de 7).
        // Fin:    i > 0. (Debemos llegar hasta el 1).
        // Paso:   Disminuir de 2 en 2 (i -= 2).

        for (int i = N - 2; i > 0; i -= 2) {

            // Reutilizamos la logica de impresion horizontal.
            // Complejidad Computacional: O(N^2). Por cada fila, recorremos columnas.
            for (int j = 0; j < i; j++) {
                std::cout << "*";
            }
            // Cierre de la fila actual.
            std::cout << "\n";
        }
    }

} // Fin de la funcion.

// ======================================================================================

void ejercicio_2_7() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que solicite un numero N.
    // Sume los pares de la serie de Fibonacci menores a N.
    // Semilla inicial: 0, 1.
    // Ejemplo (N=10): Serie -> 0, 1, 1, 2, 3, 5, 8. Pares -> 0, 2, 8. Suma -> 10.
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estandar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCION. Imagina una flecha que empuja los datos hacia la salida.
    // "\n": Caracter de escape que genera un salto de linea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 2.7 (Fibonacci Pares) ---\n";

    // 1. ENTRADA DE DATOS
    // C++ es de TIPADO ESTATICO. Debemos decirle al sistema operativo QUE tipo de dato
    // guardaremos antes de usarlo. 'int': Reserva 4 bytes (32 bits) en la memoria RAM
    // para numeros ENTEROS.
    int N;

    std::cout << "Ingresa el limite superior estricto (N): ";
    std::cin >> N;

    // 2. ESTADO INICIAL (Semilla de la Sucesion)
    // Definimos los terminos t(0) y t(1).
    // 'a': Termino actual (Presente).
    // 'b': Termino siguiente (Futuro inmediato).
    int a = 0;
    int b = 1;

    // Acumulador para la suma de los numeros pares.
    // Importante: Inicializar en 0 para evitar "basura" de memoria.
    int suma_pares = 0;

    // 3. PROCESO ITERATIVO (Maquina de Estados)
    // Condicion: Mientras el termino actual 'a' no supere el techo 'N'.

    while (a < N) {

        // --- FILTRO DE PARIDAD ---
        // Evaluamos si el numero actual es par.
        // Matematicamente: Si a cong 0 (mod 2).
        if (a % 2 == 0) {
            suma_pares = suma_pares + a;
            // Nota de depuracion (opcional):
            // std::cout << "DEBUG: Sume el par " << a << "\n";
        }

        // --- GENERACION DEL SIGUIENTE TERMINO (La Transicion) ---
        // DIFERENCIA CRITICA CON PYTHON:
        // Python: a, b = b, a + b (Tuple Unpacking / Asignacion Paralela).
        // C++:    No existe la asignacion paralela nativa para tipos basicos.
        //         Si hacemos 'a = b' primero, perdemos el valor original de 'a'
        //         y no podriamos calcular 'a + b' correctamente despues.

        // SOLUCION DE INGENIERIA (Variable Temporal):
        // Calculamos el futuro y lo guardamos en una variable auxiliar 'siguiente'.
        // Declararla DENTRO del while es eficiente: nace y muere en cada vuelta.
        int siguiente = a + b;

        // --- DESPLAZAMIENTO DE LA VENTANA (Sliding Window) ---
        // Ahora que tenemos el futuro asegurado en 'siguiente', podemos mover los punteros.
        // 1. El futuro de hoy ('b') se convierte en el presente de manana ('a').
        a = b;

        // 2. El calculo nuevo ('siguiente') se convierte en el futuro de manana ('b').
        b = siguiente;

    } // El ciclo se repite con los valores actualizados.

    // 4. SALIDA
    std::cout << "El resultado de la suma es: " << suma_pares << "\n";

} // Fin de la funcion.

// ======================================================================================

void ejercicio_2_9() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Recibir un número N y sumar cada uno de sus dígitos elevados a sí mismos.
    // Ejemplo: 1223 -> (1^1) + (2^2) + (2^2) + (3^3) = 1 + 4 + 4 + 27 = 36.
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estándar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCIÓN. Empuja los datos hacia la salida.
    // "\n": Carácter de escape que genera un salto de línea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 2.9 (Suma de Potencias de Dígitos) ---\n";

    // 1. ENTRADA DE DATOS: Solicitamos la magnitud numérica.
    // 'int': Reserva espacio para un número entero (32 bits normalmente).
    // 'std::cin': Significa "Entrada Estándar" (el teclado).
    // '>>': Operador de EXTRACCIÓN. Toma lo que el usuario escribe y lo guarda en la variable.
    int N;
    std::cout << "Ingresa un numero (N): ";
    std::cin >> N;

    // 2. INICIALIZACIÓN DE ESTADOS Y COPIA DE SEGURIDAD:
    // Creamos 'temp' para "destruir" el número dígito a dígito sin perder el valor original N.
    int temp = N;

    // VALOR ABSOLUTO MANUAL:
    // Si el usuario ingresa un negativo (ej: -123), el signo '-' no es un dígito.
    // Multiplicamos por -1 para trabajar solo con la magnitud numérica.
    if (temp < 0) {
        temp = -temp;
    }

    // TIPO DE DATO 'LONG LONG' (64 BITS):
    // Razón de Ingeniería: Los números crecen muy rápido. 9 elevado a la 9 es ~387 millones.
    // Si sumamos varios dígitos así, un 'int' normal (límite 2 mil millones) podría
    // desbordarse (overflow). 'long long' nos da un rango casi infinito para este problema.
    long long suma_total = 0;

    // MANEJO DE LA SINGULARIDAD DEL CERO:
    // Matemáticamente, el 0 es un caso especial. En este contexto discreto, 0^0 se define como 1.
    if (temp == 0) {
        suma_total = 1;
    }
    else {
        // 3. PROCESO DE DESCOMPOSICION (Algoritmo de la División):
        // Mientras el número sea mayor a 0, significa que aún tiene dígitos por procesar.
        while (temp > 0) {

            // EXTRACCIÓN DEL DÍGITO (Operador Módulo %):
            // El residuo de dividir cualquier número entre 10 es SIEMPRE su último dígito.
            // Ejemplo: 1223 % 10 = 3.
            int digito = temp % 10;

            // CÁLCULO DE POTENCIA MANUAL (Dígito ^ Dígito):
            // No usamos 'pow()' de la librería <cmath> para evitar errores de precisión
            // con decimales (floats). Lo hacemos con un ciclo de multiplicación pura.
            long long potencia = 1; // Elemento neutro de la multiplicación.

            // Este ciclo multiplica la base 'digito' por sí misma tantas veces como diga el 'digito'.
            // Si el dígito es 3, el ciclo corre 3 veces: (1 * 3 * 3 * 3) = 27.
            for (int k = 0; k < digito; k++) {
                potencia = potencia * digito;
            }

            // ACUMULACIÓN: Sumamos el resultado parcial a nuestro gran total.
            suma_total = suma_total + potencia;

            // REDUCCIÓN DEL NÚMERO (División Entera /):
            // Al dividir un entero entre 10 en C++, se "mutila" el último dígito.
            // Ejemplo: 1223 / 10 = 122. (El 3 desaparece).
            // Esto permite que el ciclo 'while' tome el siguiente dígito en la próxima vuelta.
            temp = temp / 10;
        }
    }

    // 4. SALIDA: Imprimimos el resultado cuantitativo final.
    // Usamos el flujo de salida para mostrar el mensaje y el valor acumulado.
    std::cout << "El resultado de la suma de los digitos elevados a si mismos es: " << suma_total << "\n";
}

// ======================================================================================

void ejercicio_2_11() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que reciba un número N y calcule el Mínimo Común Múltiplo (MCM)
    // de todos los números enteros en el rango que va desde 1 hasta N.
    // Ejemplo: Si N = 4, el MCM de {1, 2, 3, 4} es 12.
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout': Significa "Salida Estándar de Caracteres" (la pantalla).
    // '<<': Operador de INSERCIÓN. Empuja los datos hacia la salida.
    // "\n": Carácter de escape que genera un salto de línea (Enter).
    std::cout << "\n--- Ejecutando Ejercicio 2.11 (MCM Acumulativo de 1 a N) ---\n";

    // 1. ENTRADA DE DATOS: Solicitamos la magnitud numérica.
    // 'int': Reserva espacio para un número entero (32 bits normalmente).
    // 'std::cin': Significa "Entrada Estándar" (el teclado).
    // '>>': Operador de EXTRACCIÓN. Toma lo que el usuario escribe y lo guarda en la variable.
    int N;
    std::cout << "Ingresa el limite superior (N): ";
    std::cin >> N;

    // 2. ESTADO INICIAL (El Acumulador)
    // El MCM es una operación multiplicativa; empezamos en 1 (elemento neutro).
    // CRÍTICO - GESTIÓN DE RANGO: Usamos 'long long' (64 bits).
    // Es necesario saber que el MCM de los números del 1 al 25 supera los 2 mil
    // millones. Un 'int' normal colapsaría (overflow), devolviendo resultados erróneos.

    long long mcm_acumulado = 1;

    // 3. PROCESO ITERATIVO (Estrategia de Barrido)
    // No podemos calcular el MCM de 10 números a la vez. Lo hacemos "pareja por pareja".
    // Nuevo_MCM = MCM( MCM_anterior, Numero_actual )

    // Validación: El proceso tiene sentido matemático si N es al menos 2.
    if (N >= 2) {
        // El ciclo 'for' actúa como un transportador que nos entrega los números uno a uno.
        for (int i = 2; i <= N; i++) {

            // --- FASE A: CÁLCULO DEL MCD (Algoritmo de Euclides) ---
            // Para hallar el MCM de forma eficiente, la ingeniería dicta que primero
            // necesitamos el Máximo Común Divisor (MCD).
            // Teorema: MCM(a, b) = (a * b) / MCD(a, b).

            // VARIABLES VOLÁTILES: Creamos copias de trabajo 'a' y 'b'.
            // Si usáramos 'mcm_acumulado' directamente en las divisiones del while,
            // destruiríamos el resultado que tanto nos costó calcular.
            long long a = mcm_acumulado;
            long long b = i;
            long long residuo;

            // EL MOTOR DE EUCLIDES:
            // Este ciclo es increíblemente rápido. En lugar de probar divisores del 1 al 100,
            // usa el residuo (%) para reducir los números en saltos gigantescos.
            // Se detiene cuando el divisor 'b' colapsa a 0.
            while (b != 0) {
                residuo = a % b; // Calculamos cuánto sobra de la división.
                a = b;           // El divisor pasa a ser el dividendo.
                b = residuo;     // El residuo se convierte en el nuevo divisor.
            }

            // Al terminar el while, la variable 'a' es el MCD absoluto de la pareja.
            long long mcd = a;

            // --- FASE B: ACTUALIZACIÓN DEL MCM ---
            // Aplicamos la fórmula para integrar el número 'i' al acumulado.
            // ORDEN DE OPERACIONES: Multiplicamos (mcm_acumulado * i) y luego dividimos.
            // En C++, la división entre enteros (/) trunca los decimales, lo cual es
            // perfecto aquí porque el MCD siempre es un divisor exacto.
            mcm_acumulado = (mcm_acumulado * i) / mcd;

        } // Fin del ciclo for. La ventana se desplaza al siguiente número.
    }

    // 4. SALIDA FINAL
    // Mostramos el resultado consolidado después de integrar todos los elementos de la serie.
    std::cout << "El minimo comun multiplo de 1 a " << N << " es: " << mcm_acumulado << "\n";

} // Fin de la función.

// ======================================================================================

void ejercicio_2_13() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Escriba un programa que reciba un número N y sume todos los números primos
    // que sean estrictamente menores que N.
    // Ejemplo: Si N = 10, los primos son {2, 3, 5, 7}. La suma es 17.
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout' es el canal de salida hacia la pantalla.
    // El operador '<<' actúa como un embudo que envía los mensajes al usuario.
    std::cout << "\n--- Ejecutando Ejercicio 2.13 (Suma de Primos Optimizada) ---\n";

    // 1. ENTRADA DE DATOS: Solicitamos la magnitud numérica.
    // 'int': Reserva espacio para un número entero (32 bits normalmente).
    // 'std::cin': Significa "Entrada Estándar" (el teclado).
    // '>>': Operador de EXTRACCIÓN. Toma lo que el usuario escribe y lo guarda en la variable.
    int N;
    std::cout << "Ingresa el limite superior (N): ";
    std::cin >> N;

    // 2. PREVISIÓN DE DESBORDAMIENTO (Eficiencia de Memoria)
    // Usamos 'long long' (64 bits) en lugar de 'int' (32 bits) para la suma.
    // Razón pedagógica: Los números primos crecen y se acumulan rápido; si N es grande,
    // el resultado superaría los 2 mil millones, rompiendo un 'int' normal (overflow).
    long long suma_primos = 0;

    // 3. CICLO EXTERNO: EL EXPLORADOR
    // Este ciclo 'for' revisa cada número entre 2 y N-1.
    // Lo llamamos "Explorador" porque selecciona el "Candidato" que vamos a evaluar.
    for (int candidato = 2; candidato < N; candidato++) {

        // HIPÓTESIS DE TRABAJO (La Bandera / Flag):
        // 'bool' solo puede ser verdadero (true) o falso (false).
        // Aplicamos "Presunción de Inocencia": asumimos que es primo hasta que se demuestre lo contrario.
        bool es_primo = true;

        // 4. CICLO INTERNO: EL INTERROGADOR (Filtro Optimizado)
        // Este ciclo busca si existe algún número que pueda dividir al 'candidato'.

        // --- OPTIMIZACIÓN ALGEBRAICA (Punto clave de Ingeniería) ---
        // No necesitamos probar todos los números hasta el candidato.
        // Si no hay divisores antes de la raíz cuadrada, NO los habrá después.
        // En lugar de usar la función sqrt(), usamos (divisor * divisor <= candidato).
        // Esto es mucho más rápido porque el procesador prefiere multiplicar que calcular raíces.

        for (int divisor = 2; divisor * divisor <= candidato; divisor++) {

            // VALIDACIÓN (Operador Módulo %):
            // Si el residuo es cero, significa que la división es exacta.
            // ¡Hemos encontrado un divisor! El candidato NO es primo.
            if (candidato % divisor == 0) {

                es_primo = false; // Bajamos la bandera: Hipótesis refutada.

                // INSTRUCCIÓN 'break' (Atajo de Eficiencia):
                // Si ya sabemos que 10 es divisible por 2, no perdemos tiempo
                // viendo si es divisible por 3, 4 o 5. Salimos del interrogatorio de inmediato.
                break;
            }
        }

        // 5. ACUMULACIÓN LÓGICA
        // Si después del interrogatorio la bandera 'es_primo' sigue siendo 'true',
        // el número pasó la prueba y se suma al tesoro acumulado.
        if (es_primo == true) {
            suma_primos = suma_primos + candidato;
        }

    } // El ciclo externo avanza al siguiente número candidato.

    // 6. SALIDA FINAL
    // Mostramos el resultado consolidado guardado en nuestra variable de alta capacidad.
    std::cout << "El resultado de la suma de primos es: " << suma_primos << "\n";

} // Fin de la función.

// ======================================================================================

void ejercicio_2_15() {
    // ----------------------------------------------------------------------------------
    // ENUNCIADO DEL PROBLEMA:
    // Generar una matriz de NxN en forma de espiral (Espiral de Ulam) desde el centro.
    // Posteriormente, sumar los elementos situados en ambas diagonales.
    // Ejemplo (N=3): El 1 inicia en el centro, se mueve a la derecha, gira, y así sucesivamente.
    // ----------------------------------------------------------------------------------

    // 0. INICIO DE LA RUTINA Y SALIDA DE TEXTO (Output)
    // 'std::cout' es el canal de salida hacia la pantalla.
    // El operador '<<' actúa como un embudo que envía los mensajes al usuario.
    std::cout << "\n--- Ejecutando Ejercicio 2.15 (Espiral de Ulam y Gestion de Memoria) ---\n";

    // 1. ENTRADA DE DATOS: Solicitamos la magnitud numérica.
    // 'int': Reserva espacio para un número entero (32 bits normalmente).
    // 'std::cin': Significa "Entrada Estándar" (el teclado).
    // '>>': Operador de EXTRACCIÓN. Toma lo que el usuario escribe y lo guarda en la variable.
    int N;
    std::cout << "Ingresa un numero impar (N): ";
    std::cin >> N;

    // REGLA GEOMÉTRICA: Para que exista un "corazón" o centro único, N debe ser impar.
    if (N % 2 == 0) {
        std::cout << "Error logico: La espiral requiere un centro geometrico exacto (N impar).\n";
        return; // Finaliza la ejecución de la función si el dato es inválido.
    }

    // 2. GESTIÓN DE MEMORIA DINÁMICA (El "Heap")
    // DIFERENCIA CRÍTICA CON PYTHON:
    // Python gestiona la memoria automáticamente. En C++, si el tamaño N se define en
    // tiempo de ejecución, debemos solicitar espacio manualmente al sistema operativo.

    // Paso A: Reservamos un "arreglo de punteros". Cada posición apuntará al inicio de una fila.
    int** matriz = new int*[N];

    // Paso B: Por cada fila, reservamos espacio físico para N columnas (enteros).
    for (int i = 0; i < N; i++) {
        matriz[i] = new int[N];
    }

    // 3. CONFIGURACIÓN DEL "CAMINANTE" (Lógica de Vectores)
    // Coordenadas iniciales: Situamos nuestro cursor en el centro exacto de la matriz.
    int x = N / 2;
    int y = N / 2;

    // VECTOR DE DIRECCIÓN (dx, dy): Define hacia dónde se desplaza el cursor.
    // Iniciamos con una magnitud de 1 hacia la derecha (dx=1, dy=0).
    int dx = 1;
    int dy = 0;

    // Variables de estado para el control de la trayectoria:
    int pasos_limite = 1;      // Distancia a recorrer antes de efectuar un giro.
    int pasos_actuales = 0;    // Contador de pasos realizados en el tramo actual.
    int cambios_direccion = 0; // Contador de giros realizados.
    int total_celdas = N * N;  // Límite superior de la espiral.

    // 4. ALGORITMO DE CONSTRUCCIÓN VECTORIAL
    //
    for (int i = 1; i <= total_celdas; i++) {

        // ESCRITURA: Asignamos el valor actual a la celda donde se encuentra el cursor.
        matriz[y][x] = i;

        // Condición de ruptura: Si alcanzamos el valor máximo, detenemos el proceso.
        if (i == total_celdas) break;

        // DESPLAZAMIENTO: Actualizamos la posición sumando el vector de dirección.
        x = x + dx;
        y = y + dy;
        pasos_actuales++;

        // ¿ES MOMENTO DE GIRAR? (Lógica de crecimiento de la espiral)
        if (pasos_actuales == pasos_limite) {
            pasos_actuales = 0;

            // ROTACIÓN DE 90 GRADOS (Álgebra Lineal):
            // Cambiamos el vector de dirección. La secuencia genera giros constantes.
            // Para girar en sentido antihorario: (dx, dy) -> (-dy, dx).
            int temp_dx = dx;
            dx = -dy;
            dy = temp_dx;

            cambios_direccion++;

            // CRECIMIENTO GEOMÉTRICO:
            // Observación: La longitud del tramo aumenta en 1 cada dos giros efectuados.
            // Patrón de pasos: 1, 1, 2, 2, 3, 3, 4, 4...
            if (cambios_direccion % 2 == 0) {
                pasos_limite++;
            }
        }
    }

    // 5. ANÁLISIS DE DIAGONALES Y SALIDA GRÁFICA
    int suma_diagonales = 0;
    std::cout << "\nMatriz generada (Identificando diagonales con '!'):\n";

    for (int f = 0; f < N; f++) {
        for (int c = 0; c < N; c++) {

            // IDENTIFICACIÓN DE PERTENENCIA A DIAGONALES:
            // Diagonal Principal: Los índices de fila y columna son idénticos (f == c).
            // Diagonal Secundaria: La suma de los índices es constante (f + c == N - 1).
            if (f == c || (f + c == N - 1)) {
                suma_diagonales += matriz[f][c];
                std::cout << matriz[f][c] << "!\t"; // Marcador visual para la diagonal.
            } else {
                std::cout << matriz[f][c] << "\t";  // '\t' asegura la alineación visual.
            }
        }
        std::cout << "\n"; // Salto de línea para la siguiente fila.
    }

    // 6. CIERRE Y RECOLECCIÓN DE RESIDUOS (Gestión de Memoria Responsable)
    // En C++, el programador es responsable de liberar la memoria usada con 'new'.
    // Si olvidamos este paso, el programa dejaría una "fuga de memoria" (Memory Leak).

    std::cout << "\nSuma consolidada de las diagonales: " << suma_diagonales << "\n";

    // Liberamos primero cada fila individual...
    for (int i = 0; i < N; i++) {
        delete[] matriz[i];
    }
    // ...y finalmente liberamos el contenedor de punteros.
    delete[] matriz;

} // Al finalizar, la memoria RAM es devuelta íntegramente al sistema.

// ======================================================================================
// FUNCIÓN PRINCIPAL (Punto de entrada)
// ======================================================================================

int main() {
    // Variable para almacenar la decisión del usuario
    int opcion;

    std::cout << "==== MENU DE EJERCICIOS ====\n";
    std::cout << "1. Ejecutar Ejercicio 1.1 (Residuo)\n";
    std::cout << "2. Ejecutar Ejercicio 1.3 (Numero mayor)\n";
    std::cout << "3. Ejecutar Ejercicio 1.5 (Division redondeada)\n";
    std::cout << "4. Ejecutar Ejercicio 1.7 (Suma de 0 a N)\n";
    std::cout << "5. Ejecutar Ejercicio 1.9 (Area y perimetro del circulo)\n";
    std::cout << "6. Ejecutar Ejercicio 1.11 (Tabla de multiplicar de N)\n";
    std::cout << "7. Ejecutar Ejercicio 1.13 (Divisores de N)\n";
    std::cout << "8. Ejecutar Ejercicio 1.15 (Suma de numero ingresados)\n";
    std::cout << "9. Ejecutar Ejercicio 1.17 (Mayor de todos los numeros ingresados)\n";
    std::cout << "10. Ejecutar Ejercicio 1.19 (Validar si un numero es primo)\n";
    std::cout << "11. Ejecutar Ejercicio 1.21 (Conversion de caracter)\n";
    std::cout << "12. Ejecutar Ejercicio 1.23 (MCM de dos numeros)\n";
    std::cout << "13. Ejecutar Ejercicio 1.25 (Cantidad de digitos de N)\n";
    std::cout << "14. Ejecutar Ejercicio 1.27 (Calculadora)\n";
    std::cout << "15. Ejecutar Ejercicio 1.29 (Que la maquina adivine un numero)\n";
    std::cout << "16. Ejecutar Ejercicio 2.1 (Identificacion de caracter)\n";
    std::cout << "17. Ejecutar Ejercicio 2.3 (Identificacion de fecha)\n";
    std::cout << "18. Ejecutar Ejercicio 2.5 (Triangulo de *)\n";
    std::cout << "19. Ejecutar Ejercicio 2.7 (Serie de Fibonacci)\n";
    std::cout << "20. Ejecutar Ejercicio 2.9 (Suma de N digitos con ciertas potencias)\n";
    std::cout << "21. Ejecutar Ejercicio 2.11 (MCM de 1,..., N)\n";
    std::cout << "22. Ejecutar Ejercicio 2.13 (Suma de primos en 1,..., N)\n";
    std::cout << "23. Ejecutar Ejercicio 2.15 (Matriz ded espital Ulam)\n";
    std::cout << "0. Salir\n";
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcion;

    // Estructura de control para invocar la función correspondiente
    if (opcion == 1) {
        ejercicio_1_1();
    }
    else if (opcion == 2) {
        ejercicio_1_3();
    }
    else if (opcion == 3) {
        ejercicio_1_5();
    }
    else if (opcion == 4) {
        ejercicio_1_7();
    }
    else if (opcion == 5) {
        ejercicio_1_9();
    }
    else if (opcion == 6) {
        ejercicio_1_11();
    }
    else if (opcion == 7) {
        ejercicio_1_13();
    }
    else if (opcion == 8) {
        ejercicio_1_15();
    }
    else if (opcion == 9) {
        ejercicio_1_17();
    }
    else if (opcion == 10) {
        ejercicio_1_19();
    }
    else if (opcion == 11) {
        ejercicio_1_21();
    }
    else if (opcion == 12) {
        ejercicio_1_23();
    }
    else if (opcion == 13) {
        ejercicio_1_25();
    }
    else if (opcion == 14) {
        ejercicio_1_27();
    }
    else if (opcion == 15) {
        ejercicio_1_29();
    }
    else if (opcion == 16) {
        ejercicio_2_1();
    }
    else if (opcion == 17) {
        ejercicio_2_3();
    }
    else if (opcion == 18) {
        ejercicio_2_5();
    }
    else if (opcion == 19) {
        ejercicio_2_7();
    }
    else if (opcion == 20) {
        ejercicio_2_9();
    }
    else if (opcion == 21) {
        ejercicio_2_11();
    }
    else if (opcion == 22) {
        ejercicio_2_13();
    }
    else if (opcion == 23) {
        ejercicio_2_15();
    }
    else if (opcion == 0) {
        std::cout << "Saliendo del programa...\n";
    }
    else {
        std::cout << "Opcion no valida.\n";
    }

    return 0;
}

// The end ==================================================================================

