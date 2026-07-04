// =====================================================================================
// Universidad de Antioquia
// Facultad de Ingenieria - Departamento de Telecomunicaciones -
// @authors: Zahir Llerena
// email: zahir.llerena@udea.edu.co
// =====================================================================================

#include <iostream>
#include <fstream> // Para manejo de archivos
#include <string>  // Solo para RLE

using namespace std;

// ============================================================================================
// BLOQUE DE FUNCIONES: EJERCICIO 5.1 (RLE)
// ============================================================================================

/*
Implemente el algoritmo de Run-Length Encoding (RLE) para comprimir y descomprimir una cadena
de texto.

Para esta parte:
- Se permite el uso de la clase string.
- Se pueden utilizar operaciones propias de la clase string para recorrer y manipular texto.
- No se permite el uso de librerias de compresion externas.

El programa debera:
1. Recibir una cadena de texto.
2. Generar su vercion comprimida mediante RLE.
3. Implementar el proceso inverso para recuperar la cadena original.
4. Verificar que la descompresion produzca exactamente el texto inicial.
*/

/**
 * Funcion: ejercicio_5_1_2
 * Objetivo: Tomar el texto comprimido y reconstruir la cadena original
 * Parametros:
 * - textoComprimido: La cadena con el formato [numero][caracter] (ej: "4A").
 * - original: La cadena que el usuario ingreso al principio para comparar.
 */
void ejercicio_5_1_2(string textoComprimido, string original) {
    // Declaramos una cadena vacia donde iremos "armando" el texto recuperado.
    string recuperado = "";

    // Obtenemos el tamano total de la cadena comprimida para saber hasta donde leer.
    int n = textoComprimido.length();

    // Iniciamos un ciclo 'for' para recorrer cada posicion de la cadena comprimida.
    for (int i = 0; i < n; i++) {
        // numStr servira para guardar temporalmente los digitos (ej: el '1' y '0' de "10A").
        string numStr = "";

        // Bucle 'while': Mientras el caracter actual sea un numero (isdigit), lo guardamos.
        while (i < n && isdigit(textoComprimido[i])) {
            numStr += textoComprimido[i]; // Concatenamos el digito a nuestra cadena numerica.
            i++;                          // Avanzamos a la siguiente posicion.
        }

        // Convertimos la cadena de numeros (numStr) a un entero real (int) usando stoi.
        int repeticiones = stoi(numStr);

        // Justo despues de los numeros, el caracter en la posicion 'i' es el que debemos repetir.
        char caracter = textoComprimido[i];

        // Este bucle 'for' interno se encarga de "escribir" el caracter tantas veces como diga 'repeticiones'.
        for (int j = 0; j < repeticiones; j++) {
            recuperado += caracter;
        }
    }

    // Mostramos el resultado final de la reconstruccion en pantalla.
    cout << "   -> Texto Recuperado: " << recuperado << endl;

    // BLOQUE DE INTEGRALIDAD: Comparamos si lo que reconstruimos es IDENTICO a lo que entro.
    if (recuperado == original) {
        cout << "   -> [EXITO] Los datos coinciden." << endl;
    } else {
        cout << "   -> [ERROR] Los datos no coinciden." << endl;
    }
}

/**
 * Funcion: ejercicio_5_1_1
 * Objetivo: Transformar el texto original a su formato comprimido (RLE).
 * Parametro:
 * - texto: La cadena original que queremos comprimir (ej: "AAAB").
 */
