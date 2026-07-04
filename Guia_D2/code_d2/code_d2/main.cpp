/*
 =======================================================================================
 Universidad de Antioquia
 Facultad de Ingenieria - Departamento de Telecomunicaciones -
 PROYECTO: UdeAWorldCup 2026 - Motor de Simulación Matemática (Desafío II)
 @authors: Zahir Llerena
 email: zahir.llerena@udea.edu.co

 Objetivo: Comprender y aplicar Programación Orientada a Objetos (POO),
           gestión manual de memoria dinámica (punteros), flujos de archivos (I/O)
           y la implementación de modelos estadísticos (Poisson) en C++ puro.
 =======================================================================================
*/

// ========================================================================
// MÓDULO 0: LIBRERÍAS ESTÁNDAR (El "Maletín de Herramientas" de C++)
// ========================================================================
// La directiva #include le dice al compilador que traiga código preescrito de la biblioteca estándar.
#include <iostream>  // Input/Output Stream: Nos proporciona 'std::cout' para imprimir mensajes en la consola.
#include <fstream>   // File Stream: Nos permite crear canales de lectura (ifstream) y escritura (ofstream) archivos CSV.
#include <cmath>     // Funciones matemáticas de C. La usamos para 'std::pow' (elevar un número a una potencia).
#include <random>    // Librería moderna (C++11) para generar números aleatorios.
#include <cstdlib>   // C Standard Library: Contiene herramientas utilitarias como atoi() y atof() para convertir texto a números.
#include <string>    // Permite usar std::string, un objeto dinámico para manejar textos sin los riesgos de los char[].

// ========================================================================
// ETAPA 1: INFRAESTRUCTURA BASE DE C++ (Plantillas y Memoria Dinámica)
// ========================================================================

/*
"La Etapa 1 es mi gestor de almacenamiento dinámico. Implementé un template Lista<T>
 porque necesitaba una estructura capaz de crecer geométricamente.
 Utilicé punteros para gestionar la memoria en el Heap de manera manual, y apliqué los
 mecanismos de destructores para asegurar que no existan fugas de memoria, algo crítico
 para una simulación larga que procesa miles de registros."
 */

/*
 PLANTILLAS (TEMPLATES)
 Es un "molde" o plantilla. Le decimos al compilador: "Voy a crear una clase,
 pero el tipo de dato (T) se definirá más tarde". Esto nos permite usar la
 misma lógica para crear una Lista de enteros, de Equipos o de Registros.

'template <class T>' le dice a C++ que esta clase es un "molde genérico".
 La letra 'T' es un comodín. Más adelante, cuando escribamos Lista<Equipo>,
 el compilador reemplazará todas las 'T' por 'Equipo'. Esto nos ahorra escribir
 una clase diferente para cada tipo de dato.
*/

template <class T>
class Lista {
private:
    // VARIABLES ALMACENAMIENTO: Estas variables están protegidas. Nadie fuera de la clase puede alterarlas directamente.
    
    T* elementos;       // Puntero maestro: Almacena la dirección de memoria (RAM) donde empieza nuestro arreglo.
    int tamanoActual;   // Contador: Cuántos elementos reales hemos guardado hasta el momento.
    int capacidad;      // Límite: Cuántos "cajones" o "espacio" hemos reservado en total en la memoria.
    
    // Variables 'static': Son variables de CLASE, no de objeto.
    // Si creas 5 listas diferentes, TODAS comparten y suman a estas mismas dos variables.
    // Llevan la auditoría global del esfuerzo del procesador y la memoria consumida.
    static long long totalIteraciones;
    static size_t memoriaEnUso;

    /*
      GESTIÓN DE MEMORIA DINÁMICA
      Método redimensionar(): Se ejecuta automáticamente cuando el arreglo se llena.
      Pide más memoria al SO, muda los datos y destruye lo anterior.
      Este método es el corazón de la clase. Se llama automáticamente cuando el arreglo se llena.
    */
    // Un método privado que se activa solo cuando el arreglo está lleno.
    void redimensionar() {
        capacidad *= 2; // Multiplicamos por 2 la capacidad - Duplicamos la capacidad -.
        
        // 'new': Le pide al SO un nuevo bloque de memoria contiguo en el "Heap" con el nuevo tamaño.
        T* nuevoEspacio = new T[capacidad];
        
        // sizeof(T) nos dice cuántos bytes pesa nuestro dato. Lo sumamos a nuestra auditoría.
        memoriaEnUso += sizeof(T) * capacidad;
        
        // Mudanza: Copiamos los datos del arreglo viejo al nuevo, uno por uno.
        for (int i = 0; i < tamanoActual; i++) {
            nuevoEspacio[i] = elementos[i];
            totalIteraciones++; // Sumamos 1 a nuestro reporte de esfuerzo computacional.
        }
        
        // ¡PRECAUCIÓN! 'delete[]' destruye el arreglo viejo. Si olvidamos esto,
        // la memoria de la computadora se llenará de basura hasta colapsar (Memory Leak).
        delete[] elementos;
        
        // Finalmente, hacemos que nuestro puntero maestro apunte a la nueva casa.
        elementos = nuevoEspacio;
    }

public:
    // Constructor: Función que se ejecuta sola al nacer el objeto (Ej: Lista<int> misNumeros;)
    // Inicializa la lista pidiendo espacio para 5 elementos.
    Lista() : tamanoActual(0), capacidad(5) {
        elementos = new T[capacidad]; // Nace pidiendo 5 espacios en la RAM.
        memoriaEnUso += sizeof(T) * capacidad;
    }
    
    // Destructor: Función con la tilde (~). Se ejecuta sola cuando el objeto muere (al final del programa).
    ~Lista() {
        delete[] elementos; // Devuelve la memoria al sistema operativo.
    }

    // Método para insertar un dato al final del arreglo.
    void agregar(T objeto) {
        // Si ya no hay espacio, llama al arquitecto (funcion definida previamente) para hacer la casa más grande.
        if (tamanoActual == capacidad) redimensionar();
        
        // Guarda el objeto en la posición 'tamanoActual' y LUEGO suma 1 al tamaño (por el ++).
        elementos[tamanoActual++] = objeto;
        totalIteraciones++;
    }

