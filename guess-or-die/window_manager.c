/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   window_manager.c
 * Author: lucas
 * 
 * Created on 16 de mayo de 2018, 14:37
 */

#include <strings.h>

#include "window_manager.h"

/***************************/
/* Definicion de funciones */
/***************************/

/* add_button */
bool add_button(WINDOW *window, uint8_t x, uint8_t y, uint16_t width, uint16_t height, const char *str, ALLEGRO_COLOR bg, ALLEGRO_COLOR fg, ALLEGRO_COLOR lc, ALLEGRO_COLOR pc, ALLEGRO_COLOR fc);


/* add_button_action_by_text */
bool add_button_action_by_text(WINDOW *window, const char *text, void (*action)(void*)){
    uint16_t i;
    
    /* Verifico que hayan botones */
    if( window->numberOfButtons ){
        /* Itero por todos los botones de window */
        for(i = 0;i < window->numberOfButtons;i++){
            /* Me fijo cual tiene ese nombre */
            if( !strcmp(text, window->buttons[i].text) ){
                /* Le establezco la accion */
                window->buttons[i].onClick = action;
                return true;
            }
        }
    }
    
    return false;
}

/* destroy_window */
void destroy_window(WINDOW *window){
    uint16_t i;
    
    /* Destruyo el backbuffer */
    al_destroy_display(window->display);
    
    /* Destruyo la cola de eventos */
    al_destroy_event_queue(window->eventQueue);
    
    /* Destruyo todos los botones */
    if( window->numberOfButtons ){
        for(i = 0;i < window->numberOfButtons;i++){
            destroy_button( window->buttons[i] );
        }
    }
    
    /* Libero memoria de los botones */
    free(window->buttons);
    
    /* Devuelvo el control al parent */
    al_set_target_backbuffer(window->parentDisplay);
    
}

/* window_init */
bool window_init(WINDOW *window){
    
    /* Guardo el backbuffer del parent */
    window->parentDisplay = al_get_current_display();
    if( window->parentDisplay == NULL ){
        return false;
    }
    
    /* Creo el backbuffer de esta ventana */
    window->display = al_create_display(window->width, window->height);
    if( window->display == NULL ){
        return false;
    }
    
    /* Creo la cola de eventos */
    window->eventQueue = al_create_event_queue();
    if( window->eventQueue == NULL ){
        return false;
    }
    
    /* Inicializo parametros generales */
    window->numberOfButtons = 0;
    window->nextButtonId = 0;
    
    /* Paso el control a la nueva ventana */
    al_set_target_backbuffer(window->display);
    
    return true;
}

/* set_button_action */
void set_button_action(BUTTON *button, void (*action)(void*)){
    button->onClick = action;
}

/* is_inside_of */
void is_inside_of(BUTTON *button, int x, int y){
    if( button->pos.x < x && x < (button->pos.x + button->width) && button->pos.y < y && y < (button->pos.y + button->height) ){
        button->isFocus = 1;        
    }else{
        button->isFocus = 0; 
    }
}

/* manager_init */
bool manager_init(){
    /* Inicializo libreria general de Allegro */
    if( !al_init() ){
        return false;
    }
    
    /* Inicializo addons de Allegro */
    al_init_font_addon();
    al_init_primitives_addon();
    al_init_ttf_addon();
    
    /* Instala el mouse */
    if( !al_install_mouse() ){
        return false;
    }
    
    return true;
}

/* destroy_button */
void destroy_button(BUTTON *button){
    al_destroy_bitmap(button->bitmap);
}

/* create_button */
BUTTON create_button(uint16_t id, uint8_t x, uint8_t y, uint16_t width, uint16_t height, const char *str, ALLEGRO_COLOR bg, ALLEGRO_COLOR fg, ALLEGRO_COLOR lc, ALLEGRO_COLOR pc, ALLEGRO_COLOR fc){
    /* Inicializo la instancia del boton */
    BUTTON boton = {
        .id = id,
        .pos.x = x,
        .pos.y = y,
        .width = width,
        .height = height,
        .backgroundColor = bg,
        .foregroundColor = fg,
        .lineColor = lc,
        .pressedColor = pc,
        .focusColor = fc,
        .isPressed = 0,
        .isFocus = 0
    };
    
    /* Inicializo el texto del boton */
    strcpy(boton.text, str);
    
    /* Inicializo el bitmap del boton */    
    create_button_bitmap(&boton);
    
    return boton;
}

/* update_button */
void update_button(BUTTON *button){
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font;
    
    /* Guardo el buffer actual */
    display = al_get_current_display();
    
    /* Defino el nuevo buffer o target */
    al_set_target_bitmap(button->bitmap);
    
    /* Fondo del bitmap */
    if( button->isFocus ){
        al_clear_to_color(button->focusColor);        
    }else if( button->isPressed ){
        al_clear_to_color(button->pressedColor);      
    }else{
        al_clear_to_color(button->backgroundColor);
    }
    
    /* Imprimo los bordes */
    al_draw_rectangle(1, 0, button->width - 1, button->height - 1, button->lineColor, 1);
    
    /* Imprimo el texto */
    font = al_load_ttf_font("STARWARS.TTF", 10, 0);
    al_draw_text(font, button->foregroundColor, (button->width - strlen(button->text)*6)/2, (button->height - 10)/2, 0, button->text);
    /* Destruyo lo creado */
    al_destroy_font(font);
    
    /* Devuelvo el buffer al target */
    al_set_target_backbuffer(display);
}

/* create_button_bitmap */
void create_button_bitmap(BUTTON *button){
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font;
    
    /* Guardo el buffer actual */
    display = al_get_current_display();
    
    /* Creo el bitmap del boton */
    button->bitmap = al_create_bitmap(button->width, button->height);
    
    /* Defino el nuevo buffer o target */
    al_set_target_bitmap(button->bitmap);
    
    /* Fondo del bitmap */
    if( button->isFocus ){
        al_clear_to_color(button->focusColor);        
    }else if( button->isPressed ){
        al_clear_to_color(button->pressedColor);      
    }{
        al_clear_to_color(button->backgroundColor);
    }
    
    /* Imprimo los bordes */
    al_draw_rectangle(1, 0, button->width - 1, button->height - 1, button->lineColor, 1);
    
    /* Imprimo el texto */
    font = al_load_ttf_font("STARWARS.TTF", 10, 0);
    al_draw_text(font, button->foregroundColor, (button->width - strlen(button->text)*6)/2, (button->height - 10)/2, 0, button->text);
    /* Destruyo lo creado */
    al_destroy_font(font);
    
    /* Devuelvo el buffer al target */
    al_set_target_backbuffer(display);
}