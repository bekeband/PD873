
#include "buttons.h"
#include "menudisplay.h"

void menu_display()
{
  switch (but)
  {
    case BUT_ES_OFF:
      MAIN_STATE = MAIN_DISPLAY;
      break;
  }
  if (PROGRAM_STATUS.MUST_REDRAW)
  {

  }
}

