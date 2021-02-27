#include <PIC16F1827.h>
#include "eusart.h"

void config_serial(){
    
    RCSTA = 0x00;
    TXSTA = 0x00;
    
    TXSTAbits.TXEN = 1;
    
    TXSTAbits.SYNC = 0;
    
    RCSTAbits.SPEN = 1;
    
    BAUDCONbits.BRG16 = 1;
    
    PIE1bits.TXIE = 1;
    
    SPBRGH = 0x00;
    SPBRGL = 0x19;
    
}

void transmit(int value){
    if (value == 0){
        TXREG = 48;
    }
    else if(value ==1){
        TXREG = 49;
    }
    else if(value ==2){
        TXREG = 50;
    }
    else if(value ==3){
        TXREG = 51;
    }
    else if(value ==4){
        TXREG = 52;
    }
    else if(value ==5){
        TXREG = 53;
    }
    else if(value ==6){
        TXREG = 54;
    }
    else if(value ==7){
        TXREG = 55;
    }
    else if(value ==8){
        TXREG = 56;
    }
    else if(value ==9){
        TXREG = 57;
    }
    
}
