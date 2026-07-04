# -*- coding: utf-8 -*-
"""Spyder Editor

Este script contiene la resolucion de una serie de ejercicios y problemas
de algoritmia y logica cuantitativa en Python.

Autor: Zahir Llerena
"""

# =============================================================================
# PRIMERA SECCION: EJERCICIOS
# =============================================================================

### Ejercicio 1.1 -------------------------------------------------------------
# Escriba un programa que pida dos numeros A y B e imprima en pantalla el
# residuo de la division A/B. Por ejemplo, si se ingresan 8 y 3 se debe
# imprimir: El residuo de la division 8/3 es: 2

# 1. ENTRADA DE DATOS: Solicitud de numeros enteros
A = int(input("Ingresa el primer numero (A): "))
B = int(input("Ingresa el segundo numero (B): "))

# 2. PROCESO: Calculo del residuo mediante la operacion modulo
residuo = A % B

# 3. SALIDA: Despliegue del resultado en pantalla
print(f"El residuo de la division {A}/{B} es: {residuo}")


### Ejercicio 1.3 -------------------------------------------------------------
# Escriba un programa que solicite dos numeros A y B e imprima en pantalla el
# mayor entre ellos. Por ejemplo, si se ingresan 7 y 3 se debe imprimir:
# El mayor es 7.

# 1. ENTRADA DE DATOS
A = int(input("Ingresa el primer numero (A): "))
B = int(input("Ingresa el segundo numero (B): "))

# 2. PROCESO Y SALIDA: Evaluacion de condiciones logicas
if A > B:
    print(f"El mayor es {A}")
elif B > A:
    print(f"El mayor es {B}")
else:
    print("Ambos numeros son iguales")


### Ejercicio 1.5 -------------------------------------------------------------
# Escriba un programa que solicite dos numeros A y B e imprima en pantalla la
# division A/B con redondeo.
# Por ejemplo, si se ingresan 8 y 3, se debe imprimir: 8/3 = 3
# Si se ingresan 7 y 3 se debe imprimir: 7/3 = 2

# 1. ENTRADA DE DATOS
A = int(input("Ingresa el primer numero (A): "))
B = int(input("Ingresa el segundo numero (B): "))

# 2. PROCESO: Division aritmetica y redondeo al entero mas cercano
division_exacta = A / B
resultado = round(division_exacta)

# 3. SALIDA
print(f"{A}/{B} = {resultado}")


### Ejercicio 1.7 -------------------------------------------------------------
# Escriba un programa que solicite un numero N e imprima en pantalla la suma de
# todos los numeros entre 0 y N, incluyendo N.
# Por ejemplo, si se ingresa 5: (1 + 2 + 3 + 4 + 5 = 15), se debe imprimir:
# La sumatoria desde 0 hasta 5 es: 15

# 1. ENTRADA DE DATOS
N = int(input("Ingresa un numero (N): "))

# 2. INICIALIZACION: Variable acumuladora
suma_total = 0

# 3. PROCESO: Ciclo de acumulacion en el intervalo [0, N]
for numero in range(N + 1):
    suma_total += numero

# 4. SALIDA
print(f"La sumatoria desde 0 hasta {N} es: {suma_total}")


### Ejercicio 1.9 -------------------------------------------------------------
# Escriba un programa que solicite un numero N e imprima en pantalla el perimetro
# y el area de un circulo con radio N. Use 3.1416 como aproximacion de PI.
# Por ejemplo, si se ingresa 1 se debe imprimir:
# Perimetro: 6.28352
# Area: 3.1416

# 1. ENTRADA DE DATOS: Captura del radio con precision de punto flotante
N = float(input("Ingresa el radio del circulo (N): "))

# 2. DEFINICION DE CONSTANTES
PI = 3.1416

# 3. PROCESO: Aplicacion de ecuaciones geometricas de frontera y superficie
perimetro = 2 * PI * N
area = PI * (N ** 2)

# 4. SALIDA
print(f"Perimetro: {perimetro}")
print(f"Area: {area}")


### Ejercicio 1.11 ------------------------------------------------------------
# Escriba un programa que solicite un numero N e imprima en pantalla su tabla
# de multiplicar hasta 10xN.

