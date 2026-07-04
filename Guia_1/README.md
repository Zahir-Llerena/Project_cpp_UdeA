# Practicas de Algoritmia y Estructuras de Control en C++

## Universidad de Antioquia
**Facultad de Ingenieria - Departamento de Telecomunicaciones**
* **Asignatura:** Informatica II
* **Autor:** Zahir Llerena
* **Email:** zahir.llerena@udea.edu.co

---

## Descripcion del Proyecto

Este repositorio contiene un ecosistema modular de software desarrollado en **C++** como componente practico de la asignatura Informatica II. El objetivo primordial de este conjunto de ejercicios es afianzar las capacidades de analisis de algoritmos, entender la gestion explicita de la memoria RAM, dominar el tipado estatico y comprender el comportamiento de las estructuras de control iterativas y condicionales en un lenguaje de compilacion nativa, contrastando sus paradigmas con entornos de ejecucion dinamica como Python.

El codigo esta estructurado en forma de banco de pruebas academico unificado bajo una interfaz dirigida por menus en consola, lo que facilita la verificacion e inspeccion cuantitativa de cada solucion logica de manera aislada.

---

## Contenido y Estructura del Codigo

El script se divide metodologicamente en dos grandes bloques fundamentales de resolucion de problemas:

### Bloque 1: Ejercicios de Fundamentacion Sintactica y Aritmetica
* **Ejercicio 1.1:** Calculo del residuo algebraico utilizando el operador modulo (\%).
* **Ejercicio 1.3:** Evaluacion de limites y condiciones logicas multiples (`if-else if-else`) para determinacion de maximos.
* **Ejercicio 1.5:** Implementacion de un mecanismo de "Casting" explicito y redondeo analogico manual sobre variables de punto flotante.
* **Ejercicio 1.7:** Operacion de acumulacion lineal discreta mediante ciclos de cota cerrada `for`.
* **Ejercicio 1.9:** Optimizacion del calculo de area y perimetro circunferencial empleando tecnicas de multiplicacion directa en lugar de librerias geometricas pesadas.
* **Ejercicio 1.11:** Control de secuencias y formateo lineal de tablas de multiplicar.
* **Ejercicio 1.13:** Barrido por fuerza bruta para la determinacion del conjunto de divisores de una magnitud escalar.
* **Ejercicio 1.15 & 1.17:** Implementacion de ciclos controlados por centinelas (`while`) aplicando lecturas de preparacion (*priming read*) para la acumulacion de sumas y retencion de records maximos.
* **Ejercicio 1.19:** Algoritmo base para la validacion empirica de hipotesis de numeros primos.
* **Ejercicio 1.21:** Transformaciones binarias sobre la tabla ASCII para la conversion de caracteres alfabeticos.
* **Ejercicio 1.23:** Busqueda condicionada y aplicacion de las leyes de De Morgan para hallar el Minimo Comun Multiplo (MCM).
* **Ejercicio 1.25:** Algoritmo de descomposicion decadica destructiva para el conteo de digitos enteros.
* **Ejercicio 1.27:** Diseño modular de una calculadora basica con compuertas preventivas para el control de la indeterminacion por division por cero.
* **Ejercicio 1.29:** Implementacion de un motor de Busqueda Binaria para la convergencia logica de rangos numericos en un maximo de 7 intentos.

### Bloque 2: Problemas de Complejidad Logica y Algoritmica Avanzada
* **Ejercicio 2.1:** Analisis y clasificacion de subconjuntos de caracteres alfabeticos mediante tecnicas de normalizacion temporal.
* **Ejercicio 2.3:** Arbol de decisiones anidadas y analisis combinatorio permutacional para la validacion integral de dimensiones temporales (Fechas).
* **Ejercicio 2.5:** Ciclos anidados para construccion geometrica simetrica en consola con una complejidad de tiempo $O(N^2)$.
* **Ejercicio 2.7:** Implementacion de una ventana movil (*sliding window*) para el calculo iterativo de la sucesion de Fibonacci y su filtrado par.
* **Ejercicio 2.9:** Descomposicion e implementacion de tipos de datos de alta capacidad (`long long` de 64 bits) para evitar desbordamientos de memoria (*overflow*) al procesar potencias elevadas.
* **Ejercicio 2.11:** Algoritmo optimizado de Euclides por divisiones modulares sucesivas para el calculo del MCM acumulativo en un espacio muestral extenso.
* **Ejercicio 2.13:** Optimizacion de busqueda de numeros primos acotando dinamicamente la cota superior del interrogador mediante su raiz cuadrada geometrica.
* **Ejercicio 2.15:** Generacion dinamica de matrices bidimensionales en el "Heap" utilizando punteros dobles (`int**`), mapeo vectorial para el diseno de la Espiral de Ulam, calculo analitico de pertenencia a diagonales principales y secundarias, y liberacion manual responsable de memoria para prevenir fugas (*memory leaks*).

---

## Arquitectura de Software e Interrelacion Didactica

El diseno del software sigue un patron modular estructurado:
