
#include <lcd.h>

int len=0;

void flash_enable(void)						//enable lcd
{
	CONTROL_PIN_PORT |= 1<<ENABLE;
	asm volatile ("nop");
	asm volatile ("nop");
	CONTROL_PIN_PORT &= ~(1<<ENABLE);

}
void config_LCD(void)
{
	DDR_CONTROL_PIN |= (1<<ENABLE)|(1<<CMD_CHAR)|(1<<W_R);	//set data direction as output
	_delay_ms(15);
	send_command(0x38);										//8 bit 2 line mode
	_delay_us(4500);
	send_command(0x38);										//8 bit 2 line mode
	_delay_us(4500);
	send_command(0x38);										//8 bit 2 line mode
	_delay_us(150);
	send_command(0x01);										//clr screen
	_delay_ms(2);
	send_command(0b00001110);								//LCD on ,cursor on,blink off
	_delay_ms(2);
	
}
void send_command(uint8_t command)
{
	lcd_busy();							//check if lcd is busy
	DATA_PORT=command;
	CONTROL_PIN_PORT &= ~(1<<CMD_CHAR);	//command mode
	CONTROL_PIN_PORT &= ~(1<<W_R);		//write mode
	flash_enable();						//enable lcd
	DATA_PORT=0x00;
}
void lcd_busy(void)
{
	DDR_DATA_PORT = 0;
	CONTROL_PIN_PORT &= ~(1<<CMD_CHAR);	//command mode
	CONTROL_PIN_PORT |= (1<<W_R);		//read mode
	while(DATA_PORT >= 0X80)			//wait till lcd is free
	{
		flash_enable();
	}
	DDR_DATA_PORT = 0xFF;
}
void send_char(unsigned char character)
{
	lcd_busy();
	DATA_PORT=character;
	CONTROL_PIN_PORT |= (1<<CMD_CHAR);	//data mode
	CONTROL_PIN_PORT &= ~(1<<W_R);		//write mode
	flash_enable();
	DATA_PORT=0x00;
	_delay_us(800);
}
void send_string(char *string)
{
	len=1;
	while(*string > 0)
	{
		if(len==17)
		send_command(0xC0);
		send_char(*string);
		string++;
		len++;
	}
	len=0;
}
void send_double(double numb)
{
	char a[10];
	dtostrf(numb,8,2,a);		//convert double to string
	send_string(a);
}
void send_integer(double numb)
{
	char b[10];
	itoa(numb,b,10);			//convert integer to string
	send_string(b);
}
void goto_location(int x,int y)
{
	if (y == 2)
	{
		send_command(0x80 + 64 + x -1);
		_delay_us(4500);
	}
	else if (y == 1)
	{
		send_command(0x80 + x -1);
		_delay_us(4500);
	}
}




