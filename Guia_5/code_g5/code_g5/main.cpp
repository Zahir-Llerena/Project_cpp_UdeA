// =====================================================================================
// Universidad de Antioquia
// Facultad de Ingenieria - Departamento de Telecomunicaciones -
// @authors: Zahir Llerena
// email: zahir.llerena@udea.edu.co
// =====================================================================================

#include <iostream>  // Define los objetos de flujo estandar de entrada/salida como std::cout. Sin esto, no podemos mostrar texto en consola.
#include <vector>    // Define la plantilla de clase std::vector, que es un arreglo dinamico capaz de crecer en memoria de forma automatica.
#include <cmath>     // Incluye funciones matematicas de la libreria estandar de C como std::sqrt (raiz cuadrada) y std::abs (valor absoluto).
#include <fstream>   // Define las clases de flujos para archivos como std::ofstream, necesaria para escribir datos en discos de almacenamiento.
#include <string>    // Define la clase std::string para la creacion, manipulacion y almacenamiento seguro de cadenas de texto.
#include <algorithm> // Incluye algoritmos genericos optimizados de la STL, como std::max y std::min.
#include <limits>    // Provee propiedades de los tipos numericos basicos (como saber cual es el entero mas grande posible).

// Valor numerico maximo para representar la ausencia de conexion o fronteras Infranqueables (Infinito)
const int INF = std::numeric_limits<int>::max();

// ============================================================================
// 1. CLASE MATEMATICA: Vector2D
// EXPLICACION: Una clase es una plantilla abstracta que define las propiedades (atributos)
// y los comportamientos (metodos) de un objeto del mundo real. En este caso, modela un vector espacial.
// ============================================================================
class Vector2D {
private: // Especificador de acceso restrictivo. Todo lo que este aqui abajo solo es visible dentro de esta clase.
    double x; // Variable de precision flotante doble (64 bits). Almacena la componente o proyeccion en el eje horizontal X.
    double y; // Variable de precision flotante doble (64 bits). Almacena la componente o proyeccion en el eje vertical Y.

public: // Especificador de acceso libre. Todo lo que este aqui abajo puede ser invocado desde cualquier otra parte del programa.

    // CONSTRUCTOR: Funcion especial que se ejecuta automaticamente al instanciar (crear) un objeto de esta clase.
    // Posee el mismo nombre de la clase y no tiene tipo de retorno. Los valores por defecto (= 0.0) permiten que si
    // creas un vector vacio (Vector2D v;), este nazca con coordenadas (0.0, 0.0).
    Vector2D(double _x = 0.0, double _y = 0.0) {
        x = _x; // Asigna el valor recibido en el parametro local '_x' al atributo privado 'x' de la instancia del objeto.
        y = _y; // Asigna el valor recibido en el parametro local '_y' al atributo privado 'y' de la instancia del objeto.
    } // Cierre del cuerpo del constructor.

    // METODOS DE ACCESO PUBLICOS (GETTERS): Permiten que objetos de otras clases lean el valor de los atributos privados.
    // Nota de Xcode: Se agrega 'const' al final para asegurar la compatibilidad con el paso de objetos constantes de Clang.
    double getX() const { return x; } // Retorna el valor actual de 'x' al punto del programa donde fue invocada la funcion.
    double getY() const { return y; } // Retorna el valor actual de 'y' al punto del programa donde fue invocada la funcion.

    // METODOS DE MODIFICACION PUBLICOS (SETTERS): Permiten que objetos de otras clases alteren los atributos privados bajo supervision.
    void setX(double _x) { x = _x; } // Modifica el valor del atributo privado 'x' reemplazandolo por el parametro '_x'. No retorna nada (void).
    void setY(double _y) { y = _y; } // Modifica el valor del atributo privado 'y' reemplazandolo por el parametro '_y'. No retorna nada (void).

    // METODO SUMAR: Aplica las leyes de la suma de vectores libres. Recibe un objeto Vector2D por valor (una copia llamada 'otro').
    Vector2D sumar(Vector2D otro) const {
        // Suma de forma independiente las componentes homologas: (X propia + X del otro) e (Y propia + Y del otro).
        // Crea, inicializa y retorna un nuevo objeto temporal Vector2D con el resultado del calculo matematico.
        return Vector2D(x + otro.getX(), y + otro.getY());
    }

    // METODO RESTAR: Resta componente a componente. Esencial en fisica para hallar el vector de posicion relativa entre dos cuerpos.
    Vector2D restar(Vector2D otro) const {
        // Resta la componente X del vector entrante a la X del vector actual, e igual con la componente Y.
        // Retorna un nuevo objeto Vector2D que representa el vector que va desde 'otro' hacia el vector actual.
        return Vector2D(x - otro.getX(), y - otro.getY());
    }

    // METODO MULTIPLICAR POR ESCALAR: Modifica la longitud (magnitud) de un vector sin alterar su orientacion angular.
    Vector2D multiplicarPorEscalar(double buscarEscalar) const {
        // Multiplica individualmente cada una de las componentes cartesianas del plano por el numero real ('buscarEscalar').
        // Retorna un objeto Vector2D escalado (indispensable para calcular vectores de fuerza, momento o desplazamientos).
        return Vector2D(x * buscarEscalar, y * buscarEscalar);
    }

