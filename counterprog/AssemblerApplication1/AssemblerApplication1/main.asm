.INCLUDE "M32DEF.INC"  
CBI DDRB, 1          ; make T1 as input 
LDI R20,0xFF 
OUT DDRC,R20         ; make port C output 
OUT DDRD,R20         ; make port D output 
LDI R20,0x00 
OUT TCCR1A, R20 
LDI R20,0x06 
OUT TCCR1B, R20         ; counter falling edge 
AGAIN: 
   IN R20, TCNT1L       ; R20 = TCNT1L, TEMP = TCNT1H 
   OUT PORTC, R20       ; PORT C = TCNT0 
   IN R20, TCNT1H       ; R20 = TEMP 
   OUT PORTD, R20       ; PORT C = TCNT0 
   IN R16, TIFR 
   SBRS R16,TOV1 
   RJMP AGAIN           ; keep doing it 
   LDI R16, 1<< TOV1    ; clear TOV1 flag 
   OUT TIFR, R16 
   RJMP AGAIN           ; keep doing it 
