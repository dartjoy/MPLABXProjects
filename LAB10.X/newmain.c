// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

#include <xc.h>

void __interrupt(high_priority) ISR(void) {
    if (PIR1bits.ADIF) {
        PIR1bits.ADIF = 0;
        
//        ADRES /= 1000000;
        
        if(ADRES >= 0 && ADRES < 127) LATD = 0;
        else if (ADRES >= 128 && ADRES < 255) LATD = 1;
        else if (ADRES >= 256 && ADRES < 383) LATD = 2;
        else if (ADRES >= 384 && ADRES < 511) LATD = 3;
        else if (ADRES >= 512 && ADRES < 639) LATD = 4;
        else if (ADRES >= 640 && ADRES < 767) LATD = 5;
        else if (ADRES >= 768 && ADRES < 895) LATD = 6;
        else if (ADRES >= 896 && ADRES < 1023) LATD = 7;
    }
    else if (PIR2bits.CCP2IF) {
        PIR2bits.CCP2IF = 0;
        TMR3 = 0;
    }
    
    return;
}

void adc_init() {
    ADCON2bits.ADCS = 1; //8 * Tosc = 10^-6
    ADCON2bits.ADFM = 1; //right justified
    ADCON2bits.ACQT = 2; //4 * Tad
    
    TRISBbits.RB3 = 1;
    ADCON0bits.CHS = 9; //AN9(RB3) as input
    ADCON0bits.ADON = 1;
    
    ADCON1bits.VCFG = 0; //votage
    ADCON1bits.PCFG = 0; //analog input
    
    PIE1bits.ADIE = 1;
    INTCONbits.GIE = 1;
    RCONbits.IPEN = 1;
}

void ccp2_init() {
    CCP2CONbits.CCP2M = 11;
    PIE2bits.CCP2IE = 1;
    
    CCPR2 = 1; //Tacqt = 4 * 10^-6
}

void tmr3_init() {
    T3CONbits.T3CCP2 = 1;
    T3CONbits.T3CKPS = 3; //prescalar 8
    T3CONbits.TMR3CS = 0; //clock sourse
    T3CONbits.TMR3ON = 1;
    TMR3 = 0;
}

void main (void) {
    OSCCONbits.IRCF = 7; //8MHz
    TRISD = 0;
    adc_init();
    ccp2_init();
    tmr3_init();
    while(1);
    return;
}