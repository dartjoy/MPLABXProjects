#include "xc.inc"
GLOBAL _divide
    
PSECT mytext, local, class = CODE, reloc = 2
 
_divide:
    clrf TRISB
    movlw 8
    movwf LATA ;count
    movff 0x001, TRISA ;
    movff 0x003, WREG
    
    rlcf TRISA
    rlcf TRISB
    clrf STATUS
loop:
    subwf TRISB
    btfsc STATUS, 4
    goto neg
    rlcf TRISA
    rlcf TRISB
    bsf TRISA, 0
    decfsz LATA
    goto loop
    goto final
neg:
    addwf TRISB
    rlcf TRISA
    rlcf TRISB
    bcf TRISA, 0
    decfsz LATA
    goto loop
    goto final
final:
    rrncf TRISB
    movff TRISA, 0x002
    movff TRISB, 0x001
    return