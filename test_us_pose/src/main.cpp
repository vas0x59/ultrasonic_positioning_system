#include <Arduino.h>
#define TRIG1_PIN 4 
#define TRIG2_PIN 5
#define TRIG3_PIN 6
#define TRIG4_PIN 7
#define ECHO1_PIN 2
#define SENDING_PIN TRIG1_PIN
long timeStartSignal, timeEndSignal;
void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG1_PIN, OUTPUT);
  pinMode(TRIG2_PIN, OUTPUT);
  pinMode(TRIG3_PIN, OUTPUT);
  pinMode(TRIG4_PIN, OUTPUT);
  pinMode(SENDING_PIN, OUTPUT);
  pinMode(ECHO1_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  Serial.println("START1");
  digitalWrite(SENDING_PIN, LOW);  digitalWrite(TRIG1_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SENDING_PIN, HIGH);  digitalWrite(TRIG1_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENDING_PIN, LOW);  digitalWrite(TRIG1_PIN, LOW);
  
  // while (digitalRead(ECHO1_PIN) == LOW);   timeStartSignal = micros();
  // while (digitalRead(ECHO1_PIN) == HIGH);  timeEndSignal = micros();
  // duration = ; 
  // Рассчитаем расстояние
  float len1 = pulseIn(ECHO1_PIN, HIGH) / 58;
  // float len3 = ((timeEndSignal-timeStartSignal)/58.00)*10.00;
  // Serial.print("len1 ");
  // Serial.println(len1);
  delay(100);





  Serial.println("START2");
  digitalWrite(SENDING_PIN, LOW);  digitalWrite(TRIG2_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SENDING_PIN, HIGH);  digitalWrite(TRIG2_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENDING_PIN, LOW);  digitalWrite(TRIG2_PIN, LOW);
  
  while (digitalRead(ECHO1_PIN) == LOW);  timeStartSignal = micros();
  while (digitalRead(ECHO1_PIN) == HIGH);  timeEndSignal = micros();
  
  // float len2 = pulseIn(ECHO1_PIN, HIGH) / 58;
  float len2 = ((timeEndSignal-timeStartSignal)/58.00)*20.00;
  
  delay(100);




  Serial.println("START3");
  digitalWrite(SENDING_PIN, LOW);  digitalWrite(TRIG3_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SENDING_PIN, HIGH);  digitalWrite(TRIG3_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENDING_PIN, LOW);  digitalWrite(TRIG3_PIN, LOW);
  
  while (digitalRead(ECHO1_PIN) == LOW);   timeStartSignal = micros();
  while (digitalRead(ECHO1_PIN) == HIGH);  timeEndSignal = micros();
  // duration = ; 
  // Рассчитаем расстояние
  // float len3 = pulseIn(ECHO1_PIN, HIGH) / 58;
  float len3 = ((timeEndSignal-timeStartSignal)/58.00)*20.00;
  // Serial.print("len3 ");
  // Serial.println(len3);
  delay(100);





  Serial.println("START4");
  digitalWrite(SENDING_PIN, LOW);  digitalWrite(TRIG4_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SENDING_PIN, HIGH);  digitalWrite(TRIG4_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENDING_PIN, LOW);  digitalWrite(TRIG4_PIN, LOW);
  

  
  while (digitalRead(ECHO1_PIN) == LOW);   timeStartSignal = micros();
  while (digitalRead(ECHO1_PIN) == HIGH);  timeEndSignal = micros();
  // duration = ; 
  // Рассчитаем расстояние
  // float len4 = pulseIn(ECHO1_PIN, HIGH) / 58;
  float len4 = ((timeEndSignal-timeStartSignal)/58.00)*20.00;
  
  delay(100);
  Serial.print("len1 ");
  Serial.print(len1);
  Serial.print(" len2 ");
  Serial.print(len2);
  Serial.print(" len3 ");
  Serial.print(len3);
  Serial.print(" len4 ");
  Serial.println(len4);
   delay(100);
  // Serial.println(String(len2) + " " + String(len3));
  
  // put your main code here, to run repeatedly:
}