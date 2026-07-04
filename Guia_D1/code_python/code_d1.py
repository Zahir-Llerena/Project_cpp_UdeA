#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Mar 18 17:17:31 2026

@author: ZahirLlerena 
"""


# --- FRAGMENTO 1: CONFIGURACIÓN DE MEMORIA ---
# Este bloque establece las dimensiones del tablero (múltiplo de 8) y emula la 
# gestión de memoria dinámica mediante una lista de enteros que representan 
# filas de bits

import random
import os

# Configuración del entorno
# El ancho debe ser múltiplo de 8 para facilitar el manejo de bytes:
    
# ancho_usuario = int(input("Ancho del tablero (múltiplo de 8): "))
# alto_usuario = int(input("Alto del tablero (mínimo 8): "))

# if ancho_usuario < 8 or ancho_usuario % 8 != 0 or alto_usuario < 8:
#    print("Error: El ancho debe ser múltiplo de 8 y el alto mínimo 8.")
#     exit()

# ANCHO = ancho_usuario
# ALTO = alto_usuario

# Configuraciones iniciales 
ANCHO = 8  # Múltiplo de 8 
ALTO = 16 

# Emulación de memoria dinámica: cada fila es un byte (entero) 
tablero = [0] * ALTO

# --- FRAGMENTO 2: DEFINICIÓN DE TETRIMINOS (BITWISE) ---

# Definimos los 7 tetriminos usando literales binarios (0b). Esto permite 
# realizar desplazamientos y comparaciones rápidas a nivel de bits

# Definición de los 7 tetriminos clásicos 
PIEZAS = {
    'I': (0b1111,),             # Recta de 4 bloques 
    'O': (0b11, 0b11),          # Cuadrado 2x2 
    'T': (0b010, 0b111),        # Pieza T 
    'S': (0b011, 0b110),        # Pieza S 
    'Z': (0b110, 0b011),        # Pieza Z 
    'J': (0b100, 0b111),        # Pieza J 
    'L': (0b001, 0b111)         # Pieza L 
}

def obtener_pieza():
    # Selección aleatoria uniforme [cite: 44]
    return PIEZAS[random.choice(list(PIEZAS.keys()))]

# --- FRAGMENTO 3: LÓGICA DE ROTACIÓN ---

# Aquí reside la lógica de manipulación de bits. La rotación transpone los bits 
# de la pieza actual.

def rotar_pieza(pieza):
    # Determinamos el ancho actual de la pieza para la transposición
    ancho_p = max(f.bit_length() for f in pieza)
    nueva = []
    for j in range(ancho_p):
        nueva_fila = 0
        for i in range(len(pieza)):
            # Extraemos el bit y lo reubicamos en la nueva matriz de bits
            bit = (pieza[i] >> j) & 1
            if bit:
                nueva_fila |= (1 << (len(pieza) - 1 - i))
        nueva.append(nueva_fila)
    return tuple(nueva)

def hay_colision(pieza, px, py, tablero_actual):
    for i, fila_p in enumerate(pieza):
        y_coord = py + i
        # Verificación de límites verticales (fondo) 
        if y_coord >= ALTO: return True
        
        ancho_p = fila_p.bit_length()
        # Verificación de límites horizontales (paredes) 
        if px < 0 or (px + ancho_p) > ANCHO: return True
            
        # Comparación bit a bit entre pieza y tablero fijo 
        pieza_en_pos = fila_p << (ANCHO - ancho_p - px)
        if (tablero_actual[y_coord] & pieza_en_pos) != 0:
            return True
    return False

# --- FRAGMENTO 4: NÚCLEO DE COLISIONES ---

# Cuando una fila está llena (todos los bits en 1), debe eliminarse y las 
# superiores bajar.

def fijar_pieza(pieza, px, py, tablero_actual):
    for i, fila_p in enumerate(pieza):
        ancho_p = fila_p.bit_length()
        pieza_en_pos = fila_p << (ANCHO - ancho_p - px)
        # Usamos OR (|) para "quemar" la pieza en el tablero 
        tablero_actual[py + i] |= pieza_en_pos

def limpiar_filas(tablero_actual):
    # Máscara de fila llena (ej: 255 para ancho 8)
    FILA_LLENA = (1 << ANCHO) - 1
    # Filtrado de filas y reposición de vacías al inicio 
    nuevas = [f for f in tablero_actual if f != FILA_LLENA]
    eliminadas = ALTO - len(nuevas)
    return ([0] * eliminadas) + nuevas


# --- FRAGMENTO 5: FIJACIÓN Y LIMPIEZA DE FILAS ---

# Maneja el flujo por turnos según la dinámica solicitada en el documento

def dibujar(tablero_actual, pieza_act=None, px=0, py=0):
    os.system('cls' if os.name == 'nt' else 'clear')
    visual = list(tablero_actual)
    if pieza_act:
        for i, fila_p in enumerate(pieza_act):
            ancho_p = fila_p.bit_length()
            visual[py + i] |= (fila_p << (ANCHO - ancho_p - px))

    for fila in visual:
        # Representación visual: '#' para ocupado, '.' para vacío [cite: 55]
        bits = bin(fila)[2:].zfill(ANCHO)
        rep = "".join(['#' if b == '1' else '.' for b in bits])
        print(f"| {rep} |")
    print("Acciones: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir")

# --- FRAGMENTO 6: INTERFAZ Y BUCLE PRINCIPAL ---

# Unifica todas las funciones en una dinámica de turnos, solicitando acciones 
# al usuario y procesando el estado.

def jugar():
    global tablero
    while True:
        pieza = obtener_pieza()
        px, py = (ANCHO // 2) - 1, 0
        # Detección de Game Over al inicio 
        if hay_colision(pieza, px, py, tablero):
            dibujar(tablero); print("GAME OVER"); break
            
        while True:
            dibujar(tablero, pieza, px, py)
            accion = input("Seleccione: ").upper()
            if accion == 'Q': return
            
            n_px, n_py, p_aux = px, py, pieza
            if accion == 'A': n_px -= 1
            elif accion == 'D': n_px += 1
            elif accion == 'S': n_py += 1
            elif accion == 'W': p_aux = rotar_pieza(pieza) # Intenta rotar
            
            # Verificación de validez del nuevo estado
            if not hay_colision(p_aux, n_px, n_py, tablero):
                px, py, pieza = n_px, n_py, p_aux # Actualiza la pieza rotada aquí
            else:
                if accion == 'S':
                    fijar_pieza(pieza, px, py, tablero)
                    tablero = limpiar_filas(tablero)
                    break

if __name__ == "__main__":
    jugar()




















