LIST p=18f4520
#include<p18f4520.inc>
        CONFIG OSC = INTIO67
        CONFIG WDT = OFF
        CONFIG LVP = OFF
        CONFIG PBADEN = OFF
        org 0x00
        goto Initial
  
delay macro a, b
        local  loop1
        local loop2
        movlw a
        movwf 0x00 ; 2
        loop1:
                movlw b
                movwf 0x01 ; 2
                loop2:
                        nop
                        nop
                        nop
                        nop
                        decfsz 0x01
                        goto loop2 ;(4 + 1 + 2) * 89 + (4 + 3) = 630
                decfsz 0x00
                goto loop1 ;2 + (2 + 630 + 1 + 2) * 196 + (2 + 630 + 3) = 125097 ;125097/250000 = 0.500388 sec
endm
        
ISR: org 0x08
        btg TRISA, 0
        bcf INTCON, INT0IF
        RETFIE

Initial:
        bsf RCON, IPEN
        bsf INTCON, GIE
        bsf INTCON, INT0IE
        bcf INTCON2, INTEDG0
        clrf TRISB
        bsf TRISB, 0 ;RB0 input
        clrf TRISD ;RDx output
setting:
        movlw 0x11
        movwf LATD ;RD4 RD0 on
        clrf TRISA ;stat reg
Clk:
        btfsc TRISA, 0
        goto C_Clk
        rrncf LATD
        delay d'90', d'197'
        goto Clk
C_Clk:
        rlncf LATD
        delay d'90', d'197'
        goto Clk
end