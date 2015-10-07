
#include <stdio.h>
#include "lcddriver.h"
#include "buttons.h"
#include "maindisplay.h"

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
    case BUT_RG_OFF:
      break;
  }
}


