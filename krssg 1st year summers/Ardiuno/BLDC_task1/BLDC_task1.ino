#include<avr/io.h>
#include <avr/interrupt.h>
//N = 1
// S = 0
// Vcc = 00   GND = 10   NC = 10
//n-mos 1 = ON    0 = OFF
//p-mos 0 = ON    1 = OFF


int main()
{
    DDRD = 0b00000000 ; // hall sensors PD7-H1, PD6-H2, PD5-H3
    PCICR |= (1<<PCIE2) ;
    PCMSK2 |= (1<<PCINT23) | (1<<PCINT22) | (1<<PCNT21) ;

    DDRB = 0b00111111 ;   // output for C, B, A

}




ISR(PCINT23_vect)
{
  PB1 = ( PD5 | (~PD6) ) ;    //Q1H -p
  PB0 = ( PD5 & (~PD6) ) ;    //Q1L -n

  PB3 = ( PD7 & (~PD5) ) ;    //Q2H -p
  PB2 = ( PD7 | (~PD5) ) ;    //Q2L -n

  PB5 = ( PD5 & (~PD7) ) ;    //Q3H -p 
  PB4 = ( PD5 | (~PD7) ) ;    //Q3L -n
  
}


ISR(PCINT22_vect)
{
  PB1 = ( PD5 | (~PD6) ) ;    //Q1H -p
  PB0 = ( PD5 & (~PD6) ) ;    //Q1L -n

  PB3 = ( PD7 & (~PD5) ) ;    //Q2H -p
  PB2 = ( PD7 | (~PD5) ) ;    //Q2L -n

  PB5 = ( PD5 & (~PD7) ) ;    //Q3H -p 
  PB4 = ( PD5 | (~PD7) ) ;    //Q3L -n
  
}


ISR(PCINT21_vect)
{
  PB1 = ( PD5 | (~PD6) ) ;    //Q1H -p
  PB0 = ( PD5 & (~PD6) ) ;    //Q1L -n

  PB3 = ( PD7 & (~PD5) ) ;    //Q2H -p
  PB2 = ( PD7 | (~PD5) ) ;    //Q2L -n

  PB5 = ( PD5 & (~PD7) ) ;    //Q3H -p 
  PB4 = ( PD5 | (~PD7) ) ;    //Q3L -n
  
}




/*
ISR(PCINT23_vect)
{
  
  x = 100*PD7 + 10*PD6 + PD5 ;
  switch x:
  case 100:
    PORTB = Ob00001110 ;    //now A = - | B = S | C = N   001110   110001
  break;
 
  case 010:
    PORTB = 0b00111000 ;    //now A = N | B = - | C = S
  break;
  
  case 001:
    PORTB = 0b00100011 ;    //now A = S | B = N | C = -   100011    011100  
  break;

  case 110:
     PORTB = 0b00100011 ;    //now A = S | B = N | C = -
  break;

  case 011:
    PORTB = Ob00001110 ;    //now A = - | B = S | C = N
  break;

  case 101 :
    PORTB = 0b00111000 ;    //now A = N | B = - | C = S
  break;
  
}

ISR(PCINT22_vect)
{
  
  x = 100*PD7 + 10*PD6 + PD5 ;
  switch x:
    case 100:
    PORTB = Ob00001110 ;    //now A = - | B = S | C = N   001110   110001
  break;
 
  case 010:
    PORTB = 0b00111000 ;    //now A = N | B = - | C = S
  break;
  
  case 001:
    PORTB = 0b00100011 ;    //now A = S | B = N | C = -   100011    011100  
  break;

  case 110:
     PORTB = 0b00100011 ;    //now A = S | B = N | C = -
  break;

  case 011:
    PORTB = Ob00001110 ;    //now A = - | B = S | C = N
  break;

  case 101 :
    PORTB = 0b00111000 ;    //now A = N | B = - | C = S
  break;
  
}


ISR(PCINT21_vect)
{
  
  x = 100*PD7 + 10*PD6 + PD5 ;
  switch x:
  case 100:
    PORTB = Ob00001110 ;    //now A = - | B = S | C = N   001110   110001
  break;
 
  case 010:
    PORTB = 0b00111000 ;    //now A = N | B = - | C = S
  break;
  
  case 001:
    PORTB = 0b00100011 ;    //now A = S | B = N | C = -   100011    011100  
  break;

  case 110:
     PORTB = 0b00100011 ;    //now A = S | B = N | C = -
  break;

  case 011:
    PORTB = Ob00001110 ;    //now A = - | B = S | C = N
  break;

  case 101 :
    PORTB = 0b00111000 ;    //now A = N | B = - | C = S
  break;
  
}

*/

/*void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

*/
