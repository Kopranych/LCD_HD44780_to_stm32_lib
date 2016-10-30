#include "stm32f4xx.h"                  // Device header

#include "interrupt.h"
#include "LCD_HD44780.h"

int main()
{

	init_delay();
	delay_ms(20);
	LCD_init_pin();
	LCD_init();
	
	
	
		LCD_write(65, RS_DATA);
		LCD_write_str("Hello");

}
