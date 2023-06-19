
IPAddress local_IP;
IPAddress gateway;
IPAddress subnet(255, 255, 255, 0);

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


 //Returns: true if save successful, false if unsuccessful
bool writeToMemory(String ssid, String pass, String ipstring, String gatewaystring, String pin0, String pin1, String pin2, String pin3, String pin4, String pin5, String pin6,
 String pin7, String pin8, String pin9, String pin10, String pin11, String pin12, String pin13,  String pin14, String pin15, String pin16, String pin17, String pin18, 
 String pin19, String pin20, String pin21, String pin22, String pin23, String pin24, String pin25, String pin26, String pin27, String pin28, String pin29, String pin30, 
 String pin31, String pin32, String pin33, String pin34, String pin35, String pin36, String pin37, String pin38, String pin39)
{
  char buff1[29];
  char buff2[29];
  char buff3[19];
  char buff4[19];

  ssid.toCharArray(buff1,30);
  pass.toCharArray(buff2,30); 
  ipstring.toCharArray(buff3,20);
  gatewaystring.toCharArray(buff4,20);

  EEPROM.writeString(100,buff1);
  EEPROM.writeString(130,buff2);
  EEPROM.writeString(160,buff3);
  EEPROM.writeString(180,buff4);

  EEPROM.write(50,pin0.toInt());
  EEPROM.write(51,pin1.toInt());
  EEPROM.write(52,pin2.toInt());
  EEPROM.write(53,pin3.toInt());
  EEPROM.write(54,pin4.toInt());
  EEPROM.write(55,pin5.toInt());
  EEPROM.write(56,pin6.toInt());
  EEPROM.write(57,pin7.toInt());
  EEPROM.write(58,pin8.toInt());
  EEPROM.write(59,pin9.toInt());
  EEPROM.write(60,pin10.toInt());
  EEPROM.write(61,pin11.toInt());
  EEPROM.write(62,pin12.toInt());
  EEPROM.write(63,pin13.toInt());
  EEPROM.write(64,pin14.toInt());
  EEPROM.write(65,pin15.toInt());
  EEPROM.write(66,pin16.toInt());
  EEPROM.write(67,pin17.toInt());
  EEPROM.write(68,pin18.toInt());
  EEPROM.write(69,pin19.toInt());
  EEPROM.write(70,pin20.toInt());
  EEPROM.write(71,pin21.toInt());
  EEPROM.write(72,pin22.toInt());
  EEPROM.write(73,pin23.toInt());
  EEPROM.write(74,pin24.toInt());
  EEPROM.write(75,pin25.toInt());
  EEPROM.write(76,pin26.toInt());
  EEPROM.write(77,pin27.toInt());
  EEPROM.write(78,pin28.toInt());
  EEPROM.write(79,pin29.toInt());
  EEPROM.write(80,pin30.toInt());
  EEPROM.write(81,pin31.toInt());
  EEPROM.write(82,pin32.toInt());
  EEPROM.write(83,pin33.toInt());
  EEPROM.write(84,pin34.toInt());
  EEPROM.write(85,pin35.toInt());
  EEPROM.write(86,pin36.toInt());
  EEPROM.write(87,pin37.toInt());
  EEPROM.write(88,pin38.toInt());
  EEPROM.write(89,pin39.toInt());

  delay(100);
  

  String s = EEPROM.readString(100);
  String p = EEPROM.readString(130);
  //#if DEBUG
  Serial.print("Stored SSID, password, are: ");
  Serial.print(s);
  Serial.print(" / ");
  Serial.print(p);
  //#endif
  if(ssid == s && pass == p){
    return true;  
  }else{
    return false;
  }
}

/*
 * Function for handling form
 */
void handleSubmit(){
  String response_success="<h1>Success</h1>";
  response_success +="<h2>Device will restart in 3 seconds</h2>";
  String response_error="<h1>Error</h1>";
  response_error +="<h2><a href='/'>Go back</a>to try again";
  //"5" = null (not used)
  if(writeToMemory(String(server.arg("ssid")),String(server.arg("password")),String(server.arg("ip")),String(server.arg("gateway")), String(server.arg("pin0")),"5", 
  String(server.arg("pin2")), "5", String(server.arg("pin4")), "5", "5", "5", "5", "5", "5","5", String(server.arg("pin12")), String(server.arg("pin13")),
  String(server.arg("pin14")), "5", String(server.arg("pin16")), String(server.arg("pin17")), String(server.arg("pin18")), String(server.arg("pin19")), "5", "5", "5", 
  String(server.arg("pin23")), "5", String(server.arg("pin25")), String(server.arg("pin26")), String(server.arg("pin27")), "5", "5", "5", "5", String(server.arg("pin32")), 
  String(server.arg("pin33")), String(server.arg("pin34")), String(server.arg("pin35")), String(server.arg("pin36")), "5", "5", String(server.arg("pin39"))))
     
     {
     server.send(200, "text/html", response_success);
     EEPROM.commit();
     delay(3000);
     ESP.restart();
  }else{
     server.send(200, "text/html", response_error);
  }
}

/*
 * Function for home page
 */
void handleRoot() {
  if (server.hasArg("ssid")&& server.hasArg("password")) {
    handleSubmit();
  }
  else {
    server.send(200, "text/html", INDEX_HTML);
  }
}

/*
 * Function for loading form
 * Returns: false if no WiFi creds in EEPROM
 */
bool loadWIFICredsForm(){
  String s = EEPROM.readString(100);
  String p = EEPROM.readString(130);

  //const char* ssid     = "ESP32 WiFi Manager";
  char APname[11]; 
  sprintf(APname, "ESP_%X", ESP.getEfuseMac());
  const char* password = "12345678";
  Serial.println("Setting Access Point...");
  WiFi.softAP(APname, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  while(s.length() <= 0 && p.length() <= 0){
    server.handleClient();
    delay(100);
  }
  
  return false;
}



//Returns: true if not empty, false if empty

bool CheckWIFICreds(){
  Serial.println("Checking WIFI credentials");
  String s = EEPROM.readString(100);
  Serial.println(s);
  String p = EEPROM.readString(130);
  String ipstring = EEPROM.readString(160);
  String gatewaystring = EEPROM.readString(180);



//All GPIO pinmode status placed in array


  //#if DEBUG
  Serial.print("Found credentials: ");
  Serial.print(s);
  Serial.print("/");
  Serial.print(p);
  delay(10);
  local_IP.fromString(ipstring);
  gateway.fromString(gatewaystring);

  WiFi.config(local_IP, gateway, subnet);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(s);

  WiFi.begin(s.c_str(), p.c_str());
  int i = 0;
  while ((WiFi.status() != WL_CONNECTED) && (i < 20 )) {
    delay(500);
    i++;
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  String gpio = EEPROM.readString(300);
  Serial.println(gpio);
}

void wipeEEPROM(){
  for(int i=0;i<400;i++){
    EEPROM.writeByte(i,0);
  }
  EEPROM.commit(); 
}





