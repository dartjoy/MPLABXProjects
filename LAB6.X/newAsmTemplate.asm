LIST p=18f4520
#include<p18f4520.inc>
        CONFIG OSC = INTIO67
        CONFIG WDT = OFF
        org 0x00
    
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

Initial:
        clrf TRISA
        bsf TRISA, 4 ;RA4 input
        clrf TRISD ;RDx on
setting:
        movlw 0xF0
        movwf LATD ;RD7 ~ RD4 on, RD3 ~ RD0 off
        movlw 0x04
        movwf 0x02 ;count
loop:
        btfsc PORTA, 4 ;press(0) to escape
        goto loop
start:
        clrf TRISD ;RDx on
        rlncf LATD
        delay d'90', d'197'
        movlw 0xFF
        movwf TRISD ;RDx off
        decfsz 0x02
        goto loop
        goto setting
end