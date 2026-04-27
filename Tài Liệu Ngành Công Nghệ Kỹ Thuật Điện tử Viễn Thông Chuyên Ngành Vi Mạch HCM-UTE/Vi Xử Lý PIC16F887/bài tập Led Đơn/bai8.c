#include <16F887.h>
#fuses INTRC_IO, NOWDT, PUT, MCLR, NOPROTECT, NOLVP
#use delay(clock=8000000)
#define TIME_DELAY 100
void xuat_32led(int32 z)
{
   output_a((int8)z);
   output_b((int8)(z >> 8));
   output_c((int8)(z >> 16));
   output_d((int8)(z >> 24));
}
void main()
{
   int32 y;
   int8 i;
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   while(TRUE)
   {
      y = 0;
      
      for(i = 0; i < 32; i++)
      {
         y = (y << 1) | 1;
         xuat_32led(y);
         delay_ms(TIME_DELAY);
      }

      for(i = 0; i < 32; i++)
      {
         y = y << 1;
         xuat_32led(y);
         delay_ms(TIME_DELAY);
      }
   }
}



