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

/* window_init */
bool window_init(){
    /* Inicializo libreria general de Allegro */
    if( !al_init() ){
        return false;
    }
    
    /* Inicializo addons de Allegro */
    al_init_font_addon();
    al_init_primitives_addon();
    al_init_ttf_addon();
    
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