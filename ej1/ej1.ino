#include <TimerOne.h>

const int ledPIN_G = 8;
const int ledPIN_Y = 7;
const int ledPIN_R = 6;
int p1 = 2;
const int p2 = 3;
const int dx=0.2;   //distancia entre pulsadores
int ledState = LOW;
float vmax=16.7;  //velocidad max preestablecida de 60 km/h
uint16_t pausa = 10000000;
bool flag = false;
uint16_t tiempop1;
uint16_t tiempop2;
unsigned long tiempo_verif;
unsigned long interval = 2000000;
unsigned long MAX_TIME = 5000000;

// TENES QUE HACER EL INCLUDE DEL ARCHIVO EN 
// https://github.com/FernandezGFG/MyEP-2018/blob/master/UART-ej1/ATMEGA328P/UART.c

//    Rutina de servicio de interrupción por recepción de datos en UART
uint8_t indcom;
char comando[10];

ISR (USART_RX_vect){
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

FILE uart_io = FDEV_SETUP_STREAM(_putc, _getc, _FDEV_SETUP_RW);

//--------------------------------------------------------
// INTERPRETE DE COMANDO
void interprete(void){
  switch (comando[0]) {
    case '':
	  if (comando[1]){
      // Aca le darías el valor a la velocidad máxima
      // VMAX = atoi(&comando[1]);
		  // printf("V: %d\n", VMAX);
	  } else {
		  printf(":ERR\n");
	  }
      break;

    default:
      printf(":ERR\n");
      break;
  }
}
  
void setup() {
  //Serial.begin(9600);    //iniciar puerto serie
  pinMode(ledPIN_G , OUTPUT);  //definir pin como salida
  pinMode(ledPIN_Y , OUTPUT);  //definir pin como salida
  pinMode(ledPIN_R , OUTPUT);  //definir pin como salida
  pinMode(p1 , INPUT);
  pinMode(p2 , INPUT);
  Timer1.initialize(1000000);         // Dispara cada 250 ms
  Timer1.attachInterrupt(ISR_Blink); // Activa la interrupcion y la asocia a ISR_Blink
  attachInterrupt(digitalPinToInterrupt(p1), ISR_P1, RISING);
  attachInterrupt(digitalPinToInterrupt(p2), ISR_P2, RISING);
  
  UART_init(9600);
  stdout = stdin = &uart_io;
  indcom = 0;
  
  // Esto no se si va
  sei();
 
}
 
void loop(){
  tiempo_verif = millis();
  if (flag && (tiempo_verif - tiempop1) > MAX_TIME){
    flag = 0;
    Serial.print(":IGN\n\r");
  }
}

void ISR_Blink(){
  ledState =! ledState;
  digitalWrite(ledPIN_Y, ledState);
}
void ISR_P1(){
  flag = true;
  tiempop1 = millis();
  Serial.print(tiempop1);
  Serial.print("\n\r");
  delay(100); // Antirrebote
}

void ISR_P2(){
    if (flag){
      tiempop2 = millis();
      Serial.print(tiempop2);
      Serial.print("\n\r");
      if ((tiempop2-tiempop1) < interval){
          Serial.print(":CD1\n\r");
          digitalWrite(ledPIN_Y, LOW);
          digitalWrite(ledPIN_R, HIGH);
          delay(pausa);
          digitalWrite(ledPIN_R, LOW);
      } else if ((tiempop2 - tiempop1) > interval){
          Serial.print(":CD2\n\r");
          digitalWrite(ledPIN_Y, LOW);
          digitalWrite(ledPIN_G, HIGH);
          delay(pausa);
          digitalWrite(ledPIN_G, LOW);
      }
      flag = false;
    } else {
      Serial.print(":V");
      Serial.print(vmax);
      Serial.print("\n\r;");
    }
    delay(100);   //antirrebote
}
