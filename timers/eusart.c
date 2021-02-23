#include <PIC16F1827.h>
#include "eusart.h"

void config_serial(){
    TXSTA = 0x00;
    TXSTAbits.TXEN = 1;
    
    TXSTAbits.SYNC = 0;
    
    RCSTAbits.SPEN = 1;
    
    BAUDCONbits.BRG16 = 1;
    
    SPBRGH = 0x00;
    SPBRGL = 0x03;
    
}
