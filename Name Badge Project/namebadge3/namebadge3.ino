/*******************************************************************
    Name Badge  
    Adapted by Michael Bapst (https://www.einherjar.org)

    Name Badge is based on "Hello World" for the ESP32 Cheap Yellow Display.
    https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display

    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Twitter: https://twitter.com/witnessmenow
    
    Touch code was taken from Rui Santos & Sara Santos - Random Nerd Tutorials
    Additional code was supplied by Microsoft Copilot, who helped me remember
    a lot of C/C++, which I hadn't touched since the 90's
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

// A library for interfacing with LCD displays
// Can be installed from the library manager (Search for "TFT_eSPI")
//https://github.com/Bodmer/TFT_eSPI
#include <TFT_eSPI.h>       // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();

// Install the "XPT2046_Touchscreen" library by Paul Stoffregen to use the Touchscreen - https://github.com/PaulStoffregen/XPT2046_Touchscreen
// Note: this library doesn't require further configuration
#include <XPT2046_Touchscreen.h>

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

void RNDSeedTouch(int touchX, int touchY, int touchZ) {
  srand(touchX * touchY);
}

void setup() {
  //Initial Random seed value. The random seed will change when you touch the screen
  srand(69); //Nice...
  
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
  touchscreen.setRotation(1);

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
  
  //Checks to see if the screen has been touched, and if it has
  //Seed the random number with X * Y of where the screen has been touched.
  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();
    // Calibrate Touchscreen points with map function to the correct width and height
    x = map(p.x, 200, 3700, 1, 320);
    y = map(p.y, 240, 3800, 1, 240);
    z = p.z;
    
    RNDSeedTouch(x, y, x);

    // Uncomment the next two lines to print the new random seed to the screen.
    //tft.setTextColor(TFT_WHITE, TFT_BLACK, true);
    //tft.drawCentreString(String(x * y), 160, 220, 2);

    delay(100);
  }

  int rndNumber = rand() % 96; //Pick a number between 0 and 96
  //Randomly selected name so it doesn't look like your going down an alphabetical list

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