# 1. ENTRADA DE DATOS
N = int(input("Ingresa un numero para calcular su tabla (N): "))

# 2. PROCESO Y SALIDA: Generacion iterativa de la progresion aritmetica
for iterador in range(1, 11):
    resultado = iterador * N
    print(f"{iterador}x{N} = {resultado}")


### Ejercicio 1.13 ------------------------------------------------------------
# Escriba un programa que solicite un numero N e imprima todos los divisores de N.

# 1. ENTRADA DE DATOS
N = int(input("Ingresa un numero (N): "))

# 2. SALIDA INICIAL
print(f"Los divisores de {N} son:")

# 3. PROCESO: Iteracion y filtrado analitico de divisibilidad exacta
for candidato in range(1, N + 1):
    if N % candidato == 0:
        print(candidato)


### Ejercicio 1.15 ------------------------------------------------------------
# Escriba un programa que solicite al usuario que ingrese numeros. Una vez se
# ingrese el numero cero, se debe imprimir en pantalla la suma de todos los
# numeros ingresados.

# 1. INICIALIZACION
suma_total = 0

# 2. LECTURA INICIAL (Priming Read)
numero = int(input("Ingresa un numero (0 para terminar): "))

# 3. PROCESO INTERATIVO: Ciclo por centinela
while numero != 0:
    suma_total += numero
    numero = int(input("Ingresa un numero (0 para terminar): "))

# 4. SALIDA
print(f"El resultado de la sumatoria es: {suma_total}")


### Ejercicio 1.17 ------------------------------------------------------------
# Escriba un programa que solicite al usuario que ingrese varios numeros. Una
# vez se ingrese el numero cero, se debe imprimir en pantalla el mayor de todos
# los numeros ingresados.

# 1. LECTURA INICIAL
numero = int(input("Ingresa un numero (0 para terminar): "))

# 2. INICIALIZACIÓN DEL ESTADO MINIMO HISTORICO
mayor = numero

# 3. CICLO CONDICIONAL DE EVALUACION
while numero != 0:
    if numero > mayor:
        mayor = numero
    numero = int(input("Ingresa un numero (0 para terminar): "))

# 4. SALIDA
print(f"El numero mayor fue: {mayor}")


### Ejercicio 1.19 ------------------------------------------------------------
# Escriba un programa que solicite un numero N e imprima si es o no un numero primo.

# 1. ENTRADA DE DATOS
N = int(input("Ingresa un numero (N): "))

# 2. ESTADO INICIAL (Hipotesis)
es_primo = True

# 3. PROCESO: Evaluacion algoritmica en busca de divisores en el rango (2, N-1)
for candidato in range(2, N):
    if N % candidato == 0:
        es_primo = False
        break

# 4. SALIDA: Descarte del 1 y verificacion de la bandera logica
if es_primo and N > 1:
    print(f"{N} es un numero primo.")
else:
    print(f"{N} NO es un numero primo.")


### Ejercicio 1.21 ------------------------------------------------------------
# Escriba un programa que solicite un caracter C; si es una letra, la debe
# convertir de mayuscula a minuscula y viceversa.

# 1. ENTRADA DE DATOS
C = input("Ingresa una letra (C): ")

# 2. EVALUACION Y VALIDACION DEL DOMINIO ALFABETICO
if C.isalpha():
    if C.isupper():
        convertida = C.lower()
    else:
        convertida = C.upper()
    print(f"Letra convertida: {convertida}")
else:
    print("Error: El caracter ingresado no es una letra del alfabeto.")


### Ejercicio 1.23 ------------------------------------------------------------
# Escriba un programa que pida dos numeros A y B e imprima en pantalla el minimo
# comun multiplo entre los dos.

# 1. ENTRADA DE DATOS
A = int(input("Ingresa el primer numero (A): "))
B = int(input("Ingresa el segundo numero (B): "))

# 2. PUNTO DE PARTIDA: Determinacion de la cota inferior del MCM
mcm = A if A > B else B

# 3. PROCESO: Busqueda lineal iterativa condicionada
while (mcm % A != 0) or (mcm % B != 0):
    mcm += 1

# 4. SALIDA
print(f"El MCM de {A} y {B} es: {mcm}")


