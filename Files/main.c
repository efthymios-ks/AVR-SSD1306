/*
 * OLED.c
 *
 * Created: 16/05/2023 6:10:53 p. m.
 * Author : ASUS
 */ 
//#include "SSD1306"
#define F_CPU 16000000UL
#include "SSD1306.h"
#include "Font5x8.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "DEF_ATMEGA328P.h"
// Definir el pin analógico donde se conecta el sensor
#define MQ135_PIN PINCbits.PINC0_

// Definir la resistencia de carga del sensor en ohmios
#define RL 10

// Definir la resistencia del sensor en el aire limpio en ohmios
#define R0 76.63

// Definir los coeficientes para la curva logarítmica
#define A 116.6020682
#define B -2.769034857

// Inicializar una variable para almacenar el valor leído del sensor
int mq135_value = 0;

// Inicializar una variable para almacenar la concentración de CO2 en ppm
int co2_ppm = 0;
unsigned int address = 0;
uint8_t  comun =0;
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void EEPROM_write_int(unsigned int uiAddress, int data);
void USART_Init(unsigned int);
void USART_Transmit(unsigned char);
void send_USART_String(unsigned char * msg, unsigned int length);
void setup_adc();
void send_USART_String(unsigned char * msg, unsigned int length)
{
	for(int i = 0 ; i < length ; i++){
		USART_Transmit(msg[i]);
	}
}
void USART_Init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}
void USART_Transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!( UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
void setup_adc(void) {
	// Configurar el ADC
	ADMUX |= (1 << REFS0); // Establecer la referencia de voltaje en Vcc
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Establecer el prescaler en 128
	ADCSRA |= (1 << ADEN); // Habilitar el ADC
}
int read_adc(uint8_t adc_channel) {
	// Seleccionar el canal del ADC a leer
	ADMUX &= 0xF0; // Borrar los bits de selección del canal
	ADMUX |= adc_channel; // Seleccionar el canal a leer

	// Iniciar la conversión ADC
	ADCSRA |= (1 << ADSC);

	// Esperar a que la conversión termine
	while (ADCSRA & (1 << ADSC));

	// Leer y devolver el valor del ADC
	return ADCW;
}
unsigned char UART_read(void)
{
	if(UCSR0A&(1<<7))						//si el bit7 del registro UCSR0A se ha puesto a 1
	return UDR0;						//devuelve el dato almacenado en el registro UDR0
	else
	return 0;
}
void UART_write(unsigned char caracter)
{
	while(!(UCSR0A&(1<<5)));				// mientras el registro UDR0 esté lleno espera
	UDR0 = caracter;						//cuando el el registro UDR0 está vacio se envia el caracter
}
void UART_write_txt(char* cadena)			//cadena de caracteres de tipo char
{
	while(*cadena !=0x00)
	{
		UART_write(*cadena);				//transmite los caracteres de cadena
		cadena++;							//incrementa la ubicación de los caracteres en cadena
		//para enviar el siguiente caracter de cadena
	}
}
void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	while (EECR & (1<< EEPE));
	EEAR = uiAddress;
	EEDR = ucData;
	EECR |= (1<<EEMPE);
	EECR |=(1<<EEPE);
}
void EEPROM_write_int(unsigned int uiAddress, int data)
{
	unsigned char highByte = (unsigned char)(data >> 8);    // Obtener el byte más significativo del dato
	unsigned char lowByte = (unsigned char)(data & 0xFF);   // Obtener el byte menos significativo del dato

	EEPROM_write(uiAddress, highByte);   // Escribir el byte más significativo en la dirección especificada
	EEPROM_write(uiAddress + 1, lowByte); // Escribir el byte menos significativo en la siguiente dirección consecutiva
}

int main(void)
{	
	// Inicializar el puerto serie a 9600 baudios
	UBRR0 = 103;
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	USART_Init(MYUBRR);
	
	// Configurar el ADC
	setup_adc();
	
	char buffer[50];
	
	GLCD_Setup();
	GLCD_SetFont(Font5x8, 5, 8, GLCD_Overwrite);
	GLCD_InvertScreen();
	GLCD_Clear();
	GLCD_GotoXY(10, 10);
	GLCD_PrintString("Mire ese 5 mi sensei");


	GLCD_Render();

	while (1)
	{	
		//comunicacion con el computador
		comun=UART_read();
		// Leer el valor analógico del sensor
		mq135_value = read_adc(MQ135_PIN);

		// Calcular la resistencia del sensor según el valor leído y la resistencia de carga
		float rs = ((1023.0 / mq135_value) - 1) * RL;

		// Calcular la relación rs/r0
		float ratio = rs / R0;

		// Calcular la concentración de CO2 según la curva logarítmica
		co2_ppm = A * pow(ratio, B);//= 230;
		// Imprimir el valor de CO2 en el puerto serie
		send_USART_String(buffer, strlen(buffer));
		sprintf(buffer, "CO2: %d ppm\n", co2_ppm);
		//     AQUI ESTA LA INFORMACION DEL SENSOR
		EEPROM_write_int(address, co2_ppm);
		_delay_ms(1000);
		char buffer[16];
		
		GLCD_GotoXY(10, 40);
		GLCD_PrintString("CO2:");
		GLCD_PrintInteger(co2_ppm);
		GLCD_PrintString(" ppm");
		//GLCD_PrintDouble(mq135_value,1);
		GLCD_Render();
		//_delay_ms(500);
		//GLCD_ScrollLeft(0, 0x0F);
		//_delay_ms(1000);
		//GLCD_ScrollRight(0, 0x0F);
		//_delay_ms(1000);
		//GLCD_ScrollDiagonalLeft(0, 0x0F);
		//_delay_ms(1000);
		//GLCD_ScrollDiagonalRight(0, 0x0F);
		//_delay_ms(1000);
		//GLCD_ScrollStop();
		_delay_ms(1000);
	}
	
	return 0;
}
