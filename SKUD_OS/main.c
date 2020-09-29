/*
 * SKUD_OS.c
 *
 * Created: 29.09.2020 21:38:41
 * Author : Vladimir Chotiy
 */ 
#define F_CPU 9600000UL
#define r_active 1
#define r_nonactive 0

#include <avr/io.h>
#include <util/delay.h>

uint8_t s_ready;
uint8_t nc_last_state;
uint8_t no_last_state;


void SetPulse(void){
	s_ready = 0;
	PORTB |= (1<<PORTB0);
	_delay_ms(1000);
	PORTB &= ~(1<<PORTB0);
	_delay_ms(1000);
	s_ready = 1;
}

int main(void)
{
    /* Replace with your application code */
	//Port init
	DDRB = (1 << DDB0);
	PORTB = (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4);
	s_ready = r_active;
	
    while (1) 
    {
		if((PINB & (1<<PINB3))) nc_last_state = r_active;
		if((PINB & (1<<PINB4))) no_last_state = r_active;
		
		if((!(PINB & (1<<PINB1))) && (s_ready == 1)){
			if((!(PINB & (1<<PINB3))) && (nc_last_state == r_active)){
				_delay_ms(50);
				if(!(PINB & (1<<PINB3))){
					nc_last_state = r_nonactive;
					SetPulse();
				}
			}
		}else{
			if((!(PINB & (1<<PINB4))) && (no_last_state == r_active)){
				_delay_ms(50);
				if(!(PINB & (1<<PINB4))){
					no_last_state = r_nonactive;
					SetPulse();
				}
			}
		}
    }
}



