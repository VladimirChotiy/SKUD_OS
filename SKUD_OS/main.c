/*
 * SKUD_OS.c
 *
 * Created: 29.09.2020 21:38:41
 * Author : Vladimir Chotiy
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	//Port init
	DDRB = (1 << DDB0);
	PORTB = (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4);
	
    while (1) 
    {
		PORTB |= (1<<PORTB0);
    }
}



