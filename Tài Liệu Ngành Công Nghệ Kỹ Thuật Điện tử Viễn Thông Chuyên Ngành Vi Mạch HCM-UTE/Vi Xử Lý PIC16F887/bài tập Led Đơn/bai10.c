#include <16F887.h>
#FUSES NOWDT, PUT, INTRC_IO, NOPROTECT, NOLVP
#USE DELAY(CLOCK=8M)
unsigned int32 y;
void xuat_32_led(unsigned int32 data) {
   output_d((int8)(data >> 24));
   output_c((int8)(data >> 16));
   output_b((int8)(data >> 8));
   output_a((int8)(data));
}
void chop_tat_5_lan() {
   int i;
   for(i = 0; i < 5; i++) {
      xuat_32_led(0xFFFFFFFF);
      delay_ms(500);
      xuat_32_led(0x00000000);
      delay_ms(500);
   }
}
void sang_tat_dan_phai_sang_trai_2_lan() {
   int k, i;
   for(k = 0; k < 2; k++) {
      y = 0;
      for(i = 0; i < 32; i++) {
         y = (y << 1) | 1;
         xuat_32_led(y);
         delay_ms(200);
      }
      for(i = 0; i < 32; i++) {
         y = (y << 1);
         xuat_32_led(y);
         delay_ms(200);
      }
   }
}
void sang_tat_dan_trai_sang_phai_2_lan() {
   int k, i;
   for(k = 0; k < 2; k++) {
      y = 0;
      for(i = 0; i < 32; i++) {
         y = (y >> 1) | 0x80000000;
         xuat_32_led(y);
         delay_ms(200);
      }
      for(i = 0; i < 32; i++) {
         y = (y >> 1);
         xuat_32_led(y);
         delay_ms(200);
      }
   }
}
void sang_tat_dan_ngoai_vao_2_lan() {
   int k, i;
   for(k = 0; k < 2; k++) {
      y = 0;
      for(i = 0; i < 16; i++) {
         y = y | ((unsigned int32)1 << i) | ((unsigned int32)1 << (31 - i));
         xuat_32_led(y);
         delay_ms(300);
      }
      for(i = 0; i < 16; i++) {
         y = y & ~(((unsigned int32)1 << i) | ((unsigned int32)1 << (31 - i)));
         xuat_32_led(y);
         delay_ms(300);
      }
   }
}
void sang_tat_dan_trong_ra_2_lan() {
   int k, i;
   for(k = 0; k < 2; k++) {
      y = 0;
      for(i = 0; i < 16; i++) {
         y = y | ((unsigned int32)1 << (15 - i)) | ((unsigned int32)1 << (16 + i));
         xuat_32_led(y);
         delay_ms(300);
      }
      for(i = 0; i < 16; i++) {
         y = y & ~(((unsigned int32)1 << (15 - i)) | ((unsigned int32)1 << (16 + i)));
         xuat_32_led(y);
         delay_ms(300);
      }
   }
}
void main() {
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   xuat_32_led(0);
   while(TRUE) {
      // 1. 32 led chop tat 5 lan
      chop_tat_5_lan();
      // 2. 32 led sang dan va tat dan phai sang trai 2 lan
      sang_tat_dan_phai_sang_trai_2_lan();
      // 3. 32 led chop tat 5 lan
      chop_tat_5_lan();
      // 4. 32 led sang dan va tat dan trai sang phai 2 lan
      sang_tat_dan_trai_sang_phai_2_lan();
      // 5. 32 led sang dan va tat dan tu ngoai vao 2 lan
      sang_tat_dan_ngoai_vao_2_lan();
      // 6. 32 led chop tat 5 lan
      chop_tat_5_lan();
      // 7. 32 led sang dan va tat dan tu trong ra 2 lan
      sang_tat_dan_trong_ra_2_lan();
   }
}
