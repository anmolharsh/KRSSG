#include<avr/io.h>
#include <avr/interrupt.h>
//N = 1
// S = 0
// Vcc = 00   GND = 10   NC = 10
//n-mos 1 = ON    0 = OFF
//p-mos 0 = ON    1 = OFF

int h1 = 48 ;
int h2 = 50 ;
int h3 = 52 ;
int Q3L = 33 ;
int Q3H = 31 ;
int Q2L = 37 ;
int Q2H = 35 ;
int Q1L = 41 ;
int Q1H = 39 ;

void setup()
{
  
  pinMode(h1,INPUT);
  pinMode(h2,INPUT);
  pinMode(h3,INPUT);
  pinMode(Q1H,OUTPUT);
  pinMode(Q1L,OUTPUT);
  pinMode(Q2H,OUTPUT);
  pinMode(Q2L,OUTPUT);
  pinMode(Q3H,OUTPUT);
  pinMode(Q3L,OUTPUT);

   
}

void loop()
{
   int H1 = digitalRead(h1);
   int H2 = digitalRead(h3);
   int H3 = digitalRead(h3);
   
   int q1h = !( (!H1) && H2 ) ;
   int q1l = ( (!H2) && H1 ) ;
   int q2h = !( (!H2) && H3 ) ;
   int q2l = ( (!H3) && H2 ) ;
   int q3h = !( (!H3) && H1 ) ;
   int q3l = ( (!H1) && H3 ) ;
  /*BH = !( (!H2) && H3 ) ;    //Q2H -p
  BL = ( (!H3) && H2 ) ;    //Q2L -n

  CH = !( (!H3) && H1 ) ;    //Q3H -p
  CL = ( (!H1) && H3 ) ;    //Q3L -n

  AH = !( (!H1) && H2 ) ;    //Q1H -p 
  AL = ( (!H2) && H1 ) ;    //Q1L -n
  */
  digitalWrite(Q1H, q1h );
  digitalWrite(Q1L, q1l );
  
  digitalWrite(Q2H, q2h );
  digitalWrite(Q2L, q2l );
  
  digitalWrite(Q3H, q3h );
  digitalWrite(Q3L, q3l );
  
}


/*
int main()
{
    DDRD = 0b00000000 ; // hall sensors PD7-H1, PD6-H2, PD5-H3
    PCICR |= (1<<PCIE2) ;
    PCMSK2 |= (1<<PCINT23) | (1<<PCINT22) | (1<<PCINT21) ;

    DDRB = 0b00111111 ;   // output for C, B, A

}



/*
ISR(PCINT23_vect)
{

  //PORTB = (( H3 | (~H2) ) << PB1)  |  (( PD5 & (~PD6) )<<PB0)  |  (( PD7 & (~PD5) ) << PB3)  |  (( PD7 | (~PD5) ) << PB2)  |  (( PD5 & (~PD7) ) << PB5)  |  (( PD5 | (~PD7) ) << PB4 ) ;
  
  //PB1 = ( H3 | (~H2) ) ;    //Q1H -p
  //PB0 = ( H3 & (~H2) ) ;    //Q1L -n

  //PB3 = ( H1 & (~H3) ) ;    //Q2H -p
  //PB2 = ( H1 | (~H3) ) ;    //Q2L -n

  //PB5 = ( H3 & (~H1) ) ;    //Q3H -p 
  //PB4 = ( H3 | (~H1) ) ;    //Q3L -n
  
}




ISR(PCINT22_vect)
{

  PORTB = (( PD5 | (~PD6) ) << PB1)  |  (( PD5 & (~PD6) )<<PB0)  |  (( PD7 & (~PD5) ) << PB3)  |  (( PD7 | (~PD5) ) << PB2)  |  (( PD5 & (~PD7) ) << PB5)  |  (( PD5 | (~PD7) ) << PB4 ) ;
}



ISR(PCINT21_vect)
{

  PORTB = (( PD5 | (~PD6) ) << PB1)  |  (( PD5 & (~PD6) )<<PB0)  |  (( PD7 & (~PD5) ) << PB3)  |  (( PD7 | (~PD5) ) << PB2)  |  (( PD5 & (~PD7) ) << PB5)  |  (( PD5 | (~PD7) ) << PB4 ) ;
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
  switch(x):
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
