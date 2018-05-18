/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   window_manager.h
 * Author: lucas
 *
 * Created on 16 de mayo de 2018, 14:37
 */

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_ttf.h>

/**************/
/* Constantes */
/**************/

#define MAX_STRING 20

/************************/
/* Estructuras de datos */
/************************/

/* STRING
 * Estructura para strings
 */
typedef char STRING[MAX_STRING];

/* POSITION
 * Estructura para almacenar ubicacion (x,y) en display
 */
typedef struct{
    uint8_t x;
    uint8_t y;
} POSITION;

/* BUTTON
 * Estructura para control de botones en un display/ventana
 */
typedef struct{
    /* Position option */
    POSITION pos;
    
    /* Size options */
    uint16_t width;
    uint16_t height;
    
    /* Identifier options */
    uint16_t id;
    STRING text;
    
    /* Functionality options */
    uint16_t status;
    uint16_t isPressed;
    uint16_t isFocus;
    uint16_t enableHold;
    
    /* Color options */
    ALLEGRO_COLOR backgroundColor;
    ALLEGRO_COLOR foregroundColor;
    ALLEGRO_COLOR lineColor;
    ALLEGRO_COLOR pressedColor;
    ALLEGRO_COLOR focusColor;
    
    /* Bitmap layout */
    ALLEGRO_BITMAP *bitmap;
    
    /* OnClick action */
    void (*onClick)(void*);
    
} BUTTON;

/* WINDOW
 * Estructura para controlar una ventana
 */
typedef struct{
    
    /* Parametros de la ventana */
    uint16_t width;
    uint16_t height;
    
    /* Displays de la ventana */
    ALLEGRO_DISPLAY *display;
    ALLEGRO_DISPLAY *parentDisplay;
    
    /* Botones de la ventana */
    BUTTON *buttons;
    uint16_t numberOfButtons;
    uint16_t nextButtonId;
    
    /* Cola de eventos */
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_EVENT event;

} WINDOW;

/***************************/
/* Prototipos de funciones */
/***************************/

void run_window(WINDOW *window);

bool add_button(WINDOW *window, uint8_t x, uint8_t y, uint16_t width, uint16_t height, const char *str, ALLEGRO_COLOR bg, ALLEGRO_COLOR fg, ALLEGRO_COLOR lc, ALLEGRO_COLOR pc, ALLEGRO_COLOR fc);

bool add_button_action_by_text(WINDOW *window, const char *text, void (*action)(void*));

/* destroy_window
 * Libera la memoria ocupada por las partes integrantes
 * de esta ventana
 * 
 * window: Puntero a la ventana 
 */
void destroy_window(WINDOW *window);

/* window_init 
 * Inicializa aspectos principales de la ventana,
 * es llamada automaticamente por el run_window
 * El usuario debe unicamente haber creado una instancia
 * con los parametros width y height definidos
 * 
 * window: Puntero a la ventana a inicializar
 */
bool window_init(WINDOW *window);

/* is_inside_of
 * Actualiza isFocus segun si la posicion (x,y) esta ubicada
 * dentro del boton que se pasa como parametro
 * 
 * x:       Coordenada x de la posicion
 * y:       Coordenada y de la posicion
 * button: Instancia del boton a verificar
 */
void is_inside_of(BUTTON *button, int x, int y);

/* set_button_action
 * Establece la accion a ejecutar por un boton dado
 *
 * button: Puntero al boton a configurar
 * action: Puntero a funcion a llamar cuando se apreta boton
 */
void set_button_action(BUTTON *button, void (*action)(void*));

/* create_button
 * Crea un boton con sus carateristicas basicas
 * 
 * x:       Coordenada x de la posicion del boton
 * y:       Coordenada y de la posicion del boton
 * width:   Ancho del boton
 * height:  Alto del boton
 * str:     Texto del boton
 * bg:      Color de fondo en el boton
 * fg:      Color del texto en el boton
 * lc:      Color de la linea borde del boton
 * pc:      Color de presion del boton
 * action: Funcion a llamar en evento OnClick
 */
BUTTON create_button(uint16_t id, uint8_t x, uint8_t y, uint16_t width, uint16_t height, const char *str, ALLEGRO_COLOR bg, ALLEGRO_COLOR fg, ALLEGRO_COLOR lc, ALLEGRO_COLOR pc, ALLEGRO_COLOR fc);
 
/* destroy_button
 * Destruye el boton, liberando la memoria que lo contenia
 * 
 * button: Puntero a la instancia del boton
 */
void destroy_button(BUTTON *button);

/* create_button_bitmap
 * Crea el bitmap de un boton segun sus caracteristicas
 * 
 * button: Puntero a la instancia del boton
 */
void create_button_bitmap(BUTTON *button);

/* update_button
 * Actualiza el boton, sus estados y atributos
 * 
 * button: Puntero a la instancia del boton
 */
void update_button(BUTTON *button);

/* manager_init
 * Inicializa todos los modulos y parametros necesarios
 * para el correcto funcionamiento de la libreria
 */
bool manager_init(void);
        
#endif /* WINDOW_MANAGER_H */
