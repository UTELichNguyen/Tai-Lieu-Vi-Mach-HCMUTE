#include <16F887.h>
#fuses NOWDT, PUT, HS, NOPROTECT, NOLVP
#use delay(clock=20M)
const unsigned char ma7doan[10] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,
    0x92, 0x82, 0xF8, 0x80, 0x90
};
#define DO_1    PIN_C0
#define VANG_1  PIN_C1
#define XANH_1  PIN_C2
#define DO_2    PIN_C3
#define VANG_2  PIN_C4
#define XANH_2  PIN_C5
void main(){
    set_tris_b(0x00);
    set_tris_c(0x00);
    set_tris_d(0x00);
    output_c(0x00);
    output_d(0x00);
    int thoi_gian_1=12;
    int thoi_gian_2=15;
    int trang_thai=0;
    int i,lan_quet;
    unsigned char bo_dem_hien_thi[8];
    output_high(XANH_1);
    output_high(DO_2);
    while(true){
        bo_dem_hien_thi[0]=ma7doan[thoi_gian_1/10];
        bo_dem_hien_thi[1]=ma7doan[thoi_gian_1%10];
        bo_dem_hien_thi[2]=ma7doan[thoi_gian_2/10];
        bo_dem_hien_thi[3]=ma7doan[thoi_gian_2%10];
        bo_dem_hien_thi[4]=0xFF;
        bo_dem_hien_thi[5]=0xFF;
        bo_dem_hien_thi[6]=0xFF;
        bo_dem_hien_thi[7]=0xFF;
        for(lan_quet=0;lan_quet<85;lan_quet++){
            for(i=0;i<8;i++){
                output_b(bo_dem_hien_thi[i]);
                output_d(1<<i);
                delay_ms(1);
                output_d(0x00);
            }
        }
        thoi_gian_1--;
        thoi_gian_2--;
        if(thoi_gian_1==0||thoi_gian_2==0){
            if(trang_thai==0){
                trang_thai=1;
                thoi_gian_1=3;
                output_low(XANH_1);
                output_high(VANG_1);
            }
            else if(trang_thai==1){
                trang_thai=2;
                thoi_gian_1=15;
                thoi_gian_2=12;
                output_low(VANG_1);
                output_low(DO_2);
                output_high(DO_1);
                output_high(XANH_2);
            }
            else if(trang_thai==2){
                trang_thai=3;
                thoi_gian_2=3;
                output_low(XANH_2);
                output_high(VANG_2);
            }
            else if(trang_thai==3){
                trang_thai=0;
                thoi_gian_1=12;
                thoi_gian_2=15;
                output_low(VANG_2);
                output_low(DO_1);
                output_high(XANH_1);
                output_high(DO_2);
            }
        }
    }
}