    /*PASO POR REFERENCIA (&)
      El símbolo '&' significa que no devolvemos una COPIA del objeto (lo cual sería lento),
      sino el acceso directo a la dirección de memoria original.
      Si el usuario modifica lo que devuelve esta función, se modifica el original en la lista.
    */
    T& obtener(int indice) {
        totalIteraciones++;
        return elementos[indice];
    }

    // El 'const': "Este método solo leerá datos, no modificará nada de la clase".
    int getTamano() const { return tamanoActual; }

    // Función estática: Se puede llamar directamente sin crear un objeto (Lista<int>::mostrarAuditoria()).
    static void mostrarAuditoria() {
        std::cout << "\n============================================\n";
        std::cout << "|   REPORTE DE EFICIENCIA (AUDITORIA UdeA) |\n";
        std::cout << "============================================\n";
        std::cout << "-> Iteraciones de Memoria: " << totalIteraciones << "\n";
        std::cout << "-> Memoria Dinamica en uso: " << memoriaEnUso << " bytes\n";
        std::cout << "============================================\n\n";
    }
};

// En C++, las variables 'static' deben inicializarse explícitamente fuera de la clase.
template <class T> long long Lista<T>::totalIteraciones = 0;
template <class T> size_t Lista<T>::memoriaEnUso = 0;

// ========================================================================
// CLASES DE REGISTRO TÉCNICO (Cero Structs)
// ========================================================================
/*
  En C, se usaban 'structs' para empaquetar variables públicas. En C++ orientado a objetos,
  preferimos usar 'class' y asignar los valores a través de métodos (como 'configurar').
  Estas clases son simples "vehículos" de transporte de datos hacia los archivos.
*/
class RegistroPoisson {
// 'public' significa que cualquier parte del programa puede leer/escribir estas variables.
public:
    std::string local, visita;
    float lambdaL, lambdaV;
    int golesL, golesV;
    
    // Método para llenar todas las variables en un solo paso.
    void configurar(std::string l, std::string v, float la, float lb, int ga, int gb) {
        local = l; visita = v; lambdaL = la; lambdaV = lb; golesL = ga; golesV = gb;
    }
};

class RegistroHistorial {
public:
    std::string fase, id, local, visita, ganador;
    int golesL, golesV;
    
    void configurar(std::string f, std::string i, std::string l, std::string v, std::string gan, int gl, int gv) {
        fase = f; id = i; local = l; visita = v; ganador = gan; golesL = gl; golesV = gv;
    }
};

// ========================================================================
// ETAPA 2: ENTIDAD EQUIPO (Modelando el Dominio)
// ========================================================================
/* Una clase en POO es como un plano arquitectónico.
 Implementé una clase Equipo que encapsula tanto los datos estáticos (ranking, nombre)
 como los dinámicos (puntos, goles). Decidí utilizar arreglos de caracteres de tamaño
 fijo para garantizar una gestión de memoria predecible al leer el CSV, y apliqué
 lógica de encapsulamiento para que el objeto sea responsable de sus propios cálculos,
 asegurando que las reglas del torneo (como la suma de puntos o el cálculo de promedios)
 sean inmutables y consistentes en todo el sistema."
 */

class Equipo {

private:
    // ENCAPSULAMIENTO: Estas variables son "privadas". Solo los métodos de esta clase pueden tocarlas.
    // Usamos arreglos estáticos 'char[]' (arreglos de caracteres) porque vienen directamente del CSV como texto puro.
    // Esto es muy útil al leer datos crudos de matrices de texto (como lo haremos al leer el CSV).
    char rankingFIFA[50], pais[50], dt[50], fed[100], conf[20];
    char gf_historico[10], gc_historico[10], pg_h[10], pe_h[10], pp_h[10];
    
    // Variables dinámicas que irán cambiando a medida que se juega el Mundial.
    // Aquí guardamos los resultados de nuestra simulación.
    int puntos, golesFavor, golesContra, diferenciaGoles, pg, pe, pp, pesoJerarquia;
    std::string etapa; // El nivel alcanzado (ej. "Dieciseisavos").
    char grupoOrigen;  // Identificador del grupo (ej. 'A').

public:
    /* CONSTRUCTOR: Se ejecuta cuando creamos un objeto 'Equipo'.
      Inicializamos todo en cero para evitar "valores basura" (basura en memoria que puede causar errores).
      El peso inicial es 8 (Fase de Grupos), representando la fase inicial (Grupos).
      Mientras menor sea el número, mejor posición (1 = Campeón)
    */
    Equipo() : puntos(0), golesFavor(0), golesContra(0), diferenciaGoles(0), pg(0), pe(0), pp(0), pesoJerarquia(8), etapa("Fase de Grupos"), grupoOrigen('?') {
        pais[0] = '\0'; // '\0' es el Carácter Nulo. Le dice a C++ "aquí termina el texto". Así inicializamos el nombre vacío.
    }

    // Setters (Modificadores) y Getters (Lectores) clásicos de POO.
    // Son los "puertos" de acceso. Permiten leer o modificar variables privadas de forma segura.
    void setGrupo(char g) { grupoOrigen = g; }
    char getGrupo() const { return grupoOrigen; }
    int getPeso() const { return pesoJerarquia; }
    
    /* LÓGICA DE NEGOCIO:
      Solo actualizamos la etapa si el nuevo peso es menor (mejor) al actual.
      Esto asegura que si un equipo llega a Octavos (peso 6), no se sobreescriba accidentalmente por
      un dato erróneo de la fase de grupos (peso 8).
    */
    void setEtapaFinal(std::string e, int p) { if(p < pesoJerarquia) { etapa = e; pesoJerarquia = p; } }

    /*
      LECCIÓN: COMPARACIÓN DE C-STRINGS
      No podemos usar '==' para comparar dos arreglos de char (eso compararía sus direcciones de memoria).
      Debemos recorrer letra por letra hasta que una sea distinta, o hasta que lleguemos al final ('\0').
    */
    bool esIgualA(const char* nombreBuscado) {
        int i = 0;
        // Mientras no lleguemos al final de ninguna de las dos palabras ('\0')
        while (pais[i] != '\0' && nombreBuscado[i] != '\0') {
            if (pais[i] != nombreBuscado[i]) return false; // Letra distinta = falso.
            i++;
        }
        return (pais[i] == nombreBuscado[i]); // Retorna true si ambas terminaron en el mismo punto.
    }

