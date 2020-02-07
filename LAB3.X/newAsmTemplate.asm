LIST p=18f4520
#include<p18f4520.inc>
    CONFIG OSC = INTIO67
    CONFIG WDT = OFF
    org 0x00

Initial:
;
start_1:
    movlw b'11010111'
    andlw b'10011110'
    xorlw b'11111111'
    movwf LATA
    
    movlw b'01010011'
    iorlw b'11100100'
    xorlw b'11111111'
    movwf LATB
    
    nop
start_2:
    clrf TRISA
    clrf TRISD
    movlw 0x03
    movwf TRISB
    movlw 0x09
    movwf TRISC
    
    incf TRISD
    rrcf TRISA
    rrcf TRISC
    bc 0x2C ;ADD
    btfss TRISD, 3
    bra 0x1E ;LB
    bra 0x34 ;END
    ;ADD
    movff TRISB, WREG
    addwf TRISA, 1
    bra 0x1E ;LB
    ;END
    rrcf TRISA
    rrcf TRISC
    movff TRISC, TRISA
    
    nop
end