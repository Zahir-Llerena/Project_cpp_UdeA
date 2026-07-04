// ======================================================================================
// Universidad de Antioquia
// Facultad de Ingenieria - Departamento de Telecomunicaciones
// @authors: Zahir Llerena
// ======================================================================================

#include <iostream>  // Biblioteca estandar para entrada y salida de datos en consola (std::cout, std::cin).
#include <string>    // Permite el uso de cadenas de texto dinamicas (std::string) en lugar de arreglos de caracteres.
#include <map>       // Estructura asociativa basada en arboles balanceados. Guarda pares clave-valor indexados.
#include <vector>    // Contenedor secuencial de la STL que funciona como un arreglo dinamico de tamano ajustable.
#include <fstream>   // Flujos de archivos. Permite abrir y leer de forma nativa documentos externos (.txt).
#include <sstream>   // Flujos de cadenas (stringstream). Crucial para partir o tokenizar lineas de texto usando separadores.
#include <limits>    // Provee propiedades de los tipos numericos basicos (como saber cual es el entero mas grande posible).
#include <algorithm> // Incluye algoritmos genericos optimizados de la STL, como std::reverse para voltear contenedores.

// Definicion de una constante global. Usamos el valor maximo que puede almacenar un entero convencional.
// En teoria de grafos y redes, este valor representa matematicamente el "Infinito" (nodos que no estan conectados).
// Valor numerico maximo para representar la ausencia de conexion (Infinito)
const int INF = std::numeric_limits<int>::max();

// ============================================================================
// BLOQUE 1: ESTRUCTURA ASOCIADA A ENRUTADOR.H
// ============================================================================

// Una clase funciona como una plantilla o molde. En este caso, representa un enrutador real.
// Cada enrutador es independiente y solo conoce su propia identidad y a sus vecinos directos.

class Enrutador {
private: // Zona encapsulada: Atributos privados. Solo los metodos de esta clase pueden verlos o modificarlos.
    std::string nombre; // El identificador unico del enrutador (por ejemplo: "A", "Medellin", "Nodo_Core").

    // Lista de adyacencia local. La clave (string) es el nombre del vecino y el valor (int) es el costo del enlace.
    // Al usar std::map, buscar si un vecino existe toma un tiempo logaritmico O(log n), haciendolo muy eficiente.
    std::map<std::string, int> enlaces;

public: // Zona publica: Interfaces y metodos disponibles para que otras clases (como Red o Main) interactuen con el objeto.

    // --- CONSTRUCTORES Y DESTRUCTOR ---

    // Constructor por defecto: Se ejecuta automaticamente al crear un enrutador sin pasarle parametros.
    // Inicializa el nombre como una cadena vacia.
    Enrutador() : nombre("") {}

    // Constructor parametrizado: Permite darle una identidad al enrutador en el mismo momento de su nacimiento.
    // Asigna el parametro 'nom' al atributo privado 'nombre'.
    Enrutador(const std::string& nom) : nombre(nom) {}

    // Destructor: Se ejecuta cuando el objeto sale de su ambito de validez para liberar recursos de memoria.
    // Al usar elementos estandar como string y map, C++ limpia la memoria automaticamente por nosotros.
    ~Enrutador() {}

    // --- METODOS DE ACCESO (GETTERS) ---
    // Nota: Usamos 'const' al final de la firma para garantizar que estos metodos prometen no modificar los atributos privados.
    // Devolvemos por referencia (&) para evitar hacer copias innecesarias en la memoria RAM.

    const std::string &getNombre() const { return nombre; }  // Devuelve la identidad del enrutador.
    const std::map<std::string, int> &getEnlaces() const { return enlaces; }   // Devuelve el mapa completo de vecinos conectados.

    // --- METODOS DE FUNCIONAMIENTO LOCAL ---

    // Agrega un vecino o modifica su costo. Usamos el operador de indexacion [] de std::map.
    // Si 'destino' no existia en el mapa, el contenedor lo crea; si ya existia, sobrescribe el costo viejo con el nuevo.
    void agregarEnlace(const std::string &destino, int costo) {
        enlaces[destino] = costo;
    }

    // Corta la conexion directa con un vecino especifico.
    // El metodo erase() busca la clave ('destino') dentro del mapa y la elimina junto con su costo asociado.
    void eliminarEnlace(const std::string &destino) {
        enlaces.erase(destino);
    }