    // Recibe una fila del CSV (dividida en 10 columnas) y la guarda en los atributos.
    // Traduce el arreglo 2D que viene del CSV a los atributos de la clase.
    void configurarDesdeArreglo(char datos[10][100]) {
        // Aquí creamos una Función Lambda (una mini función dentro de otra).
        // Su trabajo es copiar letras de un origen a un destino de forma segura.
        auto copiar = [](char* dest, const char* src, int limite) {
            int i = 0;
            while (src[i] != '\0' && i < limite - 1) { dest[i] = src[i]; i++; }
            dest[i] = '\0'; // Cerramos la cadena con el nulo por seguridad.
        };
        
        // Copiamos cada posición del arreglo datos[] al atributo correspondiente.
        copiar(rankingFIFA, datos[0], 50); copiar(pais, datos[1], 50); copiar(dt, datos[2], 50);
        copiar(fed, datos[3], 100); copiar(conf, datos[4], 20); copiar(gf_historico, datos[5], 10);
        copiar(gc_historico, datos[6], 10); copiar(pg_h, datos[7], 10); copiar(pe_h, datos[8], 10); copiar(pp_h, datos[9], 10);
    }

    // Calcula el promedio histórico de goles ofensivos.
    // PROMEDIOS: Usamos std::atoi para convertir el texto "3" a número 3.
    // (float) realiza una "conversión explícita" para que la división no sea truncada a entero.
    float getPromedioGF() const {
        // std::atoi convierte texto (ej. "5") al número entero (5).
        int t = std::atoi(pg_h) + std::atoi(pe_h) + std::atoi(pp_h); // t = Total de partidos jugados históricos.
        
        // Operador Ternario (? :) condicional corto: "Si t es igual a 0, retorna 0.01
        // (para evitar dividir por cero que colapsa el programa).
        // Si no, retorna Goles a favor convertidos a flotante (std::atof) divididos por el total de partidos."
        return (t == 0) ? 0.01f : (float)std::atof(gf_historico) / t;
    }

    // Calcula el promedio histórico de goles defensivos.
    float getPromedioGC() const {
        int t = std::atoi(pg_h) + std::atoi(pe_h) + std::atoi(pp_h);
        return (t == 0) ? 0.01f : (float)std::atof(gc_historico) / t;
    }

    // RESULTADOS: Actualiza las estadísticas tras jugar un partido simulado.
    // Cambia el estado interno del equipo sumando los goles y calculando puntos del torneo actual.
    void registrarResultado(int favor, int contra) {
        golesFavor += favor;
        golesContra += contra;
        diferenciaGoles = golesFavor - golesContra; // GD (Goal Difference)
        
        if (favor > contra) { puntos += 3; pg++; }       // Gana: 3 puntos
        else if (favor == contra) { puntos += 1; pe++; } // Empata: 1 punto
        else pp++;                                       // Pierde: 0 puntos
    }

    int getPuntos() const { return puntos; }
    int getGD() const { return diferenciaGoles; }
    const char* getNombre() const { return pais; }
    int getRankingInt() const { return std::atoi(rankingFIFA); }

    /* EXPORTACIÓN: Estas funciones escriben los datos del objeto en el archivo abierto (ofstream).
       El operador '<<' inserta texto dentro del flujo del archivo.
       Usamos ';' como separador para que Excel lo reconozca como columnas CSV.
    */

    void exportarBase(std::ofstream& a) { a << rankingFIFA << ";" << pais << ";" << dt << ";" << fed << ";" << conf << ";" << gf_historico << ";" << gc_historico << ";" << pg_h << ";" << pe_h << ";" << pp_h << "\n"; }
    void exportarSimulado(std::ofstream& a) { a << pais << ";" << puntos << ";" << pg << ";" << pe << ";" << pp << ";" << golesFavor << ";" << golesContra << ";" << diferenciaGoles << "\n"; }
    void exportarEscalafon(std::ofstream& a) { a << pais << ";" << etapa << ";" << puntos << ";" << diferenciaGoles << ";" << rankingFIFA << "\n"; }
};

// ========================================================================
// ETAPA 3: MÓDULOS DE ORQUESTACIÓN (Motor de Gestión y Reglas)
// ========================================================================
/* "La Etapa de orquestación y cumplimiento de reglas. Por un lado, el
    GestorArchivos{} encargada de la entrada y salida de datos (I/O)
    mediante una arquitectura de lectura/escritura de archivos planos (CSV),
    lo que permite manejar grandes volúmenes de información de forma modular.
    Por otro lado, el ClasificadorLlaves{} encapsula el reglamento deportivo de la FIFA;
    mediante algoritmos de ordenamiento y filtros de restricciones, el sistema asegura
    que las llaves eliminatorias sean reglamentarias, gestionando dinámicamente
    la progresión de los equipos según su rendimiento estadístico."
*/
class GestorArchivos {
public:
    // La función 'leerArchivo' toma una ruta (string) y una lista donde guardará los resultados.
    // Lee un archivo CSV y lo transforma en objetos C++.
    bool leerArchivo(std::string ruta, Lista<Equipo>& lista, int lineasCabecera) {
        std::ifstream archivo(ruta); // Intenta abrir el archivo en MODO LECTURA.
        
        // Si el archivo no existe o si la ruta está mal, el programa se detiene.
        if (!archivo.is_open()) {
            std::cout << "[ERROR CRITICO] No se encuentra el archivo en: " << ruta << "\n";
            return false;
        }
        
        char linea[1000]; // Una caja temporal para guardar una línea completa de texto.
        
        // Saltamos las primeras líneas (títulos y cabeceras) que no son equipos reales.
        for(int i=0; i < lineasCabecera; i++) {
            archivo.getline(linea, 1000);
        }
        
        // Bucle de lectura: Lee línea por línea hasta llegar al final del documento.
        // getline() devuelve falso cuando alcanza el final del archivo.
        while (archivo.getline(linea, 1000)) {
            char campos[10][100]; // Matriz 2D: 10 palabras de máximo 100 letras.
            int c=0, j=0; // c controla la Columna, j marca la posición de la letra en esa columna.
            
            // Fragmentamos (Split) Recorremos la línea buscando el delimitador ';'.
            for (int i=0; linea[i]!='\0'; i++) {
                if (linea[i]==';') {
                    campos[c][j]='\0'; // Marcamos el fin de la palabra actual.
                    c++; j=0;          // Saltamos a la siguiente columna.
                }
                else {
                    if(c < 10) campos[c][j++] = linea[i]; // Llenamos la columna actual letra a letra.
                }
            }
            campos[c][j]='\0'; // Aseguramos que la última columna también termine correctamente.
            
            // Si la línea tenía datos, creamos un objeto 'Equipo' y lo configuramos.
            if(c > 0) {
                Equipo equipoNuevo;
                equipoNuevo.configurarDesdeArreglo(campos);
                lista.agregar(equipoNuevo);
            }
        }
        archivo.close(); // Siempre cerrar el archivo para liberar recursos del Sistema Operativo.
        return true;
    }

