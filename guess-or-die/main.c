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

#define EXIT(msg) printf(msg); return -1;

void check(void);

/*
 * 
 */
int main(int argc, char** argv) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    
    BUTTON testButton;
    
    bool hasFinished = false;
    
    /* Inicializo allegro */
    window_init();
    al_install_mouse();
    
    /* Creo el display */
    display = al_create_display(640, 400);
    
    /* Creo la cola de eventos */
    event_queue = al_create_event_queue();
    
    /* Creo el boton de prueba */
    testButton = create_button(20, 20, 60, 30, "Prueba", al_map_rgb(0, 0, 0), al_map_rgb(255, 255, 255), al_map_rgb(0, 255, 100), al_map_rgb(0, 255, 255), check);

    /* Imprimo el boton */
    al_draw_bitmap(testButton.bitmap, testButton.pos.x, testButton.pos.y, 0);
    al_flip_display();
    
    /* Le agrego fuentes a la cola de eventos */
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    
    while( !hasFinished ){
        if( al_get_next_event(event_queue, &event) ){
            switch( event.type ){
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    hasFinished = true;
                    break;
                case ALLEGRO_EVENT_MOUSE_AXES:
                    
                    break;
            }
        }
    }
    
    /* Destruyo el display */
    al_destroy_display(display);
    
    return (EXIT_SUCCESS);
}

void check(void){
    printf("Recibido\n");
}