LIST p=18f4520
#include<p18f4520.inc>
        CONFIG OSC = INTIO67
        CONFIG WDT = OFF
        CONFIG PBADEN = OFF
;        CONFIG LVP = OFF
        
        org 0x00
        bra Initial
        
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
        bcf INTCON, INT0IF
        movlw 8
        movwf TRISA
duty:
        bsf CCP1CON, 4
        bcf CCP1CON, 5 ;1
;        delay d'90', d'90'
        
        bcf CCP1CON, 4
        bsf CCP1CON, 5 ;2
;        delay d'90', d'90'
        
        bsf CCP1CON, 4
        bsf CCP1CON, 5 ;3
;        delay d'90', d'90'
        
        incf CCPR1L
        bcf CCP1CON, 4
        bcf CCP1CON, 5 ;0
        delay d'7', d'90'
        decfsz TRISA
        bra duty

        retfie FAST

Initial:
        bcf OSCCON, 6
        bsf OSCCON, 5
        bcf OSCCON, 4 ;OSC 250kHz
        
        bsf RCON, IPEN
        bsf INTCON, GIE
        
        bsf INTCON, INT0IE
        bcf INTCON2, INTEDG0

        movlw b'01111111'
        movwf T2CON ;TMR2 prescaler, postscaler 1 : 16
        movlw 77
        movwf PR2 ;(77 + 1) * 4 * 0.000004 * 16 = 19.98ms (Period)

        bsf CCP1CON, 3
        bsf CCP1CON, 2 ;PWM mode
        bcf CCP1CON, 4
        bcf CCP1CON, 5 ;0
        movlw 2
        movwf CCPR1L ;8 ~ 37 (Duty cycle) [512 ~ 2368]
        
        clrf TRISB
        bsf TRISB, 0 ;RB0 input
        clrf TRISC ;CCP1 output reg (RC)
Main:        
        movlw 8
        movwf TRISA
        bcf CCP1CON, 4
        bcf CCP1CON, 5 ;0
        movlw 2
        movwf CCPR1L ;8 ~ 37 (Duty cycle)
        bra Main
end