/* 
 * File:   serial.c
 * Author: guasonito
 *
 * Created on 25 de febrero de 2021, 11:04 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f1827.h>
#include "eusart.h"
#include "timers.h"
/*
 * 
 */
int main() {
    oscillator_module();
    
    TRISBbits.TRISB5 = 1;
    ANSELB = 0x00;
    config_serial();
    
    while(1){
        if(TX_flag == 1){
            transmit(7);
        }
    }
    return (EXIT_SUCCESS);
}

