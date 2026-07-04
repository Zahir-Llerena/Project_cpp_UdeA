# Bitwise Tetris Engine: Motor de Videojuego Orientado a Manipulacion de Bits

## Universidad de Antioquia
**Facultad de Ingenieria - Departamento de Telecomunicaciones**
* **Asignatura:** Informatica II (Guia de Laboratorio D1)
* **Autor:** Zahir Llerena
* **Email:** zahir.llerena@udea.edu.co

---

## Descripcion del Proyecto

Este proyecto consiste en el diseno e implementacion de un **Motor Basico de Tetris (Game Engine)** desarrollado en **C++**, cuyo nucleo logico opera mediante la **manipulacion de bits masiva (*Bitwise Operations*)**. A diferencia de las implementaciones convencionales que utilizan matrices bidimensionales de enteros o booleanos para representar el tablero de juego (lo que consume un exceso de recursos en la CPU y memoria), este motor optimiza el rendimiento abstrayendo cada fila horizontal del tablero a un unico entero sin signo de 64 bits (`uint64_t`).

El software cuenta con configuracion dinamica de dimensiones por parte del usuario, un generador de aleatoriedad formal basado en el motor Mersenne Twister y un sistema de renderizado por consola adaptado para terminales Unix (macOS/Linux) y Windows.

---

## Estructura de Datos y Arquitectura de Memoria

El diseno del motor se fundamenta en la optimizacion del uso del hardware mediante dos estructuras principales:

### 1. Definicion de Tipo (`board_t`)
Mediante la instruccion `typedef uint64_t board_t`, se crea un alias de alta claridad semantica. Cada fila del tablero es un entero positivo de 64 bits, lo que actua como un vector de 64 interruptores binarios alineados horizontalmente:
* **0 (Bit apagado):** Celda vacia o espacio de transito (`.`).
* **1 (Bit encendido):** Celda ocupada por un bloque estatico o pieza activa (`#`).
Este enfoque permite soportar tableros dinamicos de hasta 64 columnas de ancho procesando operaciones completas de fila en un solo ciclo de reloj de la ALU.

### 2. Estructura Objeto (`Pieza`)
Modela las entidades flotantes del juego encapsulando sus dimensiones y su matriz de dibujo binario:
```cpp
struct Pieza {
    board_t filas[4]; // Lienzo local de 4x4 bits para la geometria de la pieza
    int ancho;        // Columnas efectivas ocupadas por la figura
    int alto;         // Renglones efectivos ocupados por la figura
};
```
