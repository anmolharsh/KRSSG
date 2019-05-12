#include<avr/io.h>
# define UBBRVal 103
#include<avr/interrupt.h>

float check;


/*ISR(USART0_RX_vect)
{

  while( !(UCSR0A &(1<<RXC0)   )  );
      
     OCR0A = UDR0;

      check = UDR0;
      Serial.println(check);   
}
*/



int main()
{
  sei();
   

    DDRD |= (1<<PD6);  
    // PD6 is now an output

    //OCR0A = UDR0;
    
/////////////

   UBRR0H = (unsigned char)(UBBRVal>>8);
   UBRR0L = (unsigned char)UBBRVal;
  /*Enable receiver and transmitter */
  //UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  
    /* Set frame format: 8data, 2stop bit */
  //UCSR0C = (1<<USBS0)|(3<<UCSZ00);
  
  
  
  UCSR0B |= (1<<RXEN0) | (1<<RXCIE0) ;
  UCSR0C |= (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) ;   //(1<<UPM01) | (1<<UPM00) |

  ///////////////////////////////////
  
  
  
   TCCR0A |= (1 << COM0A1);
    // set none-inverting mode

    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    // set fast PWM Mode

    
    OCR0A = 18;
    
    TCCR0B |= (1 << CS01);
    // set prescaler to 8 and starts PWM

    Serial.begin(9600);

    while (1)
    {         
    //
    }
    
}