    // Modifica de forma explicita el costo hacia un vecino existente.
    // find() busca la clave. Si el iterador resultante es diferente de enlaces.end(), significa que el vecino si existe.
    void actualizarCosto(const std::string &destino, int costo) {
        if (enlaces.find(destino) != enlaces.end()) {
            enlaces[destino] = costo; // Sobrescribe el valor numerico en el mapa local.
        }
    }
};

/* 🔗 INTERRELACION DIDACTICA DEL BLOQUE 1:
  La clase Enrutador es la unidad minima de informacion (el ladrillo de la construccion).
  No sabe cuantos enrutadores existen, solo conoce su propio nombre y a quien tiene
  conectado a su lado mediante cables de red directos.
*/

// ============================================================================
// BLOQUE 2: ESTRUCTURA ASOCIADA A RED.H
// ============================================================================

// Esta clase representa la topologia global. Funciona como un administrador centralizado
// que posee una vista completa de todo el sistema y computa los algoritmos de optimizacion.

class Red {
private:
    // El mapa del mapa de la red. Almacena todos los enrutadores del sistema.
    // Clave: Nombre del enrutador (string) -> Valor: El objeto Enrutador correspondiente.
    std::map<std::string, Enrutador> enrutadores; // Contenedor para enrutadores de la red
    
    // Matriz asociativa bidimensional de rutas y costos minimos calculados.
    // Estructura semantica: Origen (string) -> Destino (string) -> pair<Costo_Total(int), Secuencia_Nodos(vector)>
    // Contenedor para guardar las tablas de enrutamiento de cada enrutador
    std::map<std::string, std::map<std::string, std::pair<int, std::vector<std::string>>>> tablasEnrutamiento;

public:
    // Constructores y destructor por defecto. Al igual que con Enrutador, delegamos la limpieza en la STL.
    // Constructores y destructor originales
    Red() {}  // Constructor por defecto
    ~Red() {} // Destructor

    // --- METODOS DE MODIFICACIONES ---
    // Agregar un enrutador a la red (Inserta un nuevo nodo autonomo)
    void agregarEnrutador(const std::string &nombre) {
        // find() verifica si ya existia un nodo con ese nombre para evitar duplicar registros en la red.
        if (enrutadores.find(nombre) == enrutadores.end()) {
            // Si no existe, crea una nueva entrada en el mapa e inicializa el objeto Enrutador llamando a su constructor.
            enrutadores[nombre] = Enrutador(nombre);
        }
        actualizarTablas(); // Ante cualquier cambio fisico de la red, recalculamos los caminos optimos globales.
    }

    // Remover un enrutador (nodo) de la red y depura todas las conexiones que apuntaban hacia el.
    void removerEnrutador(const std::string &nombre) {
        if (enrutadores.find(nombre) == enrutadores.end()) return; // Si no existe, sale inmediatamente.
        
        // Bucle "For basado en rangos": Recorre cada enrutador registrado en la topologia global.
        // Como la red es bidireccional y simetrica, si eliminamos el enrutador 'X', debemos avisarle
        // a todos los demas enrutadores que rompan sus cables de conexion locales hacia 'nombre'.

        // Purgar enlaces que apuntaban al nodo eliminado
        for (auto &par : enrutadores) {
            par.second.eliminarEnlace(nombre); // Llama al metodo del Bloque 1 de forma transparente.
        }
        enrutadores.erase(nombre); // Saca definitivamente el objeto enrutador de nuestro mapa global.
        actualizarTablas(); // Recalcula rutas globales con la nueva topologia de n-1 nodos.
    }

    // Establece un enlace de comunicacion mutuo entre dos enrutadores existentes.
    // Agregar un enlace entre dos enrutadores
    void agregarEnlace(const std::string &origen, const std::string &destino, int costo) {
        // Comprueba que ambos enrutadores existan fisicamente en el mapa global.
        if (enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()) {
            enrutadores[origen].agregarEnlace(destino, costo); // Agrega enlace de ida en el enrutador Origen.
            enrutadores[destino].agregarEnlace(origen, costo); // Agrega enlace de regreso en el enrutador Destino.
            actualizarTablas(); // Al haber una nueva autopista de datos, recalculamos las mejores rutas.
        }
    }

