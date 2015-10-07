/* 
 * File:   menudisplay.h
 * Author: user
 *
 * Created on 2015. október 7., 13:49
 */

#ifndef MENUDISPLAY_H
#define	MENUDISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"

extern unsigned  char but;
extern unsigned int MAIN_STATE;
extern s_status PROGRAM_STATUS;    // Program status. and flags.
extern unsigned char DPBUFFER[20];
extern unsigned int MAIN_STATE;

void menu_display();

typedef struct {
  char* title;
  union {
    unsigned next: 1;
    unsigned prev: 1;
  };
  union {
  uint8_t features;
  };
}s_menu_item;

#ifdef	__cplusplus
}
#endif

#endif	/* MENUDISPLAY_H */

