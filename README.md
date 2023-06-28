# Firmware that makes ESP32 function as a I/O device with Modbus-TCP + configuration interface

### Based on the following libraries
Modbus: https://github.com/emelianov/modbus-esp8266  
Wifi manager: https://github.com/tzapu/WiFiManager  
Programmed with Arduino IDE. 
Tested on TIA Portal, Codesys and Twincat3.

### Usage:
* Put pin 15 as LOW for 3 seconds to start Wifi AP mode.
* Connect to Access Point with SSID: "EvisLAB-ESP32", Key: 12345678
* Go to 192.168.4.1 on your preferred browser
* Select pinMode options by the dropdown list for each pin. "Unused" is the default option
* Write your preferred static IP and the Gateway.
* Board will restart instantly after saving and be ready to connect to any Modbus-TCP client. 

## Notes: 
### Modbus functions and addresses:  
* Write coils FC-15: 0 - 39 (Siemens: 1 - 40)
  - connected to Digital Outputs
* Read inputs FC-02: 100 - 139 (Siemens: 10101 - 10140)
  - connected to Digital Inputs
* Write Holding Registers FC-16: 200 - 239 (Siemens: 40201 - 40240)
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
 
## Flashing methods
* Arduino IDE
* ESP flash tool
  - Load the binary file and set the offset as 0x10000 (default for ESP32)
  - Keep the "boot" button pressed when connecting the USB cable, choose the COM port and press Start. 
  - After flashing start, release the "boot" button. 
 
  ![Screenshot](/build/flashing.PNG)