    // Corta la infraestructura de comunicacion directa entre dos enrutadores.
    // Eliminar un enlace entre dos enrutadores
    void eliminarEnlace(const std::string &origen, const std::string &destino) {
        if (enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()) {
            enrutadores[origen].eliminarEnlace(destino); // Rompe conexion en el nodo origen.
            enrutadores[destino].eliminarEnlace(origen); // Rompe conexion en el nodo destino.
            actualizarTablas(); // Recalcula caminos ignorando el enlace destruido.
        }
    }

    // Modifica de manera global y centralizada el costo de una arista.
    // Actualizar el costo de un enlace
    void actualizarCosto(const std::string &origen, const std::string &destino, int nuevoCosto) {
        if (enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()) {
            enrutadores[origen].actualizarCosto(destino, nuevoCosto); // Actualiza metrica local de ida.
            enrutadores[destino].actualizarCosto(origen, nuevoCosto); // Actualiza metrica local de regreso.
            actualizarTablas(); // Recalcula tablas para verificar si la nueva metrica altera las rutas previas.
        }
    }

    // --- LECTOR AUTOMATIZADO DE ARCHIVOS .TXT ---
    void cargarDesdeArchivo(const std::string &nombreArchivo) {
        std::ifstream archivo(nombreArchivo); // Intenta abrir un flujo de entrada con el archivo externo.
        if (!archivo.is_open()) return; // Si el archivo no existe o la ruta es invalida, sale de forma segura.

        enrutadores.clear(); // Limpia toda la memoria de la red previa para realizar una carga limpia y fresca.
        std::string linea;   // Variable temporal para almacenar el texto linea por linea.
        
        // std::getline lee el archivo linea por linea de manera segura hasta llegar al final del documento.
        while (std::getline(archivo, linea)) {
            // Ignora lineas que el usuario deja vacias o lineas que comienzan con '#' (comentarios del operador de red).
            if (linea.empty() || linea[0] == '#') continue;
            
            std::stringstream ss(linea); // Convierte la cadena en un flujo para poder tokenizar o cortar el texto.
            std::string orig, dest, costStr; // Variables para almacenar los tres campos: Origen, Destino y Costo.
            
            // Corta la linea utilizando la coma ',' como caracter delimitador (Formato CSV).
            if (std::getline(ss, orig, ',') && std::getline(ss, dest, ',') && std::getline(ss, costStr, ',')) {
                // Descubrimiento automatico de nodos: Si el enrutador no existia en la red, lo agrega dinamicamente.
                if (enrutadores.find(orig) == enrutadores.end()) enrutadores[orig] = Enrutador(orig);
                if (enrutadores.find(dest) == enrutadores.end()) enrutadores[dest] = Enrutador(dest);
                
                // std::stoi convierte la subcadena del costo (texto) en un numero entero computable.
                enrutadores[orig].agregarEnlace(dest, std::stoi(costStr));
                enrutadores[dest].agregarEnlace(orig, std::stoi(costStr));
            }
        }
        archivo.close(); // Cierra el archivo liberando los descriptores del sistema operativo.
        actualizarTablas(); // Inicializa las tablas globales basandose en los datos cargados.
    }