    // METODO PRODUCTO PUNTO: Operacion algebraica lineal que toma dos vectores y devuelve un unico valor escalar (un numero).
    double productoPunto(Vector2D otro) const {
        // Multiplica las componentes X entre si, multiplica las componentes Y entre si, y luego suma ambos resultados.
        // Retorna el resultado escalar. Fisicamente sirve para saber si dos vectores son perpendiculares (producto punto = 0).
        return (x * otro.getX()) + (y * otro.getY());
    }

    // METODO CALCULAR MAGNITUD: Mide la longitud geometrica o "tamano" real del vector en el espacio euclideo.
    double calcularMagnitud() const {
        // Utiliza el Teorema de Pitagoras: la raiz cuadrada de la suma de los cuadrados de los componentes catetos.
        // std::sqrt toma el numero real y devuelve su raiz cuadrada exacta en precision double.
        return std::sqrt(x * x + y * y);
    }
}; // Cierre formal de la estructura de la clase Vector2D. El punto y coma (;) es estrictamente obligatorio al terminar una clase en C++.

// ============================================================================
// 2. FUNCIONES GEOMETRICAS AUXILIARES
// EXPLICACION: Son funciones globales puras. No forman parte de ninguna clase.
// Actuan como modulos matematicos independientes que reciben datos de entrada y retornan una respuesta.
// ============================================================================

// FUNCION GEOMETRICA GLOBAL: obtenerPuntoMasCercano
// OBJETIVO GENERAL: Determina las coordenadas del punto ubicado en el perimetro o
// interior del obstaculo cuadrado que esta a la menor distancia posible del centro
// de una particula circular. Es la clave para saber donde ocurrira el impacto.
Vector2D obtenerPuntoMasCercano(Vector2D posParticula, double minX, double maxX, double minY, double maxY) {

    // ------------------------------------------------------------------------
    // SENTENCIA 1: RESTRICCION HORIZONTAL (EJE X)
    // 1. posParticula.getX() extrae la coordenada X actual del centro del circulo.
    // 2. std::min(posParticula.getX(), maxX) asegura que si la particula se pasa del limite derecho, el valor se "congela" en maxX.
    // 3. std::max(minX, ...) toma el resultado anterior y asegura que si la particula se pasa del limite izquierdo, el valor se "congela" en minX.
    // OBJETIVO MATEMATICO: Realizar una sujecion logica ("clamp"). Fuerza a que la coordenada calculada de 'cercanoX'
    // quede obligatoriamente atrapada dentro del intervalo cerrado del obstaculo [minX, maxX].
    // ------------------------------------------------------------------------
    double cercanoX = std::max(minX, std::min(posParticula.getX(), maxX));

    // ------------------------------------------------------------------------
    // SENTENCIA 2: RESTRICCION VERTICAL (EJE Y)
    // 1. posParticula.getY() extrae la coordenada Y actual del centro del circulo.
    // 2. std::min(posParticula.getY(), maxY) evalua la vecindad respecto al limite superior del bloque cuadrado.
    // 3. std::max(minY, ...) evalua la vecindad respecto al limite inferior del bloque cuadrado.
    // OBJETIVO MATEMATICO: Duplicar de forma exacta el comportamiento de sujecion para la dimension vertical.
    // Fuerza a que la coordenada calculada de 'cercanoY' quede atrapada dentro del intervalo cerrado [minY, maxY].
    // ------------------------------------------------------------------------
    double cercanoY = std::max(minY, std::min(posParticula.getY(), maxY));

    // ------------------------------------------------------------------------
    // SENTENCIA 3: CONSTRUCCION Y RETORNO DEL VECTOR RESULTANTE
    // 1. Toma los dos escalares de tipo double ('cercanoX' y 'cercanoY') calculados en las sentencias previas.
    // 2. Llama explicitamente al constructor de la clase Vector2D pasandole ambos valores como argumentos.
    // OBJETIVO INFORMATICO: Instanciar en la memoria volatil un objeto temporal de tipo Vector2D que encapsula el punto
    // perimetral de impacto y enviarlo de regreso al motor de simulacion para que resuelva la fisica del rebote.
    // ------------------------------------------------------------------------
    return Vector2D(cercanoX, cercanoY);

} // Cierre formal de la funcion obtenerPuntoMasCercano. Las variables de precision doble 'cercanoX'
  // y 'cercanoY' se destruyen de la memoria RAM al salir de este ambito (Scope).

