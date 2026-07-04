// =====================================================================================
// Universidad de Antioquia
// Facultad de Ingenieria - Departamento de Telecomunicaciones -
// @authors: Zahir Llerena
// email: zahir.llerena@udea.edu.co
// =====================================================================================

#include <iostream>
#include <string>

// ======================================================================================
// DEFINICION DE FUNCIONES (Ejercicios)
// ======================================================================================

void ejercicio_3_1() {
    /* ENUNCIADO ORIGINAL:
       Determinar la minima combinacion de billetes y monedas para una cantidad dada.
       Denominaciones: 50k, 20k, 10k, 5k, 2k, 1k (billetes) y 500, 200, 100, 50 (monedas).
       Si queda un residuo menor a $50, se reporta como "Faltante".
    */
    std::cout << "\n--- EJERCICIO 3.1: DESGLOSE DE EFECTIVO ---\n";

    int cantidad;
    std::cout << "Ingresa la cantidad de dinero: ";
    std::cin >> cantidad;

    // DEFINICION DEL ESPACIO MUESTRAL
    const int denominaciones[] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};

    int n = sizeof(denominaciones) / sizeof(denominaciones[0]);

    // PROCESO DE DESGLOSE
    for (int i = 0; i < n; i++) {
        int valor = denominaciones[i];

        // EVALUACION LOGICA: ¿El dinero alcanza para al menos uno de estos billetes?
        if (cantidad >= valor) {
            int conteo = cantidad / valor;
            std::cout << "$" << valor << " : " << conteo << "\n";
            cantidad %= valor;
        } else {
            std::cout << "$" << valor << " : 0\n";
        }
    }

    // SALIDA CUANTITATIVA FINAL
    std::cout << "---------------------------\n";
    std::cout << "Faltante (Residuo): $" << cantidad << "\n";
}

// ======================================================================================

void ejercicio_3_3() {
    /* ENUNCIADO ORIGINAL:
       Comparar dos cadenas. Si son iguales, retornar verdadero.
       Si son diferentes, identificar en que posiciones exactas coinciden los caracteres.
    */
    std::cout << "\n--- EJERCICIO 3.3: ANALISIS POSICIONAL DE CADENAS ---\n";

    std::string s1, s2;

    std::cout << "Ingresa la primera cadena: ";
    std::cin >> s1;

    std::cout << "Ingresa la segunda cadena: ";
    std::cin >> s2;

    // 1. EVALUACION DE IDENTIDAD
    if (s1 == s2) {
        std::cout << "Resultado: VERDADERO (Identidad absoluta detectada).\n";
        return;
    }

    // 2. ANALISIS DE DISPARIDAD
    std::cout << "Resultado: FALSO (Cadenas diferentes).\n";
    std::cout << "Revisando coincidencias...\n";

    int n = (s1.length() < s2.length()) ? s1.length() : s2.length();
    bool coincidencia_hallada = false;

    // 3. RECORRIDO VECTORIAL (Acceso por indice)
    for (int i = 0; i < n; i++) {
        if (s1[i] == s2[i]) {
            std::cout << " [+] Indice " << i << ": '" << s1[i] << "'\n";
            coincidencia_hallada = true;
        }
    }

    // 4. CIERRE LOGICO
    if (!coincidencia_hallada) {
        std::cout << " [!] Sin coincidencias posicionales.\n";
    }
}

// ======================================================================================

/* ENUNCIADO ORIGINAL: ejercicio_3_5
   Elabore una funcion que reciba un numero entero y por referencia retorne
   una cadena de caracteres que corresponda a dicho numero.
*/

void convertir_entero_a_cadena(int numero, std::string &resultado) {
    resultado = "";

    // CASO BASE
    if (numero == 0) {
        resultado = "0";
        return;
    }

    // GESTION DE LA MAGNITUD
    long n_temp = numero;
    bool es_negativo = false;

    if (n_temp < 0) {
        es_negativo = true;
        n_temp = -n_temp;
    }

    // 2. DESCOMPOSICION POR DIVISIONES SUCESIVAS
    while (n_temp > 0) {
        int digito = n_temp % 10;
        char caracter = (char)(digito + '0');

        // CONCATENACION PREFIJA
        resultado = caracter + resultado;
        n_temp /= 10;
    }

    // RESTAURACION DEL SIGNO
    if (es_negativo) {
        resultado = "-" + resultado;
    }
}