    // --- ALGORITMO DE DIJKSTRA ---
    // Este metodo encuentra de manera matematica los caminos minimos desde un unico nodo 'origen' hacia toda la red.
    void dijkstra(const std::string &origen) {
        std::map<std::string, int> dists; // Almacena de forma tentativa la menor distancia acumulada a cada nodo.
        std::map<std::string, std::string> padres; // Guarda la secuencia del camino: Clave (Nodo) -> Valor (Quien es su antecesor inmediato).
        std::map<std::string, bool> visitados; // Marcador booleano para recordar que nodos ya fueron procesados y cerrados.

        // PASO 1: INICIALIZACION AXIOMATICA
        // Inicializamos las distancias de todos los nodos de la red como Infinito (INF) y marcamos que ninguno ha sido visitado.
        for (const auto &p : enrutadores) dists[p.first] = INF;
        dists[origen] = 0; // La distancia desde el origen hacia si mismo es estrictamente cero.

        // PASO 2: BUCLE PRINCIPAL DE RECORRIDO
        // Iteramos tantas veces como enrutadores existan en el sistema para garantizar la exploracion de todo el grafo.
        for (size_t i = 0; i < enrutadores.size(); i++) {
            std::string u = ""; // Variable para guardar el nombre del nodo no visitado con la menor distancia posible.
            int min_dist = INF; // Centinela para buscar la distancia mas pequena.
            
            // Recorremos la red buscando el enrutador que tenga la distancia minima acumulada actual y que no este visitado.
            for (const auto& p : enrutadores) {
                if (!visitados[p.first] && dists[p.first] < min_dist) {
                    min_dist = dists[p.first];
                    u = p.first; // Encontrado el nodo candidato para expandirse.
                }
            }
            // Si no se encuentra ningun nodo alcanzable o el resto esta desconectado, rompemos el bucle antes de tiempo.
            if (u.empty() || min_dist == INF) break;
            visitados[u] = true; // Marcamos el nodo 'u' como cerrado/visitado de forma definitiva.

            // PASO 3: RELAJACION MATEMATICA
            // Exploramos todos los enlaces directos (vecinos) del nodo 'u' que acabamos de fijar.
            for (const auto &enlace : enrutadores[u].getEnlaces()) {
                std::string v = enlace.first; // Nombre del nodo vecino.
                int peso = enlace.second;     // Costo metrico del cable directo entre 'u' y 'v'.
                
                // Evaluamos matematicamente: ¿Es mas barato llegar a 'v' dando la vuelta a traves de 'u'
                // en lugar de usar el camino tentativo que conociamos antes para 'v'?
                if (!visitados[v] && dists[u] + peso < dists[v]) {
                    dists[v] = dists[u] + peso; // Si es verdadero, actualizamos la distancia minima acumulada hacia 'v'.
                    padres[v] = u; // Registramos que para llegar optimamente a 'v' tuvimos que pasar por 'u'.
                }
            }
        }

        // PASO 4: RECONSTRUCCION VECTORIAL DE CAMINOS
        // Una vez finalizadas las distancias minimas para este origen, estructuramos el camino completo para cada destino.
        for (const auto &p : enrutadores) {
            std::string dest = p.first;
            if (dists[dest] == INF) {
                // Validacion del Requerimiento 8: Si no hay conexion fisica, guardamos costo infinito y una ruta vacia.
                tablasEnrutamiento[origen][dest] = {INF, {}};
            } else {
                std::vector<std::string> cam; // Contenedor dinamico de la STL elegido para la secuencia lineal.
                std::string act = dest;
                
                // Rastrearemos la ruta en reversa: Desde el destino viajamos hacia atras usando el mapa 'padres'.
                while (act != origen) {
                    cam.push_back(act); // Anade el nodo actual al vector.
                    act = padres[act];  // Salta a su antecesor.
                }
                cam.push_back(origen);  // Anadimos finalmente el nodo inicial.
                
                // Como la ruta se construyo al reves ([Destino -> ... -> Origen]), usamos std::reverse
                // para darle la vuelta al vector, dejandolo de forma natural: [Origen -> ... -> Destino].
                std::reverse(cam.begin(), cam.end());
                
                // Almacenamos el par estructurado (Costo Total, Secuencia de Nodos) en la matriz asociativa global.
                tablasEnrutamiento[origen][dest] = {dists[dest], cam};
            }
        }
    }

    // Calcula de forma secuencial y automatica las rutas de toda la red.
    void actualizarTablas() {
        tablasEnrutamiento.clear(); // Limpia los registros anteriores para evitar datos basura residuales.
        // Ejecuta el algoritmo de Dijkstra tomando a cada enrutador registrado como centro u origen del universo.
        for (const auto &p : enrutadores) dijkstra(p.first);
    }

    // --- METODOS DE CONSULTA GLOBAL ---

    int obtenerCosto(const std::string &origen, const std::string &destino) {
        // .count() es una funcion de std::map que devuelve 1 si encuentra la clave o 0 si no existe.
        // Sirve para verificar la existencia segura del origen y destino antes de acceder a la matriz.
        if (tablasEnrutamiento.count(origen) && tablasEnrutamiento[origen].count(destino)) {
            return tablasEnrutamiento[origen][destino].first; // Retorna el entero que representa el costo minimo acumulado.
        }
        return INF;
    }

    std::vector<std::string> obtenerCamino(const std::string &origen, const std::string &destino) {
        if (tablasEnrutamiento.count(origen) && tablasEnrutamiento[origen].count(destino)) {
            return tablasEnrutamiento[origen][destino].second; // Retorna el vector secuencial de nodos elegidos.
        }
        return std::vector<std::string>(); // Retorna un contenedor vacio en caso de que sea inalcanzable.
    }

