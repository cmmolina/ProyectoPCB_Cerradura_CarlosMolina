// Universidad del Valle de Guatemala
// Simulación y Fabricación de PCB's
// Carlos Molina
// 14/04/2023

/**************************** Configuration ************************************/

//WI-Fi
#include "config.h"

// Servo

//LCD
#include <LiquidCrystal.h>

//Keypad 
#include <Keypad.h>

//Strings
#include <string.h>

//RTC
#include <ESP32Time.h>

/****************************** Variables ***********************************/
int pos = 0;        

int DOOR = 0; 

String password = "5280";
String passclose = "0000";

int cont = 0;
int temp = 0;
int temporal = 1;

const int buttonPinOpen = 35;
const int buttonPinClose = 34;

int buttonStateOpen = 0;  
int buttonStateClose = 0;

int i = 10;
int n = 0;

int k = 6;
int j = 0;

char myArray[4]={};
char Array[4]={};

const byte ROWS = 4;
const byte COLS = 4;

char Keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {13,12,14,27};
byte colPins[COLS] = {26,25,33,32};

/************************ Prototipo de Funcion *******************************/

/******************************* Main ****************************************/
// set up the feeds
/*
AdafruitIO_Feed *counter = io.feed("Lots");
AdafruitIO_Feed *temperaturefeed = io.feed("Temperature");
AdafruitIO_Feed *proximityfeed = io.feed("Proximity");
AdafruitIO_Feed *rotfeed = io.feed("Rotation");
*/

// set up the LCD Pins
LiquidCrystal lcd(19,23,18,17,16,21);

// set up the Keypad 
Keypad myKeypad = Keypad(makeKeymap(Keys), rowPins, colPins, ROWS, COLS);

void setup(){
  pinMode(buttonPinOpen, INPUT);
  pinMode(buttonPinClose, INPUT);

  // start the serial connection 
  Serial.begin(9600);             // 9600 

  // wait for serial monitor to open
  while(! Serial);

  // Número de Columnas y Filas de nuestra LCD 2x16
  lcd.begin(16,2);
  lcd.setCursor(0, 0);
  lcd.print("Carlos' Room");
  lcd.setCursor(0, 1);
  lcd.print("Enter key ____");
}

void loop(){
  buttonStateOpen = digitalRead(buttonPinOpen);
  buttonStateClose = digitalRead(buttonPinClose);

  char key = myKeypad.getKey();
  if ( (key) && (i<=13) && (DOOR == 0) ){
    lcd.setCursor(i,1);
    lcd.print(key);
    myArray[n] = key;
    n = n+1;
    i = i+1;
  }

  else if ( (i>13) && (myArray[0]==password[0]) && (myArray[1]==password[1]) && (myArray[2]==password[2]) && (myArray[3]==password[3]) && (DOOR == 0) ){
    secuencia_de_apertura();
  }

  else if ( (i>13) && (DOOR == 0) ){
    n = 0;
    i = 10;
    for (int i = 0; i < 4; i++) {
      myArray[i] = '\0';
    }
    lcd.setCursor(0,1);
    lcd.print("Incorrect key!");
    delay(2000);                      // wait for a second 
    lcd.setCursor(0, 1);
    lcd.print("Enter key ____");
  }

  else if ( (buttonStateOpen == HIGH) && (DOOR ==0) ){
    secuencia_de_apertura();
  }

  else if ( DOOR == 1 ) {

    if (cont == 0){
      lcd.setCursor(2,0);
      lcd.print("DOOR IS OPEN");

      lcd.setCursor(6,1);
      lcd.print("____");
      cont = 1;
    }

    if ( (key) && (k<=9) ){
      lcd.setCursor(k,1);
      lcd.print(key);
      Array[j] = key;
      j = j+1;
      k = k+1;
    }

    else if (k>9){
      k = 6;
      j = 0;
      for (int i = 0; i < 4; i++) {
        Array[i] = '\0';
      }
      lcd.setCursor(6,1);
      lcd.print("!!!!");
      delay(2000); 
      lcd.setCursor(6,1);
      lcd.print("____");
    }

    if ( (Array[0] == passclose[0]) && (Array[1] == passclose[1]) && (Array[2] == passclose[2]) && (Array[3] == passclose[3]) ){
      secuencia_de_cierre();
    }
    
    if (buttonStateClose == HIGH){
      secuencia_de_cierre();
    }
  }

  /*
  else{
    lcd.setCursor(0,0);
    lcd.print("HUBO ERROR!!!!");
    lcd.setCursor(0,1);
    lcd.print("HUBO ERROR!!!!");
  }
  */

  //lcd.setCursor(0, 1);
  //lcd.print(millis()/1000);
}

void secuencia_de_cierre(){
  k = 6;
  j = 0;
  for (int i = 0; i < 4; i++) {
    Array[i] = '\0';
    }
  DOOR = 0; 
  cont = 0;
  
  lcd.clear();
  // Dejamos saber a la persona que la puerta está abriendose 
  lcd.setCursor(0,1);
  lcd.print("Door Closing");
  delay(1000);                      // wait for a second 
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("Door Closing.");
  delay(1000);                      // wait for a second 
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("Door Closing..");
  delay(1000);                      // wait for a second 
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("Door Closing...");
  delay(1000);                      // wait for a second 
  lcd.clear(); 

  lcd.setCursor(0, 0);
  lcd.print("Carlos' Room");
  lcd.setCursor(0, 1);
  lcd.print("Enter key ____");
}

void secuencia_de_apertura(){
  n = 0;
  i = 10;
  for (int i = 0; i < 4; i++) {
    myArray[i] = '\0';
    }
  DOOR = 1;

  lcd.clear();
  // Dejamos saber a la persona que la puerta está abriendose 
  lcd.setCursor(0,1);
  lcd.print("Door Opening");
  delay(1000);                      // wait for a second 
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("Door Opening.");
  delay(1000);                      // wait for a second 
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("Door Opening..");
  delay(1000);                      // wait for a second 
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("Door Opening...");
  delay(1000);                      // wait for a second 
  lcd.clear();   

}