void ejercicio_3_5() {
    std::cout << "\n--- EJERCICIO 3.5: CONVERSION ESCALAR A CADENA ---\n";

    int valor;
    std::cout << "Ingresa un numero entero: ";

    // VALIDACION DE FLUJO
    if (!(std::cin >> valor)) {
        std::cout << "Error: Entrada no numerica.\n";
        return;
    }

    std::string texto;

    // LLAMADA POR REFERENCIA
    convertir_entero_a_cadena(valor, texto);

    // SALIDA FINAL
    std::cout << "Resultado: \"" << texto << "\"\n";
    std::cout << "Validacion: Magnitud de " << texto.length() << " caracteres.\n";
}

// ======================================================================================

void ejercicio_3_7() {
    /* ENUNCIADO ORIGINAL:
       Recibir una cadena y eliminar caracteres repetidos (bananas -> bans).
       Formato requerido: "Original: [X]. Sin repetidos: [Y]."
    */
    std::cout << "\n--- EJERCICIO 3.7: FILTRADO DE DUPLICADOS (CONJUNTOS) ---\n";

    std::string original;
    std::cout << "Ingresa una cadena de caracteres: ";
    std::cin >> original;

    std::string filtrada = "";

    // PROCESO DE FILTRADO (Busqueda Lineal Anidada)
    for (int i = 0; i < (int)original.length(); i++) {
        char actual = original[i];
        bool ya_existe = false;

        // BUSQUEDA DE PERTENENCIA (Bucle Interno)
        for (int j = 0; j < (int)filtrada.length(); j++) {
            if (filtrada[j] == actual) {
                ya_existe = true;
                break;
            }
        }

        // INSERCION CONDICIONAL
        if (!ya_existe) {
            filtrada += actual;
        }
    }

    // SALIDA CUANTITATIVA
    std::cout << "Original: " << original << ". Sin repetidos: " << filtrada << ".\n";
}

// ======================================================================================

void ejercicio_3_9() {
    /* ENUNCIADO ORIGINAL:
       Separar una cadena en grupos de N cifras, sumarlos e imprimir el resultado.
       Si la longitud no es multiplo de N, rellenar con ceros a la izquierda.
    */
    std::cout << "\n--- EJERCICIO 3.9: SEGMENTACION Y SUMA DE CIFRAS ---\n";

    int n_paso;
    std::string cadena;

    std::cout << "Ingresa el tamano del grupo (N): ";
    std::cin >> n_paso;

    std::cout << "Ingresa la cadena de caracteres numericos: ";
    std::cin >> cadena;

    // 1. ANALISIS DE CONGRUENCIA MODULAR
    int residuo = cadena.length() % n_paso;

    if (residuo != 0) {
        int ceros = n_paso - residuo;
        cadena.insert(0, ceros, '0');
    }

    // 2. PROCESO DE SEGMENTACION Y CONVERSION
    long long suma_total = 0;

    for (int i = 0; i < (int)cadena.length(); i += n_paso) {
        std::string segmento = cadena.substr(i, n_paso);
        suma_total += std::stoll(segmento);
    }

    // 3. SALIDA CUANTITATIVA
    std::cout << "Cadena procesada (con padding): " << cadena << "\n";
    std::cout << "Resultado de la suma: " << suma_total << "\n";
}

// ======================================================================================

void ejercicio_3_11() {
    /* ENUNCIADO ORIGINAL:
       Manejo de reservas en sala de cine (15 filas x 20 asientos).
       Filas identificadas de la A a la O y columnas del 1 al 20.
    */
    std::cout << "\n--- EJERCICIO 3.11: GESTION DE CINE ---\n";

    // 1. MEMORIA ESTATICA Y CARGA DE DATOS
    char sala[15][20];

    // INICIALIZACION LINEAL
    for (int i = 0; i < 300; i++) {
        ((char*)sala)[i] = '-';
    }

    // CARGA DE DATOS INICIALES
    int res_f[] = {0, 0, 0, 2, 5, 5, 5, 10, 10, 14, 1, 3, 7, 8, 12, 12, 6};
    int res_c[] = {0, 1, 2, 8, 5, 6, 7, 10, 11, 19, 2, 4, 15, 15, 0,  1,  9};

    for (int k = 0; k < 17; k++) {
        sala[res_f[k]][res_c[k]] = '+';
    }

    std::string cmd;

    // BUCLE DE INTERACCION
    while (true) {
        // 2. RENDERIZADO DE LA SALA
        std::cout << "\n     ";
        for (int j = 1; j <= 20; j++) {
            std::cout << (j < 10 ? "0" : "") << j << " ";
        }
        std::cout << "\n";

        for (int i = 0; i < 15; i++) {
            std::cout << (char)('A' + i) << "    ";
            for (int j = 0; j < 20; j++) {
                std::cout << sala[i][j] << "  ";
            }
            std::cout << "\n";
        }

        std::cout << "\nReserva (ej. A5) o 'Q' para salir: ";
        std::cin >> cmd;

        if (cmd[0] == 'Q' || cmd[0] == 'q') {
            break;
        }

        // 3. VALIDACION PRAGMATICA
        if (cmd.length() >= 2) {
            // NORMALIZACION DE FILA
            char f_char = (cmd[0] >= 'a') ? (char)(cmd[0] - 32) : cmd[0];
            int f = f_char - 'A';

            if (f < 0 || f >= 15) {
                std::cout << "-> ERROR: Fila invalida.\n";
                continue;
            }

            // CONVERSION MANUAL DE COLUMNA
            bool es_num = true;
            for (size_t k = 1; k < cmd.length(); k++) {
                if (cmd[k] < '0' || cmd[k] > '9') {
                    es_num = false;
                }
            }

            if (es_num) {
                int c = std::stoi(cmd.substr(1)) - 1;

                if (c >= 0 && c < 20) {
                    if (sala[f][c] == '-') {
                        sala[f][c] = '+';
                        std::cout << "-> EXITO: Asiento " << f_char << (c + 1) << " reservado.\n";
                    } else {
                        std::cout << "-> AVISO: Asiento ya ocupado.\n";
                    }
                } else {
                    std::cout << "-> ERROR: Columna fuera de rango.\n";
                }
            } else {
                std::cout << "-> ERROR: Formato de columna invalido.\n";
            }
        }
    }
}