    // Generador de reportes visuales en formato tabular.
    void mostrarTablaEnrutamiento(const std::string &nombre) {
        if (enrutadores.find(nombre) == enrutadores.end()) {
            std::cout << "El enrutador '" << nombre << "' no existe en la red.\n";
            return;
        }
        std::cout << "\nTABLA DE ENRUTAMIENTO: " << nombre << "\nDestino\tCosto\tCamino Eficiente\n";
        
        // Recorre todos los destinos posibles calculados para este enrutador especifico.
        for (const auto &par : tablasEnrutamiento[nombre]) {
            // Imprime el nombre del destino y evalua si el costo es infinito para imprimir la palabra "INF".
            std::cout << par.first << "\t" << (par.second.first == INF ? "INF" : std::to_string(par.second.first)) << "\t";
            
            // Bucle clasico con incremento 'i++' para recorrer e imprimir el vector secuencial que representa la ruta.
            for (size_t i = 0; i < par.second.second.size(); i++) {
                // Operador ternario didactico: Si es el ultimo elemento del camino, no le pone la flecha de salto.
                std::cout << par.second.second[i] << (i == par.second.second.size() - 1 ? "" : " -> ");
            }
            std::cout << "\n";
        }
    }
};

/* 🔗 INTERRELACION DIDACTICA DEL BLOQUE 2:
  La clase Red es el cerebro central del software. Almacena multiples objetos de tipo Enrutador
  en el mapa 'enrutadores'. Cuando el usuario agrega, borra o modifica cables en la interfaz,
  esta clase orquesta el algoritmo de Dijkstra para recalcular las rutas de forma inmediata,
  guardando las soluciones en la matriz 'tablasEnrutamiento' para su rapida consulta posterior.
*/

// ============================================================================
// BLOQUE 3: FUNCIONES AUXILIARES DE CONTROL DE FLUJOS (MECANISMOS DE ROBUSTEZ)
// ============================================================================
// Funciones sueltas (no pertenecen a ninguna clase) disenadas especificamente para blindar
// la entrada estandar por teclado contra datos corruptos y controlar el despliegue visual.

// Evita bucles infinitos en el menu cuando un usuario digita letras en un campo numerico entero.
void limpiarBuffer() {
    std::cin.clear(); // Restablece los flags o banderas de error del flujo std::cin (limpia el estado de falla).
    // Ignora y descarta del canal de transmision todos los caracteres residuales corruptos que el usuario haya
    // escrito por equivocacion, limpiando el buffer de manera radical hasta encontrar el caracter de salto de linea '\n'.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Pausa la consola de Xcode de forma limpia, impidiendo que el menu se imprima encima de los reportes.
void esperarTecla() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.get(); // Bloquea la consola esperando a que el usuario pulse la tecla de retorno.
#ifdef _WIN32
    std::system("cls"); // Si el programa se compila en Windows, manda a llamar al comando tradicional de MS-DOS.
#else
    // Alternativa didactica: Desplaza verticalmente el texto viejo imprimiendo rafagas de saltos de linea.
    // Esto evita abrir subprocesos externos costosos.
    std::cout << "\n\n\n\n\n\n\n";
#endif
}

/* 🔗 INTERRELACION DIDACTICA DEL BLOQUE 3:
  Estas funciones actuan como el escudo protector del programa. Interceptan la comunicacion
  entre el teclado del usuario y el flujo principal del codigo, saneando los datos numericos
  antes de que sean transmitidos al `switch-case` del `main` para evitar bloqueos del software.
*/

// ============================================================================
// BLOQUE 4: PROGRAMA PRINCIPAL (CONTROLADOR CENTRAL DE LA INTERFAZ DE USUARIO)
// ============================================================================

// Coordina el ciclo de vida, captura las peticiones del operador y manda a
// llamar los metodos del backend.

