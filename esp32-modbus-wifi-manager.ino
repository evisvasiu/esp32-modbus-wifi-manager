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
  EEPROM.begin(400);
  Serial.begin(115200);
  //reading stored pin configuration from EEPROM
  int test_print = EEPROM.read(51);

  for (int i=0;i<40;i++){
    pinconfig[i] = EEPROM.read(i+50);
    Serial.print(EEPROM.read(i+50));
  }

  for (int i=0;i<40;i++){
  int temp_value = pinconfig[i];
  Serial.print(temp_value);
    switch (temp_value) {
    case 0:
    //digital input
    pinMode(i, INPUT);
    case 1:
    //digital output
    pinMode(i, OUTPUT);
    case 4:
    //PWM, 5000Hz, 10bit
     ledcSetup(i, 5000, 10);
    switch (i){
      case 4: 
      ledcAttachPin(4, 0);
      case 13:
      ledcAttachPin(13, 2);
      case 18:
      ledcAttachPin(18, 4);
      case 19:
      ledcAttachPin(19, 6);
      case 23:
      ledcAttachPin(23, 8);
      case 27:
      ledcAttachPin(27, 10);
      case 32:
      ledcAttachPin(32, 12);
      case 33:
      ledcAttachPin(33, 14);
      break;
      }
    break;
    }
  }


  pinMode(15,INPUT); //erase EEPROM
  
  

  if(!CheckWIFICreds()){
    Serial.println("No WIFI credentials stored in memory. Loading form...");
    digitalWrite(2,HIGH);
    while(loadWIFICredsForm());
  }

  mb.server();		//Start Modbus IP
  //adding inputs to input registers
  for (int i = 0; i<40; i++){
    mb.addIreg(i); 
  }
  mb.addHreg(100);
  
  ts = millis();

  //asigning temporary values to output pins for debug purposes
  for (int i = 0; i<40; i++){

    if (pinconfig[i] == 1 || pinconfig[i] == 1 ||pinconfig[i] == 4){
      //11111 is default value for analogout and pwm
      pinvalues[i] = 11111;
    } 
    else {
      //12345 is value assigned to non used pins
      pinvalues[i] = 12345;
    }

  }

}

void loop() {

  //Reading analog values
    for (int i = 0; i<40; i++){

      if (pinconfig[i] == 0){
        //this pin is digital input
        pinvalues[i] = digitalRead(i);
      }
      else if (pinconfig[i] == 1){
        //this pin is digital output
        pinvalues[i] = pinctrlvalues[i];
        digitalWrite(i, pinvalues[i]);
      }  
      else if (pinconfig[i] == 2) {
        //this pin is analog input
        pinvalues[i] = analogRead(i);
      }
      else if (pinconfig[i] == 3) {
        //this pin is analog output
        pinvalues[i] = pinctrlvalues[i];
        dacWrite(i, pinvalues[i]); //8bit
      }
      else if (pinconfig[i] == 4) {
        //this pin is PWM
        pinvalues[i] = pinctrlvalues[i];
        ledcWrite(i, pinvalues[i]); //10bit
      }

    }

    mb.task();

   if (millis() > ts + 100) {
      ts = millis();
      for (int i = 0; i<40; i++){
       //Setting raw value (0-1024)
        mb.Ireg(i, pinvalues[i]);
        
      }
    }

  if(digitalRead(15) == HIGH){
    Serial.println("Wiping WiFi credentials from memory...");
    wipeEEPROM();
    while(loadWIFICredsForm());
  }
  Serial.println(mb.Hreg(100));
}


