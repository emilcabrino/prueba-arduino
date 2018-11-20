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
