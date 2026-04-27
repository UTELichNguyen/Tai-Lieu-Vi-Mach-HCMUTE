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
unsigned int16 xung=0;
unsigned int32 toc_do=0;
void main(){
lcd_init();
setup_timer_1(T1_EXTERNAL|T1_DIV_BY_1);
while(true){
set_timer1(0);
delay_ms(1000);
xung=get_timer1();
toc_do=(xung*60)/100;
lcd_gotoxy(1,1);
printf(lcd_putc,"Toc do: %lu RPM ",toc_do);}}
