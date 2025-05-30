#include <xc.h>
#include <stdio.h>         // Para sprintf
#include "uart.h"
#include "adc.h"

#pragma config FOSC = INTIO67  // Oscilador interno
#pragma config WDTEN = OFF     // Watchdog Timer apagado
#pragma config LVP = OFF       // Low Voltage Programming off

int valor_adc;         ///// VARIABLE PARA EL VALOR DEL ADC
float voltaje;         ///// VARIABLE PARA EL VALOR DEL VOLTAJE

void main(void) 
{
    char buffer[40];   // Buffer para el mensaje formateado

    // Configuración del oscilador a 16 MHz
    OSCCON = 0b01110000;

    UART_Init();       // Inicializa UART 
    ADC_Init();        // Inicializa ADC en AN0
    
    while(1) {
        valor_adc = ADC_Read(0);       // Leer canal AN0
        voltaje = (valor_adc * 5.0f) / 1023.0f;

        // Crear mensaje formateado
        sprintf(buffer, "V: %1.2f V\r\n", voltaje);
        
        // Enviar mensaje por UART
       // UART_WriteString("Hola, UART funcionando!\r\n");
        UART_WriteString(buffer);
        
        __delay_ms(100);
    }
}