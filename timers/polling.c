/* 
 * File:   polling.c
 * Author: guasonito
 *
 * Created on 19 de febrero de 2021, 12:23 PM
 */

#include <PIC16F1827.h>
#include <xc.h>
#include "timers.h"
#include "ADC.h"
#define result_T1H TMR1H
#define result_T1L TMR1L
#define LED1 PORTAbits.RA4

int cont = 0;
int main() {
    int status;
    int value;
    status = oscillator_module();
    config_timer(1,0,0,'I'); //Timer module, prescaler, interruptions, clock
    
    while(1){
        if(TMR1IF==1){
            cont++;
            if (cont == 10000){
                LED1 = 1;
            }
        }
        if(ADC_flag == 1){
            value=read_ADC();
            
        }
        
    }

}

