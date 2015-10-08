
#include <stdio.h>
#include "lcddriver.h"
#include "buttons.h"
#include "maindisplay.h"

void main_display()
{
  if (PROGRAM_STATUS.AD_REFRESH)
  {
/*    sprintf(DPBUFFER, "%6i", AD_VALUE);
    LCDSendCmd(DD_RAM_ADDR2);
    LCDSendStr(DPBUFFER);*/
    PROGRAM_STATUS.DISPLAY_REFRESH = 0;
    PROGRAM_STATUS.AD_REFRESH = 0;
  }
}


