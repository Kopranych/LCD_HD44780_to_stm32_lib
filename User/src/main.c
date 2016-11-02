#include "stm32f4xx.h"                  // Device header

#include "interrupt.h"
#include "LCD_HD44780.h"

int main()
{
	
	init_delay();
	delay_ms(20);
	LCD_init_pin();
	LCD_init();
	GPIO_SetBits(GPIOD, GPIO_Pin_13);
	
	while(1)
	{
		clean_display();
		LCD_write(65, RS_DATA);
		delay_ms(200);
		clean_display();
		LCD_write_str("Hello");
		delay_ms(200);
	}
	

}
