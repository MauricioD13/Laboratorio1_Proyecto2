
#include <stdio.h>
#include <PIC16F1827.h>
#include "timers.h"


void config_timer(int timer_module,int prescaler,int interruption,char clock){
    
    if(interruption==1){
        INTCON |= 0x80; //set GIE bit 
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
        T1CON |= 0x01;
        T1GCON &= 0x00;
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
            
            T1CON |= 0x40;
        }
        
        T1GCON |= 0x40;
        PIE1 |= 0x01;
        INTCON |= 0xC0;
    }
}