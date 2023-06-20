# Modbus TCP on ESP32 configurable by Wifi interface

### Based on the following libraries
Modbus: https://github.com/emelianov/modbus-esp8266  
Wifi manager: https://github.com/tzapu/WiFiManager  
Programmed with Arduino IDE. 
Tested on TIA Portal, Codesys and Twincat3.

### Usage:
* Connect for a second pin 15 to GND to start Wifi AP mode.
* Connect to Access Point with SSID: "ESP32-ModbusTCP", Key: 12345678
* Go to 192.168.4.1 on your preferred browser
* Select pinMode options by the dropdown list for each pin. "Unused" is the default option
* Write your preferred static IP and the Gateway.
* Board will restart instantly after saving and be ready to connect to any Modbus-TCP client. 

## Notes: 
### Modbus functions and addresses:  
* Write coils FC-01: 0 - 39 (Siemens: 0 - 39)
  - connected to Digital Outputs
* Read inputs FC-02: 100 - 139 (Siemens: 10101 - 10140)
  - connected to Digital Inputs
* Write Holding Registers FC-03: 200 - 239 (Siemens: 40201 - 40240)
  - connected to Analog Output (DAC), PWM pins
* Read Input Registers FC-04: 300 - 339 (Siemens: 30301 - 30340)
  - connected to Analog Inputs
* Port: 502
* Device ID: 1
 
### Signal parameters  
* Analog Inputs:
  - Resolution 12 bit
* Analog Outputs (DCA):
  - Resolution 8 bit
* PWM:
  - Resolution 12 bit
  - Frequency 10kHz
 
  ![Screenshot](/images/screenshot.jpeg)
