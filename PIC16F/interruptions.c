/* 
 * File:   interruptions.c
 * Author: Mauricio David Cuello Alzate
 *         Joan Ferney Muñoz Tarazona
 *         Daniel Guillermo Morantes
 *
 * Created on 25 de febrero de 2021, 02:55 PM
 */
#include "Timers/timers.h"
#include "numbers/numbers.h"
#include "EUSART/eusart.h"
#include "ADC/ADC.h"
#include <PIC16F1827.h>
#include <xc.h>

#define TRANS1 PORTBbits.RB3
#define TRANS2 PORTBbits.RB5
#define TRANS3 PORTBbits.RB0
#define _XTAL_FREQ 8000000

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

int cont_tx = 0; //Counter to iterate between numbers and symbols to be sended
int cont_show = 1; //Counter to iterate between displays
int value;// Save the data of ADC
STATES states; //Struct to save the voltage information between ADC reads
/*
 * 
 */
void convert_number0(float value,STATES *states){
    
    (states->seg_3) = (int) (value);
    (states->seg_2)= (int)((value*10)-((states->seg_3)*10));
    (states->seg_1) = (int)((value*100)-((states->seg_3 *100)+(states->seg_2 *10)));
    
}


void __interrupt() T1_isr(void){
    if(T1_FLAG == 1){
    
        START_CONVERSION = 1;
        cont_show++;
        T1_FLAG = 0; 
        
    }
    else if(ADC_FLAG == 1){
        
        value = read_ADC();
        states.flag_init = 1; // This flag indicate if there is a number to show 
        ADC_FLAG = 0;
        
    }
}
int main() {
    
    
    // Initialize all I/O registers to 0
    PORTB = 0x00;
    PORTA = 0x00;
    TRISA &= 0x00;
    TRISB &= 0x00; 
    ANSELA &= 0x00;
    ANSELB &= 0x00;
    
    
    oscillator_module(); // Configuration of internal oscillator at 8M
    
    config_T1(0,1); // Configuration Timer 1, prescaler of 8, and interrupts enable
    
    config_serial(0); // Configuration UART, Baud rate 9600, and interrupts enable
    
    config_ADC(1); // Configuration ADC, Reference, analog input and interrupts enable
    
    TRISBbits.TRISB2 = 1; //TX pin as output
    
    ENABLE_INTERRUPTS = 1; // Global interrupt enable (GIE)
    
    while(1){
        
        if(states.flag_init == 1){
            
            float voltage;
            
            voltage = (float)((0.004882812) * (value)*2 - 0.02); //Equation to convert ADC read to voltage
            
            convert_number0(voltage,&states); // Convert the float number in three separated numbers
            
            if(cont_show==1){
                
                TRANS2 = 0;
                TRANS3 = 0;
                show_number(states.seg_3); //Function that enable some LEDs depend of the number
                TRANS1 = 1;
                
            }
            
            else if(cont_show==2){
                
                TRANS1 = 0;
                TRANS3 = 0;
                show_number(states.seg_2);
                TRANS2 = 1;   
                
            }
            
            else{
                
                TRANS1 = 0;
                TRANS2 = 0;
                show_number(states.seg_1);
                TRANS3 = 1;
                cont_show = 0;
                
            }
            if(TXSTAbits.TRMT == 1){
                cont_tx++;
                //Serial communication works sending each digit separate by '-' and when the number ends it send '#'
                if(cont_tx == 1){
                    transmit(states.seg_3);
                }
                else if (cont_tx == 2){
                    transmit(45);
                }
                else if (cont_tx == 3){
                    transmit(states.seg_2);
                }
                else if (cont_tx == 4){
                    transmit(45);
                }
                else if (cont_tx == 5){
                    transmit(states.seg_1);
                }
                else if (cont_tx == 6){
                    transmit(35);
                    cont_tx = 0;
                }
        }
        
        }
    }
    
}
    


