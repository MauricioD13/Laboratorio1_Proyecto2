/* 
 * File:   prueba_timer.c
 * Author: USER
 *
 * Created on 15 de febrero de 2021, 02:58 PM
 */


#include "timers.h"
#include "ADC.h"
#include <xc.h>
#define LED1 PORTBbits.RB3

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

int i = 0;
int estado = 0;
void __interrupt(low_priority) isr(void){
    
    
    i++;
    if(i==10){
        PIR1bits.TMR1IF = 0;
        LED1 = 0;
        i = 0;
    }
}
int main() {
    config_timer(1,0,1,'I');
    
    PORTB = 0x00;
    TRISB &= 0x00;  
    while(1){
        LED1 = 1;
        
        
    }
    //config_ADC();
    //start_conversion = 1;
    
}


