/* 
 * File:   polling.c
 * Author: guasonito
 *
 * Created on 19 de febrero de 2021, 12:23 PM
 */


#include "numbers.h"
#include "timers.h"
#include "ADC.h"
#include "eusart.h"
#include <xc.h>
#define TRANS1 PORTBbits.RB3
#define TRANS2 PORTBbits.RB5
#define TRANS3 PORTBbits.RB0
#define _XTAL_FREQ 4000000
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

#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)


int main() {
    
    STATES states;
    int value;
    float voltage;
    int cont = 0;
    
    PORTB = 0x00;
    PORTA = 0x00;
    TRISA &= 0x00;
    TRISB &= 0x00; 
    ANSELA &= 0x00;
    ANSELB &= 0x00;
    
    TRISBbits.TRISB2 = 1;
    oscillator_module();
    
    config_T1(8,0);
    
    config_ADC(0);
    
    config_serial(0);
    
    ADC_flag = 0;
    
    PIR1 = 0x00;
   
    start_conversion = 1;
    
    while(1){
        
        if(start_conversion == 0){
            
            value = read_ADC();
            
            
            
            voltage = (float)(0.0048671) * value * 2 ;
            
            convert_number(voltage,&states);
            ADRESL = 0x00;
            ADRESH = 0x00;
            
            
            
            states.flag_result = 1;
            
            
            start_conversion = 1;
         }
        
        if(states.flag_result == 1){
            if(TXSTAbits.TRMT == 1){
                transmit(states.seg_1);
            }
            
            while(cont<30){
                
                if(cont<10){
                    
                    TRANS2 = 0;
                    TRANS3 = 0;
                    show_number(states.seg_3);
                    TRANS1 = 1;
                    
                    
                }else if(cont<21){
                    TRANS1 = 0;
                    TRANS3 = 0;
                    show_number(states.seg_2);
                    TRANS2 = 1;   
                }else{
                    TRANS1 = 0;
                    TRANS2 = 0;
                    show_number(states.seg_1);
                    TRANS3 = 1;
                }
                cont++;
           
            }
            
            cont = 0;
        }
        
    }
}

