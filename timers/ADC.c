#include <PIC16F1827.h>
#include "ADC.h"
#define A4_port_state TRISAbits.TRISA4 //State of port
#define A4_analog_config ANSELAbits.ANSA4
#define ADC_channel ADCON0bits.CHS2 
#define ADC_clock_8 ADCON1bits.ADCS0
#define ADC_interrupt PIE1bits.ADIE
#define enable_ADC ADCON0bits.ADON


void config_ADC(){
    A4_port_state = 1; //As input
    A4_analog_config = 1; //As analog input
    ADCON0 = 0x00;
    ADC_channel = 1;
    ADCON1 = 0x80; //All references config to 0 
    //ADCON1 |= 0x03;
    //FVRCON |= 0x03;
    
    ADC_interrupt = 0; //Enable interrupts
    enable_ADC = 1; //Activate module
    
}
int read_ADC(){
    int value;
    value = make16(ADRESH,ADRESL);
    return value;
}