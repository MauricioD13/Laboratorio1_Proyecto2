/* 
 * File:   eusart.h
 * Author: guasonito
 *
 * Created on 22 de febrero de 2021, 07:08 PM
 */

#ifndef EUSART_H
#define	EUSART_H
#define TX_flag PIR1bits.TXIF

void config_serial(int interruption);
void transmit();


#endif	/* EUSART_H */

