/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game_kernel.c
 * Author: lucas
 * 
 * Created on 17 de mayo de 2018, 19:03
 */

#include "game_kernel.h"

/************************/
/* Variables del nucleo */
/************************/

bool alreadyInit = false;

static SETTINGS kernel_cfg;

static GAME_DATA kernel_data;

static GAME_MODE modes_available[] = {
    {.name = "NOMBRE_DEL_MODO", .cfg.minNumber = 10, .cfg.maxNumber = 20, .cfg.timePeriod = 10, .cfg.maxTries = 5},
    {.name = "CAGON"},
    {.name = "VALIENTE"}
};

/***************************/
/* Definicion de funciones */
/***************************/

/* get_list_of_modes */
void get_list_of_modes(STRING *modes){
    GAME_MODE *modesPointer = modes_available;
    uint16_t numberOfModes, i;
    
    /* Obtengo cantidad de modos */
    numberOfModes = number_of_modes();
    
    /* Itero y busco modo por modo */
    for(i = 0;i < numberOfModes;i++){
        strcpy(modes, modesPointer->name);
        modes++;
        modesPointer++;
    }
}

/* kernel_init_by_mode */
uint8_t kernel_init_by_mode( const char *modeName ){
    GAME_MODE *mode;
    bool success;
    
    /* Busco el modo pedido */
    mode = mode_exists(modeName);
    
    /* Verifico que lo haya encontrado */
    if( mode != NULL ){
        success = kernel_init( mode->cfg.minNumber, mode->cfg.maxNumber, mode->cfg.timePeriod, mode->cfg.maxTries);
        return success;
    }else{
        return false;
    }
}

/* mode_exists */
static GAME_MODE* mode_exists( char *modeName ){
    GAME_MODE *modes = modes_available;
    uint16_t i, numberOfModes;
    bool found = false;
    
    /* Busco cantidad de modos */
    numberOfModes = number_of_modes();
    
    /* Itero por los modos */
    for(i = 0;i < numberOfModes && !found;i++){
        /* Comparo el que busco con el nombre del modo */
        if( !strcmp(modeName, modes->name) ){
            found = true;
        }else{
            modes++;
        }
    }
    
    /* Devuelvo el resultado */
    if( found ){
        return modes;
    }else{
        return NULL;
    }
}

/* number_of_modes */
uint16_t number_of_modes(void){
    uint16_t numberOfModes;
    
    numberOfModes = sizeof(modes_available) / sizeof(GAME_MODE);
    
    return numberOfModes;
}

/* kernel_init */
uint8_t kernel_init(uint32_t minNumber, uint32_t maxNumber, uint16_t timePeriod, uint16_t maxTries){
    
    /* Inicializo semilla para numero random */
    if( !alreadyInit ){
        srand(time(NULL));
        alreadyInit = true;
    }
    
    /* Verifico correcta relacion para rango */
    if( maxNumber <= minNumber ){
        return false;
    }
    kernel_cfg.minNumber = minNumber;
    kernel_cfg.maxNumber = maxNumber;
    kernel_cfg.timePeriod = timePeriod;
    
    /* Verifico cantidad de intentos */
    if( !maxTries ){
        return false;
    }
    kernel_cfg.maxTries = maxTries;
    
    return true;
}

/* start_game */
void start_game(){
    uint32_t range;
    
    /* Calculo el rango configurado */
    range = kernel_cfg.maxNumber - kernel_cfg.minNumber + 1;
    
    /* Agrego cantidad de intentos */
    kernel_data.attemptsLeft = kernel_cfg.maxTries;
    
    /* Genero el numero aleatorio */
    kernel_data.randomNumber = rand() % range + kernel_cfg.minNumber;
    
    /* Grabo el tiempo ded inicio */
    kernel_data.initialTime = time(NULL);
}

/* guess_number */
RESPONSE guess_number(uint32_t tryNumber){
    RESPONSE guessResponse;
    uint16_t timeLeft;
    
    /* Reduzco cantidad de intentos */
    kernel_data.attemptsLeft--;
    if( !kernel_data.attemptsLeft ){
        guessResponse.noMoreTries = true;
    }else{
        guessResponse.noMoreTries = false;
    }
    
    /* Verifico los numeros */
    if( tryNumber == kernel_data.randomNumber ){
        guessResponse.isCorrect = true;
    }else{
        guessResponse.isCorrect = false;
        if( tryNumber > kernel_data.randomNumber ){
            guessResponse.isHigher = true;
        }else{
            guessResponse.isHigher = false;
        }
    }
    
    /* Compruebo el tiempo */
    timeLeft = time_left();
    if( timeLeft ){
        guessResponse.timeout = false;
    }else{
        guessResponse.timeout = true;
    }
    
    return guessResponse;
}

/* time_left */
uint16_t time_left(){
    uint32_t finalTime;
    uint16_t timeLeft;
    
    /* Obtengo tiempo actual */
    finalTime = time(NULL);
    
    /* Verifico que no haya pasado el tiempo */
    if( kernel_cfg.timePeriod < (finalTime - kernel_data.initialTime) ){
        return false;
    }
    
    /* Calculo tiempo restante */
    timeLeft = kernel_cfg.timePeriod - (finalTime - kernel_data.initialTime);
    return timeLeft;
}

/* get_random_number */
uint32_t get_random_number(){
    return kernel_data.randomNumber;
}