// FUNCION CALCULAR NORMAL DEL OBSTACULO:
// Determina vectorialmente hacia cual de las 4 direcciones del espacio (Izquierda,
// Derecha, Abajo o Arriba) debe salir rebotada la particula tras impactar un bloque cuadrado.
Vector2D calcularNormalDelObstaculo(Vector2D posParticula, double minX, double maxX, double minY, double maxY) {

    // SENTENCIA 1: std::abs calcula el valor absoluto (elimina el signo negativo).
    // Resta la coordenada X de la particula menos el limite izquierdo del cuadrado (minX).
    // OBJETIVO: Obtener la distancia geometrica escalar pura desde el centro de la esfera hasta la cara izquierda del obstaculo.
    double distIzquierda = std::abs(posParticula.getX() - minX);

    // SENTENCIA 2: Resta la coordenada X de la particula menos el limite derecho del cuadrado (maxX).
    // OBJETIVO: Obtener la distancia geometrica escalar pura desde el centro de la esfera hasta la cara derecha del obstaculo.
    double distDerecha = std::abs(posParticula.getX() - maxX);

    // SENTENCIA 3: Resta la coordenada Y de la particula menos el limite inferior del cuadrado (minY).
    // OBJETIVO: Obtener la distancia geometrica escalar pura desde el centro de la esfera hasta la cara inferior del obstaculo.
    double distAbajo = std::abs(posParticula.getY() - minY);

    // SENTENCIA 4: Resta la coordenada Y de la particula menos el limite superior del cuadrado (maxY).
    // OBJETIVO: Obtener la distancia geometrica escalar pura desde el centro de la esfera hasta la cara superior del obstaculo.
    double distArriba = std::abs(posParticula.getY() - maxY);

    // SENTENCIA 5: std::min analiza la lista envuelta en llaves {} que contiene las 4 distancias previamente calculadas.
    // OBJETIVO: Encontrar cual de las 4 caras esta fisicamente mas cerca del centro de la particula, lo que define el punto de impacto.
    double menorDistancia = std::min({distIzquierda, distDerecha, distAbajo, distArriba});

    // BLOQUE DE DECISION LOGICO-GEOMETRICA:
    // Compara la 'menorDistancia' hallada contra cada una de las distancias individuales
    // para retornar el vector director unitario (normal) perpendicular a dicha cara.

    // SENTENCIA 6: Evalua si la menor distancia corresponde a la cara izquierda.
    // OBJETIVO: Si es verdadero, el impacto fue en el lateral izquierdo. Retorna un Vector2D apuntando a la izquierda (-1 en X, 0 en Y).
    if (menorDistancia == distIzquierda) return Vector2D(-1, 0);

    // SENTENCIA 7: Evalua si la menor distancia corresponde a la cara derecha.
    // OBJETIVO: Si es verdadero, el impacto fue en el lateral derecho. Retorna un Vector2D apuntando a la derecha (1 en X, 0 en Y).
    if (menorDistancia == distDerecha) return Vector2D(1, 0);

    // SENTENCIA 8: Evalua si la menor distancia corresponde a la cara inferior.
    // OBJETIVO: Si es verdadero, el impacto fue en la base de abajo. Retorna un Vector2D apuntando hacia abajo (0 en X, -1 en Y).
    if (menorDistancia == distAbajo) return Vector2D(0, -1);

    // SENTENCIA 9: Sentencia de descarte final (Clausula else implícita).
    // OBJETIVO: Si no fue ninguna de las caras anteriores, por geometria fisica el impacto ocurrio en la cara superior.
    // Retorna un objeto Vector2D que actua como vector normal apuntando hacia arriba (0 en X, 1 en Y).
    return Vector2D(0, 1);
} // Cierre formal de la funcion. El ciclo de vida de las variables locales de distancia termina aqui en la pila de memoria (Stack).

// ============================================================================
// 3. ENTIDADES DEL MUNDO FISICO
// EXPLICACION: Clases destinadas a almacenar el estado del objeto e implementar
// las ecuaciones de movimiento que alteran sus propias variables cinematicas.
// ============================================================================
class Particle {
public: // Todos sus miembros seran accesibles por el motor controlador.
    int id;          // Atributo: Numero entero que sirve de identificador unico de la particula en los ficheros de salida.
    Vector2D pos;    // Atributo: Objeto Vector2D que almacena las coordenadas de posicion (x, y) en el plano cartesiano.
    Vector2D vel;    // Atributo: Objeto Vector2D que almacena las componentes vectoriales de la velocidad (vx, vy).
    double mass;     // Atributo: Magnitud escalar que representa la masa (inercia) de la particula para la conservacion del momento.
    double radius;   // Atributo: Magnitud escalar del radio de la esfera para evaluar puntos de contacto perimetrales.
    bool active;     // Atributo de control: Bandera booleana (true/false) que define si el cuerpo esta interactuando o si ya fue absorbido.

    // CONSTRUCTOR DE PARTICULA: Inicializa todas las propiedades del cuerpo al momento de su creacion en la memoria.
    Particle(int _id, Vector2D _pos, Vector2D _vel, double _mass, double _radius) {
        id = _id;         // Copia el parametro entero '_id' en el atributo de clase 'id'.
        pos = _pos;       // Copia el estado del vector posicion recibido en el atributo de clase 'pos'.
        vel = _vel;       // Copia el estado del vector velocidad recibido en el atributo de clase 'vel'.
        mass = _mass;     // Copia el parametro decimal de masa en el atributo de clase 'mass'.
        radius = _radius; // Copia el parametro decimal de radio en el atributo de clase 'radius'.
        active = true;    // Inicializa la bandera de existencia en verdadero de forma automatica.
    } // Cierre del cuerpo del constructor de Particle.

