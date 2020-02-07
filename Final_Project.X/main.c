#include <xc.h>
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "math.h"
#include <time.h>

#define _XTAL_FREQ 1000000

#pragma config OSC = INTIO67      // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = ON       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 1        // Watchdog Timer Postscale Select bits (1:1)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
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

#define C5 59  //1
#define C51 55  //#1
#define D5 52 //2
#define D51 49 //#2
#define E5 47 //3
#define F5 45 //4
#define F51 41 //#4
#define G5 39 //5
#define G51 37 //#5
#define A5 35 //6
#define A51 33 //#6
#define B5 31 //7

int pr_arr[180] = { E5,0,E5,0,E5,0,C5,0,E5,0,B5,0,G5*2,0,C5,0,G5*2,0,E5*2,0,A5*2,0,B5,0,A51*2,0,A5*2,0,G5*2,0,E5,0,G5,0,A5,0,F5,0,G5,0,E5,0,C5,0,D5,0,B5*2,0,G5,0,F51,0,F5,0,D51,0,E5,0,G51*2,0,A5*2,0,C5,0,A5*2,0,C5,0,D5,0,G5,0,F51,0,F5,0,D51,0,E5,0,C5/2,0,C5/2,0,C5/2,0,G5,0,F51,0,F5,0,D51,0,E5,0,G51*2,0,A5*2,0,C5,0,A5*2,0,C5,0,D5,0,D51,0,D5,0,C5,0,G5,0,F51,0,F5,0,D51,0,E5,0,G51*2,0,A5*2,0,C5,0,A5*2,0,C5,0,D5,0,G5,0,F51,0,F5,0,D51,0,E5,0,C5/2,0,C5/2,0,C5/2,0,G5,0,F51,0,F5,0,D51,0,E5,0,G51*2,0,A5*2,0,C5,0,A5*2,0,C5,0,D5,0,D51,0,D5,0,C5,0};
int tmr_arr[180] = {1,1,1,2,1,2,1,1,1,2,1,4,1,4,1,3,1,3,1,3,    1  ,3, 1  ,2,     1   ,1,    1  ,2,    1   ,1, 1 ,1, 1 ,2, 1  ,3, 1 ,1, 1 ,2, 1 ,2, 1 ,1, 1  ,1,    1  ,7,  1 ,1,  1 ,1,  1,1,  1   ,3, 1 ,2,    1    ,1,    1   ,1,  1,2,   1   ,1,  1,1,  1 ,4,  1 ,1,  1 ,1,  1,1,  1   ,3, 1 ,2,  1   ,2,    1   ,1,   1   ,6,  1 ,1,  1 ,1,  1,1,  1   ,3, 1 ,2,    1    ,1,    1   ,1,  1,2,   1   ,1,  1,1,  1 ,4,   1 ,3,  1 ,3, 1 ,9,  1 ,1,  1 ,1,  1,1,  1   ,3, 1 ,2,    1    ,1,    1   ,1,  1,2,   1   ,1,  1,1,  1 ,4,  1 ,1,  1 ,1,  1,1,  1   ,3, 1 ,2,  1   ,2,    1   ,1,   1   ,6,  1 ,1,  1 ,1,  1,1,  1   ,3, 1 ,2,    1    ,1,    1   ,1,  1,2,   1   ,1,  1,1,  1 ,4,   1 ,3,1,3,1,9};

int pr_idx = 0;
int tmr1_count = 0;

int line = -1;

unsigned int din_ori[8] = {0,0,0,0,0x30,0x20,0x30,0x60};
unsigned int din_dun[8] = {0,0,0,0,0x00,0x38,0x30,0x60};
unsigned int din[8];//only 8 bit
unsigned long obj[8];//only 8 bit
unsigned int rock1[8] = {0,0,0,0,0,0x02,0x07,0x07}; 
unsigned int rock2[8] = {0,0,0,0,0,0x06,0x0f,0x0f};
unsigned int arrow[8] = {0,0,0x02,0x0f,2,0,0,0};

