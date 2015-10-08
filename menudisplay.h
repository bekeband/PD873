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

typedef struct s_menu_item {
  char* title;
  union {
    unsigned next: 1;
    unsigned prev: 1;
  };
  union {
  uint8_t features;
  };
};

#ifdef	__cplusplus
}
#endif

#endif	/* MENUDISPLAY_H */

