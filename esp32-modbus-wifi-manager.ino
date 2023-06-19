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
    Serial.print(" ");
  }

  
  mb.server();		//Start Modbus IP

  /*
  Read Coil: 0
  Discrete Inputs : 100
  Holding registers : 200
  Input registers : 300
  */

  for (int i=0;i<40;i++){
    
    if (pinconfig[i] == 0){
    //digital input
    pinMode(i, INPUT);
    }

    else if (pinconfig[i] == 1){
    //digital output
    pinMode(i, OUTPUT);
    }

    else if (pinconfig[4] == 4){
    //PWM, 10kHz, 12bit. only high speed channel
    ledcSetup(i, 10000, 12);

      if (i == 4){
        ledcAttachPin(4, 0);
      }
      
      else if (i == 13) {
      ledcAttachPin(13, 2);
      }

      else if (i == 18) {
      ledcAttachPin(18, 4);
      }
      else if (i == 19){
      ledcAttachPin(19, 6);
      }
    } 
  }

  //asigning temporary values to output pins for debug purposes
  for (int i = 0; i<40; i++){
    
    mb.addCoil(i);
    mb.addIsts(100+i);
    mb.addHreg(200+i);
    mb.addIreg(300+i);

    if (pinconfig[i] < 5 ){
      //33333 is initial value for debub for pins in use
      pinvalues[i] = 33333;
      if (pinconfig[i] == 1 || pinconfig[i]== 3 || pinconfig[i] == 4){
        pinctrlvalues[i] = 33333;
      }
    } 
    else {
      //22222 is value assigned to unused pins
      pinvalues[i] = 22222;
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
        bool binput = (bool)digitalRead(i);
        pinvalues[i] = (int)binput;
        mb.Ists(100+i, binput);
      }

      else if (pinconfig[i] == 1){
        //this pin is digital output
        bool boutput = (int)mb.Coil(i);
        pinctrlvalues[i] = (int)boutput;
        pinvalues[i] = (int)boutput;
        digitalWrite(i, boutput);
      }  

      else if (pinconfig[i] == 2) {
        //this pin is analog input
        int itempinput = analogRead(i);
        pinvalues[i] = itempinput;
        mb.Ireg(300+i, itempinput);
      }

      else if (pinconfig[i] == 3) {
        //this pin is analog output 8bit
        int itempoutput = mb.Hreg(i);
        pinctrlvalues[i] = itempoutput;
        pinvalues[i] = itempoutput;
        dacWrite(i, itempoutput);
        mb.Ireg(200+i, itempoutput);
      }

      else if (pinconfig[i] == 4) {
        //this pin is PWM. 
        int itempoutput = mb.Hreg(i);
        pinctrlvalues[i] = itempoutput;
        pinvalues[i] = itempoutput;
        ledcWrite(i, itempoutput); //12bit
        mb.Ireg(200+i, itempoutput);
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