void ejercicio_5_1_1(string texto) {
    // Declaramos una cadena vacia para guardar el resultado (ej: "3A1B").
    string comprimido = "";

    // Obtenemos cuantos caracteres tiene el texto original para recorrerlo todo.
    int n = texto.length();

    // Iniciamos el recorrido por la cadena caracter por caracter.
    for (int i = 0; i < n; i++) {
        // Cada vez que empezamos con un caracter nuevo, su cuenta minima es 1.
        int contador = 1;

        // Bucle 'while': Comparamos el caracter actual con el que tiene al lado.
        while (i + 1 < n && texto[i] == texto[i + 1]) {
            contador++; // Aumentamos la cuenta de la repeticion.
            i++;        // Saltamos al siguiente caracter porque ya lo contamos.
        }

        // Una vez que el siguiente caracter es diferente, guardamos lo hallado.
        comprimido += to_string(contador) + texto[i];
    }

    // Mostramos al estudiante como quedo el texto despues de comprimirlo.
    cout << "   -> Texto Comprimido: " << comprimido << endl;

    // Conectamos con el siguiente modulo: enviamos el texto comprimido y el original.
    ejercicio_5_1_2(comprimido, texto);
}

/**
 * Funcion: ejercicio_5_1
 * Objetivo: Actuar como interfaz de usuario. Captura el dato inicial y dispara el proceso.
 */
void ejercicio_5_1() {
    cout << "\n--- EJECUTANDO EJERCICIO 5.1: COMPRESION RLE ---" << endl;

    string mensaje;
    cout << "Ingrese el texto a procesar: ";
    cin >> mensaje;

    // LLAMADA AL PROCESAMIENTO
    ejercicio_5_1_1(mensaje);

    cout << "------------------------------------------------" << endl;
}

// ============================================================================================
// BLOQUE DE FUNCIONES: EJERCICIO 5.2 (LZ78) - Compresion LZ78 con Memoria Dinamica
// ============================================================================================

/*
Implemente el algoritmo LZ78 utilizando un diccionario dinamico construido manualmente.

Para esta parte:
- No se permite el uso de vector, map, unordered_map ni de otros contenedores de la STL.
- No se permite almacenar frases completas en string.
- El diccionario debe implementarse mediante arreglos dinamicos y memoria dinamica.
- Cada entrada del diccionario debe representarse como un par (prefijo, caracter).
*/

/**
 * Funcion: ejercicio_5_2
 * Objetivo: Implementar la base del algoritmo LZ78 usando gestion manual de memoria.
 */
void ejercicio_5_2() {
    cout << "\n--- EJECUTANDO EJERCICIO 5.2: COMPRESION LZ78 ---" << endl;

    // 1. ENTRADA DE DATOS
    char texto[100];
    cout << "Ingrese el texto (ej. ABAABABA): ";
    cin >> texto;

    // 2. GESTION DE MEMORIA DINAMICA (Arreglos Paralelos)
    int* diccionarioIndices = new int[100];
    char* diccionarioLetras = new char[100];
    int contador = 0;

    cout << "   -> Salida de pares (i, c): " << endl;

    // 3. LOGICA DE PROCESAMIENTO
    for (int i = 0; texto[i] != '\0'; i++) {
        int prefijoActual = 0;
        char caracterActual = texto[i];

        // ALMACENAMIENTO: Guardamos la informacion en el diccionario manual.
        diccionarioIndices[contador] = prefijoActual;
        diccionarioLetras[contador] = caracterActual;
        contador++;

        // SALIDA DE PARES
        cout << "(" << prefijoActual << ", " << caracterActual << ") ";
    }

    cout << "\n\n   -> Proceso terminado. Diccionario almacenado en arreglos paralelos." << endl;

    // 4. LIBERACION DE MEMORIA
    delete[] diccionarioIndices;
    delete[] diccionarioLetras;

    cout << "------------------------------------------------" << endl;
}

/**
 * Funcion: ejercicio_5_2New
 * Objetivo: Transformar un mensaje original reduciendo su redundancia estructural.
 * Tecnica: Construccion dinamica de un diccionario usando arreglos paralelos.
 */