### Ejercicio 1.25 ------------------------------------------------------------
# Escriba un programa que solicite un numero N e imprima en pantalla la cantidad
# de digitos de N.

# 1. ENTRADA DE DATOS
N = int(input("Ingresa un numero (N): "))

# 2. INICIALIZACION Y CONTROL DE MAGNITUD ABSOLUTA
temp = abs(N)
cantidad_digitos = 0

# 3. PROCESO: Reduccion por division entera sucesiva sobre base 10
if temp == 0:
    cantidad_digitos = 1
else:
    while temp > 0:
        cantidad_digitos += 1
        temp = temp // 10

# 4. SALIDA
print(f"{N} tiene {cantidad_digitos} digitos.")


### Ejercicio 1.27 ------------------------------------------------------------
# Escriba un programa que actue como una calculadora aritmetica.

# 1. ENTRADA DE DATOS
A = float(input("Ingresa el primer numero: "))
operacion = input("Ingresa la operacion (+, -, *, /): ")
B = float(input("Ingresa el segundo numero: "))

# 2. PROCESO Y SALIDA: Estructura condicional multiple
if operacion == '+':
    print(f"{A} {operacion} {B} = {A + B}")
elif operacion == '-':
    print(f"{A} {operacion} {B} = {A - B}")
elif operacion == '*':
    print(f"{A} {operacion} {B} = {A * B}")
elif operacion == '/':
    # Control preventivo de indeterminacion analitica
    if B == 0:
        print("Error analitico: La division por cero no esta definida.")
    else:
        print(f"{A} {operacion} {B} = {A / B}")
else:
    print("Error logico: Operador no reconocido.")


### Ejercicio 1.29 ------------------------------------------------------------
# Escriba un programa que adivine un numero A (entre 0 y 100) utilizando
# un algoritmo de busqueda binaria. Maximo 7 intentos.

# 1. INICIALIZACION DEL ESPACIO MUESTRAL
limite_inferior = 0
limite_superior = 100
intento_actual = 1
acertado = False

print("Piensa en un numero entre 0 y 100.")
print("Instrucciones de entrada:")
print("  >  Si mi numero es MAYOR que el tuyo.")
print("  <  Si mi numero es MENOR que el tuyo.")
print("  =  Si acerte.")
print("-" * 40)

# 2. PROCESO DE REDUCCION DE ESPACIO DE BUSQUEDA
while intento_actual <= 7:
    if limite_inferior > limite_superior:
        print("Error logico: Las condiciones se contradicen.")
        break

    # Calculo de la mediana del rango actual
    B = (limite_inferior + limite_superior) // 2
    respuesta = input(f"Intento {intento_actual}: ¿Mi numero {B} es (> / < / =)? ")

    if respuesta == '=':
        print(f"iHe acertado! Adivine el {B} en el intento {intento_actual}.")
        acertado = True
        break
    elif respuesta == '>':
        limite_superior = B - 1
        intento_actual += 1
    elif respuesta == '<':
        limite_inferior = B + 1
        intento_actual += 1
    else:
        print("Simbolo invalido. Intenta de nuevo usando solo >, < o =.")

if not acertado and limite_inferior <= limite_superior:
    print("Agote mis 7 intentos sin lograr determinar el numero.")


# =============================================================================
# SEGUNDA SECCION: PROBLEMAS
# =============================================================================

### Ejercicio 2.1 -------------------------------------------------------------
# Escriba un programa que identifique si un caracter ingresado es una vocal, una
# consonante o ninguna de las dos.

# 1. ENTRADA DE DATOS
caracter = input("Ingresa un caracter: ")

# 2. EVALUACION DE PERTENENCIA A SUBCONJUNTOS ALFABETICOS
if caracter.isalpha():
    if caracter.lower() in "aeiou":
        print(f"{caracter} es una vocal")
    else:
        print(f"{caracter} es una consonante")
else:
    print(f"{caracter} no es una letra")


### Ejercicio 2.3 -------------------------------------------------------------
# Escriba un programa que reciba un mes y un dia e indique si la fecha es valida,
# evaluando tambien las variaciones de anos bisiestos.