    /* 'generarGruposBase()' organiza el torneo: crea los 12 archivos de grupo (.csv)
        basándose en la configuración inicial de la FIFA. Se hace el sorteo
    */
    void generarGruposBase(std::string rutaBase, Lista<Equipo>& maestro) {
        std::cout << "\n[Fase 1] Extrayendo y generando 12 archivos base de la FIFA...\n";
        
        // Array de nombres para los archivos.
        const char* nombresGrupos[] = {"Grupo_A","Grupo_B","Grupo_C","Grupo_D","Grupo_E","Grupo_F","Grupo_G","Grupo_H","Grupo_I","Grupo_J","Grupo_K","Grupo_L"};

        // Matriz de equipos, 12 filas 4 columnas: Aquí definimos la composición inicial definida por la FIFA.
        // Tomamos la lista de los 48 equipos y los organizamos en la en los grupo.
        const char* matrizFIFA[12][4] = {{"Mexico","South Africa","Korea Republic","Czech Republic"},{"Canada","Bosnia and Herzegovina","Qatar","Denmark"},{"Brazil","Morocco","Haiti","Scotland"},{"United States","Paraguay","Australia","Turkey"},{"Germany","Serbia","Nigeria","Costa Rica"},{"Netherlands","Japan","Sweden","Tunisia"},{"Belgium","Egypt","Iran","New Zealand"},{"Spain","Cabo Verde","Saudi Arabia","Uruguay"},{"France","Senegal","Iraq","Cameroon"},{"Argentina","Italy","Austria","Jordan"},{"Portugal","DR Congo","Uzbekistan","Colombia"},{"England","Croatia","Ghana","Panama"}};
        
        Lista<Equipo> controlDuplicados; // Registramos a quién ya asignamos para no repetir.
        
        for(int g=0; g<12; g++) { // Iteramos los 12 grupos.
            // std::ofstream crea el archivo físico en MODO ESCRITURA. Si ya existe, lo sobreescribe.
            // Al crear archivos independientes, le damos a nuestro programa un entorno controlado.
            // Cada grupo tiene su propia "burbuja" donde los datos no se mezclan con los demás grupos
            // hasta que los partidos hayan terminado.
            std::ofstream archivoCSV(rutaBase + "/" + nombresGrupos[g] + ".csv");
            if(archivoCSV.is_open()) {
                archivoCSV << "Ranking;Pais;DT;Fed;Conf;GF;GC;PG;PE;PP\n";// Escribimos los títulos.
                int asignados = 0;
                
                // Buscamos los 4 nombres dictados por la FIFA en nuestra lista Maestra.
                for(int p=0; p<4; p++) {
                    // Uso de 'esIgualA': Comparamos strings manualmente porque '=='
                    // en punteros compara direcciones de memoria, no el contenido del texto.
                    for(int i=0; i<maestro.getTamano(); i++) {
                        if(maestro.obtener(i).esIgualA(matrizFIFA[g][p])) {
                            maestro.obtener(i).exportarBase(archivoCSV); // Escribimos al disco.
                            controlDuplicados.agregar(maestro.obtener(i)); // Marcamos como ocupado.
                            asignados++; break;
                        }
                    }
                }
                
                // Si en la base de datos el nombre estaba mal escrito,
                // rellenamos los cupos faltantes con equipos que aún no han sido asignados.
                if(asignados < 4) {
                    for(int i=0; i<maestro.getTamano() && asignados < 4; i++) {
                        bool yaExiste = false;
                        for(int u=0; u<controlDuplicados.getTamano(); u++) if(maestro.obtener(i).esIgualA(controlDuplicados.obtener(u).getNombre())) yaExiste=true;
                        if(!yaExiste) { maestro.obtener(i).exportarBase(archivoCSV); controlDuplicados.agregar(maestro.obtener(i)); asignados++; }
                    }
                }
                archivoCSV.close();
            }
        }
        std::cout << "-> 12 Grupos extraidos exitosamente.\n";
    }
};

/*
 Una vez que el Motor de Poisson termina de jugar los partidos, tenemos una tabla de
 posiciones dentro de cada Grupo_X.csv. Aquí entra la clase ClasificadorLlaves:
 'ClasificadorLlaves{}' es la lógica que aplica las reglas del torneo
 para saber quién avanza a la siguiente ronda.
*/
class ClasificadorLlaves {
public:
    /*
     5 objetos independientes de tipo Lista<Equipo>, cada uno funcionando como un contenedor dinámico
     exclusivo para almacenar selecciones de fútbol. Cada lista opera con su propia memoria y estado,
     */
    Lista<Equipo> primeros, segundos, terceros, mejoresTerceros, tercerosUsados;
    
    // La función registrarPosiciones toma los 4 equipos de un grupo, mira su puntaje y los organiza.
    // Los dos mejores pasan a la lista de "Primeros" o "Segundos".
    void registrarPosiciones(Lista<Equipo>& grupo, char letra) {
        grupo.obtener(0).setGrupo(letra); primeros.agregar(grupo.obtener(0));
        grupo.obtener(1).setGrupo(letra); segundos.agregar(grupo.obtener(1));
        grupo.obtener(2).setGrupo(letra); terceros.agregar(grupo.obtener(2));
    }
    