    // METODO DE INTEGRACION NUMERICA DISCRETA: Desplaza la particula en trayectorias libres rectilineas.
    void updatePosition(double dt) { // Recibe la variable diferencial de tiempo 'dt' (paso de tiempo). No retorna datos (void).
        if (!active) return; // Clausula de guarda: Si la particula fue desactivada (fusion), sale de la funcion inmediatamente sin gastar CPU.

        // INTERRELACION DE CLASES: Invocacion secuencial de operaciones internas de la clase Vector2D.
        // Calcula el vector de desplazamiento multiplicando la velocidad vectorial por el escalar del tiempo diferencial: Delta_r = v * dt
        Vector2D desplazamiento = vel.multiplicarPorEscalar(dt);
        // Modifica la posicion actual sumandole el desplazamiento calculado: r_nuevo = r_actual + Delta_r
        pos = pos.sumar(desplazamiento);
    } // Cierre del metodo updatePosition.
}; // Cierre formal de la estructura de la clase Particle. Requiere punto y coma (;).

class Obstacle { // Inicio de la definicion de la clase Obstacle.
public: // Miembros accesibles para procesos analiticos externos.
    // Atributos de tipo double que almacenan los 4 limites espaciales absolutos de un bloque cuadrado (Eje X y Eje Y).
    double minX, maxX, minY, maxY;

    // CONSTRUCTOR DE OBSTACULO: Calcula la geometria de la caja de colision a partir de un centro y el tamano de sus lados.
    Obstacle(Vector2D centro, double longitudLado) {
        double mitadLado = longitudLado / 2.0; // Divide el tamano de la arista entre dos para obtener la distancia del centro al perimetro.
        // INTERRELACION DE CLASES: Extrae las componentes privadas del vector centro usando los getters publicos de Vector2D.
        minX = centro.getX() - mitadLado; // Calcula el limite izquierdo restando la mitad de la arista a la coordenada de centro X.
        maxX = centro.getX() + mitadLado; // Calcula el limite derecho sumando la mitad de la arista a la coordenada de centro X.
        minY = centro.getY() - mitadLado; // Calcula el limite inferior restando la mitad de la arista a la coordenada de centro Y.
        maxY = centro.getY() + mitadLado; // Calcula el limite superior sumando la mitad de la arista a la coordenada de centro Y.
    } // Cierre del constructor de Obstacle.
}; // Cierre formal de la estructura de la clase Obstacle. Requiere punto y coma (;).

// ============================================================================
// 4. MOTOR DE SIMULACION Y TRATAMIENTO DE EVENTOS
// EXPLICACION: Esta clase implementa el patron controlador. No representa un objeto
// tangible, sino el "universo" logico donde habitan los elementos y se ejecutan las leyes de colision.
// ============================================================================
class CollisionsSimulation { // Inicio de la definicion de la clase controladora.
private: // Los parametros fisicos de configuracion interna no pueden ser alterados por el main.
    double boxWidth;          // Atributo: Ancho fisico total de la caja del escenario de pruebas.
    double boxHeight;         // Atributo: Alto fisico total de la caja del escenario de pruebas.
    double dt;                // Atributo: Variable delta de tiempo. Determina la velocidad y precision del reloj discreto.
    double restitutionCoef;   // Atributo: Coeficiente de elasticidad 'e' para la amortiguacion del vector en obstaculos.

    // USO DE PLANTILLAS DE LA LIBRERIA ESTANDAR (STL):
    // std::vector<Tipo> crea arreglos dinamicos anidados en memoria que manejan de forma automatica punteros internos.
    std::vector<Particle> particles; // Contenedor dinamico que almacena todos los objetos de tipo Particle instanciados.
    std::vector<Obstacle> obstacles; // Contenedor dinamico que almacena los obstaculos fijos del escenario.
    std::ofstream outputFile;        // Objeto de flujo para gestionar y escribir flujos de texto en un archivo plano en disco.

    // REQUERIMIENTO 1: Colisíon perfectamente elastica con los limites perimetrales externos de la caja (e = 1.0).
    // Recibe el objeto Particle mediante un pasaje por REFERENCIA (&). Esto es crucial: no envia una copia,
    // envia la direccion de memoria original de la particula, permitiendo que las modificaciones alteren el objeto real.
    void checkWallCollisions(Particle& p) {

        // --- EVALUACION DE LAS PAREDES VERTICALES ---
        // Evalua si el perimetro izquierdo del circulo (Posicion X - Radio) perforo el limite izquierdo de la caja (0.0).
        if (p.pos.getX() - p.radius <= 0.0) {
            p.pos.setX(p.radius);       // Correccion geometrica: Ubica a la particula tocando exactamente el borde para evitar atrapamientos numericos.
            p.vel.setX(-p.vel.getX());  // Rebote elastico puro: Invierte el signo de la velocidad en el eje horizontal (vx = -vx).
        }
        // Evalua si el perimetro derecho del circulo (Posicion X + Radio) perforo la frontera derecha de la caja (boxWidth).
        else if (p.pos.getX() + p.radius >= boxWidth) {
            p.pos.setX(boxWidth - p.radius); // Correccion posicional: Empuja la particula hacia adentro restando el radio al limite del muro.
            p.vel.setX(-p.vel.getX());       // Invierte la componente de velocidad horizontal para iniciar el viaje en sentido contrario.
        } // Fin del bloque condicional de muros laterales.

        // --- EVALUACION DE LAS PAREDES HORIZONTALES ---
        // Evalua si el perimetro inferior del circulo (Posicion Y - Radio) perforo el suelo del escenario (0.0).
        if (p.pos.getY() - p.radius <= 0.0) {
            p.pos.setY(p.radius);       // Desplaza verticalmente el objeto asentandolo de forma exacta sobre el piso cartesiano.
            p.vel.setY(-p.vel.getY());  // Invierte de forma instantanea la velocidad vertical (vy = -vy).
        }
        // Evalua si el perimetro superior del circulo (Posicion Y + Radio) perforo el techo del escenario (boxHeight).
        else if (p.pos.getY() + p.radius >= boxHeight) {
            p.pos.setY(boxHeight - p.radius); // Reposiciona la esfera en el borde superior exacto restando su radio a la altura total.
            p.vel.setY(-p.vel.getY());        // Invierte la componente de velocidad vertical reflejando el vector hacia abajo.
        } // Fin del bloque condicional de muros de piso y techo.
    } // Cierre del metodo checkWallCollisions.