// ======================================================================================

/* ENUNCIADO ORIGINAL:
   Se tiene una fotografia digitalizada de una porcion de la galaxia NGC 1300.
   Si (1/5)*(a_{i,j} + a_{i,j-1} + a_{i,j+1} + a_{i-1,j} + a_{i+1,j}) > 6
   representa una estrella. Ignore los bordes.
*/

int analizar_estrellas(int *matriz, int filas, int columnas) {
    int conteo_estrellas = 0;

    // FILTRO ESPACIAL (VECINDARIO DE VON NEUMANN)
    for (int i = 1; i < filas - 1; i++) {
        // PRE-CALCULO DE INDICES
        int fila_actual = i * columnas;
        int fila_arriba = (i - 1) * columnas;
        int fila_abajo  = (i + 1) * columnas;

        for (int j = 1; j < columnas - 1; j++) {
            // ARITMETICA DE PUNTEROS
            int suma = *(matriz + fila_actual + j)     +
                       *(matriz + fila_actual + (j-1)) +
                       *(matriz + fila_actual + (j+1)) +
                       *(matriz + fila_arriba + j)     +
                       *(matriz + fila_abajo  + j);

            // FILTRO DE UMBRAL (Suma > 30 equivalente algebraico de Promedio > 6)
            if (suma > 30) {
                conteo_estrellas++;
            }
        }
    }
    return conteo_estrellas;
}

void ejercicio_3_13() {
    std::cout << "\n--- EJERCICIO 3.13: ANALISIS NGC 1300 (VERSION LINEAL) ---\n";

    const int F = 6;
    const int C = 8;

    int imagen[F][C] = {
        {0, 3,  4, 0,  0, 0, 6,  8},
        {5, 13, 6, 0,  0, 0, 2,  3},
        {2, 6,  2, 7,  3, 0, 10, 0},
        {0, 0,  4, 15, 4, 1, 6,  0},
        {0, 0,  7, 12, 6, 9, 10, 4},
        {5, 0,  6, 10, 6, 4, 8,  0}
    };

    int total = analizar_estrellas(&imagen[0][0], F, C);

    std::cout << "Direccion base en RAM: " << &imagen[0][0] << "\n";
    std::cout << "-> Estrellas detectadas: " << total << "\n";
}

// ======================================================================================

