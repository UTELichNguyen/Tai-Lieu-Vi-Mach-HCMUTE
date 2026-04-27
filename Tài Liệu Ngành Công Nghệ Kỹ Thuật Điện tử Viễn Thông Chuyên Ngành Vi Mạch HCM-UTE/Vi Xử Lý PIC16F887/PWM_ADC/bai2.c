#include <16F887.h>
#device ADC=10
#fuses HS, NOWDT, NOPUT, NOLVP, NOPROTECT
#use delay(clock=20M)
#define LCD_ENABLE_PIN  PIN_E2
#define LCD_RS_PIN      PIN_E0
#define LCD_RW_PIN      PIN_E1
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7
#include <lcd.c>
unsigned int16 ket_qua_adc;
unsigned int8 nhiet_do_do;
unsigned int8 nhiet_do_dat = 37;
signed int8 do_lech;
unsigned int16 gia_tri_pwm;
unsigned int8 phan_tram_pwm;
unsigned int8 i;
unsigned int32 tong_adc;
void main() {
    set_tris_a(0xFF); 
    set_tris_d(0x00); 
    set_tris_e(0x00); 
    set_tris_c(0x00); 
    lcd_init();
    lcd_gotoxy(1, 1);
    printf(lcd_putc, "Nhiet do: ");
    lcd_gotoxy(1, 2);
    printf(lcd_putc, "Cong suat: ");
    setup_adc(ADC_CLOCK_DIV_32);
    setup_adc_ports(sAN0 | VSS_VDD);
    set_adc_channel(0);
    setup_ccp1(CCP_PWM);
    setup_timer_2(T2_DIV_BY_16, 249, 1);
    set_pwm1_duty(0);
    while(TRUE) {
        tong_adc = 0;
        for(i = 0; i < 100; i++) {
            tong_adc = tong_adc + read_adc();
            delay_ms(1);
        }
        ket_qua_adc = tong_adc / 100;
        nhiet_do_do = ket_qua_adc / 2.046;
        do_lech = nhiet_do_dat - nhiet_do_do;
        if (do_lech <= 0) {
            phan_tram_pwm = 0;
            gia_tri_pwm = 0;
        } 
        else if (do_lech >= 10) {
            phan_tram_pwm = 100;
            gia_tri_pwm = 1000;
        } 
        else {
            phan_tram_pwm = do_lech * 10; 
            gia_tri_pwm = do_lech * 100;
        }
        set_pwm1_duty(gia_tri_pwm);
        lcd_gotoxy(11, 1);
        printf(lcd_putc, "%02u C", nhiet_do_do);
        lcd_gotoxy(12, 2);
        printf(lcd_putc, "%03u %%", phan_tram_pwm);
    }
}