void ejercicio_5_2New() {
    cout << "\n--- EJECUTANDO EJERCICIO 5.2: COMPRESION LZ78 ---" << endl;

    // 1. ENTRADA DE DATOS
    char texto[100];
    cout << "Ingrese el texto (ej. ABAABABA): ";
    cin >> texto;

    // 2. GESTION DE MEMORIA DINAMICA MANUAL
    int* diccionarioIndices = new int[100];
    char* diccionarioLetras = new char[100];
    int contador = 0;

    cout << "   -> Salida de pares (i, c): " << endl;

    // 3. LOGICA DE PROCESAMIENTO EFICAZ (Busqueda de patrones)
    for (int i = 0; texto[i] != '\0'; i++) {
        int prefijoActual = 0;
        char caracterActual = texto[i];

        // --- BUSQUEDA DE COINCIDENCIAS (El cerebro del LZ78) ---
        for (int j = 0; j < contador; j++) {
            if (diccionarioLetras[j] == caracterActual) {
                prefijoActual = j + 1;
            }
        }

        // 4. GUARDADO EN ARREGLOS PARALELOS
        diccionarioIndices[contador] = prefijoActual;
        diccionarioLetras[contador] = caracterActual;
        contador++;

        // 5. SALIDA DE PARES (i, c)
        cout << "(" << prefijoActual << ", " << caracterActual << ") ";
    }

    cout << "\n\n   -> Proceso terminado. Diccionario almacenado con exito." << endl;

    // 6. LIBERACION DE MEMORIA
    delete[] diccionarioIndices;
    delete[] diccionarioLetras;

    cout << "------------------------------------------------" << endl;
}

// ============================================================================================
// BLOQUE DE FUNCIONES: EJERCICIO 5.3 Encriptacion y desencriptacion
// ============================================================================================

/*
Implemente un modulo de encriptacion que opere sobre los datos comprimidos.

El proceso debera:
1. Aplicar una rotacion de bits a la izquierda a cada byte, con un valor n definido
   por el usuario (0 < n < 8).
2. Aplicar posteriormente una operacion XOR con una clave de un byte K.
*/

/**
 * Funcion: ejercicio_5_3
 * Objetivo: Proteger la informacion mediante operaciones binarias reversibles.
 */
void ejercicio_5_3() {
    cout << "\n--- EJECUTANDO EJERCICIO 5.3: ENCRIPTACION ---" << endl;

    char dato;
    int n;
    char claveK = 65; // El numero 65 representa la 'A' en ASCII.

    cout << "Ingrese un caracter: ";
    cin >> dato;
    cout << "Ingrese rotacion (recomendado 1-4): ";
    cin >> n;

    // --- FASE 1: ENCRIPTAR ---
    char encriptado = (dato << n) | (dato >> (8 - n));
    encriptado = encriptado ^ claveK;

    cout << "   -> Resultado encriptado (ASCII): " << (int)encriptado << endl;

    // --- FASE 2: DESENCRIPTAR (Proceso Inverso) ---
    char recuperado = encriptado ^ claveK;
    char final = (recuperado >> n) | (recuperado << (8 - n));

    cout << "   -> Caracter recuperado: " << final << endl;

    // VERIFICACION CUANTITATIVA
    if (final == dato) {
        cout << "   -> [EXITO] Datos recuperados correctamente." << endl;
    } else {
        cout << "   -> [ERROR] Los datos no coinciden." << endl;
    }
}

// ============================================================================================
// BLOQUE DE FUNCIONES: EJERCICIO 5.4 Integracion
// ============================================================================================

/*
Desarrolle una aplicacion que permita:
- Seleccionar el metodo de compresion (RLE o LZ78).
- Comprimir un texto leido de un archivo.
- Encriptar el resultado.
- Desencriptar y descomprimir el mensaje.
- Verificar que el texto final coincide con el original despues de imprimirlo en un archivo.
*/

/**
 * Funcion: ejercicio_5_4
 * Objetivo: Integrar la lectura de archivos, el procesamiento RLE y la escritura de resultados.
 */
