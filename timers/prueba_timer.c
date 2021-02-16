/* 
 * File:   prueba_timer.c
 * Author: USER
 *
 * Created on 15 de febrero de 2021, 02:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "timers.h"
#include <xc.h>
#define PORTBbits.RB
/*
 * 
 */
void __interrupt() isr(){
    PORTBbits.RB7 ;
}
int main() {
    config_timer(1,0,1,'I');
    TRISB &= 0x00;
    
}


