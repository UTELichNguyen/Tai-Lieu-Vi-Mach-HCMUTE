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
unsigned int8 gio=0,phut=0,giay=0,bdn=0;
#int_timer0
void timer0_isr(){
set_timer0(61);
bdn++;
if(bdn>=100){
bdn=0;
giay++;
if(giay>=60){
giay=0;
phut++;
if(phut>=60){
phut=0;
gio++;
if(gio>=24) gio=0;}}}}
void main(){
lcd_init();
setup_timer_0(T0_INTERNAL|T0_DIV_256);
set_timer0(61);
enable_interrupts(INT_TIMER0);
enable_interrupts(GLOBAL);
while(true){
lcd_gotoxy(1,1);
printf(lcd_putc,"%02u:%02u:%02u",gio,phut,giay);}}



