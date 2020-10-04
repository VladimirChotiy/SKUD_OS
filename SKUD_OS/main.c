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
#include <avr/wdt.h>

uint8_t s_ready;
uint8_t nc_last_state;
uint8_t no_last_state;


void SetPulse(void){
	wdt_reset();
	s_ready = r_nonactive;
	PORTB |= (1<<PORTB0);
	_delay_ms(1000);
	PORTB &= ~(1<<PORTB0);
	_delay_ms(1000);
	s_ready = r_active;
}

int main(void)
{
    /* Replace with your application code */
	//Port init
	DDRB = (1 << DDB0);
	PORTB = (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4);
	s_ready = r_active;
	nc_last_state = r_active;
	no_last_state = r_active;
	
	wdt_enable(WDTO_4S);
	
    while (1) 
    {
		wdt_reset();
		if(((PINB & (1<<PINB3))) && (nc_last_state == r_nonactive)) nc_last_state = r_active;
		if(((PINB & (1<<PINB4))) && (no_last_state == r_nonactive)) no_last_state = r_active;
		
		if((!(PINB & (1<<PINB1))) && (s_ready == 1)){
			if((!(PINB & (1<<PINB3))) && (nc_last_state == r_active)){
				_delay_ms(20);
				wdt_reset();
				if(!(PINB & (1<<PINB3))){
					nc_last_state = r_nonactive;
					SetPulse();
				}
			}
		}else{
			if((!(PINB & (1<<PINB4))) && (no_last_state == r_active)){
				wdt_reset();
				_delay_ms(20);
				if(!(PINB & (1<<PINB4))){
					no_last_state = r_nonactive;
					SetPulse();
				}
			}
		}
    }
}



