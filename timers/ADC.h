/* 
 * File:   ADC.h
 * Author: guasonito
 *
 * Created on 16 de febrero de 2021, 06:36 PM
 */

#ifndef ADC_H
#define	ADC_H
#define start_conversion ADCON0bits.GO_nDONE
#define ADC_flag PIR1bits.ADIF
void config_ADC();
int read_ADC();

#endif	/* ADC_H */