    /*
     De los 12 terceros, debemos seleccionar a los 8 mejores.
     - Ponemos a los 12 terceros en una sola lista común.
     - El código pregunta: ¿El equipo A tiene más puntos que el B?
       Si es igual, pregunta: ¿Tiene mejor diferencia de goles (GD)?
       Si el equipo A es peor, los intercambiamos. Al final del bucle, tenemos una
       lista perfecta de "mejor a peor" rendimiento.
     - Tomamos solo los 8 primeros de esa lista ordenada.
    */
    void seleccionarMejoresTerceros() {
        /*
          Compara equipos adyacentes y los intercambia si están en el orden equivocado.
        */
        for(int i=0; i<terceros.getTamano()-1; i++) {
            for(int j=0; j<terceros.getTamano()-i-1; j++) {
                // Regla FIFA: Puntos mandan. En caso de empate de puntos, desempata la Diferencia de Goles (GD).
                if(terceros.obtener(j).getPuntos() < terceros.obtener(j+1).getPuntos() ||
                  (terceros.obtener(j).getPuntos() == terceros.obtener(j+1).getPuntos() && terceros.obtener(j).getGD() < terceros.obtener(j+1).getGD())) {
                    
                    // Intercambio usando una variable temporal para no perder el dato original.
                    Equipo temp = terceros.obtener(j);
                    terceros.obtener(j) = terceros.obtener(j+1);
                    terceros.obtener(j+1) = temp;
                }
            }
        }
        // Guardamos a los primeros 8 en la lista definitiva.
        for(int i=0; i<8; i++) mejoresTerceros.agregar(terceros.obtener(i));
    }
    
    // La función recorre la lista de mejores terceros y compara la letra del grupo (getGrupo()).
    // Si el equipo disponible proviene de un grupo prohibido para esa llave, lo salta. Si está permitido, lo asigna.
    Equipo buscarTercero(const char* gruposPermitidos) {
        for(int i=0; i<mejoresTerceros.getTamano(); i++) {
            Equipo& candidato = mejoresTerceros.obtener(i);
            bool enUso = false;
            
            // Verifica si ya lo usamos en otro partido de eliminatoria.
            for(int u=0; u<tercerosUsados.getTamano(); u++) if(candidato.esIgualA(tercerosUsados.obtener(u).getNombre())) enUso = true;
            
            if(!enUso) {
                // Revisa letra por letra si su grupo base coincide con los permitidos.
                bool cumpleRegla = false;
                for(int p=0; gruposPermitidos[p]!='\0'; p++) if(candidato.getGrupo()==gruposPermitidos[p]) cumpleRegla = true;
                
                if(cumpleRegla) { tercerosUsados.agregar(candidato); return candidato; }
            }
        }
        // Plan B: Si la llave se traba matemáticamente, toma al primer equipo libre sin importar la regla.
        for(int i=0; i<mejoresTerceros.getTamano(); i++) {
            Equipo& candidato = mejoresTerceros.obtener(i); bool enUso = false;
            for(int u=0; u<tercerosUsados.getTamano(); u++) if(candidato.esIgualA(tercerosUsados.obtener(u).getNombre())) enUso = true;
            if(!enUso) { tercerosUsados.agregar(candidato); return candidato; }
        }
        return mejoresTerceros.obtener(0);
    }
};

// ========================================================================
// ETAPA 4: MOTOR MATEMÁTICO (El Cerebro de Poisson)
// ========================================================================

/* "La Etapa 4 implementa un motor de simulación basado en la Distribución de Poisson,
    que es el estándar en modelado de eventos deportivos de baja frecuencia.
    En lugar de utilizar una generación aleatoria simple, calculé un valor de intensidad (λ)
    para cada equipo ponderado por factores de corrección ofensiva y defensiva (α y β).
    Finalmente, utilice mecanismo de aleatoriedad, permitiendo que la simulación refleje
    la incertidumbre inherente al fútbol manteniendo una coherencia estadística con los datos
    históricos de entrada."
 */
class MotorMundial {
private:
    // Coeficientes de corrección estadística:
    // MU: Constante promedio de goles globales.
    // ALFA: Peso de ataque / BETA: Peso de defensa.
    const float ALFA=0.6f, BETA=0.4f, MU=1.35f;
    
    // Generador de números pseudoaleatorios superior a la función rand() clásica.
    std::mt19937 randomizador;
public:
    // Al instanciar, inicializa la "semilla" (seed) usando entropía del hardware del procesador.
    MotorMundial() : randomizador(std::random_device{}()) {}

