#include <16F887.h>
#FUSES NOWDT, PUT, INTRC_IO, NOPROTECT, NOLVP
#USE DELAY(CLOCK=8M)
unsigned int32 y;
int i;
void xuat_32_led(unsigned int32 data) {
   output_d((int8)(data >> 24));
   output_c((int8)(data >> 16));
   output_b((int8)(data >> 8));
   output_a((int8)(data));
}
void main() {
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   y = 0;
   xuat_32_led(y);
   while(TRUE) {
      for(i = 0; i < 32; i++) {
         y = (y >> 1) | 0x80000000;
         xuat_32_led(y);
         delay_ms(100);
      }
      for(i = 0; i < 32; i++) {
         y = y >> 1;
         xuat_32_led(y);
         delay_ms(100);
      }
   }
}


