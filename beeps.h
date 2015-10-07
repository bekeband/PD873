/* 
 * File:   beeps.h
 * Author: user
 *
 * Created on 2015. október 1., 11:35
 */

#ifndef BEEPS_H
#define	BEEPS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define OUTBUZZERPORTS TRISC &= 0b11001111;

#define	BUZZ1		PORTCbits.RC4
#define	BUZZ2		PORTCbits.RC5

void Beep1(void);
void Beep2(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BEEPS_H */

