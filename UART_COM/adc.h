#ifndef ADC_H
#define ADC_H

#include <xc.h>
#define _XTAL_FREQ 64000000UL

void ADC_Init(void);
unsigned int ADC_Read(unsigned char ch);

#endif