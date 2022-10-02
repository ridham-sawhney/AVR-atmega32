.INCLUDE "M32DEF.INC"  
 .MACRO INITSTACK   ;set up stack 
        LDI R20, HIGH (RAMEND) 
        OUT SPH, R20  
        LDI R20, LOW (RAMEND); 0000 0001 
        OUT SPL, R20         ; 0010 0000 
   .ENDMACRO  
        INITSTACK 
   LDI R16,1<<5        ;R16 = 0x20 
        SBI DDRB, 5         ; PB5 as an output 
        LDI R17,0 
        OUT PORTB, R17      ; clear PORT B 
BEGIN:  RCALL DELAY         ; call Timer delay 
        EOR R17, R16        ; toggle D5 of R17 by Ex-oring with 1 
        OUT PORTB, R17      ; toggle PB5 
        RJMP BEGIN 
;…………………....................Timer 0 delay 
DELAY: LDI R20, 0xF2        ; R20  0xF2 
       OUT TCNT0,R20        ;load Timer 0 
       LDI R20, 0x01         
       OUT TCCR0,R20    ;Timer 0, normal mode, internal clock, no prescalar    
AGAIN: IN R20,TIFR      ; read TIFR 
       SBRS R20,TOV0    ; if TOV0 is set skip next instruction 
       RJMP AGAIN 
       LDI R20,0x00 
       OUT TCCR0, R20   ; stop timer0 
       LDI R20,(1<<TOV0) 
       OUT TIFR,R20      ; clear TOV0 flag by writing a 1 to TIFR 
       RET 
