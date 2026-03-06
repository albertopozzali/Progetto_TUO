#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
const int BUZZERPIN = 4;
const int VERDEPIN = 8;
const int ROSSOPIN = 9;
const int MODE = 12;
const int BLUPIN = 13;
 
float temperatura;
float umidita;
 
unsigned long del, change;
 
const int LIMMIN = 15;
const float LAMP = 23.5;
const int LIMMAX = 25;
const int LIMUMMIN = 60;
const int LAMPUM = 85;
const int LIMUMMAX = 90;
bool Stato = false;
 
void setup() {
  Serial.begin(9600);
  pinMode(MODE, INPUT_PULLUP);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(VERDEPIN, OUTPUT);
  pinMode(ROSSOPIN, OUTPUT);
  pinMode(BLUPIN, OUTPUT);
  dht.begin();
}
 
void loop(){
  del = millis();
  temperatura = (float)dht.readTemperature();
  umidita = (float)dht.readHumidity();
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C ");
  Serial.print("Umidita: ");
  Serial.print(umidita);
  Serial.println("% ");
  if(digitalRead(MODE) == 1){
    digitalWrite(BLUPIN, LOW);
    if(temperatura >= LIMMIN && temperatura < LAMP){
      digitalWrite(VERDEPIN, HIGH);
      digitalWrite(ROSSOPIN, LOW);
      digitalWrite(BUZZERPIN, LOW);
    }else if (temperatura >= LAMP && temperatura < LIMMAX){
      digitalWrite(ROSSOPIN, LOW);
      change = del;
      if(change < del + 100 && Stato == false){
        digitalWrite(VERDEPIN, HIGH);
        digitalWrite(BUZZERPIN, HIGH);
        Stato = true;
      }else if(change < del + 100 && Stato == true){
        digitalWrite(VERDEPIN, LOW);
        digitalWrite(BUZZERPIN, LOW);
        Stato = false;
      }
    }else if (temperatura >= LIMMAX){
      digitalWrite(ROSSOPIN, HIGH);
      digitalWrite(VERDEPIN, LOW);
      digitalWrite(BUZZERPIN, HIGH);
    }else{
      digitalWrite(VERDEPIN, LOW);
      digitalWrite(ROSSOPIN, LOW);
      digitalWrite(BUZZERPIN, LOW);
    }
  } else {
    digitalWrite(VERDEPIN, LOW);
    if(umidita >= LIMUMMIN && umidita < LAMPUM){
      digitalWrite(BLUPIN, HIGH);
      digitalWrite(ROSSOPIN, LOW);
      digitalWrite(BUZZERPIN, LOW);
    }else if (umidita >= LAMPUM && umidita < LIMUMMAX){
      digitalWrite(ROSSOPIN, LOW);
      change = del;
      if(change < del + 100 && Stato == false){
        digitalWrite(BLUPIN, HIGH);
        digitalWrite(BUZZERPIN, HIGH);
        Stato = true;
      }else if(change < del + 100 && Stato == true){
        digitalWrite(BLUPIN, LOW);
        digitalWrite(BUZZERPIN, LOW);
        Stato = false;
      }
    }else if (umidita >= LIMUMMAX){
      digitalWrite(ROSSOPIN, HIGH);
      digitalWrite(BLUPIN, HIGH);
      digitalWrite(BUZZERPIN, HIGH);
    }else{
      digitalWrite(BLUPIN, LOW);
      digitalWrite(ROSSOPIN, LOW);
      digitalWrite(BUZZERPIN, LOW);
    }
  }
}