//image
unsigned long hold[8] = {0x0000,0x0000,0xA48C,0xAA8A,0xEA8A,0xAA8A,0xA4EC,0x0000};
unsigned long go[8] = {0x0000,0x38E6,0x4516,0x4116,0x4D16,0x4510,0x38E6,0x0000};
unsigned long endimg[8] = {0x0000,0x0000,0x7A5C,0x4352,0x7AD2,0x4252,0x7A5C,0x0000};

unsigned int score=0;
unsigned int num1[8] = {0x00,0x02,0x06,0x02,0x02,0x02,0x07,0x00};
unsigned int num2[8] = {0x00,0x06,0x09,0x01,0x02,0x04,0x0f,0x00};
unsigned int num3[8] = {0x00,0x06,0x09,0x02,0x01,0x09,0x06,0x00};
unsigned int num4[8] = {0x00,0x02,0x06,0x0a,0x0a,0x0f,0x02,0x00};
unsigned int num5[8] = {0x00,0x0f,0x08,0x0e,0x01,0x09,0x06,0x00};
unsigned int num6[8] = {0x00,0x06,0x08,0x0e,0x09,0x09,0x06,0x00};
unsigned int num7[8] = {0x00,0x0f,0x01,0x01,0x02,0x04,0x04,0x00};
unsigned int num8[8] = {0x00,0x06,0x09,0x06,0x09,0x09,0x06,0x00};
unsigned int num9[8] = {0x00,0x06,0x09,0x09,0x07,0x01,0x01,0x00};
unsigned int num0[8] = {0x00,0x06,0x09,0x09,0x09,0x09,0x06,0x00};


unsigned long row[8];    //output 16*8
unsigned long crush[8];    //output 16*8

int running_flag = 0;
int jump_flag;    //1=jump 0=no
int fall_flag;
int dun_flag;
int jump_time = 1;    //1=groung    4=highest
int timer3_count;
int create;
int time_count = 0;
int test1 = 0;  //jump
int test2 = 0;  //dun
int distance[10];
int dis_i = 0;
int dis_avr ;

int detect[10];
int det_i = 0;

unsigned long timer3_val = 47000;

void initial(void){
//    jump_flag = 1;
    jump_time = 1;
    fall_flag = 0;
    timer3_count = 0;
    
    ADCON1 = 0x0f;

    LATA = 0x00;    //line
    PORTA = 0x00;
    TRISA = 0x00;
    LATB = 0x00;    //col
    PORTB = 0x00;
    TRISB = 0x00;    
    LATC = 0x00;
    PORTC = 0x00;
    TRISC = 0x00;
    LATD = 0x00;    //col
    PORTD = 0x00;
    TRISD = 0x00;
    
    TRISCbits.RC4 = 0;  //tri = output
    TRISCbits.RC5 = 1;  //echo = input
    
    // ADCON2 = 0x92;  	
    ADFM = 1 ;          // Right Justifie
    ADCON2bits.ADCS = 7; // 
    ADRESH=0;  			// Flush ADC output Register
    ADRESL=0;  

    for(int i=0;i<8;i++){
        crush[i]=0;
        obj[i]=0;
        
    }
}
int ADC_Read()
{
    int digital;
    
    ADCON0bits.CHS = 0x07 ; // Select Channe7
    ADCON0bits.GO = 1;
    ADCON0bits.ADON = 1;
    
    while(ADCON0bits.GO_nDONE==1);

    digital = (ADRESH*256) | (ADRESL);
    return(digital);
}

void start(){
    __delay_ms(2000);
    
    //hold img
    for(int i=0;i<8;i++){
        row[i] = hold[i];
    }
    
    //detect dist
//    while(dis_avr >= 2){
        int temp = 0;
        while(temp<1000){
            time_count = 0;
            LATCbits.LATC4 = 1;
            while(time_count < 3) time_count++;
            time_count = 0;
            LATCbits.LATC4 = 0;
            while(time_count < 3) time_count++;
            time_count = 0;
            while(time_count < 15 && PORTCbits.RC5 == 1) {  //time_count = distance
                time_count++;
                if(PORTCbits.RC5 == 0){
                    detect[(det_i)%10] = time_count;
                    det_i ++;
                    break;
                }
            }
            time_count = 0;
            temp++;
        }

        //get dist
        int sum = 0;
        int nzero = 0;
        for(int i=0;i<10;i++){
            if(detect[i] != 0 && detect[i] >= 3){
                nzero ++;
                sum = sum + detect[i];
            }
        }
        dis_avr = sum/nzero;
//    }
    __delay_ms(1000);
}

