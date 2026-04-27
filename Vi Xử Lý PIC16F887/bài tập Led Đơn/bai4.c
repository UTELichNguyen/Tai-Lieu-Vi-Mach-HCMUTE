#include <16F887.h>
#fuses HS, NOWDT, PUT, MCLR, NOPROTECT, NOLVP
#use delay(clock=20000000)
void main()
{
   int16 y; 
   int8 i;
   set_tris_c(0x00);
   set_tris_d(0x00);
   output_c(0x00);
   output_d(0x00);
   while(TRUE)
   {
      y = 0x0000;
      for(i = 0; i < 16; i++)
      {
         y = (y << 1) | 0x0001;
         output_c((int8)y);         
         output_d((int8)(y >> 8));  
         delay_ms(200);
      }
      for(i = 0; i < 16; i++)
      {
         y = y << 1;
         output_c((int8)y);         
         output_d((int8)(y >> 8));  
         delay_ms(200);
      }
   }
}


