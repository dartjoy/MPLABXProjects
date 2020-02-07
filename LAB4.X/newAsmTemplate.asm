LIST p=18f4520
#include<p18f4520.inc>
    CONFIG OSC = INTIO67
    CONFIG WDT = OFF
    org 0x00

movlf macro var, reg
    movlw var
    movwf reg
endm
    
addfff macro reg1, reg2, reg3
    movf reg1, 0
    addwf reg2, 0
    movwf reg3
endm
    
Initial:
    movlf 0x0A, LATA
start:
    movlf 0, 0x00
    movlf 1, 0x01
    rcall Fib
    dcfsnz LATA
    rcall finish
    movlf 0x0C, PCL
Fib:
    addfff 0x00, 0x01, 0x02
    movff 0x01, 0x00
    movff 0x02, 0x01
    return
finish:
    movff 0x02, 0x33
end