    // REQUERIMIENTO 2: Colision inelastica con los 4 bloques cuadrados estaticos de la guia.
    void checkObstacleCollisions(Particle& p) {
        // BUCLE INDEXADO FOR: Recorre secuencialmente la lista de obstaculos.
        // Nota de Xcode: Se corrige 'int' a 'size_t' para eliminar la advertencia de comparacion con y sin signo (sign-compare).
        for (size_t i = 0; i < obstacles.size(); i++) {
            Obstacle obs = obstacles[i]; // Extrae una copia del obstaculo indexado en la posicion 'i' y lo guarda en la variable local 'obs'.

            // CONEXION ENTRE MODULOS: Envia la posicion de la particula y los limites del obstaculo actual a la funcion geometrica global.
            Vector2D puntoCercano = obtenerPuntoMasCercano(p.pos, obs.minX, obs.maxX, obs.minY, obs.maxY);
            // Calcula el vector de separacion restando la posicion de la frontera menos la posicion del centro de la particula.
            Vector2D vectorDistancia = p.pos.restar(puntoCercano);
            // Calcula la longitud lineal euclidea del vector de separacion (la distancia real en unidades).
            double distancia = vectorDistancia.calcularMagnitud();

            // DETERMINACION DE INTRUSION: Si la distancia al punto perimetral es menor al radio del circulo, hay solapamiento fisico.
            if (distancia < p.radius) {
                Vector2D normal; // Instancia un objeto Vector2D vacio destinado a almacenar la direccion normal de impacto.

                // CONTROL DE SINGULARIDAD: Si la distancia es mayor a una tolerancia minima, normaliza el vector de distancia de forma segura.
                if (distancia > 0.0001) {
                    // Normalizacion: Divide el vector por su magnitud multiplicandolo por el inverso (1 / distancia) para volverlo unitario (longitud = 1).
                    normal = vectorDistancia.multiplicarPorEscalar(1.0 / distancia);
                } else {
                    // Si penetro completamente por error numerico, invoca la funcion analitica basada en distancias relativas a las caras.
                    normal = calcularNormalDelObstaculo(p.pos, obs.minX, obs.maxX, obs.minY, obs.maxY);
                } // Fin del condicional de normalizacion.

                // EXTRAER COMPONENTE ORTOGONAL: Proyecta la velocidad sobre el vector normal mediante el Producto Punto.
                double vNormal = p.vel.productoPunto(normal);

                // FILTRO DE TRATAMIENTO: Solo se ejecuta el rebote si el objeto se mueve hacia el obstaculo (velocidad normal negativa).
                if (vNormal < 0) {
                    // Aisla la porcion de velocidad perpendicular al plano de impacto multiplicando la direccion por la magnitud escalar.
                    Vector2D velNormal = normal.multiplicarPorEscalar(vNormal);
                    // Resta la velocidad normal a la velocidad total para aislar la componente tangencial paralela: v_tangencial = v - v_normal
                    Vector2D velTangential = p.vel.restar(velNormal);

                    // APLICACION DEL COEFICIENTE 'e' (Formula de la Guia): Modifica solo la porcion perpendicular multiplicandola por 'restitutionCoef'.
                    p.vel = velTangential.restar(velNormal.multiplicarPorEscalar(restitutionCoef));
                    // Correccion posicional real: Reposiciona el cuerpo en la frontera exacta del obstaculo para evitar rebotes infinitos fantasmas.
                    p.pos = puntoCercano.sumar(normal.multiplicarPorEscalar(p.radius));
                } // Fin del filtro de vector de aproximacion.
            } // Fin del condicional de impacto con el obstaculo actual.
        } // Fin del bucle for que recorre los obstaculos.
    } // Cierre del metodo checkObstacleCollisions.

