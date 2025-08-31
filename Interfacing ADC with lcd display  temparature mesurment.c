/*

 *  lm35
 * Created: 10/20/2024 10:48:10 PM
 * Author : HASHIBUR
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd/lcd.h"

void ADC_Int(void){
	//set voltage reference
	ADMUX &= ~(1<<REFS1);//clear bit 
	ADMUX|=(1<<REFS0);//set bit
	// clear adc channel 
	ADMUX &=~(1<<MUX0);
	ADMUX &=~(1<<MUX1);
	ADMUX &=~(1<<MUX2);
	ADMUX &=~(1<<MUX3);
	
	
	//set prescelar
	ADCSRA|=(1<<ADPS0);
	ADCSRA|=(1<<ADPS1);
	ADCSRA|=(1<<ADPS2);
	//enable adc
	ADCSRA |=(1<<ADEN);
	}
void adc_select_channel(uint8_t channel){
		ADMUX &=~(1<<MUX0);
		ADMUX &=~(1<<MUX1);
		ADMUX &=~(1<<MUX2);
		ADMUX &=~(1<<MUX3);
		ADMUX|= channel;
		}
		
uint16_t ADC_Read(void)
{
		//start conversion
		ADCSRA|=(1<<ADSC);
	   //	waiting conversion
		while((ADCSRA &(1<<ADIF))==0);
		//clear ADIF bit and past 
		ADCSRA|=(1<<ADIF);
		return(ADCW);
		}
int main(void)
   {
				DDRB=0xff;
				DDRD=0XFF;
				DDRA=0x00;
				int temp;
				char buffer[10];
				
				ADC_Int();	
				adc_select_channel(0);
				lcd_init(LCD_DISP_ON_CURSOR);
				lcd_clrscr();
    
    while (1) 
			{
				int val = ADC_Read();
				temp=val/2.04;
				itoa(temp,buffer,10);
				lcd_gotoxy(0,1);
				lcd_puts("temp: ");
				lcd_puts(buffer);
				lcd_puts(" C");
		if (temp==80)
			{ 
				PORTB|=(1<<PINB0);
				   }
					else
					{
						PORTB &=~(1<<PINB0);
				      }
			           _delay_ms(50);
		             }
			s}
		