# 1. ENTRADA DE DATOS: Diagnostico independiente de componentes
N1 = int(input("Ingresa el primer numero: "))
N2 = int(input("Ingresa el segundo numero: "))

print("\n--- Datos independientes ---")
if 1 <= N1 <= 12:
    print(f"{N1} es un mes valido.")
else:
    print(f"{N1} es un mes invalido.")

if 1 <= N2 <= 31:
    print(f"{N2} es un dia valido.")
else:
    print(f"{N2} es un dia invalido.")

print()

if 1 <= N1 <= 31:
    print(f"{N1} es un dia valido.")
else:
    print(f"{N1} es un dia invalido.")

if 1 <= N2 <= 12:
    print(f"{N2} es un mes valido.")
else:
    print(f"{N2} es un mes invalido.")

print("\n--- Datos conjuntos ---")

# Arbol de decision para Permutacion A (N2/N1 -> Dia/Mes)
dia_A, mes_A = N2, N1
estado_A = "invalida"

if 1 <= mes_A <= 12:
    if mes_A == 2:
        if dia_A == 29:
            estado_A = "valida en ano bisiesto"
        elif 1 <= dia_A <= 28:
            estado_A = "valida"
    elif mes_A in [4, 6, 9, 11]:
        if 1 <= dia_A <= 30:
            estado_A = "valida"
    else:
        if 1 <= dia_A <= 31:
            estado_A = "valida"

print(f"{dia_A}/{mes_A} es una fecha (dia/mes) {estado_A}.")

# Arbol de decision para Permutacion B (N1/N2 -> Dia/Mes)
dia_B, mes_B = N1, N2
estado_B = "invalida"

if 1 <= mes_B <= 12:
    if mes_B == 2:
        if dia_B == 29:
            estado_B = "valida en ano bisiesto"
        elif 1 <= dia_B <= 28:
            estado_B = "valida"
    elif mes_B in [4, 6, 9, 11]:
        if 1 <= dia_B <= 30:
            estado_B = "valida"
    else:
        if 1 <= dia_B <= 31:
            estado_B = "valida"

print(f"{dia_B}/{mes_B} es una fecha (dia/mes) {estado_B}.")


# --- Subprograma: Validacion completa con ano integrado ---
print("\n--- Validacion de fecha con ano integrado ---")
dia = int(input("Ingresa el dia: "))
mes = int(input("Ingresa el mes: "))
anio = int(input("Ingresa el ano: "))

# Evaluacion matematica de la regla del calendario gregoriano para bisiestos
es_bisiesto = (anio % 4 == 0 and (anio % 100 != 0 or anio % 400 == 0))
fecha_valida = False

if 1 <= mes <= 12:
    if mes == 2:
        if es_bisiesto and 1 <= dia <= 29:
            fecha_valida = True
        elif not es_bisiesto and 1 <= dia <= 28:
            fecha_valida = True
    elif mes in [4, 6, 9, 11]:
        if 1 <= dia <= 30:
            fecha_valida = True
    else:
        if 1 <= dia <= 31:
            fecha_valida = True

print("-" * 30)
if fecha_valida:
    print(f"La fecha {dia}/{mes}/{anio} es VALIDA.")
else:
    print(f"La fecha {dia}/{mes}/{anio} es INVALIDA.")


### Ejercicio 2.5 -------------------------------------------------------------
# Escriba un programa que reciba un numero impar e imprima un patron simetrico de asteriscos.

# 1. ENTRADA DE DATOS Y VERIFICACION
N = int(input("Ingresa un numero impar para el centro del patron (N): "))

if N % 2 == 0:
    print("Error logico: El patron simetrico requiere un numero impar.")
else:
    # FASE ASCENDENTE (Incluye linea central de longitud N)
    for i in range(1, N + 1, 2):
        print("*" * i)
        
    # FASE DESCENDENTE (Decremento simetrico)
    for i in range(N - 2, 0, -2):
        print("*" * i)


### Ejercicio 2.7 -------------------------------------------------------------
# Subprograma: Despliegue de los primeros n terminos de Fibonacci

n = int(input("Ingresa un numero natural mayor a 2 para terminos simples (n): "))

if n <= 2:
    print("Error logico: Se requiere n > 2.")