void end(){
    //end image
    for(int i=0;i<8;i++){
        row[i] = endimg[i];
    }
    __delay_ms(1500);
    
    //clear
    for(int i=0;i<8;i++){
        row[i] = 0;
        obj[i] = 0;
    }
    __delay_ms(1500);
    
    //output score
    int num;
    int shift;
    score /= 5;
    for(int j=0;j<3;j++){
        num = score%10; //_ _ 0
        if(j == 0) shift = 2;
        else if(j == 1) shift = 64;
        else if(j == 2) shift = 2048;
        switch(num){
            case 1:
                for(int i=0;i<8;i++){
                    row[i] = row[i]|(num1[i]*shift);
                }
                break;
            case 2:
                for(int i=0;i<8;i++){
                    row[i] = row[i]|(num2[i]*shift);
                }
                break;
            case 3:
                for(int i=0;i<8;i++){
                    row[i] = row[i]|(num3[i]*shift);
                }
                break;
            case 4:
                for(int i=0;i<8;i++){
                    row[i] = row[i]|(num4[i]*shift);
                }
                break;
            case 5:
                for(int i=0;i<8;i++){
                    row[i] = row[i]|(num5[i]*shift);
                }
                break;
            case 6:
                for(int i=0;i<8;i++){
                    row[i] = row[i]|(num6[i]*shift);
                }
                break;
            case 7:
                for(int i=0;i<8;i++){
                    row[i] = row[i]|(num7[i]*shift);
                }
                break;
            case 8:
                for(int i=0;i<8;i++){
                    row[i] = row[i]|(num8[i]*shift);
                }
                break;
            case 9:
                for(int i=0;i<8;i++){
                    row[i] = row[i]|(num9[i]*shift);
                }
                break;
            case 0:
                for(int i=0;i<8;i++){
                    row[i] = row[i]|(num0[i]*shift);
                }
                break;
        }
        score = score/10;
        if(score == 0){
            break;
        }
    }
    return ;
}

