#define F_CPU 16000000
#include <avr/io.h>
int main()
{
  Serial.begin(9600);
 int UBRR_Value = 103; //9600 Baud 16MHz
  UBRR0H = (unsigned char) (UBRR_Value >> 8);
  UBRR0L = (unsigned char) UBRR_Value;
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
  UCSR0C = (1 << USBS0) | (3 << UCSZ00); 


 while(1)
  {
   /* ADMUX=(0<<REFS1)|(0<<REFS0)|(1<<ADLAR)|(0<<MUX0)|(0<<MUX1)|(0<<MUX2); 

  ADCSRA=(1<<ADEN)|(1<<ADSC);
  int adc = (ADCH<<2)|(ADCL>>6);
  while(ADCSRA&(1<<6)!=0);
    Serial.println(adc); */
    while (! (UCSR0A & (1 << UDRE0)) );
   UDR0 = 10;
   Serial.println(UDR0);
  }
  
  return 0;
}