void ejercicio_3_15() {
    /* ENUNCIADO ORIGINAL:
       Hallar la interseccion entre un par de rectangulos representados por {x, y, w, h}.
       Retornar un rectangulo C que corresponda a la interseccion.
    */
    std::cout << "\n--- EJERCICIO 3.15: COLISION DE RECTANGULOS (OPTIMIZADO) ---\n";

    int A[4], B[4];

    // 1. CAPTURA DE DATOS
    std::cout << "Rectangulo A (x y ancho alto): ";
    for (int i = 0; i < 4; i++) {
        std::cin >> A[i];
    }

    std::cout << "Rectangulo B (x y ancho alto): ";
    for (int i = 0; i < 4; i++) {
        std::cin >> B[i];
    }

    // 2. PRE-CALCULO DE LIMITES
    int der_A = A[0] + A[2], inf_A = A[1] + A[3];
    int der_B = B[0] + B[2], inf_B = B[1] + B[3];

    // 3. TEOREMA MIN-MAX PARA LA INTERSECCION
    int x_inter = (A[0] > B[0]) ? A[0] : B[0];
    int y_inter = (A[1] > B[1]) ? A[1] : B[1];

    int der_inter = (der_A < der_B) ? der_A : der_B;
    int inf_inter = (inf_A < inf_B) ? inf_A : inf_B;

    // 4. CALCULO DE MAGNITUDES RESULTANTES
    int w_inter = der_inter - x_inter;
    int h_inter = inf_inter - y_inter;

    // 5. VALIDACION Y SALIDA
    if (w_inter > 0 && h_inter > 0) {
        std::cout << "\n-> Interseccion: {"
                  << x_inter << ", " << y_inter << ", "
                  << w_inter << ", " << h_inter << "}\n";
    } else {
        std::cout << "\n-> Resultado: Los rectangulos no comparten area (Conjuntos disjuntos).\n";
    }
}

// ======================================================================================

/*
  1. FUNCIÓN MATEMÁTICA: SUMATORIA DE DIVISORES PROPIOS
*/
int calcular_suma_divisores(int n) {
    if (n <= 1) return 0;

    int suma = 1;

    // OPTIMIZACION O(sqrt(N))
    for (int i = 2; (i * i) <= n; i++) {
        if (n % i == 0) {
            suma += i;
            int conjugado = n / i;

            if (i != conjugado) {
                suma += conjugado;
            }
        }
    }
    return suma;
}

void ejercicio_3_17() {
    /* ENUNCIADO ORIGINAL:
       Dos numeros A y B son amigables si la suma de los divisores de A es igual a B,
       y al sumar los divisores de B el resultado es A.
    */
    std::cout << "\n--- EJERCICIO 3.17: SUMA DE NUMEROS AMIGABLES (OPTIMIZADO) ---\n";

    int N;
    std::cout << "Ingresa un numero limite (N): ";

    if (!(std::cin >> N)) return;

    int suma_total = 0;

    // 3. ANALISIS DEL DOMINIO [2, N-1]
    for (int a = 2; a < N; a++) {
        int b = calcular_suma_divisores(a);

        // PODA LOGICA
        if (b > a) {
            if (calcular_suma_divisores(b) == a) {
                suma_total += a;
                if (b < N) {
                    suma_total += b;
                }
            }
        }
    }

    // SALIDA FINAL
    std::cout << "Resultado de la sumatoria: " << suma_total << "\n";
    std::cout << "(Nota: Para N = 300, el resultado esperado es 504 [220 + 284])\n";
}

// ======================================================================================
// FUNCION PRINCIPAL (Punto de entrada)
// ======================================================================================

int main() {
    int opcion;

    std::cout << "==== MENU DE EJERCICIOS ====\n";
    std::cout << "1. Ejecutar Ejercicio 3.1 (Distribucion de dinero)\n";
    std::cout << "2. Ejecutar Ejercicio 3.3 (Comparacion de Arreglos de Char)\n";
    std::cout << "3. Ejecutar Ejercicio 3.5 (Conversion Int a String)\n";
    std::cout << "4. Ejecutar Ejercicio 3.7 (Filtro de Duplicados Base)\n";
    std::cout << "5. Ejecutar Ejercicio 3.9 (Suma de Segmentos)\n";
    std::cout << "6. Ejecutar Ejercicio 3.11 (Reserva cine)\n";
    std::cout << "7. Ejecutar Ejercicio 3.13 (Analisis astronomico)\n";
    std::cout << "8. Ejecutar Ejercicio 3.15 (Interseccion de rectangulos)\n";
    std::cout << "9. Ejecutar Ejercicio 3.17 (Suma de numeros amigables)\n";
    std::cout << "0. Salir\n";
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcion;

    if (opcion == 1) {
        ejercicio_3_1();
    }
    else if (opcion == 2) {
        ejercicio_3_3();
    }
    else if (opcion == 3) {
        ejercicio_3_5();
    }
    else if (opcion == 4) {
        ejercicio_3_7();
    }
    else if (opcion == 5) {
        ejercicio_3_9();
    }
    else if (opcion == 6) {
        ejercicio_3_11();
    }
    else if (opcion == 7) {
        ejercicio_3_13();
    }
    else if (opcion == 8) {
        ejercicio_3_15();
    }
    else if (opcion == 9) {
        ejercicio_3_17();
    }
    else if (opcion == 0) {
        std::cout << "Saliendo del programa...\n";
    }
    else {
        std::cout << "Opcion no valida.\n";
    }

    return 0;
}
