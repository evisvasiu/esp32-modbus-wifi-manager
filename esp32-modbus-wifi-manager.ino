#include "EEPROM.h"
#include "html.h"
#include <WebServer.h>
#include <ModbusIP_ESP8266.h>

WebServer server(80);
#include "WiFiManager.h"


//ModbusIP object
ModbusIP mb;
long ts;

int pinvalues[40];  //Storing all current pin values to this array
int pinconfig[40]; //pin configuration
int pinctrlvalues[40]; //Holding register values 
int pwmchannels[20]; //Designated PWM channel addresses


void setup() {

//Assigning PWM channels to the 4 designated PWM pins. 
  pwmchannels[4] = 0;
  pwmchannels[13] = 2;
  pwmchannels[18] = 4;
  pwmchannels[19] = 6;

  Serial.begin(115200);
  EEPROM.begin(400);
  pinMode(15, INPUT); //erasing EEPROM

  
  if(!CheckWIFICreds()){
    Serial.println("No WIFI credentials stored in memory. Loading HTML form...");
    while(loadWIFICredsForm());
  }


  //reading and printing pin configuration stored in EEPROM
  Serial.println("Pin configuration:");
  for (int i=0;i<40;i++){
    pinconfig[i] = EEPROM.read(i+50);
    Serial.print(EEPROM.read(i+50));
    Serial.print(" ");
  }

  
  mb.server();		//Start Modbus IP


  for (int i=0;i<40;i++){
    
    if (pinconfig[i] == 0){
    //digital input
    pinMode(i, INPUT);
    }

    else if (pinconfig[i] == 1){
    //digital output
    pinMode(i, OUTPUT);
    }

    else if (pinconfig[i] == 4){
    //PWM, 10kHz, 12bit. only high speed channel
    ledcSetup(pwmchannels[i], 10000, 12);
    ledcAttachPin(i, pwmchannels[i]);
    } 
  }

  for (int i = 0; i<40; i++){
    
    /* 
    Register offsets:
    Write Coils: 0
    Discrete Inputs : 100
    Holding registers : 200
    Input registers : 300
    */
    
    mb.addCoil(i);
    mb.addIsts(100+i);
    mb.addHreg(200+i);
    mb.addIreg(300+i);

  //asigning temporary values to output pins for debugging purposes
    if (pinconfig[i] < 5 ){
      //33333 is the initial value. (Assigned for debugging)
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

  mb.task();  //keeping modbus active

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
        int temp_value = averagingRawValues(i);
        pinvalues[i] = temp_value;
        mb.Ireg(300+i, temp_value);
      }

      else if (pinconfig[i] == 3) {
        //this pin is analog output 8bit
        int temp_value = (int)mb.Hreg(200+i);
        pinctrlvalues[i] = temp_value;
        pinvalues[i] = temp_value;
        dacWrite(i, temp_value);
      }

      else if (pinconfig[i] == 4) {
        //this pin is PWM. 
        int temp_value = (int)mb.Hreg(200+i);
        pinctrlvalues[i] = temp_value;
        pinvalues[i] = temp_value;
        ledcWrite(pwmchannels[i], temp_value); //12bit
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

  long reset_delay = millis();
  while (digitalRead(15) == HIGH){
    //3 Seconds delay to reset the board. 
    if (millis() > reset_delay + 3000){
    Serial.println("Wiping WiFi credentials from memory...");
    wipeEEPROM();
    while(loadWIFICredsForm());
    }
  }
}

int averagingRawValues(int pin) {
  int average_output = 0;
  int max_reads = 5;
  for (int i=0; i<max_reads; i++){
    average_output = average_output + analogRead(pin);
  }

  return average_output / max_reads;
}
