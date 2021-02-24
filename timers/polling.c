/* 
 * File:   polling.c
 * Author: guasonito
 *
 * Created on 19 de febrero de 2021, 12:23 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include "numbers.h"
#include "timers.h"
#include "ADC.h"
#include <xc.h>
#define TRANS1 PORTBbits.RB3
#define TRANS2 PORTBbits.RB2
#define _XTAL_FREQ 31000
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = ON        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

typedef struct STATES{
    int seg_1;
    int seg_2;
    int seg_3;
    int flag_result;
}STATES;
int i = 0;
int estado = 0;
/*void __interrupt(low_priority) isr(void){
    
    
    i++;
    if(i==10){
        PIR1bits.TMR1IF = 0;
        LED1 = 0;
        i = 0;
    }
}*/

void convert_number(float value,int* result){
    *(result+0) = (int) value;
    *(result+1)= (int)((value*10)-((*result+0)*10));
    *(result+2) = (int)((value*100)-((*(result+0)*100)+(*(result+1)*10)));
}
int main() {
    //config_timer(1,0,1,'I');
    int result[3];
    STATES states;
    int value;
    float voltage;
    PORTB = 0x00;
    PORTA = 0x00;
    TRISA &= 0x00;
    TRISB &= 0x00; 
    ANSELA &= 0x00;
    ANSELB &= 0x00;
    oscillator_module();
    
    config_T1(0,8);
    
    estado = 1;
    config_ADC();
    
    ADC_flag = 0;
    
    PIR1 = 0x00;
    TRANS1 = 1;
    TRANS2 = 0;
    eight();
    __delay_ms(2);
    start_conversion = 1;
    
    while(1){
        TRANS2 = 0;
        TRANS1 = 1;
        if(start_conversion == 0){
            
            value = read_ADC();
            
            
            
            voltage = (float)(0.00488) * value;
            
            convert_number(voltage,result);
            ADRESL = 0x00;
            ADRESH = 0x00;
            show_number(result[0]);
            
            states.seg_1 = result[0];
            states.seg_2 = result[1];
            states.seg_3 = result[2];
            states.flag_result = 1;
            
        
            start_conversion = 1;
         }
        
        if(states.flag_result == 1){
            do{
                if(TRANS1 == 1){
                    TRANS2 = estado;
                    show_number(states.seg_1);
                    
                    
                }else{
                    TRANS1 = estado;
                    show_number(states.seg_2);
                    
                }
            
            show_number(states.seg_2);
            TRANS2 = estado;
            }while(T1_flag == 0);
        }
        
    }
        /*if(TMR1H >= 0x0F && TMR1L == 0xFF){
            
           
            if(estado == 1){
                PORTAbits.RA2 = 0;
                estado = 0;
            }else{
                LED_A = 1;
                estado = 1;
            }
            if(start_conversion == 0){
                start_conversion = 1;
            }
        }
        if(ADC_flag == 1){
            value = read_ADC();
            ADRESL = 0x00;
            ADRESH = 0x00;
            ADC_flag = 0;
         }*/
        
        
       
    //config_ADC();
    //start_conversion = 1;
      
}

