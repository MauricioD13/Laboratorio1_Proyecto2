/* 
 * File:   prueba_timer.c
 * Author: USER
 *
 * Created on 15 de febrero de 2021, 02:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "timers.h"
#include "ADC.h"
#include <xc.h>
#define LED1 PORTBbits.RB4

void __interrupt() isr(){
    LED1 = 1 ;
}
int main() {
    config_timer(1,0,1,'I');
    TRISB &= 0x00;
    LED1 = 0;
    config_ADC();
    start_conversion = 1;
    
}


