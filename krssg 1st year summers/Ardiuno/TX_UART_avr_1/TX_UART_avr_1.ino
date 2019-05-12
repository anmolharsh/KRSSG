#include<avr/io.h>
#define UBBRVal 100

int main()
{

  Serial.begin(9600);
/*  ADCSRA |= (1<<ADEN) | (1<<ADPS2) |  (1<<ADPS0) ;
ADMUX |= (1<<REFS0)| (1<<ADLAR)|(1<<MUX2)|(1<<MUX0);
  */
  
  
  
  UBRR0H |= (unsigned char)(UBBRVal>>8);
  UBRR0L |= (unsigned char)UBBRVal;

  
  /*Enable receiver and transmitter */
  //UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  
    /* Set frame format: 8data, 2stop bit */
  //UCSR0C = (1<<USBS0)|(3<<UCSZ00);
  
  
  
  UCSR0B |= (1<<TXEN0) ;
  UCSR0C |= (1<<UPM01) | (1<<UPM00) | (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) ;
  
 
  
   while(1)
  {
    
  /*  ADCSRA |= (1<<ADSC) ;
    while(ADCSRA & (1<<ADSC));
    float X;
    X=(float)ADC;
    Serial.println(X*255/65535);  
    */
    
    
    // while (    !(  UCSR0A & (1<<UDRE0) )    );
    /* Put data into buffer, sends the data */
  //  UDRn = data;
    
    
        //Wait until the Transmitter is ready
    while (! (UCSR0A & (1 << UDRE0))  ); 
     
     UDR0 = 10 ;      //UDR0 = X;
     int c = (int)UDR0;
    
    Serial.println(c);
  }

}
