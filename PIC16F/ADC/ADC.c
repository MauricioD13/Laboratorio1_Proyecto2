/* 
 * File:   interruptions.c
 * Author: Mauricio David Cuello Alzate
 *         Joan Ferney Muñoz Tarazona
 *         Daniel Guillermo Morantes
 *
 * Created on 25 de febrero de 2021, 02:55 PM
 */

#include <PIC16F1827.h>
#include "ADC.h"
#define A4_PORT_STATE TRISAbits.TRISA4 //State of port
#define A4_ANALOG_CONFIG ANSELAbits.ANSA4
#define ADC_CHANNEL ADCON0bits.CHS2 
#define ADC_INTERRUPT PIE1bits.ADIE
#define ENABLE_ADC ADCON0bits.ADON


void config_ADC(int interruption){
    A4_PORT_STATE = 1; //As input
    A4_ANALOG_CONFIG = 1; //As analog input
    ADCON0 = 0x00;
    ADC_CHANNEL = 1;
    ADCON1 = 0x80; //All references config to 0 
    //ADCON1 |= 0x03;
    //FVRCON |= 0x03;
    
    ADC_INTERRUPT = 0; //Enable interrupts
    if(interruption == 1){
        ADC_INTERRUPT = 1;
    }
    ENABLE_ADC = 1; //Activate module
    
}
int read_ADC(void){
    int value;
    value = ADRESL | (ADRESH<<8);
    return value;
}