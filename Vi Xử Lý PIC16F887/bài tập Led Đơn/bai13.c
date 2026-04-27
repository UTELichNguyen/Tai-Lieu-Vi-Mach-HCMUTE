#include <16F887.h>
#FUSES NOWDT, PUT, HS, NOPROTECT, NOLVP
#USE DELAY(CLOCK=20M)
unsigned int32 y_save;
unsigned int32 y_run;
signed int i, j;
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
   while(TRUE) {
      y_save = 0;
      xuat_32_led(y_save);
      for(i = 15; i >= 0; i--) {
         for(j = 0; j <= i; j++) {
            y_run = ((unsigned int32)1 << j) | ((unsigned int32)1 << (31 - j));
            xuat_32_led(y_save | y_run);
            delay_ms(30);
         }
         y_save = y_save | y_run;
      }
      delay_ms(500);
   }
}