    // ¡Observa 'Lista<Equipo>& maestro'! Se pasa por referencia para poder actualizar los puntos globales.
    void ejecutarFaseGrupos(std::string rutaBase, GestorArchivos& io, ClasificadorLlaves& llaves, Lista<RegistroHistorial>& historial, Lista<Equipo>& maestro) {
        const char letras[] = {'A','B','C','D','E','F','G','H','I','J','K','L'};
        std::cout << "\n==================================================================================\n";
        std::cout << "|                         FASE DE GRUPOS (72 PARTIDOS)                           |\n";
        std::cout << "==================================================================================\n";
        
        // Lectura de archivos de grupo
        for(int k=0; k<12; k++) {
            std::string rutaCSV = rutaBase + "/Grupo_" + letras[k] + ".csv";
            Lista<Equipo> grupoActual;
            
            // Le decimos al Gestor que salte solo 1 línea (el título de las columnas).
            io.leerArchivo(rutaCSV, grupoActual, 1);
            
            if(grupoActual.getTamano() < 4) {
                std::cout << "[ALERTA] Fallo de integridad en Grupo " << letras[k] << "\n";
                continue;
            }
            
            Lista<RegistroPoisson> logTecnico;
            
            // Doble ciclo para el "Todos contra Todos". Juegan el 0vs1, 0vs2, 0vs3, 1vs2, etc. (6 partidos por grupo).
            for(int i=0; i<3; i++) {
                for(int j=i+1; j<4; j++) {
                    Equipo& eqA = grupoActual.obtener(i);
                    Equipo& eqB = grupoActual.obtener(j);
                    
                    /*
                      MODELO POISSON
                      En el fútbol, los goles son eventos independientes y poco frecuentes.
                      La distribución de Poisson es el modelo estándar en estadística deportiva
                      para predecir resultados discretos (0, 1, 2, 3 goles) cuando se conoce el
                      promedio esperado.
                                                       
                      Calculamos la intensidad probabilística (Lambda) de cada equipo.
                      Lambda A (Goles esperados de A) = MU * (Fuerza Ofensiva A)^ALFA * (Debilidad Defensiva B)^BETA.
                     
                     P(k; lambda) = [lambda^k * exp(-lambda)]/k!
                     
                    */
                    float lambdaA = MU * std::pow((eqA.getPromedioGF()/MU), ALFA) * std::pow((eqB.getPromedioGC()/MU), BETA);
                    float lambdaB = MU * std::pow((eqB.getPromedioGF()/MU), ALFA) * std::pow((eqA.getPromedioGC()/MU), BETA);
                    
                    // Configuramos un objeto generador (fabrica) de resultados Poison que depende de lambda.
                    std::poisson_distribution<int> distribucionA(lambdaA), distribucionB(lambdaB);
                    
                    // Para obtener el número entero (el número de goles), necesitas usar el
                    // generador de números aleatorios (randomizador) sobre ese objeto.
                    int golesA = distribucionA(randomizador);
                    int golesB = distribucionB(randomizador);
                    
                    /*
                     Modificamos a los objetos.
                     Una vez que el motor obtiene golesA y golesB, llama al método del objeto Equipo:
                     eqA.registrarResultado(golesA, golesB);
                     */
                    
                    eqA.registrarResultado(golesA, golesB);
                    eqB.registrarResultado(golesB, golesA);
                    
                    // Empaqueta los parámetros estadísticos de entrada y el resultado final de un partido en un
                    // objeto de registro para almacenarlo en una bitácora técnica, permitiendo así auditar
                    RegistroPoisson rp; rp.configurar(eqA.getNombre(), eqB.getNombre(), lambdaA, lambdaB, golesA, golesB); logTecnico.agregar(rp);
                    
                    std::string identificadorFase = "Grupo "; identificadorFase += letras[k];
                    
                    // El operador ternario (?) nos ahorra hacer un IF gigante para ver quién ganó o si fue empate.
                    RegistroHistorial rh; rh.configurar(identificadorFase, "GRP", eqA.getNombre(), eqB.getNombre(), (golesA>golesB?eqA.getNombre():(golesB>golesA?eqB.getNombre():"Empate")), golesA, golesB);
                    historial.agregar(rh);
                    
                    std::cout << "| " << identificadorFase << " | " << eqA.getNombre() << " " << golesA << " - " << golesB << " " << eqB.getNombre() << "\n";
                }
            }
            
            // CÓDIGO CRÍTICO: Sincronización del Estado Global
            // Traspasamos los Puntos ganados en la lista temporal del grupo hacia la Lista Maestra de 48 equipos.
            for(int i=0; i<grupoActual.getTamano(); i++) {
                for(int m=0; m<maestro.getTamano(); m++) {
                    if(maestro.obtener(m).esIgualA(grupoActual.obtener(i).getNombre())) {
                        maestro.obtener(m) = grupoActual.obtener(i);
                    }
                }
            }

            // Ordenamos internamente quién ganó el grupo usando Burbuja.
            for(int i=0; i<3; i++) for(int j=0; j<3-i; j++) {
                if(grupoActual.obtener(j).getPuntos() < grupoActual.obtener(j+1).getPuntos() || (grupoActual.obtener(j).getPuntos() == grupoActual.obtener(j+1).getPuntos() && grupoActual.obtener(j).getGD() < grupoActual.obtener(j+1).getGD())) {
                    Equipo temp = grupoActual.obtener(j); grupoActual.obtener(j) = grupoActual.obtener(j+1); grupoActual.obtener(j+1) = temp;
                }
            }
            
            llaves.registrarPosiciones(grupoActual, letras[k]);
            
            // Creamos los 12 archivos físicos con las tablas de los grupos simulados.
            std::ofstream archivoSimulado(rutaBase + "/Grupo_" + letras[k] + "_Simulado.csv");
            if(archivoSimulado.is_open()) {
                archivoSimulado << "TABLA;PTS;PG;PE;PP;GF;GC;GD\n";
                for(int i=0; i<4; i++) grupoActual.obtener(i).exportarSimulado(archivoSimulado);
                archivoSimulado << "\nLOG TECNICO (LAMBDA);VISITA;LAM_L;LAM_V;G_L;G_V\n";
                for(int i=0; i<logTecnico.getTamano(); i++) { RegistroPoisson& p = logTecnico.obtener(i); archivoSimulado << p.local << ";" << p.visita << ";" << p.lambdaL << ";" << p.lambdaV << ";" << p.golesL << ";" << p.golesV << "\n"; }
                archivoSimulado.close();
            }
        }
    }

    // Lógica para Muerte Súbita. Retorna el objeto del Equipo que avanza a la siguiente ronda.
    Equipo simularPartidoEliminatorio(const char* fase, const char* id, Equipo eqA, Equipo eqB, Lista<RegistroHistorial>& historial) {
        float lambdaA = MU * std::pow((eqA.getPromedioGF()/MU), ALFA) * std::pow((eqB.getPromedioGC()/MU), BETA);
        float lambdaB = MU * std::pow((eqB.getPromedioGF()/MU), ALFA) * std::pow((eqA.getPromedioGC()/MU), BETA);
        std::poisson_distribution<int> distribucionA(lambdaA), distribucionB(lambdaB);
        int golesA = distribucionA(randomizador), golesB = distribucionB(randomizador);
        
        Equipo ganador;
        // En eliminatorias no hay empate técnico, avanzamos forzosamente al mejor Ranking FIFA.
        if (golesA > golesB) ganador = eqA;
        else if (golesB > golesA) ganador = eqB;
        else ganador = (eqA.getRankingInt() < eqB.getRankingInt() ? eqA : eqB);

        RegistroHistorial rh; rh.configurar(fase, id, eqA.getNombre(), eqB.getNombre(), ganador.getNombre(), golesA, golesB); historial.agregar(rh);
        std::cout << "| " << fase << " | " << id << " | " << eqA.getNombre() << " vs " << eqB.getNombre() << " |  " << golesA << " - " << golesB << "  | " << ganador.getNombre() << " |\n";
        
        return ganador;
    }
};

