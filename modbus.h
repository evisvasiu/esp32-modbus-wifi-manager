// =================================================================================================
// eModbus: Copyright 2020 by Michael Harwerth, Bert Melis and the contributors to ModbusClient
//               MIT license - see license.md for details
// =================================================================================================
// Includes: <Arduino.h> for Serial etc., WiFi.h for WiFi support
#include <Arduino.h>

// Modbus server TCP
#include "ModbusServerTCPasync.h"


// Create server
ModbusServerTCPasync MBserver;

// Server function to handle FC 0x03 and 0x04
ModbusMessage FC03(ModbusMessage request) {
  ModbusMessage response;      // The Modbus message we are going to give back
  uint16_t addr = 0;           // Start address
  uint16_t words = 1;          // # of words requested
  request.get(2, addr);        // read address from request
  request.get(4, words);       // read # of words from request

  // Address overflow?
  if ((addr + words) > 20) {
    // Yes - send respective error response
    response.setError(request.getServerID(), request.getFunctionCode(), ILLEGAL_DATA_ADDRESS);
  }
  // Set up response
  response.add(request.getServerID(), request.getFunctionCode(), (uint8_t)(words * 2));
  //FC 0x03
  if (request.getFunctionCode() == READ_HOLD_REGISTER) {
    // Yes. Complete response
    for (uint8_t i = 0; i < words; ++i) {
      // send increasing data values
      response.add((uint16_t)(addr + i));
    }
  } else {
    //FC 0x04
    for (uint8_t i = 0; i < words; ++i) {
      // send increasing data values
      response.add((uint16_t)analogRead(34));
    }
  }
  // Send response back
  return response;
}
