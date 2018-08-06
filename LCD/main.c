#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL

#include <lcd.h>


int main(void)
{
    config_LCD();
    goto_location(1,1);
    send_string("Hello World!");
	
    while (1) 
    {
    }
}

