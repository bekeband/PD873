/* 
 * File:   maindisplay.h
 * Author: user
 *
 * Created on 2015. október 7., 13:34
 */

#ifndef MAINDISPLAY_H
#define	MAINDISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
  
extern s_status PROGRAM_STATUS;    // Program status. and flags.
extern unsigned  char but;
extern unsigned int MAIN_STATE;
extern unsigned int AD_VALUE;
extern unsigned char DPBUFFER[20];

void main_display();


#ifdef	__cplusplus
}
#endif

#endif	/* MAINDISPLAY_H */

