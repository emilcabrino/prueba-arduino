/*
	Fuente:
	https://forum.arduino.cc/index.php?topic=349921.0
*/

#include <avr/interrupt.h>
#include <avr/io.h>

#define USART_BAUDRATE 9600

void setup(){
	...
	UBRR0L = USART_BAUDRATE & 0xff;
   	UBRR0H = USART_BAUDRATE >> 8;
  	UCSR0C |= (1 << UCSZ00) | (1 << USBS0); // Use 8-bit character sizes
   	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);   // Turn on the transmission, reception, and Receive interrupt     
   	interrupts();
}


ISR(USART0_RXC){ 
  	UDR0 = 1;
	char dato=getc();
 	 switch (dato) {
    		case ':':
      			indcom=0;
      			break;
    		case '\r':
      			comando[indcom]=0;
      			interprete();
      			break;
    		default:
      			comando[indcom++]=dato;
      			break;
	}
}


//------------INTERPRETE DE COMANDO-----------------------
void interprete(void){
  switch (comando[0]) {
    case 'V':
	  if (comando[1]){
		  // V_MAX = atoi(&comando[1]);
		  // printf("V: %d\n", V_MAX);
	  } else {
		  printf(":ERR\n");
	  }
      break;

    default:
      printf(":ERR\n");
      break;
  }
}
