#include <16F887.h>
#fuses NOWDT, PUT, HS, NOPROTECT, NOLVP
#use delay(clock=20M)
const unsigned char chuoi_dich[30] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 8 khoang trang dau
    0xC6, 0x88, 0x8E, 0x86, 0xBF,                   // CAFE-
    0xC6, 0xC0, 0xC6, 0x88, 0xBF,                   // COCA-
    0xC6, 0xC0, 0xC7, 0x88,                         // COLA
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  // 8 khoang trang cuoi
};
void main() {
    set_tris_b(0x00); 
    set_tris_d(0x00); 
    output_d(0x00); 
    int k, i, scan;
    while(true) {
        for(k = 0; k <= 22; k++) {
            for(scan = 0; scan < 45; scan++) {
                for(i = 0; i < 8; i++) {
                    output_b(chuoi_dich[k + i]); 
                    output_d(1 << i);          
                    delay_ms(1);                
                    output_d(0x00);             
                }
            }
        }
    }
}
