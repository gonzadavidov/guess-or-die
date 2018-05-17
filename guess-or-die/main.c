/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: lucas
 *
 * Created on 16 de mayo de 2018, 14:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "window_manager.h"
#include "game_kernel.h"

#define EXIT(msg) printf(msg); return -1;

void check(void);

/*
 * 
 */
int main(int argc, char** argv) {
    uint32_t number;
    RESPONSE response;
    
    if( kernel_init(10, 40, 10, 4) ){
        start_game();
        
        do{
            /* Pido el numero */
            printf("\nNumero: ");
            scanf("%d", &number);
            
            /* Busco si gano o perdio */
            response = guess_number(number);
            
        }while( !response.isCorrect && time_left() && !response.noMoreTries );
        
        if( response.isCorrect ){
            printf("GANASTE!!\n");
        }else if( response.noMoreTries ){
            printf("Te quedaste sin intentos.\n");
        }else{
            printf("Perdiste.... :(\n");
        }
        
        printf("El numero era: %d\n", get_random_number());
    }else{
        printf("No se pudo inicializar.\n");
    }
    
    
    return (EXIT_SUCCESS);
}

void check(void){
    printf("Recibido\n");
}