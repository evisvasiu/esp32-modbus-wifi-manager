#include "EEPROM.h"
#include "HTML.h"
#include <WebServer.h>
#include <ModbusIP_ESP8266.h>

WebServer server(80);
#include "WiFiManager.h"


//ModbusIP object
ModbusIP mb;

long ts;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(15,INPUT); //for resetting WiFi creds
  EEPROM.begin(400);
  Serial.begin(115200);
  if(!CheckWIFICreds()){
    Serial.println("No WIFI credentials stored in memory. Loading form...");
    digitalWrite(2,HIGH);
    while(loadWIFICredsForm());

  }
   mb.server();		//Start Modbus IP
  mb.addIreg(0);
  ts = millis();
}


void loop() {
  mb.task();
  if(digitalRead(15) == HIGH){
    Serial.println("Wiping WiFi credentials from memory...");
    wipeEEPROM();
    while(loadWIFICredsForm());
  }

   if (millis() > ts + 100) {
       ts = millis();
       //Setting raw value (0-1024)
       mb.Ireg(0, analogRead(34));

   }

    static unsigned long lastMillis = 0;
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    Serial.printf("free heap: %d\n", ESP.getFreeHeap());
  }

}

void wipeEEPROM(){
  for(int i=0;i<400;i++){
    EEPROM.writeByte(i,0);
  }
  EEPROM.commit(); 
}
