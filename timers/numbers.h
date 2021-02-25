
#ifndef NUMBERS_H
#define	NUMBERS_H
#define LED_A PORTAbits.RA2
#define LED_B PORTAbits.RA3
#define LED_C PORTBbits.RB4
#define LED_D PORTAbits.RA6
#define LED_E PORTAbits.RA7
#define LED_F PORTAbits.RA1
#define LED_G PORTAbits.RA0

typedef struct STATES{
    int seg_1;
    int seg_2;
    int seg_3;
    int flag_result;
}STATES;

void zero();
void one();
void two();
void three();
void four();
void five();
void six();
void seven();
void eight();
void nine();
void show_number(int result);
void convert_number(float value, STATES *states);
#endif	/* NUMBERS_H */