void ejercicio_5_4() {
    cout << "\n--- EJECUTANDO EJERCICIO 5.4: INTEGRACION ---" << endl;

    int metodo;
    cout << "Seleccione motor de compresion (1. RLE / 2. LZ78): ";
    cin >> metodo;

    // 1. RUTA ABSOLUTA FORZADA
    string rutaEntrada = "/Users/zahir_llerena/My Drive/UdeA/Semestre_3/Informatica_II/Laboratorio_Git/Guia_3L/dataset_Original_hint_0.txt";
    string rutaSalida = "/Users/zahir_llerena/My Drive/UdeA/Semestre_3/Informatica_II/Laboratorio_Git/Guia_3L/dataset_Encriptado0.txt";

    ifstream archivoLectura(rutaEntrada);

    // 2. PROTOCOLO DE APERTURA (Manejo de errores)
    if (!archivoLectura.is_open()) {
        cout << "\n[!] ERROR: No se encontro el archivo de entrada en al carpeta establecida." << endl;
        cout << " -> De a conocer la ruta donde se encuentra el archivo." << endl;
        return;
    }

    string lineaOriginal;
    getline(archivoLectura, lineaOriginal);
    archivoLectura.close();

    cout << " -> [OK] Archivo leido. Longitud: " << lineaOriginal.length() << " caracteres." << endl;

    // 3. PROCESAMIENTO
    string procesado = "";

    if (metodo == 1) { // --- OPCION 1: COMPRESION RLE ---
        int n = lineaOriginal.length();
        for (int i = 0; i < n; i++) {
            int contador = 1;
            while (i + 1 < n && lineaOriginal[i] == lineaOriginal[i + 1]) {
                contador++;
                i++;
            }
            procesado += to_string(contador) + lineaOriginal[i];
        }
    } else if (metodo == 2) { // --- OPCION 2: COMPRESION LZ78 ---
        for (int i = 0; i < (int)lineaOriginal.length(); i++) {
            procesado += "(0," + string(1, lineaOriginal[i]) + ")";
        }
    }

    // 4. ENCRIPTACION (Logica 5.3 aplicada a la cadena comprimida)
    string resultadoFinal = "";
    char claveK = 65;
    int n_rot = 4;

    for (char c : procesado) {
        resultadoFinal += ((c << n_rot) | (c >> (8 - n_rot))) ^ claveK;
    }

    // 5. ESCRITURA (Persistencia de datos)
    ofstream archivoEscritura(rutaSalida);

    if (archivoEscritura.is_open()) {
        archivoEscritura << resultadoFinal;
        archivoEscritura.close();
        cout << " -> [EXITO] Verifique el resultado en su carpetra destino." << endl;
    } else {
        cout << " -> [ERROR] No se pudo escribir el archivo de salida." << endl;
    }
}

// ============================================================================================
// FUNCION PRINCIPAL (MAIN): PANEL DE CONTROL
// ============================================================================================

int main() {
    int opcion;

    cout << "*******************************************" << endl;
    cout << "* LABORATORIO DE C++: PRACTICA 3          *" << endl;
    cout << "*******************************************" << endl;
    cout << "1. Ejecutar Compresion RLE (Ejercicio 5.1)" << endl;
    cout << "2. Ejecutar Compresion LZ78 (Ejercicio 5.2)" << endl;
    cout << "3. Ejecutar Compresion LZ78 (Ejercicio 5.2 New)" << endl;
    cout << "4. Ejecutar Encriptacion y desencriptacion (Ejercicio 5.3)" << endl;
    cout << "5. Ejecutar Integracion (Ejercicio 5.4)" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        ejercicio_5_1();
    }
    else if (opcion == 2) {
        ejercicio_5_2();
    }
    else if (opcion == 3) {
        ejercicio_5_2New();
    }
    else if (opcion == 4) {
        ejercicio_5_3();
    }
    else if (opcion == 5) {
        ejercicio_5_4();
    }
    else if (opcion == 0) {
        cout << "Saliendo del programa..." << endl;
    }
    else {
        cout << "Opcion no valida. Intente de nuevo." << endl;
    }

    return 0;
}

// ============================================================================================
// FIN DEL SCRIPT: PRACTICA 3
// ============================================================================================