int main() {
    Red red; // Instanciacion unica del objeto administrador de nuestra Red global.
    std::string archivoInicial; // Variable para almacenar la cadena de texto de la ruta del archivo.
    bool archivoCargado = false; // Flag o bandera logica de control secuencial.

    std::cout << "==================================================\n";
    std::cout << " BIENVENIDO AL SIMULADOR CENTRALIZADO DE REDES   \n";
    std::cout << "==================================================\n";
    
    // FLUJO GUIADO SECUENCIAL: El programa bloquea el inicio y no mostrara el menu principal
    // hasta que el operador cargue de forma exitosa una topologia base valida desde un archivo .txt.
    while (!archivoCargado) {
        std::cout << "Por favor, ingrese la ruta del archivo de topologia (.txt):\n-> ";
        std::getline(std::cin, archivoInicial); // std::getline lee la linea completa soportando espacios como "My Drive".
        
        std::ifstream test(archivoInicial); // Abrimos un flujo temporal de verificacion rapida.
        if (test.is_open()) {
            test.close(); // Cierra el flujo de prueba.
            red.cargarDesdeArchivo(archivoInicial); // Invoca al parser de la clase Red (Bloque 2) para poblar los mapas.
            std::cout << "\n[OK]: Topologia inicializada correctamente.\n";
            archivoCargado = true; // Activa la bandera rompiendo el bucle de bloqueo inicial.
            esperarTecla(); // Limpia la visualizacion de la consola de Xcode.
        } else {
            // Manejo de errores (Requerimiento 8 de la guia): Avisa al usuario que la ruta ingresada es invalida.
            std::cout << "\n[ERROR]: No se pudo abrir el archivo. Verifique la ruta.\n\n";
        }
    }

    int opcion; // Variable numerica para registrar la alternativa elegida del menu.
    do { // Bucle interactivo infinito controlado: Muestra las opciones una y otra vez hasta que seleccionemos '0'.
        std::cout << "\n--- MENU SIMULADOR RED DE ENRUTADORES ---\n"
                  << "1. Agregar enrutador\n"
                  << "2. Remover enrutador\n"
                  << "3. Agregar enlace\n"
                  << "4. Eliminar enlace\n"
                  << "5. Actualizar costo de enlace\n"
                  << "6. Cargar topologia desde archivo\n"
                  << "7. Mostrar tabla de enrutamiento\n"
                  << "8. Obtener costo entre dos enrutadores\n"
                  << "9. Obtener camino eficiente entre dos enrutadores\n"
                  << "0. Salir\n"
                  << "Seleccione una opcion: ";

        // FLUJO DE CONTROL DE SEGURIDAD: Intentamos extraer un entero desde la consola.
        if (!(std::cin >> opcion)) {
            std::cout << "Error: Ingrese un valor numerico.\n";
            limpiarBuffer(); // Invoca la limpieza del Bloque 3 si el usuario ingreso letras accidentales.
            esperarTecla();
            opcion = -1;     // Setea un valor invalido controlado para forzar el reinicio del bucle dinamicamente.
            continue;        // Salta directo al final del bucle do-while para evaluar la condicion sin colapsar.
        }
        
        limpiarBuffer(); // CRITICO: Purga de inmediato el caracter residual '\n' (el Enter) para no corromper los std::getline posteriores.

        // Variables temporales aisladas para capturar las peticiones especificas de cada caso de uso.
        std::string nombre, origen, destino, archivo;
        int costo;

        // EVALUADOR ESTRUCTURAL DE CASOS (SWITCH)
        switch (opcion) {
            case 1: // CASO DE EXPANSION: Adicion de un nuevo nodo aislado.
                std::cout << "Nombre del enrutador: ";
                std::getline(std::cin, nombre);
                red.agregarEnrutador(nombre); // Llama al backend global.
                std::cout << "Operacion realizada.\n";
                esperarTecla();
                break;
                
            case 2: // CASO DE CONVERGENCIA POR PERDIDA: Eliminacion fisica de un nodo de la topologia.
                std::cout << "Nombre del enrutador a remover: ";
                std::getline(std::cin, nombre);
                red.removerEnrutador(nombre); // Desencadena depuracion simetrica interna de aristas.
                std::cout << "Operacion realizada.\n";
                esperarTecla();
                break;
                
            case 3: // CASO DE CONEXION: Establece una autopista bidireccional nueva en la infraestructura.
                std::cout << "Origen: "; std::getline(std::cin, origen);
                std::cout << "Destino: "; std::getline(std::cin, destino);
                std::cout << "Costo: "; std::cin >> costo;
                red.agregarEnlace(origen, destino, costo); // Modifica mapas y recalcula Dijkstra globalmente.
                std::cout << "Operacion realizada.\n";
                limpiarBuffer(); // Sanea el buffer tras usar std::cin directo con tipos primitivos enteros.
                esperarTecla();
                break;
                
            case 4: // CASO DE DESCONEXION: Rompe de forma explicita una arista.
                std::cout << "Origen: "; std::getline(std::cin, origen);
                std::cout << "Destino: "; std::getline(std::cin, destino);
                red.eliminarEnlace(origen, destino);
                std::cout << "Operacion realizada.\n";
                esperarTecla();
                break;
                
            case 5: // CASO DE INGENIERIA DE TRAFICO: Optimizacion manual de costos.
                std::cout << "Origen: "; std::getline(std::cin, origen);
                std::cout << "Destino: "; std::getline(std::cin, destino);
                std::cout << "Nuevo Costo: "; std::cin >> costo;
                red.actualizarCosto(origen, destino, costo);
                std::cout << "Operacion realizada.\n";
                limpiarBuffer();
                esperarTecla();
                break;
                
            case 6: // CASO DE SOBREESCRITURA TOPOLOGICA: Carga una configuracion externa completamente nueva.
                std::cout << "Ruta completa (.txt): ";
                std::getline(std::cin, archivo);
                red.cargarDesdeArchivo(archivo); // Purga todo el estado de la red e inicializa de cero el sistema.
                std::cout << "Operacion realizada.\n";
                esperarTecla();
                break;
                
            case 7: // CASO DE INSPECCION TABULAR: Despliega el reporte consolidado de Dijkstra para un origen.
                std::cout << "Enrutador a consultar: ";
                std::getline(std::cin, nombre);
                red.mostrarTablaEnrutamiento(nombre); // Barre los mapas e imprime los reportes matematicos.
                esperarTecla();
                break;
                
            case 8: // CASO DE TRAFICO CUANTITATIVO: Extrae puntualmente la metrica optima de un enlace calculado.
                std::cout << "Origen: "; std::getline(std::cin, origen);
                std::cout << "Destino: "; std::getline(std::cin, destino);
                costo = red.obtenerCosto(origen, destino);
                // Si el costo es INF, informa al usuario mediante texto claro el estado de grafo no conexo.
                std::cout << "Costo: " << (costo == INF ? "INFINITO" : std::to_string(costo)) << "\n";
                esperarTecla();
                break;
                
            case 9: // CASO DE INGENIERIA DE RUTAS: Traza visualmente el camino fisico completo de un paquete.
                std::cout << "Origen: "; std::getline(std::cin, origen);
                std::cout << "Destino: "; std::getline(std::cin, destino);
                {
                    // Almacena localmente en la interfaz la respuesta vectorial de la clase Red.
                    auto camino = red.obtenerCamino(origen, destino);
                    if (camino.empty()) {
                        std::cout << "Ruta no disponible.\n"; // Escudo protector ante grafos no conexos.
                    } else {
                        std::cout << "Camino: ";
                        // Bucle clasico con incremento i++ para recorrer el contenedor STL e imprimir la trayectoria.
                        for (size_t i = 0; i < camino.size(); i++) {
                            std::cout << camino[i] << (i == camino.size() - 1 ? "" : " -> ");
                        }
                        std::cout << "\nCosto: " << red.obtenerCosto(origen, destino) << "\n";
                    }
                }
                esperarTecla();
                break;
                
            case 0: // CASO DE SALIDA DE LA APLICACION.
                std::cout << "Saliendo...\n";
                break;
                
            default: // MANEJO DE ROBUSTEZ: Intercepta opciones invalidas fuera del rango del menu.
                std::cout << "Opcion no valida.\n";
                esperarTecla();
                break;
        }
    } while (opcion != 0); // La evaluacion se ejecuta al final. El programa continuara vivo mientras opcion != 0.

    return 0; // Fin de la ejecucion. Devuelve un estado exitoso (cero) al sistema operativo.
}