else:
    a, b = 0, 1
    print(f"Los primeros {n} terminos de la serie de Fibonacci son:")
    for _ in range(n):
        print(a)
        a, b = b, a + b

# --- Resolucion del problema principal: Sumar pares menores a N ---
print("\n--- Solucion al problema de sumatoria ---")
N = int(input("Ingresa el limite superior estricto (N): "))

a, b = 0, 1
suma_pares = 0

while a < N:
    if a % 2 == 0:
        suma_pares += a
    a, b = b, a + b

print(f"El resultado de la suma es: {suma_pares}")


### Ejercicio 2.9 -------------------------------------------------------------
# Escriba un programa que reciba un numero N y sume sus digitos elevados a si mismos.

# 1. ENTRADA DE DATOS
N = int(input("Ingresa un numero (N): "))

temp = abs(N)
suma_total = 0

if temp == 0:
    suma_total = 0 ** 0
else:
    while temp > 0:
        digito = temp % 10
        suma_total += (digito ** digito)
        temp = temp // 10

print(f"El resultado de la suma es: {suma_total}")


### Ejercicio 2.11 ------------------------------------------------------------
# Calcule el MCM acumulado de todos los numeros enteros entre 1 y N utilizando Euclides.

N = int(input("Ingresa un numero (N): "))
mcm_acumulado = 1

if N >= 1:
    for i in range(2, N + 1):
        a = mcm_acumulado
        b = i
        
        # Algoritmo de Euclides para hallar el MCD
        while b != 0:
            a, b = b, a % b
        mcd = a
        
        # Obtencion del MCM mediante la propiedad inversa
        mcm_acumulado = (mcm_acumulado * i) // mcd

print(f"El minimo comun multiplo es: {mcm_acumulado}")


### Ejercicio 2.13 ------------------------------------------------------------
# Escriba un programa que reciba un numero N y sume todos los primos menores que N.

N = int(input("Ingresa un numero (N): "))
suma_primos = 0

for candidato in range(2, N):
    es_primo = True
    # Cota superior de busqueda optimizada mediante la raiz cuadrada de la magnitud
    limite = int(candidato ** 0.5) + 1
    
    for divisor in range(2, limite):
        if candidato % divisor == 0:
            es_primo = False
            break
            
    if es_primo:
        suma_primos += candidato

print(f"El resultado de la suma es: {suma_primos}")


### Ejercicio 2.15 ------------------------------------------------------------
# Generacion de la matriz en Espiral de Ulam de tamano NxN y sumatoria de sus diagonales.

N = int(input("Ingresa un numero impar (N): "))

if N % 2 == 0:
    print("Error logico: La espiral requiere un numero impar para un centro geometrico exacto.")
else:
    # Inicializacion del espacio bidimensional vacio
    matriz = [[0] * N for _ in range(N)]
    
    # Coordenadas en el centro exacto
    x = N // 2
    y = N // 2
    
    # Vectores de direccion cinematica inicial (Derecha)
    dx, dy = 1, 0
    pasos_limite = 1
    pasos_actuales = 0
    cambios_direccion = 0
    
    for i in range(1, (N * N) + 1):
        matriz[y][x] = i
        
        if i == N * N:
            break
            
        x += dx
        y += dy
        pasos_actuales += 1
        
        if pasos_actuales == pasos_limite:
            pasos_actuales = 0
            # Matriz de rotacion horaria de 90 grados
            dx, dy = -dy, dx
            cambios_direccion += 1
            
            if cambios_direccion % 2 == 0:
                pasos_limite += 1
                
    # Extraccion matricial y calculo cuantitativo de diagonales
    suma_diagonales = 0
    print("\nMatriz generada:")
    
    for fila in range(N):
        fila_texto = ""
        for col in range(N):
            if fila == col or fila + col == N - 1:
                suma_diagonales += matriz[fila][col]
                fila_texto += f"{matriz[fila][col]}!\t"
            else:
                fila_texto += f"{matriz[fila][col]}\t"
        print(fila_texto)
        
    print(f"\nEl resultado de la suma de las diagonales es: {suma_diagonales}")


### Ejercicio 2.17 ------------------------------------------------------------
# No lo entiendo...

# =============================================================================
# FIN DEL SCRIPT
# =============================================================================