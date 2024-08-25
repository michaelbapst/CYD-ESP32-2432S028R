/************************************************************************************************************
  Wifi Access Point LED Test for ESP32 Cheap Yellow Display 
  Adapted by Michael Bapst (https://www.einherjar.org)
  Creates a customized Wifi Access Point and serves up a Webpage (Default: 192.168.4.1) with 3 links.
  Displays Server access information on the display. Clicking a link will toggle CYD's built in LED Red/Green/Blue colors on/off

  This code was a learning project on how to set up and access point, serve simple html, how to deal with simple client requests,
  and working with simple GPIO interface.

  WIFI_AP_LED_TEST.ino based on WiFiAccessPoint.ino
  Created for arduino-esp32 on 04 July, 2018 by Elochukwu Ifediora (fedy0)
*************************************************************************************************************/

// Make sure to copy the UserSetup.h file libraries\TFT_eSPI as
// per the Github Instructions . The pins are defined in there.
// https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display/blob/main/DisplayConfig/User_Setup.h

#include <WiFi.h>
#include <NetworkClient.h>
#include <WiFiAP.h>
#include <TFT_eSPI.h>
                                                                                           
#define LED_GREEN 16  // Set the CYD's LED GPIO pin for Green
#define LED_RED 4     // Set the CYD's LED GPIO pin for Red
#define LED_BLUE 17   // Set the CYD's LED GPIO pin for Blue


// Uncomment the next lines if you want a custom IP Address, otherwise the default is 192.168.4.1
// const IPAddress APIPAddress(10, 10, 10, 1);
// const IPAddress SubNetIP(255, 255, 255, 0);

// Set these to your desired credentials.
const char *ssid = "TestServer";
const char *password = "123456789"; // Set to "" for no password, Open Network

NetworkServer server(80);
TFT_eSPI tft = TFT_eSPI();

void SetLED(int LEDColor, bool On_Off = true) {
  //Turns on or off the built in LED color
  switch (LEDColor) {
    case LED_RED:
      if (On_Off == true) {
          digitalWrite(LED_RED, LOW);
        } else {
          digitalWrite(LED_RED, HIGH);
      }
      break;
    case LED_BLUE:
      if (On_Off == true) {
          digitalWrite(LED_BLUE, LOW);
        } else {
          digitalWrite(LED_BLUE, HIGH);
      }
      break;
    case LED_GREEN:
      if (On_Off == true) {
          digitalWrite(LED_GREEN, LOW);
        } else {
          digitalWrite(LED_GREEN, HIGH);
      }
      break;
    default:
      break;  //Do Nothing
  }
}

void setup() {
  // Set up the LED GPIO pins and turn them all off. 
  // The RGB LED set up is reversed. HIGH = ON, LOW = OFF
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, HIGH);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Initializing screen...");

  // Initialize the LCD Screen
  tft.init();
  tft.setRotation(1); // This is the display in landscape
  tft.fillScreen(TFT_BLACK);
  
  Serial.println();
  Serial.println("Configuring access point...");

  // Setup Wifi Access Point
  WiFi.mode(WIFI_AP_STA);

  // Uncomment the next line If you set a custom IP Address
  // WiFi.softAPConfig(APIPAddress, APIPAddress, SubNetIP);

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while (1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
  
  //Print Title
  tft.setTextColor(TFT_RED, TFT_BLACK, true);
  tft.drawCentreString("Wireless AP Server LED Test " , 160, 10, 4);   
  
  //Print Host Name to screen
  tft.setTextColor(TFT_YELLOW, TFT_BLACK, true);
  tft.drawString("WIFI AP Name:", 5, 40, 2); // Left Aligned
  tft.setTextColor(TFT_WHITE, TFT_BLACK, true);
  tft.drawCentreString(ssid, 160, 40, 2); 
 
  //Print IP Address to screen
  tft.setTextColor(TFT_YELLOW, TFT_BLACK, true);
  tft.drawString("IP Address:", 5, 70, 2); // Left Aligned
  tft.setTextColor(TFT_WHITE, TFT_BLACK, true);
  tft.drawCentreString(WiFi.softAPIP().toString(), 160, 70, 2);
  
  //Print Password to screen
  tft.setTextColor(TFT_YELLOW, TFT_BLACK, true);
  tft.drawString("IP Address:", 5, 100, 2); // Left Aligned
  tft.setTextColor(TFT_WHITE, TFT_BLACK, true);
  if (password == "") {
    tft.drawCentreString("<NONE>", 160, 100, 2);
  } else {
    tft.drawCentreString(password, 160, 100, 2);
  }
}

void loop() {
  NetworkClient client = server.accept();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("New Client.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        if (c == '\n') {            // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<font size = \"5\">");
            client.print("Click <a href=\"/RED\">here</a> to turn TOGGLE the RED LED.<br><br>");
            client.print("Click <a href=\"/BLUE\">here</a> to turn TOGGLE the BLUE LED.<br><br>");
            client.print("Click <a href=\"/GREEN\">here</a> to turn TOGGLE the GREEN LED.<br><br>");
            client.print("</font>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /RED", "GET /GREEN", or "GET /BLUE"
        // and toggle the correct color.
        if (currentLine.endsWith("GET /RED")) {
          Serial.println("Red Clicked");
          if (digitalRead(LED_RED) == HIGH) {
              Serial.println("RED on");
              SetLED(LED_RED, true);
            } else {
              Serial.println("RED off");
              SetLED(LED_RED, false);
          }
        }
        if (currentLine.endsWith("GET /BLUE")) {
          Serial.println("BLUE Clicked");
          if (digitalRead(LED_BLUE) == HIGH) {
              Serial.println("BLUE on");
              SetLED(LED_BLUE, true);
            } else {
              Serial.println("BLUE off");
              SetLED(LED_BLUE, false);
          }
        }
        if (currentLine.endsWith("GET /GREEN")) {
          Serial.println("GREEN Clicked");
          if (digitalRead(LED_GREEN) == HIGH) {
              Serial.println("GREEN on");
              SetLED(LED_GREEN, true);
            } else {
              Serial.println("GREEN off");
              SetLED(LED_GREEN, false);
          }
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

