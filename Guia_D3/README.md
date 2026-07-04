# Motor de Videojuego 2D: Invasión Alien con Qt6 y Graphics View Framework

## Universidad de Antioquia
**Facultad de Ingenieria - Departamento de Telecomunicaciones**
* **Asignatura:** Informatica II (Desafio Final - Proyecto de Semestre)
* **Autor:** Zahir Llerena
* **Email:** zahir.llerena@udea.edu.co

---

## Descripcion del Proyecto

Este repositorio contiene la implementacion en **C++** de un **Motor de Videojuego Arcadade de Disparos en 2D (Invasión Alien)**, desarrollado sobre el framework industrial **Qt6**. En lugar de utilizar bucles de renderizado basados en fuerza bruta que saturan la CPU, el core del juego emplea el **Graphics View Framework** de Qt. Esta arquitectura optimiza el procesamiento grafico mediante un arbol de indexacion espacial de los objetos en escena, logrando una tasa estable de refresco de 60 FPS con bajo consumo de hardware.

La aplicacion modela leyes cinemáticas vectoriales directas para proyectiles, implementa algoritmos dinamicos de deteccion de colisiones por vecindad geometrica, gestiona maquinas de estados sincronas y cuenta con escalabilidad de dificultad automatica en base a escalas exponenciales de velocidad y puntaje.

---

## Arquitectura de Software y Framework de Renderizado

El diseno arquitectonico del software separa estrictamente los parametros de configuracion, el estado de la partida, los componentes de la interfaz de usuario (UI) y las entidades logicas del juego:

### 1. El Entorno de Renderizado Grafico (Qt Graphics View)
* **`QGraphicsScene` (La Escena):** Actua como el contenedor abstracto bidimensional en memoria. Almacena, gestiona y rastrea la ubicacion fisica de todos los elementos graficos (`QGraphicsItem`).
* **`QGraphicsView` (El Visor / Camara):** Funciona como la compuerta de visualizacion que renderiza la escena. Desactiva las barras de desplazamiento perimetrales para asegurar un confinamiento de pantalla estricto de 1200 x 800 pixeles.
* **`QTimer` (El Reloj del Sistema):** Actua como el corazon de la simulacion cronologica, gatillando de forma asincrona la señal de *timeout* cada 16 milisegundos para ejecutar el lazo principal (*Game Loop*).

### 2. Modulos Basicos y Maquina de Estados
* **`Settings`:** Centraliza los atributos estaticos y dinamicos del sistema (dimensiones, limites de municion, colores vectoriales). Implementa el metodo `aumentar_velocidad()`, el cual multiplica los factores fisicos de transporte lineal por una escala exponencial (`speedup_scale = 1.25`) cada vez que el usuario limpia el escenario.
* **`GameStats`:** Actua como la bitacora de estado logico de la partida (puntuacion actual, record historico *Hi-Score*, nivel de dificultad y control de bandera de juego activo).
* **`Scoreboard`:** Interfaz de datos sincronizada que hereda de `QGraphicsTextItem`. Recibe punteros directos a las estadisticas y redibuja en tiempo real las cadenas informativas en la escena mediante fuentes tipograficas vectoriales.

### 3. Jerarquia de Entidades del Juego (`QGraphicsItem`)
* **`Ship` (`QGraphicsPixmapItem`):** Entidad controlada por el usuario. Interpreta eventos del teclado para alterar variables booleanas de movimiento y se desplaza horizontalmente aplicando traslaciones discretas (`moveBy`), restringiendo su posicion de manera estricta dentro del *bounding box* de la pantalla.
* **`Bullet` (`QGraphicsRectItem`):** Proyectiles basicos de 3x15 pixeles. Nacen dinamicamente en el ancla central superior de la nave y ascienden verticalmente reduciendo su coordenada Y de acuerdo a la magnitud escalar `bullet_speed`.
* **`Alien` (`QGraphicsPixmapItem`):** Elemento invasor de la flota. Posee metodos predictivos como `tocar_limites()` para evaluar colisiones de frontera con los extremos laterales del escenario.

---

## Logica del Game Loop y Tratamiento de Eventos
La ejecucion interactiva y las transiciones del motor se orquestan bajo metodos protegidos y ranuras privadas (*slots*).
