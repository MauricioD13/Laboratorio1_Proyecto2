/* 
 * File:   timers.h
 * Author: USER
 *
 * Created on 12 de febrero de 2021, 07:24 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

//Timer 0
#define prescaler_T0_2 0x00
#define prescaler_T0_4 0x01
#define prescaler_T0_8 0x02
#define prescaler_T0_16 0x03
#define prescaler_T0_32 0x04
#define prescaler_T0_64 0x05
#define prescaler_T0_128 0x06
#define prescaler_T0_256 0x07

//Timer 1
#define prescaler_T1_0 0x00
#define prescaler_T1_2 0x10
#define prescaler_T1_4 0x20
#define prescaler_T1_8 0x30
#define result_T1 TMR1L | (TMR1H<<8)
#define T1_flag PIR1bits.TMR1IF
#define enable_interrupts INTCONbits.GIE
#define enable_T1 T1CONbits.TMR1ON

void config_T0(int prescaler,int interruption);
void config_T1(int prescaler,int interruption);
int oscillator_module();
#endif	/* TIMERS_H */