    // REQUERIMIENTO 3: Colision completamente inelastica (Choque mutuo entre dos particulas con acoplamiento de masa).
    // Recibe los indices numericos de las dos particulas bajo analisis (i, j) para manipularlas por referencia dentro del vector dinamico.
    // Nota de Xcode: Se corrige la firma a 'size_t' para consistencia con los indices del vector dinámico y evitar warnings.
    void checkParticleCollisions(size_t i, size_t j, double currentTime) {
        Particle& p1 = particles[i]; // Crea una referencia directa llamada 'p1' apuntando a la particula de la posicion 'i'.
        Particle& p2 = particles[j]; // Crea una referencia directa llamada 'p2' apuntando a la particula de la posicion 'j'.

        // CONTROL DE EXISTENCIA: Si alguna de las dos particulas ya fue absorbida en ciclos anteriores, se cancela la evaluacion.
        if (!p1.active || !p2.active) return;

        // Calcula el vector de separacion espacial entre los dos centros de masa: r_distancia = pos2 - pos1
        Vector2D vectorDistancia = p2.pos.restar(p1.pos);
        // Aplica Pitagoras para calcular la distancia geometrica lineal entre los dos centros.
        double distancia = vectorDistancia.calcularMagnitud();
        // Suma los radios de ambos circulos para determinar la distancia limite de contacto fisico.
        double sumaRadios = p1.radius + p2.radius;

        // DETECCION DE CONTACTO MUTUO: Si la distancia real es menor o igual a la suma de los radios, los cuerpos se tocan.
        if (distancia <= sumaRadios) {
            double m1 = p1.mass;     // Resguarda la masa escalar de la particula 1 en una variable local 'm1'.
            double m2 = p2.mass;     // Resguarda la masa escalar de la particula 2 en una variable local 'm2'.
            double mTotal = m1 + m2; // Conservacion de la masa compuesta: La masa final (M) es estrictamente la suma de ambas.

            // FORMULA DE CONSERVACION DEL MOMENTO LINEAL: v' = (m1*v1 + m2*v2) / (m1+m2)
            Vector2D m1_v1 = p1.vel.multiplicarPorEscalar(m1); // Calcula el vector de momento lineal inicial del cuerpo 1.
            Vector2D m2_v2 = p2.vel.multiplicarPorEscalar(m2); // Calcula el vector de momento lineal inicial del cuerpo 2.
            // Suma ambos vectores de momento y divide el vector resultante multiplicandolo por el inverso de la masa total combinada.
            Vector2D nuevaVelocidad = (m1_v1.sumar(m2_v2)).multiplicarPorEscalar(1.0 / mTotal);

            // CORRECCION GEOMETRICA DE TRASLAPE: Evita que el nuevo cuerpo combinado quede enganchado numericamente.
            double overlap = sumaRadios - distancia; // Calcula los componentes numericos exactos de la penetracion.
            // Crea un vector unitario de direccion de colision evitando divisiones por cero.
            Vector2D normalDireccion = (distancia > 0.0) ? vectorDistancia.multiplicarPorEscalar(1.0 / distancia) : Vector2D(1.0, 0.0);
            // Reposiciona el centro del nuevo cuerpo unificado basandose en las proporciones de masa relativas.
            Vector2D posCorregida = p1.pos.restar(normalDireccion.multiplicarPorEscalar(overlap * (m2 / mTotal)));

            // CONSERVACION DEL VOLUMEN EN EL PLANO (Ley de Areas): El area final es la suma de las areas de los circulos incidentes.
            // Despejando pi: r_nuevo = sqrt(r1^2 + r2^2)
            double nuevoRadio = std::sqrt((p1.radius * p1.radius) + (p2.radius * p2.radius));

            // VOLCADO ANALITICO DE LOGS: Escribe de forma inmediata el reporte del evento en el canal del flujo del archivo.
            // Utiliza operadores de insercion << y saltos de linea con el caracter de control escape '\n'.
            outputFile << "[COLISION FUSION],Tiempo=" << currentTime
                       << ",ID_Absorbente=" << p1.id << ",Masa_m1=" << m1
                       << ",ID_Absorbida=" << p2.id << ",Masa_m2=" << m2
                       << ",Nueva_Masa_M=" << mTotal << "\n";

            // MUTACION DE PROPIEDADES: Transferimos todas las propiedades compuestas fisicas calculadas a la particula 'p1'.
            p1.pos = posCorregida;     // Reemplaza la posicion vieja por la posicion del nuevo centro de masa unificado.
            p1.vel = nuevaVelocidad;   // Reemplaza la velocidad por la velocidad compuesta que conserva el momento lineal total.
            p1.mass = mTotal;          // Asigna la nueva masa combinada consolidada (M).
            p1.radius = nuevoRadio;    // Modifica su tamano perimetral asignandole el nuevo radio proporcional al area.

            // DESACTIVACION LOGICA DEL SEGUNDO CUERPO: Absorcion completa.
            p2.active = false; // Al poner la bandera en false, 'p2' se vuelve invisible para el resto de los bucles fisicos de movimiento.
        } // Fin del condicional de contacto inter-particula.
    } // Cierre del metodo checkParticleCollisions.

public: // Interfaz de control accesible desde el main para inicializar y correr el experimento.

