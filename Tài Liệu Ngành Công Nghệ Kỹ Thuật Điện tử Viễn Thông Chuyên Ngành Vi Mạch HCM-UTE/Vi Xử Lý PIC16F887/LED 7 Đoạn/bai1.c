#include <16F887.h>
#fuses NOWDT, PUT, HS, NOPROTECT, NOLVP
#use delay(clock=20M)
const unsigned char ma7doan[16] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};
void main() {
    set_tris_b(0x00);
    set_tris_d(0x00);
    output_d(0x00); 
    unsigned char data_hien_thi[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    int i;
    while(true) {
        for(i = 0; i < 8; i++) {
            output_b(ma7doan[data_hien_thi[i]]); 
            output_d(1 << i);                 
            delay_ms(5);                        
            output_d(0x00);                      
        }
    }
}
