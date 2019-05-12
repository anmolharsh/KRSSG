#include<avr/io.h>
#define UBBRVal 103
#include<avr/interrupt.h>

int X=0;

/*ISR(ADC_vect)
{
 
    X=ADC;
    
   while (! (UCSR0A & (1 << UDRE0)) );         //temp
     
    UDR0 = X ;   
    Serial.println(X*255/65535);        //*255/65535      //temp
    ADCSRA |= (1<<ADSC) ;  
}
*/


int main()
{
  sei();
 
  
  //ADCSRA |= (1<<ADEN) | (1<<ADPS2) |  (1<<ADPS1) | (1<<ADIE)  ;
  //ADMUX |= (1<<REFS0)| (1<<ADLAR) ;
    
  UBRR0H = (unsigned char)(UBBRVal>>8);    //temp
  UBRR0L = (unsigned char)UBBRVal;          //temp

  //UDR0 = 2;//X ;
  /*Enable receiver and transmitter */
  //UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2stop bit */
  //UCSR0C = (1<<USBS0)|(3<<UCSZ00);

  UCSR0B |= (1<<TXEN0) ;          //temp
  UCSR0C |=  (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) ;      //temp (1<<UPM01) | (1<<UPM00) |

  //ADCSRA |= (1<<ADSC);

  Serial.begin(9600);
  
   while(1)
  {    //X++;
       
      // UDR0 = 2; 
       
  }

return 0;

}
