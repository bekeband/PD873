
//
// PROCESSOR : PIC16F873
// CLOCK	 : 20MHz, EXTERNAL


#include  <stdio.h>
#include  <stdint.h>
#include  <pic16f873.h>
#include  "delay.h"
#include  "lcddriver.h"
#include  "buttons.h"
#include  "beeps.h"

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low Voltage In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = ON         // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

#define	LED			PORTBbits.RB4
#define	RELAY		PORTAbits.RA1

#define VERH  2
#define VERL  1

#define TMR0DATA  (0x080)
#define TMR2DATA  (0x06)  // 256 - 250 5M/16 = 312500 / 250 = 1250/s

#define MAIN_DISPLAY  56
#define MENU_DISPLAY  65

typedef struct {
  union {
    unsigned DISPLAY_REFRESH: 1;
    unsigned AD_REFRESH:      1;
  };
  union {
    uint8_t STATUS_BYTE;
  };
} s_status;

typedef struct  {
  uint8_t serial_speed;
  uint8_t button_beep;
  uint16_t display_refresh_time;
}s_setting_datas;

typedef struct s_analog_data {
  uint8_t input_type; // 0 = 4 - 20 mA, 1 = 0- 20 mA
  float min_val;
  float max_val;
  uint16_t min_eng;
  uint16_t max_eng;
  uint8_t input_dim;
  uint8_t average;
  float summa;
} s_analog_datas;

unsigned  char but;

unsigned char WELCOME[] = "PD873 VER %i.%i";
unsigned char bname[10];

s_setting_datas settings = {9600, 0, 625};
s_analog_datas analogs;

unsigned char DPBUFFER[20];
unsigned int next_ad_data;

unsigned int MAIN_STATE = MAIN_DISPLAY;

/* display refresh counter to display refresh time calculating.. */
static unsigned int display_refresh_counter = 0;

/* A/D average counters, and datas.*/
unsigned long int AD_SUMMA = 0;
unsigned int AD_OVERSAMPLE_COUNTER = 0;
unsigned int AD_VALUE;

s_status PROGRAM_STATUS;    // Program status. and flags.

void interrupt isr(void)
{
  if (PIR1bits.TMR2IF)
  {
    PIR1bits.TMR2IF = 0;
    if (display_refresh_counter++ >= settings.display_refresh_time)
    {
      display_refresh_counter = 0;
      PROGRAM_STATUS.DISPLAY_REFRESH = 1; //
    }

  };
  if (INTCONbits.TMR0IF)
  {
    INTCONbits.TMR0IF = 0;
  }
  if (PIR1bits.ADIF)
  {
    PIR1bits.ADIF = 0;
    next_ad_data = (ADRESL + (ADRESH * 256));
    next_ad_data >>= 6;
    AD_SUMMA += next_ad_data;
    if (AD_OVERSAMPLE_COUNTER++ >= 1024)
    {
      AD_VALUE = AD_SUMMA >> 5;
      AD_SUMMA = 0;
      PROGRAM_STATUS.AD_REFRESH = 1;
      AD_OVERSAMPLE_COUNTER = 0;
//      LED = !LED;
    }
    ADCON0bits.GO = 1;  /* Restart A/D conversion. */
  }
};

void menu_display()
{
  switch (but)
  {
    case BUT_ES_OFF:
      MAIN_STATE = MAIN_DISPLAY;
      break;
  }
}

void main_display()
{
  if (PROGRAM_STATUS.AD_REFRESH)
  {
    sprintf(DPBUFFER, "%6i", AD_VALUE);
    LCDSendCmd(DD_RAM_ADDR2);
    LCDSendStr(DPBUFFER);
    PROGRAM_STATUS.DISPLAY_REFRESH = 0;
    PROGRAM_STATUS.AD_REFRESH = 0;
  }
  switch (but)
  {
    case BUT_OK_OFF:
      MAIN_STATE = MENU_DISPLAY;
      break;
  }
}

// main function
void main( void ) {

	TRISAbits.TRISA1 = 0;	// RELAY pin as output
  TRISAbits.TRISA4 = 0; // freq pin as output.

	//OPTION 	= 0x80;		// PORTB pull-ups are disabled
  TRISBbits.TRISB5 = 0;
  TRISBbits.TRISB4 = 0;
  OUTBUZZERPORTS

  T2CONbits.TOUTPS = 0b1111;
  T2CONbits.T2CKPS = 0b10;
  PR2 = TMR2DATA;
  PIE1bits.TMR2IE = 1;
  T2CONbits.TMR2ON = 1;

  InitButtons();

  InitLCD();
	LCDSendCmd(DISP_ON);
	LCDSendCmd(CLR_DISP);
  sprintf(DPBUFFER, WELCOME, VERH, VERL);
	LCDSendStr(DPBUFFER);

  ADCON0bits.ADON = 0;
//  ADCON1bits.PCFG = 0b1110;//
  ADCON1 = 0b00101110;
  ADCON0bits.ADCS = 0b01;
  ADCON0bits.ADON = 1;
  PIR1bits.ADIF = 0;
  PIE1bits.ADIE = 1;  // Enable A/D interrupt
  INTCONbits.PEIE = 1;
  INTCONbits.GIE = 1;
  ADCON0bits.GO = 1;  // First start A/D conversion.

	while(1) {

		// Scan Button
	 	but = ButtonScan();

    switch (MAIN_STATE)
    {
      case MAIN_DISPLAY:
        main_display();
        break;
      case MENU_DISPLAY:
        menu_display();
        break;
    }


	}
}
