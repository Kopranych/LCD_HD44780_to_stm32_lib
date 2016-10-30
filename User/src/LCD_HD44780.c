// ���������� ��� ������ � LCD HD44780 ��������


#include "LCD_HD44780.h"
#include "stm32f4xx.h"    
#include <stdlib.h>

GPIO_InitTypeDef PORT_LCD;// ��������� ��������� ��� ������������� ������

void LCD_init_pin(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//�������� ������������ ���� AHB1 �� ��� ����� D � A
	
	//������������� ������ ������ ����� E
	PORT_LCD.GPIO_Pin = RS|E|DB0|DB1|DB2|DB3;
	PORT_LCD.GPIO_Mode = GPIO_Mode_OUT;
	PORT_LCD.GPIO_Speed = GPIO_Low_Speed;
	PORT_LCD.GPIO_PuPd = GPIO_PuPd_NOPULL;
	PORT_LCD.GPIO_OType = GPIO_OType_PP;
	
	GPIO_Init(GPIOE, &PORT_LCD);// �������������� ���� �����

	
}


/////////////////////////////////////////
void LCD_init(void)
{	
	delay_ms(40);//
	PORT_LCD.GPIO_Mode = GPIO_Mode_OUT;//����� �� //�����//����������� ����� //�� �����
	//PORT_SIG &= ~(ON<<RW);//���� ������/������  �� ������
	delay_ms(40);
	LCD_write(BUS_LINE,RS_COM);//2 ����� ������, 4 ���� ����
	LCD_write(BUS_LINE,RS_COM);
	LCD_write(BUS_LINE,RS_COM);
	LCD_write(BUS_LINE,RS_COM);
	LCD_write(0x01,RS_COM);//������� ������
	LCD_write(0x06,RS_COM);//��������� ������ ����� �� ��������
	
	LCD_write(0x0C,RS_COM);//�������� �������

}

void LCD_write(uint16_t data, uint8_t BIT_RS)
{
	delay_ms(40);
//	LCD_read_BF();
	PORT_LCD.GPIO_Mode = GPIO_Mode_OUT;//�� �����
//	PORT_SIG &= ~(ON<<RW);
	if(BIT_RS == RS_COM)// ���� 0  
	{
		GPIO_ResetBits(PORT_SIG, RS);//�� �������
	} 
	else GPIO_SetBits(PORT_SIG, RS);// ����� 1 �� ������ 
	uint16_t tmp = data;//��������� ������ �� ���������
	uint16_t temp = GPIOB->IDR & 0xFE1F;// �������� ���� PB5,PB6,PB7,PB8 ��� ������ ���� ������
	temp |= (data &0xFFF0)<<1;// �������� ������� ������� ������ 
	GPIO_Write(PORT_DATA, temp);//�������� ������� � ����
	GPIO_SetBits(PORT_SIG, E);//����� �����
	delay_ms(2);
	GPIO_ResetBits(PORT_SIG, E);//����� ���� ������� ������� �� ������� 
	temp = GPIOB->IDR & 0xFE1F;// �������� ���� PB5,PB6,PB7,PB8 ��� ������ ���� ������
	temp|= (tmp&0xFF0F)<<5;// �������� ������� �������
	GPIO_Write(PORT_DATA, temp);//��������� ������� ������� � ����
	GPIO_SetBits(PORT_SIG, E);//����� �����
	delay_ms(2);
	GPIO_ResetBits(PORT_SIG, E);//����� ���� ������� ������� �� ������� 
//	_delay_ms(40);	

}

void LCD_write_adress(uint16_t data, uint16_t adress)
{
	delay_ms(40);
//	LCD_read_BF();
	LCD_write(adress, RS_COM);
	PORT_LCD.GPIO_Mode = GPIO_Mode_OUT;//�� �����
//	PORT_SIG &= ~(ON<<RW);
	GPIO_SetBits(PORT_SIG, RS);// ����� 1 �� ������ 
	uint16_t tmp = data;//��������� ������ �� ���������
	uint16_t temp = GPIOB->IDR & 0xFE1F;// �������� ���� PB5,PB6,PB7,PB8 ��� ������ ���� ������
	temp |= (data &0xFFF0)<<1;// �������� ������� ������� ������ 
	GPIO_Write(PORT_DATA, temp);//�������� ������� � ����
	GPIO_SetBits(PORT_SIG, E);//����� �����
	delay_ms(2);
	GPIO_ResetBits(PORT_SIG, E);//����� ���� ������� ������� �� ������� 
	temp = GPIOB->IDR & 0xFE1F;// �������� ���� PB5,PB6,PB7,PB8 ��� ������ ���� ������
	temp|= (tmp&0xFF0F)<<5;// �������� ������� �������
	GPIO_Write(PORT_DATA, temp);//��������� ������� ������� � ����
	GPIO_SetBits(PORT_SIG, E);//����� �����
	delay_ms(2);
	GPIO_ResetBits(PORT_SIG, E);//����� ���� ������� ������� �� ������� 
	delay_ms(40);	
}

void LCD_write_str(int8_t *string)
{
	while(*string)
	{
		LCD_write(*string,RS_DATA);
		string++;
	}
}

void line_wrapping(int8_t number)
{
	if(number == 1)
	{
	 LCD_write(FIRS_LINE,RS_COM); 
	}
	else
	 LCD_write(SEC_LINE,RS_COM);	
}

void clean_display(void)
{
	LCD_write(0x01,RS_COM);
}

void kursor_adress(uint8_t adress)
{
		LCD_write(adress, RS_COM);
}

/*inline void LCD_alignment(int16_t str, uint8_t adress)
{	
	uint16_t buffer[] = {' ',' ',' ',' '};
	uint16_t buffer1[] = {' ',' ',' ',' ',' '};
	itoa(str, buffer, 10);

	if (str < 0)
		{
			if (str > (-10))
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str(buffer1);
			}
			else if (str > (-100))
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("    ");
			}
			else if (str  >(-1000))
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("   ");
			}
			else if (str  <=(-1000))
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("   ");
			}
		}

		else
		{
			if (str < 10)
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("     ");
			}
			else if (str < 100)
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("    ");
			}
			else if (str < 1000)
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("   ");
			}
			else if (str >= 1000)
			{
				kursor_adress(adress);
				LCD_write_str(buffer);
				LCD_write_str("   ");
			}
		}
}


void LCD_read_BF()
{
	uint8_t tmp = 0;
	uint8_t data = 0;

	DDR_DATA &= 0x0F;
	PORT_DATA |= 0xF0;
	PORT_SIG |= (ON<<RW);
	PORT_SIG &= ~(ON<<RS);
	
	do{
	PORT_SIG|= (ON<<E);
	_delay_ms(10);
	data = PIN_DATA & 0xF0;
	PORT_SIG &= ~(ON<<E);
	
	tmp = data;
	PORT_SIG|= (ON<<E);
	_delay_ms(10);
	data = PIN_DATA & 0xF0;
	PORT_SIG &= ~(ON<<E);
	
	data = data>>4;
	tmp|=data;
	}while((tmp &(1<<BF))!=0);		
}
*/




