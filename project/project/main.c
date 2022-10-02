
#include <avr/io.h>

#include <util/delay.h>

#include <stdlib.h>

#include "lcd.h"

#include "adc.h"

#include "mq2.h"



float Ro=10;                 //Ro is initialized to 10 kilo ohms



int main()
{
	
	unsigned char Res[16], lpg[16], smoke[16];

	lcdinit();
	adcinit();
	
	
	lcdstr("Calibrating...");
	Ro = SensorCalibration();                       //Please make sure the sensor is in clean air when you perform the calibration
	dtostrf(Ro, 6, 2, Res);
	lcdclear();
	_delay_ms(2);	                                //clearing takes around 1.64ms to execute
	lcdstr("Calibration done...");
	lcdgoto(3,2);
	lcdstr("Ro=");
	lcdstr(Res);
	lcdstr("KOhm ");
	_delay_ms(2000);
	lcdclear();
	_delay_ms(2);	                                 //clearing takes around 1.64ms to execute
	
	lcdgoto(1,1);
	lcdstr("LPG:");
	lcdgoto(13,1);
	lcdstr("PPM");
	lcdgoto(1,2);
	lcdstr("SMOKE:");
	lcdgoto(13,2);
	lcdstr("PPM");
	
	while (1)
	{
		
		
		itoa(GetGasPercentage(ReadSensor()/Ro,LPG), lpg, 10);
		lcdgoto(5,1);
		lcdstr(lpg);
		
			
		
		
		
		itoa(GetGasPercentage(ReadSensor()/Ro,SMOKE), smoke, 10);
		lcdgoto(7,2);
		lcdstr(smoke);
		
		_delay_ms(2000);
		lcdgoto(5,1);
		lcdstr("        ");
		lcdgoto(7,2);
		lcdstr("      ");
	
	}
	return 0;
}