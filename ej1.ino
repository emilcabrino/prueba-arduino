#include <TimerOne.h>

const int ledPIN_G = 8;
const int ledPIN_Y = 7;
const int ledPIN_R = 6;
 int p1 = 12;
const int p2 = 11;
const int dx=0.2;   //distancia entre pulsadores
int ledState = LOW;
int ledState1 = LOW; // El LED empieza apagado
volatile unsigned long blinkCount = 0; // Somos muy obedientes
unsigned long previousMillis=0; // millis() returns an unsigned long.
 float vmax=16.7;  //velocidad max preestablecida de 60 km/h
  long pausa=10000000;
    bool flag1=true;
  int high1 = LOW;
void setup() {
  Serial.begin(9600);    //iniciar puerto serie
  pinMode(ledPIN_G , OUTPUT);  //definir pin como salida
  pinMode(ledPIN_Y , OUTPUT);  //definir pin como salida
  pinMode(ledPIN_R , OUTPUT);  //definir pin como salida
  pinMode(p1 , INPUT);
  pinMode(p2 , INPUT);
  Timer1.initialize(1000000);         // Dispara cada 250 ms
  Timer1.attachInterrupt(ISR_Blink); // Activa la interrupcion y la asocia a ISR_Blink
  p1.attachInterrupt(ISR_P1);
 
}
 
void loop(){
  
  unsigned long interval=2000; // the time we need to wait

      unsigned long N;  // holds a copy of the blinkCount
      if (digitalRead(p1)==HIGH){
        unsigned long tiempop1 = millis();
        digitalWrite(p1 , HIGH);
        if (digitalRead(p2)==HIGH){
          unsigned long tiempop2 = millis();
          if((unsigned long)(tiempop1 - tiempop2) > interval){
            noInterrupts();
            digitalWrite(ledPIN_Y , LOW);
            digitalWrite(ledPIN_R , HIGH);
            delay(1000000); 
            digitalWrite(ledPIN_R , LOW);
            interrupts();
          }
          if ((unsigned long)(tiempop1 - tiempop2) < interval){
            noInterrupts();
            digitalWrite(ledPIN_Y , LOW);
            digitalWrite(ledPIN_G , HIGH);
            delay(1000000); 
            digitalWrite(ledPIN_G , LOW);
            interrupts();
          }
          
        }
      }

     


}
void ISR_Blink()
{
  ledState = !ledState;
  digitalWrite(ledPIN_Y, ledState);
}
void ISR_P1()
{
  ledState1 = !ledState1;
  digitalWrite(ledPIN_R, ledState1);
}
    
