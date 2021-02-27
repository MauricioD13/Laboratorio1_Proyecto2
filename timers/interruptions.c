/* 
 * File:   interruptions.c
 * Author: guasonito
 *
 * Created on 25 de febrero de 2021, 02:55 PM
 */
#include "timers.h"
#include "numbers.h"
#include "eusart.h"
#include "ADC.h"
#include <PIC16F1827.h>
#include <xc.h>

#define TRANS1 PORTBbits.RB3
#define TRANS2 PORTBbits.RB5
#define TRANS3 PORTBbits.RB0
#define _XTAL_FREQ 4000000
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = ON        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = ON        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)



int cont = 0;
STATES states;
/*
 * 
 */
void convert_number0(float value,STATES *states){
    
    (states->seg_3) = (int) (value);
    (states->seg_2)= (int)((value*10)-((states->seg_3)*10));
    (states->seg_1) = (int)((value*100)-((states->seg_3 *100)+(states->seg_2 *10)));
    
}


void __interrupt() isr(void){
    if(T1_flag ==1){
        cont++;
        if(cont >= 5){
            start_conversion = 1;
            cont = 0;
        }
        T1_flag = 0;
        if(states.flag_show == 1){
            WDTCONbits.SWDTEN = 1;
            SLEEP();
        }
        //enable_interrupts = 1;
    }
    else if(ADC_flag == 1){
        
        float voltage;
        voltage = (float)((0.004882812) * (read_ADC())*2 - 0.02);
        
        convert_number0(voltage,&states);
        
        states.flag_result = 1;
        //enable_interrupts = 1;
        ADC_flag = 0;
        
    }else if(TX_flag == 1 && states.flag_result == 1){
        transmit(states.seg_1);
        TX_flag = 0;
    }
    //enable_interrupts = 1;
}
int main() {
    oscillator_module();
    config_T1(8,1);
    
    //Watchdog
    WDTCON = 0x00;
    
    WDTCONbits.WDTPS2 = 1;
    WDTCONbits.WDTPS3 = 1;  
    
    
    config_serial();
    
    PORTB = 0x00;
    PORTA = 0x00;
    TRISA &= 0x00;
    TRISB &= 0x00; 
    ANSELA &= 0x00;
    ANSELB &= 0x00;
    
    config_ADC(1);
    TRISBbits.TRISB2 = 1;
    enable_interrupts = 1;
    
    while(1){
        if(states.flag_result == 1){
            
            
            while(cont<30){
                
                if(cont<10){
                    
                    TRANS2 = 0;
                    TRANS3 = 0;
                    show_number(states.seg_3);
                    TRANS1 = 1;
                    
                    
                }else if(cont<20){
                    TRANS1 = 0;
                    TRANS3 = 0;
                    show_number(states.seg_2);
                    TRANS2 = 1;   
                }else{
                    TRANS1 = 0;
                    TRANS2 = 0;
                    show_number(states.seg_1);
                    TRANS3 = 1;
                    states.flag_result = 1;
                }
                cont++;
           
            }
            
            cont = 0;
        }
    }
    
    
    
}

