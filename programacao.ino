#include "DFRobotDFPlayerMini.h"

#include "SoftwareSerial.h"

#include <Ultrasonic.h>

#define velocidade 340
#define pinTx 10
#define pinRx 11
#define volumeMP3 30

SoftwareSerial playerMP3Serial (pinRx, pinTx);
DFRobotDFPlayerMini playerMP3;

int btn_OnOff = 10;
int btn_Modo = 9;
int Vibra = 8;
int PinoTrig1 = 7;
int PinoEcho1 = 6;
int PinoTrig2 = 5;
int PinoEcho2 = 4;

//buttons estados
int estado_btn_OnOff = 0;
int estado_btn_Modo = 0;
int estado_btn_OnOff_Valor = 0;

void setup()
{
  Serial.begin(9600);
  playerMP3Serial.begin(9600);
  
  pinMode(btn_OnOff, INPUT);
  pinMode(btn_Modo, INPUT);
  pinMode(Vibra, OUTPUT);
  pinMode(PinoTrig1, OUTPUT);
  pinMode(PinoEcho1, INPUT);
  pinMode(PinoTrig2, OUTPUT);
  pinMode(PinoEcho2, INPUT);

  playerMP3.playFolder(1, 1);
}

void loop()
{
  char voz = 0;
  estado_btn_OnOff = digitalRead(btn_OnOff);
  estado_btn_Modo = digitalRead(btn_Modo);
 
  //sinal sonoro senso 1
  digitalWrite(PinoTrig1, HIGH);
  delayMicroseconds (10);
  digitalWrite(PinoTrig1, LOW);
 
  float tempo1 = pulseIn(PinoEcho1, HIGH);
  tempo1 = tempo1 / 1000000;
 
  //sinal sonoro sensor 2
  digitalWrite (PinoTrig2, HIGH);
  delayMicroseconds (10);
  digitalWrite (PinoTrig2, LOW);
 
  float tempo2 = pulseIn(PinoEcho2, HIGH);
  tempo2 = tempo2 / 1000000;
 
  //conversão
  float dist1 = tempo1 * velocidade;
  dist1 = dist1/2;
  dist1 = dist1*100; //conversão para CM
  Serial.print("A distancia1 eh: ");
  Serial.print(dist1);
  Serial.println(" cm");
 
  float dist2 = tempo2 * velocidade;
  dist2 = dist2/2;
  dist2 = dist2*100; //conversão para CM
  Serial.print("A distancia2 eh: ");
  Serial.print(dist2);
  Serial.println(" cm");
 //delay(1000);
 
  //if (estado_btn_OnOff == HIGH){
//estado_btn_OnOff_Valor = 1;    
  //}
 
  //if (estado_btn_OnOff_Valor == 1){
  //programação vibracall
  //funcionamento caso distancia do sensor 1 seja menor que do 2

  if (dist1 < dist2) {
    Serial.println("Distancia 1 eh menor");
    if (dist1 > 300 && dist1 < 500){
      playerMP3.playFolder(2, 4);
      digitalWrite(Vibra,LOW);
      delay(300);
      digitalWrite(Vibra, HIGH);
      delay(1700);
    }
   
    else if (dist1 > 200 && dist1 < 300){
      playerMP3.playFolder(2, 3);
      digitalWrite(Vibra,LOW);
      delay(300);
      digitalWrite(Vibra,HIGH);
      delay(1500);
    }
 
    else if (dist1 > 100 && dist1 < 200){
      playerMP3.playFolder(2, 2);
      digitalWrite(Vibra,LOW);
      delay(300);
      digitalWrite(Vibra,HIGH);
      delay(1000);
    }
   
    else if (dist1 < 100){
      playerMP3.playFolder(2, 1);
      digitalWrite(Vibra,LOW);
      delay(1000);
      digitalWrite(Vibra,HIGH);
      delay(300);
    }
  }
   
  //funcionamento caso distancia do sensor 2 seja menor que do 1
  else {
   Serial.println("Distancia 2 eh menor");
   if (dist2 > 300 && dist2 < 500){
      playerMP3.playFolder(2, 4);
      digitalWrite(Vibra,LOW);
      delay(300);
      digitalWrite(Vibra, HIGH);
      delay(1700);
    }
   
    else if (dist2 > 200 && dist1 < 300){
      playerMP3.playFolder(2, 3);
      digitalWrite(Vibra,HIGH);
      delay(300);
      digitalWrite(Vibra,LOW);
      delay(1500);
    }
   
    else if (dist2 > 100 && dist1 < 200){
      playerMP3.playFolder(2, 2);
      digitalWrite(Vibra,LOW);
      delay(300);
      digitalWrite(Vibra,HIGH);
      delay(1300);
    }
   
    else if (dist2 < 100){
      playerMP3.playFolder(2, 1);
      digitalWrite(Vibra,LOW);
      delay(1000);
      digitalWrite(Vibra,HIGH);
      delay(300);
    }
  }
  //}
}
