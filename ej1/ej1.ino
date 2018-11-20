#include <TimerOne.h>

const int ledPIN_G = 8;
const int ledPIN_Y = 7;
const int ledPIN_R = 6;
 int p1 = 2;
const int p2 = 3;
const int dx=0.2;   //distancia entre pulsadores
int ledState = LOW;
int ledState1 = LOW; // El LED empieza apagado
int ledState2 = LOW;
volatile unsigned long blinkCount = 0; // Somos muy obedientes
unsigned long previousMillis=0; // millis() returns an unsigned long.
 float vmax=16.7;  //velocidad max preestablecida de 60 km/h
  long pausa=10000000;
    bool flag1=true;
  int high1 = LOW;
  unsigned long tiempop1;
  unsigned long tiempop2;
  unsigned long interval = 2000000;
  
void setup() {
  Serial.begin(9600);    //iniciar puerto serie
  pinMode(ledPIN_G , OUTPUT);  //definir pin como salida
  pinMode(ledPIN_Y , OUTPUT);  //definir pin como salida
  pinMode(ledPIN_R , OUTPUT);  //definir pin como salida
  pinMode(p1 , INPUT);
  pinMode(p2 , INPUT);
  Timer1.initialize(1000000);         // Dispara cada 250 ms
  Timer1.attachInterrupt(ISR_Blink); // Activa la interrupcion y la asocia a ISR_Blink
  attachInterrupt(digitalPinToInterrupt(p1), ISR_P1, RISING);
  attachInterrupt(digitalPinToInterrupt(p2), ISR_P2, RISING);
 
}
 
void loop(){
  
}

void ISR_Blink(){
  ledState =! ledState;
  digitalWrite(ledPIN_Y, ledState);
}
void ISR_P1(){
  tiempop1 = millis();
  Serial.print(tiempop1);
  Serial.print("\n\r");
}

void ISR_P2(){
    tiempop2 = millis();
    Serial.print(tiempop2);
    Serial.print("\n\r");
    if ((unsigned long)(tiempop1-tiempop2) < interval){
        digitalWrite(ledPIN_Y, LOW);
        digitalWrite(ledPIN_R, HIGH);
        delay(10000000);
        digitalWrite(ledPIN_R, LOW);
    } else if ((unsigned long)(tiempop1 - tiempop2) > interval){
        digitalWrite(ledPIN_Y, LOW);
        digitalWrite(ledPIN_G, HIGH);
        delay(10000000);
        digitalWrite(ledPIN_G, LOW);
    }
}
