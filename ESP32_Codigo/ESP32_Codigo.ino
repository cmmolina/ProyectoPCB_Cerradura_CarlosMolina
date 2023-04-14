// Universidad del Valle de Guatemala
// Simulación y Fabricación de PCB's
// Carlos Molina
// 14/04/2023

/**************************** Configuration ************************************/

//WI-Fi
#include "config.h"

//I2C
#include "Wire.h"
#include <Arduino.h>

/****************************** Variables ***********************************/
int rojo = 0;
int azul = 0;
int verde = 0;
int linea = 0;
int mobi = 0;
int estado = 0;
uint32_t i = 0;

#define I2C_DEV_ADDR 0x48
#define SDA_PIN 21
#define SCL_PIN 22

/************************ Prototipe of Function ******************************/

/******************************** Main ***************************************/
void onReceive(int len){

  while(Wire.available()){
    //rojo = Wire.read();
    //verde = Wire.read();
    //azul = Wire.read();
    estado = Wire.read();
    mobi = Wire.read();
    linea = Wire.read();
  }

}

void onRequest(){
  Wire.print(i++);
  Wire.print(" Packets.");
  Serial.println("onRequest");
}

// set up the feeds
AdafruitIO_Feed *rojofeed = io.feed("Rojo");
AdafruitIO_Feed *azulfeed = io.feed("Azul");
AdafruitIO_Feed *verdefeed = io.feed("Verde");
AdafruitIO_Feed *lineafeed = io.feed("Linea");
AdafruitIO_Feed *mobydickfeed = io.feed("Movimiento");

void setup() {
  
  // start the serial connection 
  

  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  Wire.begin((uint8_t)I2C_DEV_ADDR);

  Serial.begin(9600);                                // 9600 
  
  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");
  
  // connect to io.adafruit.com
  io.connect();
  
  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  // rotfeed->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Because Adafruit IO doesn't support the MQTT retain flag, we can use the
  // get() function to ask IO to resend the last value for this feed to just
  // this MQTT client after the io client is connected.
  //** rotfeed->get();

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  if (estado == 0){
    rojo = 0;
    verde = 0;
    azul = 0;
  }

  else if (estado == 1){
    rojo = 0;
    verde = 1;
    azul = 0;
  }

  else if (estado == 2){
    rojo = 0;
    verde = 0;
    azul = 1;
  }

  else{
    rojo = 1;
    verde = 0;
    azul = 0;
  }

  // Enviamos Identificación del color "Rojo"
  Serial.print("sending -> ");
  Serial.println(rojo);
  rojofeed->save(rojo);
  
  // Enviamos Identificación del color "Azul"
  Serial.print("sending -> ");
  Serial.println(azul);
  azulfeed->save(azul);
  
  // Enviamos Identificación del color "Verde"
  Serial.print("sending -> ");
  Serial.println(verde);
  verdefeed->save(verde);
  
  // Enviamos Reconocimiento de Objetos Cercanos 
  Serial.print("sending -> ");
  Serial.println(mobi);
  mobydickfeed->save(mobi);
  
  // Enviamos Reconocimiento de Linea
  Serial.print("sending -> ");
  Serial.println(linea);
  lineafeed->save(linea);

  Serial.print(Wire.read());
  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  
  delay(3000);
}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.

void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

  delay(1);
}
