/* 
 * File:   ADC.h
 * Author: Mauricio David Cuello Alzate
 *         Joan Ferney Muñoz Tarazona
 *         Daniel Guillermo Morantes
 *
 * Created on 16 de febrero de 2021, 06:36 PM
 */

#ifndef ADC_H
#define	ADC_H
#define START_CONVERSION ADCON0bits.GO_nDONE
#define ADC_FLAG PIR1bits.ADIF
void config_ADC(int interruption);
int read_ADC(void);

#endif	/* ADC_H */

