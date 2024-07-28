/*******************************************************************
    Name Badge  
    Adapted by Michael Bapst (https://www.einherjar.org)

    Name Badge is based on "Hello World" for the ESP32 Cheap Yellow Display.
    https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display

    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/

// Make sure to copy the UserSetup.h file into the library as
// per the Github Instructions. The pins are defined in there.
#include <string>
#include "NotoSansBold36.h"
#include "FutharkAOE.h"
#include "namelist.h"

// The font names are arrays references, thus must NOT be in quotes ""
#define AA_FONT_LARGE NotoSansBold36
#define AA_FONT_RUNIC FutharkAOE28 
#define Name_List cNameList

#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library
// A library for interfacing with LCD displays
// Can be installed from the library manager (Search for "TFT_eSPI")
//https://github.com/Bodmer/TFT_eSPI


TFT_eSPI tft = TFT_eSPI();

void setup() {
  //Add your own Random seed here. CYD Doesn't have a RTC so using Timer doesn't help
  //I tried using X,Y from touch screen or Light value from Light Dependent Resistor for a seed
  //But it made the code way more complex than it needed to be. Pseudo Random is Pseudo Random.  
  srand(369);

  // Start the tft display and set it to black
  tft.init();
  tft.setRotation(1); //This is the display in landscape
  
  // Clear the screen before writing to it
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK, true);
  tft.drawString("HELLO, MY NAME IS...", 5, 10, 4); // Left Aligned
  tft.drawCentreString("(ODIN)", 160, 200, 2); 
  tft.loadFont(AA_FONT_LARGE); // Must load the font first
  tft.setTextColor(TFT_WHITE, TFT_BLACK, true);
  tft.drawCentreString("Michael", 160, 90, 4); //Center Aligned
  tft.unloadFont(); // Remove the font to recover memory used
  delay(3000);
}


void loop() {
  // put your main code here, to run repeatedly:

  int rndNumber = rand() % 96; //Pick a number between 0 and 95
  //Randomly selected name so it doesn't look like your going down an alphabetical list
  //rtnName = getTwoNames(rndNumber); 
  //Print Name in Roman Characters
  tft.loadFont(AA_FONT_LARGE);    // Must load the font first]
  //Blank out old text instead of clearing the screen. This prevents screen flashing 
  tft.setTextColor(TFT_WHITE, TFT_BLACK, true);
  tft.drawCentreString("                                  ", 160, 90, 4);
  tft.drawCentreString(Name_List[rndNumber][0], 160, 90, 4);              //Write new text
  tft.unloadFont(); // Remove the font to recover memory used
  
  //Print Name is Runic Characters
  tft.loadFont(AA_FONT_RUNIC);    // Must load the font first
  tft.setTextColor(TFT_RED, TFT_BLACK, true);
  tft.drawCentreString("                                  ", 160, 140, 4); //Clear old text
  tft.drawCentreString(Name_List[rndNumber][1], 160, 140, 4);              //Write new text
  tft.unloadFont(); // Remove the font to recover memory used
  delay(2000); //wait 2 seconds and start over
}