/*
 * lcd.h
 *
 * Created: 25-06-2021 21:40:43
 *  Author: sawhn
 */ 


#ifndef LCD_H_
#define LCD_H_


void lcdinit();

void lcdcmd(uint8_t);

void lcdchar(uint8_t);

void lcdstr(unsigned char *);

void latch(void);

void lcdgoto(uint8_t , uint8_t );


#endif /* LCD_H_ */