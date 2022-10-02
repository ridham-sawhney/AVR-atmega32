/*
 * lcd.c
 *
 * Created: 25-06-2021 21:42:31
 *  Author: sawhn
 */ 
#include <avr/io.h>

#include  <util/delay.h>

#include "lcd.h"



#define E (1<<PD3)

#define RS (1<<PD2)



void lcdinit(){

	

	//initialize PORT D for LCD

	DDRD |= (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7);

	

	_delay_ms(50);

	PORTD &= ~E;		//send low

	_delay_ms(50);  		//delay for stable power

	lcdcmd(0x33);

	lcdcmd(0x32);

	lcdcmd(0x28);		// for using 4 pins

	lcdcmd(0x0C);  	// display ON, Cursor OFF

	lcdcmd(0x01);		//clear LCD

	lcdcmd(0x06);		//shift cursor to right

	_delay_us(1000);

}



void lcdcmd(unsigned char cmd){

	PORTD = (PORTD & 0x0F) | (cmd & 0xF0);  // send high nibble

	PORTD &= ~RS;	//send 0 to select command register

	PORTD |= E;		//send high

	_delay_ms(50);		//wait

	PORTD &= ~E;		//send low

	

	PORTD = (PORTD & 0x0F) | (cmd<<4);	//send low nibble

	PORTD |= E;		//send high

	_delay_ms(50);		//wait

	PORTD &= ~E;		//send low

}



void lcdchar(unsigned char data){

	

	PORTD = (PORTD & 0x0F) | (data & 0xF0);  // send high nibble

	PORTD |= RS;		//send 1 to select data register

	PORTD |= E;		//send high

	_delay_ms(50);		//wait

	PORTD &= ~E;		//send low

	

	PORTD = (PORTD & 0x0F) | (data<<4);  // send low nibble

	PORTD |= E;		//send high

	_delay_ms(50);		//wait

	PORTD &= ~E;		//send low

}



void lcdstr(unsigned char *str){

	unsigned char k=0;

	while(str[k] != 0){

		lcdchar(str[k]);

		k++;

	}

}



void lcdgoto(unsigned char x, unsigned char y){

	unsigned char firstcharadr[] = {0x80, 0xC0, 0x94, 0xD4};

	lcdcmd(firstcharadr[y-1] + x-1);

	_delay_us(100);

}



void lcdclear(){

	lcdcmd(0x01);

	_delay_ms(1);

}