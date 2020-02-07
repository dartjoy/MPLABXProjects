LIST p=18f4520
#include<p18f4520.inc>
        CONFIG OSC = INTIO67
        CONFIG WDT = OFF
        CONFIG PBADEN = OFF
        CONFIG LVP = OFF
        org 0x00
        bra Initial

ISR_H: org 0x08
        bcf PIR1, TMR2IF
        incf TRISA
        btfsc TRISA, 3 ;Interrupt 8 times = 2 sec
        call rotate
        retfie FAST
        
rotate:
        rlncf LATD
        clrf TRISA
        return

Initial:
        bsf RCON, IPEN
        bsf INTCON, GIE

        bsf PIE1, TMR2IE
        movlw b'01111111'
        movwf T2CON ;TMR2 prescaler, postscaler 1 : 16
        movlw d'244'
        movwf PR2 ;0.25 sec (10^6 / 16 / 16 ~= 976[1 sec] => 976 / 4 = 244[0.25 sec])
        
        clrf TRISD
        movlw 0x55
        movwf LATD
        
        clrf TRISA; counting reg
Main:
        bra Main
end