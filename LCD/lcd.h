#ifndef LCD_H_
#define LCD_H_

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/sfr_defs.h>

#define DATA_PORT			PORTD
#define DDR_DATA_PORT		DDRD
#define DATA_READ			PIND
#define D7					7
#define CONTROL_PIN_PORT	PORTB
#define DDR_CONTROL_PIN		DDRB
#define ENABLE				PINB2
#define W_R					PINB1
#define CMD_CHAR			PINB0

void flash_enable(void);
void send_char(unsigned char);
void send_command(uint8_t);
void lcd_busy(void);
void send_string(char *string);
void config_LCD(void);
void send_integer(double);
void send_double(double);
void goto_location(int,int);

#endif /* LCD_H_ */