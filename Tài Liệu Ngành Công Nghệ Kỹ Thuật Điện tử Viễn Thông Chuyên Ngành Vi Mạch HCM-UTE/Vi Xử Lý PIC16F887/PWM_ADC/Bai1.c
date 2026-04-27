#include <16f887.h>
#device ADC=10
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=20M)
unsigned int16 gia_tri_adc,he_so_chu_ky;
void main(){
setup_adc(ADC_CLOCK_INTERNAL);
setup_adc_ports(sAN0|VSS_VDD);
set_adc_channel(0);
setup_ccp1(CCP_PWM);
setup_timer_2(T2_DIV_BY_16,255,1);
set_pwm1_duty(0);
while(true){
gia_tri_adc=read_adc();
he_so_chu_ky=1023-gia_tri_adc;
set_pwm1_duty(he_so_chu_ky);
delay_ms(10);}}
