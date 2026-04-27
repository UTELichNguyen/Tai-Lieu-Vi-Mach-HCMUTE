#include <16F887.h>
#fuses NOWDT, PUT, HS, NOPROTECT, NOLVP
#use delay(clock=20M)
const unsigned char ma7doan[16] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};
void main() {
    set_tris_b(0x00); 
    set_tris_d(0x00); 
    output_d(0x00); 
    int gio = 0, phut = 0, giay = 0; 
    int i, lan_quet; 
    unsigned char bo_dem_hien_thi[8]; 
    while(true) {
        bo_dem_hien_thi[0] = ma7doan[gio / 10]; 
        bo_dem_hien_thi[1] = ma7doan[gio % 10];
        bo_dem_hien_thi[2] = 0xBF; // Dau gach ngang "-"
        bo_dem_hien_thi[3] = ma7doan[phut / 10];
        bo_dem_hien_thi[4] = ma7doan[phut % 10];
        bo_dem_hien_thi[5] = 0xBF; // Dau gach ngang '-'
        bo_dem_hien_thi[6] = ma7doan[giay / 10];
        bo_dem_hien_thi[7] = ma7doan[giay % 10];
        for(lan_quet = 0; lan_quet < 2; lan_quet++) {
            for(i = 0; i < 8; i++) {
                output_b(bo_dem_hien_thi[i]);   
                output_d(1 << i);        
                delay_ms(1);                    
                output_d(0x00);           
            }
        }
        giay++;
        if(giay == 60) {
            giay = 0;
            phut++;
            if(phut == 60) {
                phut = 0;
                gio++;
                if(gio > 12) gio = 1;
            }
        }
    }
}