    // CONSTRUCTOR DEL MOTOR: Recibe las dimensiones de la caja, el tamano del incremento de tiempo y el coeficiente de rebote.
    CollisionsSimulation(double ancho, double alto, double pasoTiempo, double e) {
        boxWidth = ancho;          // Inicializa el ancho del escenario con el valor pasado en el parametro 'ancho'.
        boxHeight = alto;          // Inicializa el alto del escenario con el valor pasado en el parametro 'alto'.
        dt = pasoTiempo;           // Configura el tamano del paso del reloj discreto (step temporal).
        restitutionCoef = e;       // Configura el factor de amortiguacion para los impactos contra los obstaculos.

        // Define una cadena de texto estandar (string) que contiene la ruta absoluta fisica de almacenamiento local.
        std::string path = "/Users/zahir_llerena/My Drive/UdeA/Semestre_3/Informatica_II/Laboratorio_Git/Guia_5L/simulation_output.txt";
        outputFile.open(path);     // Invoca el metodo publico .open() de std::ofstream para crear y enlazar el archivo de texto en el disco.
    } // Cierre del constructor del motor.

    // DESTRUCTOR DE CLASE: Se ejecuta de forma automatica en el momento exacto en que el objeto 'sim' sale del ambito del main.
    ~CollisionsSimulation() {
        if (outputFile.is_open()) { // Verifica mediante una funcion booleana si el canal de flujo con el archivo en disco sigue abierto.
            outputFile.close();     // Cierra de forma segura el archivo liberando los buferes y los recursos de escritura del sistema operativo macOS.
        } // Fin del condicional de verificacion de flujo de archivo.
    } // Cierre del destructor de clase.

    // METODO ADD PARTICLE: Crea un objeto intermedio del tipo Particle y lo agrega a la lista de control dinamico.
    void addParticle(Vector2D pos, Vector2D vel, double mass, double radius) {
        // Determina el ID secuencial calculando el tamano actual de la lista con .size() y sumandole 1 (Garantiza IDs: 1, 2, 3, 4...).
        int nuevoId = (int)particles.size() + 1;
        // Instancia un objeto temporal de la clase Particle llamando a su constructor con las variables recibidas.
        Particle p(nuevoId, pos, vel, mass, radius);
        // .push_back es una funcion miembro de std::vector. Copia el objeto 'p' y lo inserta fisicamente al final del arreglo dinamico.
        particles.push_back(p);
    } // Cierre del metodo addParticle.

    // METODO ADD OBSTACLE: Valida las restricciones fisicas e inyecta un bloque cuadrado en la simulacion.
    void addObstacle(Vector2D centro, double longitudLado) {
        if (obstacles.size() < 4) { // Restriccion de diseno: Evalua que la lista tenga menos de 4 elementos para cumplir con la guia de laboratorio.
            Obstacle obs(centro, longitudLado); // Instancia un objeto de tipo Obstacle pasando el centro y el tamano de arista recibido.
            obstacles.push_back(obs);           // Inserta el obstaculo al final de la coleccion dinamica en memoria.
        } // Fin del condicional de restriccion de cantidad.
    } // Cierre del metodo addObstacle.

    // EL BUCLE DE CONTROL DE SIMULACION (INTEGRADOR DE TIEMPO DISCRETO): Ejecuta el avance continuo de la linea de tiempo.
    void runSimulation(double tiempoTotal) {
        double currentTime = 0.0; // Inicializa la variable de control de tiempo cronologico del universo fisico en cero.
        outputFile << "Tiempo,ID,PosX,PosY,Masa,Activa\n"; // Inserta la primera linea del archivo (Encabezado CSV) para el DataFrame de Pandas.

        // BUCLE PRINCIPAL DE TIEMPO: Repite todas las instrucciones secuenciales mientras el tiempo actual sea menor al tiempo limite.
        // Nota de Xcode: Corregido el operador accidental '<<=' por el comparador '<=' para evitar bucles infinitos y warnings de Clang.
        while (currentTime <= tiempoTotal) {

            // --- PASO 1: VOLCADO DE TRAZAS CINEMATICAS ---
            // Bucle clasico for que itera a traves de todos los indices de la lista de particulas.
            for (size_t i = 0; i < particles.size(); i++) {
                Particle p = particles[i]; // Crea una copia local de la particula actual en la variable 'p'.
                // Escribe en una linea del archivo las magnitudes cinematicas separadas estrictamente por comas (,).
                // Al final usa la condicion ternaria (p.active ? 1 : 0) para escribir un numero entero binario (1=VIVA, 0=ABSORBIDA).
                outputFile << currentTime << "," << p.id << "," << p.pos.getX() << ","
                           << p.pos.getY() << "," << p.mass << "," << (p.active ? 1 : 0) << "\n";
            } // Fin del bucle for de volcado de datos.

            // --- PASO 2: ACTUALIZACION CINEMATICA LIBRE ---
            // Recorre todas las particulas y ejecuta su metodo interno de movimiento independiente pasandole el diferencial temporal dt.
            for (size_t i = 0; i < particles.size(); i++) {
                particles[i].updatePosition(dt);
            } // Fin del bucle for de movimiento libre.

            // --- PASO 3: TRATAMIENTO DE PAREDES DE LA CAJA ---
            // Envia cada particula de la lista al metodo privado encargado de evaluar y resolver los rebotes perfectamente elasticos.
            for (size_t i = 0; i < particles.size(); i++) {
                checkWallCollisions(particles[i]);
            } // Fin del bucle for de colisiones con las paredes.

            // --- PASO 4: TRATAMIENTO DE OBSTACULOS CUADRADOS ---
            // Evalua los perimetros contra los 4 bloques fijos amortiguando los vectores mediante el coeficiente de restitucion.
            for (size_t i = 0; i < particles.size(); i++) {
                checkObstacleCollisions(particles[i]);
            } // Fin del bucle for de colisiones con obstaculos fijos.

            // --- PASO 5: TRATAMIENTO DE IMPACTOS DE MUTUO ACOPLAMIENTO (PARTICULA-PARTICULA) ---
            // ALGORITMO COMBINATORIO SIN REPETICION: Estructura dos bucles for anidados de forma inteligente.
            // El bucle externo 'i' va desde la posicion 0 hasta el final. El bucle interno 'j' inicia siempre una posicion adelante (i + 1).
            // Esto asegura que evaluemos la colision del par (Particula 1 con Partícula 2), pero jamas perdamos ciclos evaluando (2 con 1).
            for (size_t i = 0; i < particles.size(); i++) {
                for (size_t j = i + 1; j < particles.size(); j++) {
                    checkParticleCollisions(i, j, currentTime); // Envia los indices del par al metodo de fusion inelastica.
                } // Fin del bucle interno j.
            } // Fin del bucle externo i.

            currentTime += dt; // INCREMENTO DISCRETO DEL TIEMPO: Avanza el reloj sumandole el tamano del paso temporal 'dt'.
        } // Fin del bucle condicional while. La simulacion ha terminado.

        // Imprime en la consola el aviso informativo final utilizando el objeto de flujo de salida estandar de caracteres.
        std::cout << "Simulación finalizada. Archivo escrito en la carpeta directorio de Zahir Llerena.\n";
    } // Cierre del metodo runSimulation.
}; // Cierre formal de la estructura de la clase CollisionsSimulation. Requiere punto y coma (;).

