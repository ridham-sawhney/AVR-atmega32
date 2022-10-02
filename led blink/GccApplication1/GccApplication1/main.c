#include <avr/io.h>
#include<util/delay.h>
int main(void)
{

	DDRC=0xff;
	while(1)
	{

		PORTC=0XFF;

		_delay_ms(1000);

		PORTC=0x00;

		_delay_ms(1000);		/* Replace with your application code */

	}

}