void running(){
    running_flag = 1;
    for(int i=0;i<8;i++)
    {
        timer3_count = 0;
        obj[i] = 0;
        row[i] = 0;
        create = 0;
    }
    //clear
    for(int i=0;i<8;i++){
        row[i] = 0;
    }
    __delay_ms(1500);
    
    //GO image
    for(int i=0;i<8;i++){
        row[i] = go[i];
    }
    __delay_ms(500);
    PIE2bits.TMR3IE = 1;
    INTCONbits.TMR0IE = 1;
    PIE1bits.TMR2IE = 1;
    T0CONbits.TMR0ON = 1;
    T2CONbits.TMR2ON = 1;
    T3CONbits.TMR3ON = 1;
    
    //mainframe
    unsigned long digital = 0;
    while(1){
        digital = ADC_Read();
        digital *= 10;
        timer3_val = digital + 47000;
        //emit ultrasound
        time_count = 0;
        LATCbits.LATC4 = 1;
        while(time_count < 3) time_count++;
        time_count = 0;
        LATCbits.LATC4 = 0;
        while(time_count < 3) time_count++;
        time_count = 0;
        
        //receive ultrasound
        while(time_count < 15 && PORTCbits.RC5 == 1) {  //time_count = distance
            time_count++;
            if(PORTCbits.RC5 == 0 && time_count <= dis_avr-2){
                test1++;
                break;
            }
            else if(PORTCbits.RC5 == 0 && time_count >= dis_avr+2){
                test2++;
                break;
            }
        }
        time_count = 0;
        
        //for jump
        if(test1 > 0){
            if(fall_flag != 1){
                jump_flag = 1;
                test1=0;
                test2=0;
            }
        }
        
        //for dun
        if(test2 > 0){
            if(fall_flag != 1){
                dun_flag = 1;
                test1=0;
                test2=0;
            }
        }
        
        //movement
        int i=0;
        if(jump_time == 0){
            for(i=0;i<8;i++){
                din[i]=din_dun[i];
            }
        }
        if(jump_time == 1){
            for(i=0;i<8;i++){
                din[i]=din_ori[i];
            }
        }
        else if(jump_time == 2){
            for(i=0;i<8;i++){
                din[i]=din_ori[(i+1)%8];
            }
        }
        else if(jump_time == 3){
            for(i=0;i<8;i++){
                din[i]=din_ori[(i+2)%8];
            }
        }
        else if(jump_time == 4 || jump_time == 5){
            for(i=0;i<8;i++){
                din[i]=din_ori[(i+3)%8];
            }
        }
        else if(jump_time == 8 || jump_time == 7 || jump_time == 6){
            for(i=0;i<8;i++){
                din[i]=din_ori[(i+4)%8];
            }
        }
        
        //create obj
        if(create == 1){
            for(i=0;i<8;i++){
                obj[i] |= rock1[i];
            }
            create = 0;
        }
        else if(create == 2){
            for(i=0;i<8;i++){
                obj[i] |= rock2[i];
            }
            create = 0;
        }
        else if(create == 3){
            for(i=0;i<8;i++){
                obj[i] |= arrow[i];
            }
            create = 0;
        }
        
        //collision
        for(i=0;i<8;i++){
            row[i]=(obj[i]/256)^(din[i]*256);
            crush[i] = (obj[i]/256)&(din[i]*256);
            if(crush[i] != 0){
                running_flag = 0;
                timer3_count = 0;
                PIE2bits.TMR3IE = 0;
                INTCONbits.TMR0IE = 0;
                PIE1bits.TMR2IE = 0;
                T0CONbits.TMR0ON = 0;
                T2CONbits.TMR2ON = 0;
                T3CONbits.TMR3ON = 0;
                end();
                return;
            }
        }
    }
}

void main(void) {
    initial();    
    
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    
    //TMR1 initial
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    IPR1bits.TMR1IP = 1;
    T1CON = 0xd9; //11011001
    TMR1L = 0x4c;   //TMR1=65100
    TMR1H = 0xfe;
    
    PIR2bits.TMR3IF = 0;
    PIE2bits.TMR3IE = 0;
    IPR2bits.TMR3IP = 1;
    T3CON = 0xd8; //11011000
    TMR3L = 0x70;   //TMR1=38000
    TMR3H = 0xd4;
    
    T2CON = 0x01;
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 0;
    IPR1bits.TMR2IP = 1;
    
    TRISCbits.RC2 = 0;
    
    pr_idx = 0;
    PR2 = pr_arr[pr_idx] * 2;
    CCP1CON = 0x0f;
    CCPR1L = pr_arr[pr_idx];
    
    INTCONbits.TMR0IE = 0;
    INTCONbits.TMR0IF = 0;
    INTCON2bits.TMR0IP = 1;
    T0CON = 0x08;
    TMR0 = 49036;
    
    
    srand(time(NULL));
    while(1){
        start();
        running();
        while(1){
            int temp = 0;
            int access = 0;
            while(temp<20){
                time_count = 0;
                LATCbits.LATC4 = 1;
                while(time_count < 3) time_count++;
                time_count = 0;
                LATCbits.LATC4 = 0;
                while(time_count < 3) time_count++;
                time_count = 0;
                while(time_count < 15 && PORTCbits.RC5 == 1) {  //time_count = distance
                    time_count++;
                    if(PORTCbits.RC5 == 0){
                        break;
                    }
                    else if(time_count >= 10){
                        access++;
                        break;
                    }
                }
                __delay_ms(100);
                time_count = 0;
                temp++;
            }
            int nothing = 0;
            
            if(access >= 1){   //nothing
                for(int i = 0;i<8;i++){
                    row[i] = 0;
                    nothing = 1;
                }
            }
            if(nothing == 1){
                __delay_ms(1000);
                while(1){
                    temp = 0;
                    access = 0;
                    while(temp<20){
                        time_count = 0;
                        LATCbits.LATC4 = 1;
                        while(time_count < 3) time_count++;
                        time_count = 0;
                        LATCbits.LATC4 = 0;
                        while(time_count < 3) time_count++;
                        time_count = 0;
                        while(time_count < 15 && PORTCbits.RC5 == 1) {  //time_count = distance
                            time_count++;
                            if(PORTCbits.RC5 == 0){
                                break;
                            }
                            else if(time_count >= 10){
                                access++;
                                break;
                            }
                        }
                        __delay_ms(100);
                        time_count = 0;
                        temp++;
                    }
                    if(access == 0){    //restart
                        score = 0;
                        timer3_count = 0;
                        for(int i=0;i<8;i++){
                            obj[i] = 0;
                            row[i] = 0;
                        }
                        create = 0;
                        running_flag = 0;
                        break;
                    }
                }
                break;
            }
        }
    }
    return;
}

