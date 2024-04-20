/*
 * stopW.c
 *
 *  Created on: Sep 17, 2022
 *      Author: merna
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


unsigned char g_S1 = 0;
unsigned char g_S2 = 0;
unsigned char g_H1 = 0;
unsigned char g_H2 = 0;
unsigned char g_M1 = 0;
unsigned char g_M2 = 0;

void Timer1_CTC_Init(void)
{
	TCNT1 = 0;//timer1 = 0
	OCR1A = 976;//Compare value to 10^6/1024=976
	TIMSK |= (1<<OCIE1A);//Enable Timer1
	TCCR1A &= (1<<FOC1A);
	TCCR1B |= (1<<CS10) | (1<<CS12) | (1<<WGM12);//F_CPU/1024 CS10=1 CS11=0 CS12=1

}
ISR(TIMER1_COMPA_vect)
{
	g_S1++;
	if(g_S1==10)
	{
		g_S2++;
		g_S1=0;
	}
	if(g_S2==6)
	{
		g_M1++;
		g_S2=0;
	}
	if(g_M1==10)
	{
		g_M2++;
		g_M1=0;
	}
	if(g_M2==6)
	{
		g_H1++;
		g_M2=0;
	}
	if(g_H1==10)
	{
		g_H2++;
		g_H1=0;
	}

}

ISR(INT0_vect)
{
	g_S1 = 0;
	g_S2 = 0;
	g_M1 = 0;
	g_M2 = 0;
	g_H1 = 0;
	g_H2 = 0;
}
ISR(INT1_vect)
{
	TCCR1A = ~(1<<FOC1A);
	TCCR1B &= ~(1<<CS10) & ~(1<<CS12);
}
ISR(INT2_vect)
{
	TCCR1A |= (1<<FOC1A);
	TCCR1B |= (1<<CS10) | (1<<CS12);
}

void INT0_Init(void)
{
	DDRD  &= ~(1<<PD2);   // Configure INT0 as input pin
	PORTD |=(1<<PD2);     //PULL UP
	MCUCR |= (1<<ISC01) ;   // Trigger INT0 with the falling edge
	GICR  |= (1<<INT0);    // Enable external interrupt pin INT0
}
void INT1_Init(void)
{
	DDRD  &= ~(1<<PD3);   // Configure INT1 as input pin
	MCUCR |= (1<<ISC10)| (1<<ISC11);   // Trigger INT1 with the raising edge
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
}
void INT2_Init(void)
{
	DDRB   &= ~(1<<PB2);   // Configure INT2 as input pin
	PORTB |=(1<<PB2);      //PULL UP
	MCUCSR|=(1<<ISC2);    // Trigger INT1 with the falling edge
	GICR  |= (1<<INT2);    // Enable external interrupt pin INT2
}
void Seven_Segment_display(){

	PORTA =(PORTA & 0xC0) | (1<<5) ;
	PORTC =(PORTC & 0xF0) | (0x0F & g_S1) ;
	_delay_ms(2);
	PORTA =(PORTA & 0xC0) | (1<<4) ;
	PORTC =(PORTC & 0xF0) | (0x0F & g_S2) ;
	_delay_ms(2);
	PORTA =(PORTA & 0xC0) | (1<<3) ;
	PORTC =(PORTC & 0xF0) | (0x0F & g_M1) ;
	_delay_ms(2);
	PORTA =(PORTA & 0xC0) | (1<<2) ;
	PORTC =(PORTC & 0xF0) | (0x0F & g_M2) ;
	_delay_ms(2);
	PORTA =(PORTA & 0xC0) | (1<<1) ;
	PORTC =(PORTC & 0xF0) | (0x0F & g_H1) ;
	_delay_ms(2);
	PORTA =(PORTA & 0xC0) | (1<<0) ;
	PORTC =(PORTC & 0xF0) | (0x0F & g_H2) ;
	_delay_ms(2);

}
int main(void)
{
	INT0_Init();
	INT1_Init();
	INT2_Init();
	Timer1_CTC_Init();

	SREG|=(1<<7);

	DDRC |= 0x0F;
	PORTC &= 0xF0;

	DDRA |= 0x3F;
	PORTA &= 0xC0;

	while(1)
	{
		Seven_Segment_display();
	}
}
