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

static SETTINGS kernel_cfg = {.alreadySet = false};
static GAME_DATA kernel_data;

/***************************/
/* Definicion de funciones */
/***************************/

/* kernel_init */
uint8_t kernel_init(uint32_t minNumber, uint32_t maxNumber, uint16_t timePeriod, uint16_t maxTries){
    
    /* Inicializo semilla para numero random */
    if( !kernel_cfg.alreadySet ){
        srand(time(NULL));
        kernel_cfg.alreadySet = true;
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