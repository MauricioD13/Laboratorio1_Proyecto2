#include <PIC16F1827.h>
#include "ADC.h"
#define A2_port_state TRISAbits.TRISA2 //State of port
#define A2_analog_config ANSELAbits.ANSA2
#define ADC_channel ADCON0bits.CHS0 
#define ADC_clock_8 ADCON1bits.ADCS0
#define ADC_interrupt PIE1bits.ADIE
#define enable_ADC ADCON0bits.ADON


void config_ADC(){
    A2_port_state = 1; //As input
    A2_analog_config = 1; //As analog input
    ADCON0 &= 0x00;
    ADC_channel = 1;
    ADCON1 &= 0x00; //All references config to 0 
    
    ADC_clock_8 = 1;
    ADC_interrupt = 1; //Enable interrupts
    enable_ADC = 1; //Activate module
    
}
int read_ADC(){
    int value;
    value = ADRESL;
    value = 8<<ADRESH;
}