// ============================================================================
// BLOQUE 5: BITACORA FORMAL DE VALIDACION Y AUDITORIA DE LA RED
// ============================================================================
/*
Ejercicio de validacion del MENU SIMULADOR RED DE ENRUTADORES:
 
 - Requisito Inicial de Arranque (Carga de Topologia Base):
   Al ejecutar el programa, se solicitara obligatoriamente la ruta del archivo inicial.
   Entrada en consola: /Users/zahir_llerena/My Drive/UdeA/Semestre_3/Informatica_II/Laboratorio_Git/Guia_4L/Code_L4/red_enrutadores.txt
   Comportamiento Esperado: Mensaje "[OK]: Topologia inicializada correctamente." El mapa global contendra los nodos {A, B, C, D}.
 
 - Opcion 7: Mostrar tabla de enrutamiento
   Entrada en consola: 7
   Siguiente entrada (Enrutador a consultar): A
   Comportamiento Esperado: La consola debe imprimir la tabla de adyacencias optimas calculada por Dijkstra para el nodo A.
   Metricas iniciales de convergencia: A->A (0), A->B (5), A->C (9), A->D (6).
  
 - Opcion 8: Obtener costo entre dos enrutadores
   Entrada en consola: 8
   Siguiente entrada (Origen): A
   Siguiente entrada (Destino): C
   Comportamiento Esperado: Costo minimo acumulado entre A y C es: 9.
   (Notese que descarta la ruta directa de costo 10 por no ser la mas eficiente).

 - Opcion 9: Obtener camino eficiente entre dos enrutadores
   Entrada en consola: 9
   Siguiente entrada (Origen): A
   Siguiente entrada (Destino): C
   Comportamiento Esperado:
   Ruta Optima Hallada: A -> B -> C (o la equivalente simetrica A -> D -> C)
   Costo Metrico Total: 9

 - Opcion 1: Agregar enrutador (Expansion de Red)
   Entrada en consola: 1
   Siguiente entrada (Nombre): E
   Comportamiento Esperado: Se anade el nodo E de forma aislada.
   Si ejecutas la Opcion 7 para consultar al nuevo nodo E, todos sus destinos (A, B, C)
   deben figurar con costo INF (Inalcanzable), validando de forma correcta el estado de
   grafo no conexo exigido en el requerimiento 8.
 
 - Opcion 3: Agregar enlace (Conectar Nuevo Nodo)
   Entrada en consola: 3
   Siguiente entrada (Origen): C
   Siguiente entrada (Destino): E
   Siguiente entrada (Costo): 4
   Comportamiento Esperado: El nodo E se integra al sistema. Al consultar el camino desde A hasta E
   (Opcion 9), el programa debe trazar la ruta a traves de la infraestructura existente hasta
   alcanzar el nuevo extremo. Ruta resultante: A -> B -> C -> E (Costo Total: 11).
  
 - Opcion 4: Eliminar enlace
   Simulemos una caida catastrofica del enlace entre B y D.
   Entrada en consola: 4
   Siguiente entrada (Origen): B
   Siguiente entrada (Destino): D
   Comportamiento Esperado: Al eliminarse la arista de costo 2, la red converge
   a una nueva topologia. Si consultas la tabla de enrutamiento de B (Opcion 7),
   el nuevo camino eficiente para llegar a D pasara a ser B->C->D con un costo total de 3+2=5.
 
 - Opcion 5: Actualizar costo de enlace (Optimizacion de Ruta)
   Vamos a simular una mejora en la infraestructura del enlace directo
   entre A y C, reduciendo su costo de 10 a 2.
  
   Entrada en consola: 5
   Siguiente entrada (Origen): A
   Siguiente entrada (Destino): C
   Siguiente entrada (Nuevo Costo): 2
  
   Comportamiento Esperado: Al consultar nuevamente la ruta hacia C con la Opcion 9
   (A a C), el sistema debe haber modificado la trayectoria.
   Nueva salida esperada: Ruta Optima Hallada: A -> C
   Nuevo costo esperado: 2
 
 - Opcion 2: Remover enrutador (Perdida de Nodo)
   Eliminemos por completo el enrutador D de la topologia global.
   Entrada en consola: 2
   Siguiente entrada (Enrutador a remover): D
   Comportamiento Esperado: El enrutador desaparece y se purgan todos los enlaces
   adyacentes a el (los enlaces hacia A, B y C). Las tablas de enrutamiento globales se
   actualizan automaticamente de forma centralizada.

 - Opcion 6: Cargar topologia desde archivo
   Entrada en consola: 6
   Siguiente entrada: /Users/zahir_llerena/My Drive/UdeA/Semestre_3/Informatica_II/Laboratorio_Git/Guia_4L/Code_L4/red_enrutadores.txt
  
   Comportamiento Esperado: El programa procesa los tokens, inicializa los objetos
   Enrutador en el mapa, calcula las rutas mediante la funcion dijkstra y muestra
   el mensaje: "Operacion realizada." restaurando la topologia inicial de la practica.
*/

// ============================================================================
// FIN DEL SCRIPT: SIMULADOR DE RED
// ============================================================================
