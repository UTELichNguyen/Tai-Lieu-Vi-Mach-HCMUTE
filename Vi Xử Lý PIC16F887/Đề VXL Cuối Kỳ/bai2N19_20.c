#include <16F887.h>
#device ADC=10
#fuses HS,NOWDT,PUT,MCLR,NOPROTECT,NOLVP
#use delay(clock=20000000)
#include <lcd.c>
void main(){
    unsigned int16 kq_adc;
    unsigned int8 nhiet_do;
    unsigned int8 san_pham=0;
    unsigned int16 hop=0;
    int1 timer_dang_chay=1;
    set_tris_e(0xFF);
    set_tris_c(0xFF);
    set_tris_d(0x00);
    lcd_init();
    setup_adc(ADC_CLOCK_DIV_32);
    setup_adc_ports(sAN5|VSS_VDD);
    set_adc_channel(5);
    delay_us(10);
    setup_timer_1(T1_EXTERNAL|T1_DIV_BY_1);
    set_timer1(0);
    while(TRUE){
        kq_adc=read_adc();
        nhiet_do=kq_adc/2.046;
        if(nhiet_do<=100){
            if(timer_dang_chay==0){
                setup_timer_1(T1_EXTERNAL|T1_DIV_BY_1);
                timer_dang_chay=1;
            }
        }else{
            if(timer_dang_chay==1){
                setup_timer_1(T1_DISABLED);
                timer_dang_chay=0;
            }
        }
        san_pham=get_timer1();
        if(san_pham>50){
            hop++;
            set_timer1(san_pham-50);
            san_pham=get_timer1();
        }
        lcd_gotoxy(1,1);
        printf(lcd_putc,"P=%02u     T=%03u%cC",san_pham,nhiet_do);
        lcd_gotoxy(1,2);
        printf(lcd_putc,"Box=%05lu       ",hop);
        delay_ms(100);
    }
}
