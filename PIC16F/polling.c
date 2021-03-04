/* 
 * File:   polling.c
  * Author: Mauricio David Cuello Alzate
 *         Joan Ferney Muñoz Tarazona
 *         Daniel Guillermo Morantes
 *
 * Created on 19 de febrero de 2021, 12:23 PM
 */


#include "numbers/numbers.h"
#include "Timers/timers.h"
#include "ADC/ADC.h"
#include "EUSART/eusart.h"
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

void convert_number0(float value,STATES *states){
    
    (states->seg_3) = (int) (value);
    (states->seg_2)= (int)((value*10)-((states->seg_3)*10));
    (states->seg_1) = (int)((value*100)-((states->seg_3 *100)+(states->seg_2 *10)));
    
}

int main() {

    
    int cont_conversion = 0; //Counter to start the conversion
    int cont_tx = 0; //Counter to iterate between numbers and symbols to be sended
    int cont_show = 1; //Counter to iterate between displays
    int value;// Save the data of ADC
    STATES states; //Struct to save the voltage information between ADC reads
    float voltage;
    PORTB = 0x00;
    PORTA = 0x00;
    TRISA &= 0x00;
    TRISB &= 0x00; 
    ANSELA &= 0x00;
    ANSELB &= 0x00;
    
    TRISBbits.TRISB2 = 1;
    oscillator_module();
    
    config_T0(64,0);
    
    config_ADC(0);
    
    config_serial(0);
    
    PIR1 = 0x00;
    while(1){
        if(T0_FLAG == 1){
            if(cont_conversion>=1000){
                START_CONVERSION = 1;
                cont_conversion = 0;
            }
            cont_conversion++;
            cont_show++;
            T0_FLAG = 0;
            
        }
        //ADC convertion complete
        if(ADC_FLAG == 1){
            value = read_ADC();
            voltage = (float)(0.0048671) * value * 2 ;
            
            convert_number0(voltage,&states);
            ADRESL = 0x00;
            ADRESH = 0x00;
            
            states.flag_result = 1;
            ADC_FLAG = 0;
         }
        
        if(states.flag_result == 1){
            
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
            
            if(cont_show>=4){
                cont_show=0;
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

