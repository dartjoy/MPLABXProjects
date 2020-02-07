#include <xc.h>

extern unsigned int divide(unsigned int a, unsigned int b);

void main(void) {
    volatile unsigned int res = divide(250, 15);
    volatile unsigned char quo = res >> 8;
    volatile unsigned char rem = res % 256;
    while(1);
    return;
}
