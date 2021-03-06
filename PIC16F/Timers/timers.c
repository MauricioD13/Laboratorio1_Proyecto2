
#include <PIC16F1827.h>
#include "timers.h"


#define overflow_interrupt_T1 PIE1bits.TMR1IE
#define peripheral_interrupt INTCONbits.PEIE

//TIMER 0
#define T0_source OPTION_REGbits.T0CS
#define T0_enable_prescaler OPTION_REGbits.PSA


//OSCILLATOR
#define enable_INTOSC OSCCONbits.SCS1 
#define H_INTOSC_status OSCSTATbits.HFIOFR

#define int_clock_4M OSCCONbits.IRCF0 = 0, OSCCONbits.IRCF1=1, OSCCONbits.IRCF2 = 1, OSCCONbits.IRCF3 = 1
//FOR TIMER 1

#define T1_source_0 T1CONbits.TMR1CS0
#define T1_source_1 T1CONbits.TMR1CS1
#define clean_T1 TMR1H = 0x00, TMR1L = 0x00, PIR1bits.TMR1IF = 0





int oscillator_module(void){
    OSCCON &= 0x00; //Leave to word config the clock system
    OSCCONbits.SCS1 = 1;
    int_clock_4M;
    return H_INTOSC_status;
}

void config_T1(int prescaler,int interruption){
        clean_T1;
        
        T1CON = 0x00;
        T1GCON &= 0x00;
        
            if(prescaler == 0){
                T1CON |= prescaler_T1_0;
            }
            if(prescaler == 2){
                T1CON |= prescaler_T1_2;
            }
            else if(prescaler == 4){
                T1CON |= prescaler_T1_4;
            }
            else if(prescaler == 8){
                T1CON |= prescaler_T1_8;
            }
            
        T1_source_0 = 1; //System clock enable (Fosc)
        T1_source_1 = 0;
        ENABLE_T1 = 1;
        overflow_interrupt_T1 = 0;
        peripheral_interrupt = 0;
        if (interruption == 1){
            overflow_interrupt_T1 = 1;
            peripheral_interrupt = 1;
            
        }
        
      
        
}

void config_T0(int prescaler,int interruption){

    if(interruption==1){

        ENABLE_INTERRUPTS = 1; //set GIE bit

        peripheral_interrupt = 1; //set PEIE bit

    }

    T0_source = 0;// set TMR0CS

    if(prescaler == 0){

        T0_enable_prescaler = 1;

    }

    else if(prescaler == 2){

        OPTION_REG |= prescaler_T0_2;

    }

    else if(prescaler == 4){

        OPTION_REG |= prescaler_T0_4;

    }

    else if(prescaler == 8){

        OPTION_REG |= prescaler_T0_8;

    }

    else if(prescaler == 16){

        OPTION_REG |= prescaler_T0_16;

    }

    else if(prescaler == 32){

        OPTION_REG |= prescaler_T0_32;

    }

    else if(prescaler == 64){

        OPTION_REG |= prescaler_T0_64;

    }

    else if(prescaler == 128){

        OPTION_REG |= prescaler_T0_128;

    }

    else if(prescaler == 264){

        OPTION_REG |= prescaler_T0_256;

    }

    CPSCON0 |= 0x01;

    if(interruption == 1){

        INTCON |= 0x20;

    }

}