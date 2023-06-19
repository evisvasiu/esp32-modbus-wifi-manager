#include "EEPROM.h"
#include "HTML.h"
#include <WebServer.h>
#include <ModbusIP_ESP8266.h>

WebServer server(80);
#include "WiFiManager.h"


//ModbusIP object
ModbusIP mb;
long ts;

int pinvalues[40];
int pinconfig[40];
int pinctrlvalues[40];


void setup() {

  Serial.begin(115200);
  EEPROM.begin(400);
  pinMode(15, INPUT); //erasing EEPROM

  
  if(!CheckWIFICreds()){
    Serial.println("No WIFI credentials stored in memory. Loading HTML form...");
    while(loadWIFICredsForm());
  }


  //reading and printing stored pin configuration from EEPROM
  Serial.println("Pin configuration:");
  for (int i=0;i<40;i++){
    pinconfig[i] = EEPROM.read(i+50);
    Serial.print(EEPROM.read(i+50));
  }

  
  mb.server();		//Start Modbus IP

  for (int i=0;i<40;i++){
  int temp_value = pinconfig[i];
    switch (temp_value) {
    case 0:
    //digital input
    pinMode(i, INPUT);

    case 1:
    //digital output
    pinMode(i, OUTPUT);

    case 4:
    //PWM, 10kHz, 12bit. only high speed channel
     ledcSetup(i, 10000, 12);

    switch (i){
      case 4: 
      ledcAttachPin(4, 0);
      case 13:
      ledcAttachPin(13, 2);
      case 18:
      ledcAttachPin(18, 4);
      case 19:
      ledcAttachPin(19, 6);
      break;
      }
    break;
    }
  }


  //asigning temporary values to output pins for debug purposes
  for (int i = 0; i<40; i++){

    mb.addIreg(i);
    mb.addHreg(i);
    if (pinconfig[i] < 5 ){
      //33333 is initial value for debub for pins in use
      pinvalues[i] = 33333;
      if (pinconfig[i] == 1 || pinconfig[i]== 3 || pinconfig[i] == 4){
        pinctrlvalues[i] = 33333;
      }
    } 
    else {
      //12345 is value assigned to unused pins
      pinvalues[i] = 22222;
      mb.Ireg(i, 22222);
      pinctrlvalues[i] = 22222;
    }

  }
  ts = millis();
}

void loop() {

  mb.task();
  //modbus refresh rate
  if (millis() > ts + 100) {
    ts = millis();

    for (int i = 0; i<40; i++){

      if (pinconfig[i] == 0){
        //this pin is digital input
        pinvalues[i] = digitalRead(i);
        mb.Ireg(i, pinvalues[i]);
      }
      else if (pinconfig[i] == 1){
        //this pin is digital output
        pinctrlvalues[i] = mb.Hreg(i);
        pinvalues[i] = pinctrlvalues[i];
        digitalWrite(i, pinvalues[i]);
        mb.Ireg(i, pinvalues[i]);
      }  
      else if (pinconfig[i] == 2) {
        //this pin is analog input
        pinvalues[i] = analogRead(i);
        mb.Ireg(i, pinvalues[i]);
      }
      else if (pinconfig[i] == 3) {
        //this pin is analog output 8bit
        pinctrlvalues[i] = mb.Hreg(i);
        pinvalues[i] = pinctrlvalues[i];
        dacWrite(i, pinvalues[i]);
        mb.Ireg(i, pinvalues[i]);
      }
      else if (pinconfig[i] == 4) {
        //this pin is PWM
        pinctrlvalues[i] = mb.Hreg(i);
        pinvalues[i] = pinctrlvalues[i];
        ledcWrite(i, pinvalues[i]); //12bit
        mb.Ireg(i, pinvalues[i]);
      }

    }
/*
      Serial.println("Input registers:");
      for (int i = 0; i<40; i++){
        Serial.print(pinvalues[i]);
        Serial.print(" ");
      }
      Serial.println();

      Serial.println("Hold registers:");
      for (int i = 0; i<40; i++){
        Serial.print(pinctrlvalues[i]);
        Serial.print(" ");
      }
      Serial.println();*/
    }

  
  if(digitalRead(15) == HIGH){
    Serial.println("Wiping WiFi credentials from memory...");
    wipeEEPROM();
    while(loadWIFICredsForm());
  }
}