void __interrupt(high_priority) Hi_ISR(void)
{
    if(INTCONbits.TMR0IF == 1){
        INTCONbits.TMR0IF = 0;
        tmr1_count ++;
        if(tmr1_count == tmr_arr[(pr_idx)%(sizeof(pr_arr)/sizeof(pr_arr[0]))]){
            tmr1_count = 0;
            pr_idx++;
            if(pr_arr[(pr_idx)%(sizeof(pr_arr)/sizeof(pr_arr[0]))] != 0){
                PR2 = pr_arr[(pr_idx)%(sizeof(pr_arr)/sizeof(pr_arr[0]))] * 2;
            }
            else
                PR2 = 255;
            CCPR1L = pr_arr[(pr_idx)%(sizeof(pr_arr)/sizeof(pr_arr[0]))];
        }
        TMR0 = 49036;
    }
    
    else if(PIR1bits.TMR2IF == 1){
        PIR1bits.TMR2IF = 0;
    }
    
    else if(PIR1bits.TMR1IF == 1){
        TMR1L = 0xb0;
        TMR1H = 0xfe;
        switch(line){
            case 0:
                LATB = row[0]/256;
                LATD = row[0]%256;
                TRISA = 0xfe;
                break;
            
            case 1:
                LATB = row[1]/256;
                LATD = row[1]%256;
                TRISA = 0xfd;
                break;
            case 2:
                TRISA = 0xfb;
                LATB = row[2]/256;
                LATD = row[2]%256;
                break;
            case 3:
                TRISA = 0xf7;
                LATB = row[3]/256;
                LATD = row[3]%256;
                break;
            case 4:
                TRISA = 0xef;
                LATB = row[4]/256;
                LATD = row[4]%256;
                break;
            case 5:
                TRISA = 0xdf;
                LATB = row[5]/256;
                LATD = row[5]%256;
                break;
            case 6:
                TRISA = 0xbf;
                LATB = row[6]/256;
                LATD = row[6]%256;
                break;
            case 7:
                LATB = row[7]/256;
                LATD = row[7]%256;
                TRISA = 0x7f;
                break;
        }
        line++;
        if(line > 7){
            line = 0;
        }
        PIR1bits.TMR1IF = 0;
    }
    else if(PIR2bits.TMR3IF == 1){
        
        if(running_flag == 1){
            timer3_count++;
            score++;
        }
        TMR3 = timer3_val;
        int i=0;
        for(i=0;i<8;i++){
            obj[i] = obj[i]*2;
        }
        
        //jump
        if(jump_flag == 1){
            jump_time++;
            if(jump_time==8){
                jump_flag=0;
                fall_flag=1;
            }
        }
        if(fall_flag == 1){
            jump_time--;
            if(jump_time==1){
                fall_flag=0;
            }
        }
        
        //dun
        if(dun_flag == 1 && jump_flag != 1 && fall_flag != 1){
            jump_time --;
        }
        if(jump_time == -10){
            jump_time = 1;
            dun_flag = 0;
        }
        
        //obj rand create
        if(timer3_count == 15){
            create = rand()%3+1;
            timer3_count = 0;
        }
        PIR2bits.TMR3IF = 0;
    }
    
    return ;
}