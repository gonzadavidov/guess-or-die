/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game_kernel.h
 * Author: lucas
 *
 * Created on 17 de mayo de 2018, 19:03
 */

#ifndef GAME_KERNEL_H
#define GAME_KERNEL_H

/* Librerias incluidas */
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

/**************/
/* Constantes */
/**************/

#define MAX_STRING 20

/************************/
/* Estructuras de datos */
/************************/

typedef struct{
    uint8_t name[MAX_STRING];
    SETTINGS cfg;
} GAME_MODE;

typedef struct{
    
    /* Rango del numero aleatorio */
    uint32_t minNumber;
    uint32_t maxNumber;
    
    /* Cantidad de tiempo limite en segundos */
    uint16_t timePeriod;
    
    /* Cantidad maxima de intentos */
    uint16_t maxTries;
    
} SETTINGS;

typedef struct{
    
    /* Numero random */
    uint32_t randomNumber;
    
    /* Registros de tiempo */
    uint32_t initialTime;
    
    /* Cantidad de intentos restantes */
    uint16_t attemptsLeft;
    
} GAME_DATA;

typedef struct{
    
    bool isCorrect;
    bool isHigher;
    bool timeout;
    bool noMoreTries;
    
} RESPONSE;

/***************************/
/* Prototipos de funciones */
/***************************/

uint8_t kernel_init_by_mode( SETTINGS )

/* kernel_init
 * Inicializa modulos, librerias, parametros necesarios
 * del juego, devuelve 1 o 0, OK o fail...
 *
 * minNumber: Minimo numero del rango aleatorio
 * maxNumber: Maximo numero del rango aleatorio
 * timePeriod: Tiempo para responder
 * maxTries: Cantidad maxima de intentos
 */
uint8_t kernel_init(uint32_t minNumber, uint32_t maxNumber, uint16_t timePeriod, uint16_t maxTries);

/* start_game
 * Inicializa parametros para arrancar a jugar,
 * luego de su invocacion el tiempo cuenta
 */
void start_game(void);

/* guess_number
 * Devuelve una instancia de respuesta con informacion
 * sobre si acerto, entre otras cosas
 *
 * tryNumber: Numero a tirar por el usuario
 */
RESPONSE guess_number(uint32_t tryNumber);

/* time_left
 * Devuelve el tiempo restante medido en segundos
 * o 0 / false si no queda tiempo
 */
uint16_t time_left(void);

/* get_random_number
 * Devuelve el numero aleatorio, para mostrarlo si
 * nunca logra resolver el resultado
 */
uint32_t get_random_number(void);

#endif /* GAME_KERNEL_H */