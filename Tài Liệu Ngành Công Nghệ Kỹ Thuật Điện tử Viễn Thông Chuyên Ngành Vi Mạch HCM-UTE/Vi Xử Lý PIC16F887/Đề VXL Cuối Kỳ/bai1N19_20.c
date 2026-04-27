#include <16F887.h>
#fuses HS,NOWDT,NOPUT,NOLVP,NOPROTECT
#use delay(clock=8M)
#define ADJ PIN_E0
unsigned int8 ma7doan[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned int8 level=0;
void main(){
    set_tris_d(0x00);
    set_tris_e(0xFF);
    set_tris_c(0x00);
    output_d(ma7doan[level]);
    setup_ccp1(CCP_PWM);
    setup_timer_2(T2_DIV_BY_16,249,1);
    set_pwm1_duty(0);
    while(TRUE){
        if(input(ADJ)==0){
            delay_ms(20);
            if(input(ADJ)==0){
                level++;
                if(level>9) level=0;
                output_d(ma7doan[level]);
                set_pwm1_duty((int16)level*100);
                while(input(ADJ)==0);
                delay_ms(20);
            }
        }
    }
}