// ============================================================================
// 5. PROGRAMA PRINCIPAL
// EXPLICACION: El punto de entrada obligatorio e indispensable para la ejecucion de cualquier software en C++.
// Aqui instanciamos los objetos reales a partir de los moldes abstractos definidos arriba.
// ============================================================================
int main() { // Inicio de la funcion main. Retorna un numero entero al sistema operativo.
    // Instancia el objeto controlador principal del universo fisico llamado 'sim'.
    // Configura los parametros: Caja de 100.0x100.0 unidades, paso temporal dt = 0.01 segundos, y e = 0.75 para obstaculos fijos.
    CollisionsSimulation sim(100.0, 100.0, 0.01, 0.75);

    // INICIALIZACION DE ENTORNO: Invocamos el metodo addObstacle de nuestro objeto 'sim'.
    // Anade de forma exacta los 4 bloques cuadrados simetricos requeridos en la practica pasandoles sus centros vectoriales y el tamano de lado.
    sim.addObstacle(Vector2D(30.0, 30.0), 10.0); // Obstaculo cuadrante inferior izquierdo.
    sim.addObstacle(Vector2D(70.0, 30.0), 10.0); // Obstaculo cuadrante inferior derecho.
    sim.addObstacle(Vector2D(30.0, 70.0), 10.0); // Obstaculo cuadrante superior izquierdo.
    sim.addObstacle(Vector2D(70.0, 70.0), 10.0); // Obstaculo cuadrante superior derecho.

    // INICIALIZACION DE PARTICULAS: Registramos 4 cuerpos concurrentes simultaneos con trayectorias incidentes cruzadas.
    // Parametros de la llamada: Vector2D(Posicion Inicial), Vector2D(Velocidad Inicial), Masa Escalar, Radio Geometrico.
    sim.addParticle(Vector2D(10.0, 10.0), Vector2D(15.0, 12.0),  2.0, 2.5); // Particula 1: Nace abajo a la izquierda viajando hacia arriba-derecha.
    sim.addParticle(Vector2D(90.0, 10.0), Vector2D(-12.0, 14.0), 3.0, 3.0); // Particula 2: Nace abajo a la derecha viajando hacia arriba-izquierda.
    sim.addParticle(Vector2D(10.0, 90.0), Vector2D(11.0, -15.0), 1.5, 2.0); // Particula 3: Nace arriba a la izquierda viajando hacia abajo-derecha.
    sim.addParticle(Vector2D(90.0, 90.0), Vector2D(-14.0, -11.0), 2.5, 2.8); // Particula 4: Nace arriba a la derecha viajando hacia abajo-izquierda.

    // DISPARO DEL MOTOR: Invoca el bucle de control de la simulacion.
    // El integrador procesara y escribira paso a paso todos los eventos fisicos durante un tiempo continuo de 15.0 unidades de segundo.
    sim.runSimulation(15.0);

    return 0; // Envia el codigo de retorno estandar cero al sistema operativo, indicando que el programa se ejecuto y cerro sin errores.
} // Cierre definitivo de la funcion main y del archivo de codigo fuente de la Practica 5.

// Version corregida y optimizada del algoritmo de simulacion de colisiones por Zahir Llerena
// ============================================================================
// FIN DEL SCRIPT: MOTOR DE COLISIONES
// ============================================================================
