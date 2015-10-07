
#include <pic.h>

void ReadDataEEP(char* d_ptr, int baddr, int size)
{ int i;
  for (i=0; i < size; i++)
  {
    *d_ptr++ = eeprom_read(baddr++);
//    *d_ptr++ = Read_b_eep(baddr++);
  }
}

void WriteDataEEP(unsigned char* d_ptr, int baddr, int size)
{int i;
  for (i = 0; i < size; i++)
  {
    eeprom_write(baddr++, *d_ptr++);
//    Write_b_eep(baddr++, *d_ptr++);
  }
}

