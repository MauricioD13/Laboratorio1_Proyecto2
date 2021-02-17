
#include <PIC16F1827.h>
#include "timers.h"
#define enable_interrupts INTCONbits.GIE
#define enable_T1 T1CONbits.TMR1ON
#define clock_source_0 T1CONbits.TMR1CS0
#define clock_source_1 T1CONbits.TMR1CS1
#define overflow_interrupt_T1 PIE1bits.TMR1IE
#define peripheral_interrupt INTCONbits.PEIE


void config_timer(int timer_module,int prescaler,int interruption,char clock){
    
    if(interruption==1){
        enable_interrupts = 1; //set GIE bit 
        peripheral_interrupt = 1; //set PEIE bit
    }
    if (timer_module == 0){
        OPTION_REG = 0x20; // set TMR0CS 
        if(prescaler == 2){
            OPTION_REG |= prescaler_T0_2;
        }
        else if(prescaler == 4){
            OPTION_REG |= prescaler_T0_4;
        }
        else if(prescaler == 8){
            OPTION_REG |= prescaler_T0_8;
        }
        else if(prescaler == 16){
            OPTION_REG |= prescaler_T0_16;
        }
        else if(prescaler == 32){
            OPTION_REG |= prescaler_T0_32;
        }
        else if(prescaler == 64){
            OPTION_REG |= prescaler_T0_64;
        }
        else if(prescaler == 128){
            OPTION_REG |= prescaler_T0_128;
        }
        else if(prescaler == 264){
            OPTION_REG |= prescaler_T0_256;
        }
        CPSCON0 |= 0x01;
        if(interruption == 1){
            INTCON |= 0x20;
        }
    }
    if (timer_module == 1){
        T1CON &= 0x00;
        T1GCON &= 0x00;
        enable_T1 = 1;
        
        if(clock == 'I'){ //Internal clock
      
            if(prescaler == 2){
                T1CON |= prescaler_T1_2;
            }
            else if(prescaler == 4){
                T1CON |= prescaler_T1_4;
            }
            else if(prescaler == 8){
                T1CON |= prescaler_T1_8;
            }
            
            clock_source_0 = 1; //System clock enable (Fosc)
        }
        
        overflow_interrupt_T1 = 1;
        
    }
}