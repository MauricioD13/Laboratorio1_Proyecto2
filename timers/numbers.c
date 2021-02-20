
#include <PIC16F1827.h>
#define LED_A PORTAbits.RA2
#define LED_B PORTAbits.RA3
#define LED_C PORTAbits.RA4
#define LED_D PORTBbits.RB0
#define LED_E PORTBbits.RB1
#define LED_F PORTBbits.RB2
#define LED_G PORTBbits.RB3

void one(){
    LED_B = 1;
    LED_C = 1;
}
void two(){
    LED_A = 1;
    LED_B = 1;
    LED_G = 1;
    LED_E = 1;
    LED_D = 1;
}
void three() {
    LED_A = 1;
    LED_B = 1;
    LED_C = 1;
    LED_D = 1;
    LED_G = 1;
}
void four(){
    LED_B = 1;
    LED_C = 1;
    LED_G = 1;
    LED_F = 1;
}
void five(){
    LED_A = 1;
    LED_C = 1;
    LED_D = 1;
    LED_F = 1;
    LED_G = 1;
}

void six(){
    LED_A = 1;
    LED_C = 1;
    LED_D = 1;
    LED_E = 1;
    LED_F = 1;
    LED_G = 1;
}

void seven(){
    LED_A = 1;
    LED_B = 1;
    LED_C = 1;
}

void eight(){
    LED_A = 1;
    LED_B = 1;
    LED_C = 1;
    LED_D = 1;
    LED_E = 1;
    LED_F = 1;
    LED_G = 1;
}
void nine(){
    LED_A = 1;
    LED_B = 1;
    LED_C = 1;
    LED_D = 1;
    LED_F = 1;
    LED_G = 1;
}
void clean_LED(){
    LED_A = 0;
    LED_B = 0;
    LED_C = 0;
    LED_D = 0;
    LED_E = 0;
    LED_F = 0;
    LED_G = 0;
}