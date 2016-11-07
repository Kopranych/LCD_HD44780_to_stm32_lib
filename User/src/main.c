#include "stm32f4xx.h"                  // Device header

#include "interrupt.h"
#include "LCD_HD44780.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void)
{
	init_delay();
	delay_ms(100);
	int8_t hour, minuts, second;
	char HOUR[2], MINUTS[2], SECOND[2];
	LCD_init_pin();
	LCD_init();
	GPIO_SetBits(GPIOD, GPIO_Pin_13);
	for(;;)
	{
		for(hour = 0; hour<24; hour++)
		{
			if(hour<10)
			{	
				my_itoa(hour, HOUR, 10);
				LCD_write_adress(0x30, FIRST);//
				LCD_write_str(HOUR);
				LCD_write(0x3A,RS_DATA);
			}
			else
			{
				my_itoa(hour, HOUR, 10);
				kursor_adress(FIRST);
				LCD_write_str(HOUR);
				LCD_write(0x3A,RS_DATA);
			}
			for(minuts = 0; minuts<60; minuts++)
			{
				if(minuts<10)
				{
					my_itoa(minuts, MINUTS, 10);
					LCD_write_adress(0x30, FOURTH);
					LCD_write_str(MINUTS);
					LCD_write(0x3A,RS_DATA);
				}
				else
				{
					my_itoa(minuts, MINUTS, 10);
					kursor_adress(FOURTH);
					LCD_write_str(MINUTS);
					LCD_write(0x3A,RS_DATA);
				}				
				for(second = 0; second<60; second++)
				{
					if(second<10)
					{
						my_itoa(second, SECOND, 10);
						LCD_write_adress(0x30, SEVENTH);
						LCD_write_str(SECOND);
					}
					else 
					{
						kursor_adress(SEVENTH);
						my_itoa(second, SECOND, 10);
						LCD_write_str(SECOND);
					}
					delay_ms(850);

/*					itoa(hour, BUF_H, 10);
					itoa(minuts, BUF_M, 10);
					itoa(second, BUF_S, 10);
					strcat(BUF_H,':');
					strcat(BUF_M,':');
					strcat(BUF_H,BUF_M);
					strcat(BUF_H,BUF_S);
					clean_display();
					line_wrapping(1);
					LCD_write_str(BUF_H);
*/				}
			}
		}
	}
	return;
}
