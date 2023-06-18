#include "EEPROM.h"
#include "HTML.h"
#include <WebServer.h>
#include "modbus.h"

WebServer server(80);
#include "WiFiManager.h"

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


  // Define and start RTU server
  //MBserver.registerWorker(1, READ_HOLD_REGISTER, &FC03);      // FC=03 for serverID=1
  MBserver.registerWorker(1, READ_INPUT_REGISTER, &FC03);     // FC=04 for serverID=1
  MBserver.start(502, 1, 20000);

}


void loop() {
  if(digitalRead(15) == HIGH){
    Serial.println("Wiping WiFi credentials from memory...");
    wipeEEPROM();
    while(loadWIFICredsForm());
  }
  digitalWrite(2,HIGH);
  delay(1000);
  digitalWrite(2,LOW);
  delay(1000);

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
