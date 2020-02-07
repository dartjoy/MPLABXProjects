    #include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
// using namespace std;

char str[20];

void Mode1();
void Mode2();

void main(void) 
{
    SYSTEM_Initialize() ;
    
    while(1) {
        strncpy(str, GetString(), 20);
        if(str[0] == 'm' && str[1] == 'o' && str[2] == 'd' && str[3] == 'e' && str[4] == '1'){
            Mode1();
            ClearBuffer();
        }
        else if(str[0] == 'm' && str[1] == 'o' && str[2] == 'd' && str[3] == 'e' && str[4] == '2'){
            do{
                int data = ADC_Read(7);
                
                float out = (float)data * 5 / 1023;
        
                char yee[10] = {0};
                sprintf(yee, "%.2f", out);
//                sprintf(yee, "%d", data);
                UART_Write_Text(yee);
                strncpy(str, GetString(), 20);
                ClearBuffer();
            }while(str[0] != 'e');
            ClearBuffer();
        }
//        else if(str[0] == 'e'){
//            Mode2(0);
//            ClearBuffer();
//        }
    }
    return;
    
}

void Mode1(){
    char* text = "Hello World";
    UART_Write_Text(text);
}

void Mode2(int a){

}

// old version: 
// void interrupt high_priority Hi_ISR(void)
void __interrupt(high_priority) Hi_ISR(void)
{
    if(PIR1bits.CCP1IF == 1) {
        RC2 ^= 1;
        PIR1bits.CCP1IF = 0;
        TMR3 = 0;
    }
    return ;
}