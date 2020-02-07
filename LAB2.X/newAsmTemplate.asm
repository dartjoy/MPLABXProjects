LIST p=18f4520
#include<p18f4520.inc>
    CONFIG OSC = INTIO67
    CONFIG WDT = OFF
    org 0x00

asgn macro arg1
    movlw arg1
    movwf INDF0
    movf POSTINC0
endm

add macro arg1
    movff INDF0, WREG
    movf POSTINC0
    addlw arg1
    movwf INDF1
    movf POSTINC1
endm

Initial:
;
assign:
    lfsr FSR0, 0x0100
    asgn 0x39
    asgn 0x4e
    asgn 0x4f
    asgn 0x1f
    asgn 0x0d
    asgn 0x56
    asgn 0x60
    asgn 0x0d
    asgn 0x52
    asgn 0x4e
    asgn 0x60
    asgn 0x66
addition:
    lfsr FSR0, 0x0100
    lfsr FSR1, 0x0200
    add 0x13
    add 0x13
    add 0x13
    add 0x13
    add 0x13
    add 0x13
    add 0x13
    add 0x13
    add 0x13
    add 0x13
    add 0x13
    add 0x13

end