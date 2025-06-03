#include "adc.h"

void ADC_Init(void)
{
    TRISAbits.TRISA0 = 1;         // RA0 como entrada
    ANSELAbits.ANSA0 = 1;         // Habilita analógico en RA0
    ADCON1 = 0x00;                // Vref+ = VDD, Vref- = VSS
    ADCON2 = 0b10111110;          // Justificado a la derecha, Tacq=20TAD, Fosc/64
    ADCON0 = 0x01;                // Selecciona canal AN0 y habilita el ADC
}

unsigned int ADC_Read(unsigned char ch)
{
    if (ch > 13) return 0;        // Validar canal

    ADCON0 &= 0b11000011;         // Limpia bits del canal
    ADCON0 |= (ch << 2);          // Selecciona nuevo canal
    __delay_us(5);                // Pequeño retardo de adquisición

    ADCON0bits.GO_DONE = 1;       // Inicia conversión
    while (ADCON0bits.GO_DONE);  // Espera a que termine

    return ((ADRESH << 8) + ADRESL); // Retorna resultado de 10 bits
}