// ========================================================================
// ORQUESTADOR PRINCIPAL (El punto de entrada del programa)
// ========================================================================
/*
  LECCIÓN: LA FUNCIÓN MAIN
  C++ siempre empieza su ejecución buscando la función `int main()`.
  Aquí no hacemos cálculos matemáticos; solo creamos a nuestros "trabajadores"
  (Clases) y les damos las instrucciones en el orden correcto.
*/
int main() {
    // Declaración de ruta cruda (Adaptable según el sistema del estudiante).
    std::string entornoTrabajo = "/Users/zahir_llerena/My Drive/C_Work/Project_cpp/Guia_D2";
    
    // Instanciación de los trabajadores en la memoria.
    Lista<Equipo> seleccionMaestra;
    GestorArchivos gestorIO;
    ClasificadorLlaves arbitro;
    MotorMundial fifa2026;
    Lista<RegistroHistorial> baseDatosPartidos;

    std::cout << ">>> INICIANDO PLATAFORMA UdeAWorldCup 2026 <<<\n";
    
    // Orden 1: Leer el CSV de entrada. Saltamos 2 líneas iniciales (Metadatos).
    if (gestorIO.leerArchivo(entornoTrabajo + "/selecciones_clasificadas_mundial.csv", seleccionMaestra, 2)) {
        
        // Orden 2: Generar y Simular fase de grupos.
        gestorIO.generarGruposBase(entornoTrabajo, seleccionMaestra);
        fifa2026.ejecutarFaseGrupos(entornoTrabajo, gestorIO, arbitro, baseDatosPartidos, seleccionMaestra);
        arbitro.seleccionarMejoresTerceros();

        std::cout << "\n==================================================================================\n";
        std::cout << "| Fase   | ID   | Encuentro                        | Marcador | Clasifica / Gana |\n";
        std::cout << "|--------|------|----------------------------------|----------|------------------|\n";
        
        // --- Orden 3: FASE DE ELIMINATORIAS DIRECTAS ---
        
        // --- 1/16 DE FINAL (Ronda de 32) ---
        // Extraemos a los clasificados de la Fase de Grupos pasándolos por el Simulador.
        Equipo ganador_R32_1 = fifa2026.simularPartidoEliminatorio("R32","M73",arbitro.segundos.obtener(0),arbitro.segundos.obtener(1),baseDatosPartidos);
        Equipo ganador_R32_2 = fifa2026.simularPartidoEliminatorio("R32","M74",arbitro.primeros.obtener(4),arbitro.buscarTercero("ABCDF"),baseDatosPartidos);
        Equipo ganador_R32_3 = fifa2026.simularPartidoEliminatorio("R32","M75",arbitro.primeros.obtener(5),arbitro.segundos.obtener(2),baseDatosPartidos);
        Equipo ganador_R32_4 = fifa2026.simularPartidoEliminatorio("R32","M76",arbitro.primeros.obtener(2),arbitro.segundos.obtener(5),baseDatosPartidos);
        Equipo ganador_R32_5 = fifa2026.simularPartidoEliminatorio("R32","M77",arbitro.primeros.obtener(8),arbitro.buscarTercero("CDFGH"),baseDatosPartidos);
        Equipo ganador_R32_6 = fifa2026.simularPartidoEliminatorio("R32","M78",arbitro.segundos.obtener(4),arbitro.segundos.obtener(8),baseDatosPartidos);
        Equipo ganador_R32_7 = fifa2026.simularPartidoEliminatorio("R32","M79",arbitro.primeros.obtener(0),arbitro.buscarTercero("CEFHI"),baseDatosPartidos);
        Equipo ganador_R32_8 = fifa2026.simularPartidoEliminatorio("R32","M80",arbitro.primeros.obtener(11),arbitro.buscarTercero("EHIJK"),baseDatosPartidos);
        Equipo ganador_R32_9 = fifa2026.simularPartidoEliminatorio("R32","M81",arbitro.primeros.obtener(3),arbitro.buscarTercero("BEFIJ"),baseDatosPartidos);
        Equipo ganador_R32_10 = fifa2026.simularPartidoEliminatorio("R32","M82",arbitro.primeros.obtener(6),arbitro.buscarTercero("AEHIJ"),baseDatosPartidos);
        Equipo ganador_R32_11 = fifa2026.simularPartidoEliminatorio("R32","M83",arbitro.segundos.obtener(10),arbitro.segundos.obtener(11),baseDatosPartidos);
        Equipo ganador_R32_12 = fifa2026.simularPartidoEliminatorio("R32","M84",arbitro.primeros.obtener(7),arbitro.segundos.obtener(9),baseDatosPartidos);
        Equipo ganador_R32_13 = fifa2026.simularPartidoEliminatorio("R32","M85",arbitro.primeros.obtener(1),arbitro.buscarTercero("EFGIJ"),baseDatosPartidos);
        Equipo ganador_R32_14 = fifa2026.simularPartidoEliminatorio("R32","M86",arbitro.primeros.obtener(9),arbitro.segundos.obtener(7),baseDatosPartidos);
        Equipo ganador_R32_15 = fifa2026.simularPartidoEliminatorio("R32","M87",arbitro.primeros.obtener(10),arbitro.buscarTercero("DEIJL"),baseDatosPartidos);
        Equipo ganador_R32_16 = fifa2026.simularPartidoEliminatorio("R32","M88",arbitro.segundos.obtener(3),arbitro.segundos.obtener(6),baseDatosPartidos);

        // --- OCTAVOS DE FINAL ---
        // Emparejamos a los objetos que retornaron victoriosos de la línea anterior.
        Equipo ganador_R16_1 = fifa2026.simularPartidoEliminatorio("R16","P89",ganador_R32_2,ganador_R32_5,baseDatosPartidos);
        Equipo ganador_R16_2 = fifa2026.simularPartidoEliminatorio("R16","P90",ganador_R32_1,ganador_R32_3,baseDatosPartidos);
        Equipo ganador_R16_3 = fifa2026.simularPartidoEliminatorio("R16","P91",ganador_R32_4,ganador_R32_6,baseDatosPartidos);
        Equipo ganador_R16_4 = fifa2026.simularPartidoEliminatorio("R16","P92",ganador_R32_7,ganador_R32_8,baseDatosPartidos);
        Equipo ganador_R16_5 = fifa2026.simularPartidoEliminatorio("R16","P93",ganador_R32_11,ganador_R32_12,baseDatosPartidos);
        Equipo ganador_R16_6 = fifa2026.simularPartidoEliminatorio("R16","P94",ganador_R32_9,ganador_R32_10,baseDatosPartidos);
        Equipo ganador_R16_7 = fifa2026.simularPartidoEliminatorio("R16","P95",ganador_R32_14,ganador_R32_16,baseDatosPartidos);
        Equipo ganador_R16_8 = fifa2026.simularPartidoEliminatorio("R16","P96",ganador_R32_13,ganador_R32_15,baseDatosPartidos);

        // --- CUARTOS DE FINAL ---
        Equipo semifinalista_1 = fifa2026.simularPartidoEliminatorio("QF","QF1",ganador_R16_1,ganador_R16_2,baseDatosPartidos);
        Equipo semifinalista_2 = fifa2026.simularPartidoEliminatorio("QF","QF2",ganador_R16_3,ganador_R16_4,baseDatosPartidos);
        Equipo semifinalista_3 = fifa2026.simularPartidoEliminatorio("QF","QF3",ganador_R16_5,ganador_R16_6,baseDatosPartidos);
        Equipo semifinalista_4 = fifa2026.simularPartidoEliminatorio("QF","QF4",ganador_R16_7,ganador_R16_8,baseDatosPartidos);

        // --- SEMIFINALES ---
        Equipo finalista_1 = fifa2026.simularPartidoEliminatorio("SF","SF1",semifinalista_1,semifinalista_2,baseDatosPartidos);
        Equipo finalista_2 = fifa2026.simularPartidoEliminatorio("SF","SF2",semifinalista_3,semifinalista_4,baseDatosPartidos);
        
        // Identificar perdedores para jugar el Tercer Puesto (Operador Ternario).
        Equipo perdedor_SF1 = (finalista_1.esIgualA(semifinalista_1.getNombre())) ? semifinalista_2 : semifinalista_1;
        Equipo perdedor_SF2 = (finalista_2.esIgualA(semifinalista_3.getNombre())) ? semifinalista_4 : semifinalista_3;

        // --- PARTIDOS DE MEDALLAS ---
        Equipo tercerPuesto = fifa2026.simularPartidoEliminatorio("Final","M103",perdedor_SF1,perdedor_SF2,baseDatosPartidos);
        Equipo campeonMundial = fifa2026.simularPartidoEliminatorio("Final","M104",finalista_1,finalista_2,baseDatosPartidos);
        Equipo subcampeon = (campeonMundial.esIgualA(finalista_1.getNombre())) ? finalista_2 : finalista_1;

        std::cout << "\n============================================\n|     PODIO FINAL - COPA MUNDIAL 2026      |\n============================================\n";
        std::cout << "| 1ero (Oro)   | " << campeonMundial.getNombre() << "\n| 2do (Plata)  | " << subcampeon.getNombre() << "\n| 3ero (Bronce)| " << tercerPuesto.getNombre() << "\n============================================\n";

        // ========================================================================
        // Orden 4: ESCRITURA DE ARCHIVOS DEFINITIVOS
        // ========================================================================
        
        // Archivo que contiene los 104 partidos.
        std::ofstream h_f(entornoTrabajo + "/Resumen_Eliminatorias_2026.csv");
        if(h_f.is_open()){
            h_f << "Fase;ID;Local;Visita;G_L;G_V;Ganador\n";
            for(int i=0; i<baseDatosPartidos.getTamano(); i++) { RegistroHistorial& h = baseDatosPartidos.obtener(i); h_f << h.fase << ";" << h.id << ";" << h.local << ";" << h.visita << ";" << h.golesL << ";" << h.golesV << ";" << h.ganador << "\n"; }
            h_f.close();
         }

        // --- CÁLCULO DE JERARQUÍAS (Ranking Final) ---
        // Le asigna un "Peso" numérico a cada equipo según la ronda a la que llegó.
        for(int i=0; i<baseDatosPartidos.getTamano(); i++) {
            for(int j=0; j<seleccionMaestra.getTamano(); j++) {
                if(seleccionMaestra.obtener(j).esIgualA(baseDatosPartidos.obtener(i).local.c_str()) || seleccionMaestra.obtener(j).esIgualA(baseDatosPartidos.obtener(i).visita.c_str())) {
                    std::string f = baseDatosPartidos.obtener(i).fase;
                    if(f == "R32") seleccionMaestra.obtener(j).setEtapaFinal("Dieciseisavos", 7);
                    else if(f == "R16") seleccionMaestra.obtener(j).setEtapaFinal("Octavos", 6);
                    else if(f == "QF") seleccionMaestra.obtener(j).setEtapaFinal("Cuartos", 5);
                    else if(f == "SF") seleccionMaestra.obtener(j).setEtapaFinal("Semifinalistas", 4);
                }
            }
        }
        // Medallistas tienen los pesos de máxima prioridad.
        for(int j=0; j<seleccionMaestra.getTamano(); j++) {
            if(seleccionMaestra.obtener(j).esIgualA(tercerPuesto.getNombre())) seleccionMaestra.obtener(j).setEtapaFinal("Tercer Puesto", 3);
            if(seleccionMaestra.obtener(j).esIgualA(subcampeon.getNombre())) seleccionMaestra.obtener(j).setEtapaFinal("Subcampeon", 2);
            if(seleccionMaestra.obtener(j).esIgualA(campeonMundial.getNombre())) seleccionMaestra.obtener(j).setEtapaFinal("Campeon", 1);
        }

        // Algoritmo de Burbuja: Ordena el top 48.
        // Criterio 1: Peso (Etapa alcanzada). Criterio 2: Puntos acumulados.
        for(int i=0; i<seleccionMaestra.getTamano()-1; i++) for(int j=0; j<seleccionMaestra.getTamano()-i-1; j++) {
            if(seleccionMaestra.obtener(j).getPeso() > seleccionMaestra.obtener(j+1).getPeso() || (seleccionMaestra.obtener(j).getPeso() == seleccionMaestra.obtener(j+1).getPeso() && seleccionMaestra.obtener(j).getPuntos() < seleccionMaestra.obtener(j+1).getPuntos())) {
                Equipo temporal = seleccionMaestra.obtener(j); seleccionMaestra.obtener(j) = seleccionMaestra.obtener(j+1); seleccionMaestra.obtener(j+1) = temporal;
            }
        }
        
        // Archivo del Escalafón Mundial Final.
        std::ofstream r_f(entornoTrabajo + "/Posiciones_Finales_Mundial_2026.csv");
        if(r_f.is_open()){
            r_f << "Ranking;Pais;Etapa;Pts;GD;Ranking_FIFA\n";
            for(int i=0; i<seleccionMaestra.getTamano(); i++) { r_f << i+1 << ";"; seleccionMaestra.obtener(i).exportarEscalafon(r_f); }
            r_f.close();
            std::cout << "[EXITO] Ranking Mundial actualizado correctamente con Puntos y GD.\n";
        }
    }
    
    // Invocación final de nuestra función estática para auditar memoria.
    Lista<int>::mostrarAuditoria();
    
    // 'return 0' le indica al sistema operativo que el programa terminó sin errores críticos.
    return 0;
}


//  Teh end ===================================================================================
