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

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>

/**************/
/* Constantes */
/**************/

#define MAX_STRING 20

/************************/
/* Estructuras de datos */
/************************/

/* POSITION
 * Estructura para almacenar ubicacion (x,y) en display
 */
typedef struct{
    int x;
    int y;
} POSITION;

/* BUTTON
 * Estructura para control de botones en un display/ventana
 */
typedef struct{
    /* Position option */
    POSITION pos;
    
    /* Size options */
    int width;
    int height;
    
    /* Identifier options */
    int id;
    char text[MAX_STRING];
    
    /* Functionality options */
    int status;
    int isPressed;
    int isFocus;
    int enableHold;
    
    /* Color options */
    ALLEGRO_COLOR backgroundColor;
    ALLEGRO_COLOR foregroundColor;
    ALLEGRO_COLOR lineColor;
    ALLEGRO_COLOR pressedColor;
    ALLEGRO_COLOR focusColor;
    
    /* Bitmap layout */
    ALLEGRO_BITMAP *bitmap;
    
    /* OnClick action */
    void (*on_click)(void*);
    
} BUTTON;

/***************************/
/* Prototipos de funciones */
/***************************/

/* is_inside_of
 * Actualiza isFocus segun si la posicion (x,y) esta ubicada
 * dentro del boton que se pasa como parametro
 * 
 * x:       Coordenada x de la posicion
 * y:       Coordenada y de la posicion
 * button: Instancia del boton a verificar
 */
void is_inside_of(BUTTON *button, int x, int y);

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
BUTTON create_button(int x, int y, int width, int height, const char *str, ALLEGRO_COLOR bg, ALLEGRO_COLOR fg, ALLEGRO_COLOR lc, ALLEGRO_COLOR pc, ALLEGRO_COLOR fc, void (*action)(void*));

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

/* window_init
 * Inicializa todos los modulos y parametros necesarios
 * para el correcto funcionamiento de la libreria
 */
int window_init(void);
        
#endif /* WINDOW_MANAGER_H */
