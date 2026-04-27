#include <16f887.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=20M)
#define LCD_ENABLE_PIN PIN_E2
#define LCD_RS_PIN PIN_E0
#define LCD_RW_PIN PIN_E1
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>
unsigned int16 t1=0,t2=0,delta=0;
unsigned int8 state=0;
unsigned int32 toc_do=0;
#int_ccp1
void ccp1_isr(){
if(state==0){
t1=CCP_1;
state=1;}
else if(state==1){
t2=CCP_1;
delta=t2-t1;
state=0;}}
void main(){
lcd_init();
setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
setup_ccp1(CCP_CAPTURE_RE);
enable_interrupts(INT_CCP1);
enable_interrupts(GLOBAL);
while(true){
if(delta>0){
toc_do=375000/delta;
lcd_gotoxy(1,1);
printf(lcd_putc,"Toc do: %lu RPM ",toc_do);
delay_ms(200);}}}




