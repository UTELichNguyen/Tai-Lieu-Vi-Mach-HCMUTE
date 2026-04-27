#include <16F887.h>
#fuses HS, NOWDT, PUT, MCLR, NOPROTECT, NOLVP
#use delay(clock=20000000)
void main()
{
   set_tris_c(0x00);
   set_tris_d(0x00);
   output_c(0x00);
   output_d(0x00);
   while(TRUE)
   {
      output_c(0xFF);
      output_d(0xFF);
      delay_ms(500);
      output_c(0x00);
      output_d(0x00);
      delay_ms(500);
   }
}



