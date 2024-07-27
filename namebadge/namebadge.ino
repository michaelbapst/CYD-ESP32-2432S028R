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

#include "NotoSansBold36.h"
#include "FutharkAOE.h"

// The font names are arrays references, thus must NOT be in quotes ""
#define AA_FONT_LARGE NotoSansBold36
#define AA_FONT_RUNIC FutharkAOE28 

#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library
// A library for interfacing with LCD displays
// Can be installed from the library manager (Search for "TFT_eSPI")
//https://github.com/Bodmer/TFT_eSPI

struct Names {
    char first[25];   //First Name English Spelling
    char second[25];  //Second Name Runic Font Spelling
};


TFT_eSPI tft = TFT_eSPI();
struct Names rtnName;

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
  tft.drawCentreString("Grimnir", 160, 90, 4); //Center Aligned
  tft.unloadFont(); // Remove the font to recover memory used
}

/* 
Odin has 170 different names. More if you count the different spellings of the same name:
ODIN -> ODHINN -> OTHEN -> WODEN -> WOTAN
Here I have selected 95 of them.
*/
struct Names getTwoNames(int number) {
  struct Names names;  
	switch (number) {
        case 0:
			strcpy(names.first, "Alfadhr");   //The first name is Old Norse ---> English spelling 
			strcpy(names.second, "Alfadhr");  //The Second Name is the Rune friendly Spelling (Y=I, C=K, V=W, etc.)
			return names;

        case 1:
			strcpy(names.first, "Aldagautr");
			strcpy(names.second, "Aldagautr");
			return names;

        case 2:
			strcpy(names.first, "Atridhr");
			strcpy(names.second, "atridhr");
			return names;

        case 3:
			strcpy(names.first, "Asagrim");
			strcpy(names.second, "asagrim");
			return names;

        case 4:
			strcpy(names.first, "Audhun");
			strcpy(names.second, "audhun");
			return names;

        case 5:
			strcpy(names.first, "Baleygr Baleyg");
			strcpy(names.second, "baleigr baleig");
			return names;

        case 6:
			strcpy(names.first, "Biflindi");
			strcpy(names.second, "biflindi");
			return names;

        case 7:
			strcpy(names.first, "Blindr");
			strcpy(names.second, "blindr");
			return names;

        case 8:
			strcpy(names.first, "Bolverkr");
			strcpy(names.second, "bolwerkr");
			return names;

        case 9:
			strcpy(names.first, "Draugadrottinn");
			strcpy(names.second, "draugadrottinn");
			return names;

        case 10:
			strcpy(names.first, "Dresvarpr");
			strcpy(names.second, "dreswarpr");
			return names;

        case 11:
			strcpy(names.first, "Drottinn");
			strcpy(names.second, "drottinn");
			return names;

        case 12:
			strcpy(names.first, "Farmagnudhr");
			strcpy(names.second, "farmagnudhr");
			return names;

        case 13:
			strcpy(names.first, "Farmatyr");
			strcpy(names.second, "farmatir");
			return names;

        case 14:
			strcpy(names.first, "Fimbultyr");
			strcpy(names.second, "fimbultir");
			return names;

        case 15:
			strcpy(names.first, "Fimbulthulr");
			strcpy(names.second, "fimbulthulr");
			return names;

        case 16:
			strcpy(names.first, "Fjolnir");
			strcpy(names.second, "fjolnir");
			return names;

        case 17:
			strcpy(names.first, "Fjolsvidhr");
			strcpy(names.second, "fjolswidhr");
			return names;

        case 18:
			strcpy(names.first, "Foldardrottinn");
			strcpy(names.second, "foldardrottinn");
			return names;

        case 19:
			strcpy(names.first, "Forni");
			strcpy(names.second, "forni");
			return names;

        case 20:
			strcpy(names.first, "Gagnradhr");
			strcpy(names.second, "gagnradhr");
			return names;

        case 21:
			strcpy(names.first, "Galdrafodhr");
			strcpy(names.second, "galdrafodhr");
			return names;

        case 22:
			strcpy(names.first, "Fadhir galdrs");
			strcpy(names.second, "fadhir galdrs");
			return names;

        case 23:
			strcpy(names.first, "Ganglari");
			strcpy(names.second, "ganglari");
			return names;

        case 24:
			strcpy(names.first, "Gautr");
			strcpy(names.second, "gautr");
			return names;

        case 25:
			strcpy(names.first, "Geirtyr");
			strcpy(names.second, "geirtir");
			return names;

        case 26:
			strcpy(names.first, "Geirvaldr");
			strcpy(names.second, "geirwaldr");
			return names;

        case 27:
			strcpy(names.first, "Glapsvidhr");
			strcpy(names.second, "glapswidhr");
			return names;

        case 28:
			strcpy(names.first, "Gondlir");
			strcpy(names.second, "gondlir");
			return names;

        case 29:
			strcpy(names.first, "Grimnir");
			strcpy(names.second, "grimnir");
			return names;

        case 30:
			strcpy(names.first, "Gunnblindi");
			strcpy(names.second, "gunnblindi");
			return names;

        case 31:
			strcpy(names.first, "Hagvirkr");
			strcpy(names.second, "hagwirkr");
			return names;

        case 32:
			strcpy(names.first, "Hangadrottinn");
			strcpy(names.second, "hangadrottinn");
			return names;

        case 33:
			strcpy(names.first, "Hangatyr");
			strcpy(names.second, "hangatir");
			return names;

        case 34:
			strcpy(names.first, "Hangi");
			strcpy(names.second, "hangi");
			return names;

        case 35:
			strcpy(names.first, "Haptagudh");
			strcpy(names.second, "haptagudh");
			return names;

        case 36:
			strcpy(names.first, "Harbardhr");
			strcpy(names.second, "harbardhr");
			return names;

        case 37:
			strcpy(names.first, "Harr");
			strcpy(names.second, "harr");
			return names;

        case 38:
			strcpy(names.first, "Havi");
			strcpy(names.second, "hawi");
			return names;

        case 39:
			strcpy(names.first, "Helblindi");
			strcpy(names.second, "helblindi");
			return names;

        case 40:
			strcpy(names.first, "Herjafodhr");
			strcpy(names.second, "herjafodhr");
			return names;

        case 41:
			strcpy(names.first, "Herjan");
			strcpy(names.second, "herjan");
			return names;

        case 42:
			strcpy(names.first, "Herteitr");
			strcpy(names.second, "herteitr");
			return names;

        case 43:
			strcpy(names.first, "Hildolfr");
			strcpy(names.second, "hildolfr");
			return names;

        case 44:
			strcpy(names.first, "Hjaldrgegnir");
			strcpy(names.second, "hjaldrgegnir");
			return names;

        case 45:
			strcpy(names.first, "Hjalmberi");
			strcpy(names.second, "hjalmberi");
			return names;

        case 46:
			strcpy(names.first, "Hnikarr");
			strcpy(names.second, "hnikarr");
			return names;

        case 47:
			strcpy(names.first, "Hoarr");
			strcpy(names.second, "hoarr");
			return names;

        case 48:
			strcpy(names.first, "Hrafnagudh");
			strcpy(names.second, "hrafnagudh");
			return names;

        case 49:
			strcpy(names.first, "Hroptatyr");
			strcpy(names.second, "hroptatir");
			return names;

        case 50:
			strcpy(names.first, "Jafnharr");
			strcpy(names.second, "jafnharr");
			return names;

        case 51:
			strcpy(names.first, "Odhinn");
			strcpy(names.second, "odhinn");
			return names;

        case 52:
			strcpy(names.first, "Ofnir");
			strcpy(names.second, "ofnir");
			return names;

        case 53:
			strcpy(names.first, "Reidhartyr");
			strcpy(names.second, "reidhartir");
			return names;

        case 54:
			strcpy(names.first, "Rognir");
			strcpy(names.second, "rognir");
			return names;

        case 55:
			strcpy(names.first, "Runatyr");
			strcpy(names.second, "runatir");
			return names;

        case 56:
			strcpy(names.first, "Sadhr");
			strcpy(names.second, "sadhr");
			return names;

        case 57:
			strcpy(names.first, "Sanngetall");
			strcpy(names.second, "sanngetall");
			return names;

        case 58:
			strcpy(names.first, "Sidhgrani");
			strcpy(names.second, "sidhgrani");
			return names;

        case 59:
			strcpy(names.first, "Sidhhottr");
			strcpy(names.second, "sidhhottr");
			return names;

        case 60:
			strcpy(names.first, "Sidhskeggr");
			strcpy(names.second, "sidhskeggr");
			return names;

        case 61:
			strcpy(names.first, "Sigfodhr");
			strcpy(names.second, "sigfodhr");
			return names;

        case 62:
			strcpy(names.first, "Sigrunnr");
			strcpy(names.second, "sigrunnr");
			return names;

        case 63:
			strcpy(names.first, "Sigtryggr");
			strcpy(names.second, "sigtriggr");
			return names;

        case 64:
			strcpy(names.first, "Sigtyr");
			strcpy(names.second, "sigtir");
			return names;

        case 65:
			strcpy(names.first, "Sigthror");
			strcpy(names.second, "sigthror");
			return names;

        case 66:
			strcpy(names.first, "Skilfingr");
			strcpy(names.second, "skilfingr");
			return names;

        case 67:
			strcpy(names.first, "Skollvaldr");
			strcpy(names.second, "skollwaldr");
			return names;

        case 68:
			strcpy(names.first, "Svafnir");
			strcpy(names.second, "swafnir");
			return names;

        case 69:
			strcpy(names.first, "Sveigdhir");
			strcpy(names.second, "sweigdhir");
			return names;

        case 70:
			strcpy(names.first, "Svidhrir");
			strcpy(names.second, "swidhrir");
			return names;

        case 71:
			strcpy(names.first, "Svipall");
			strcpy(names.second, "swipall");
			return names;

        case 72:
			strcpy(names.first, "Svolnir");
			strcpy(names.second, "swolnir");
			return names;

        case 73:
			strcpy(names.first, "Tviblindi");
			strcpy(names.second, "twiblindi");
			return names;

        case 74:
			strcpy(names.first, "Thekkr");
			strcpy(names.second, "thekkr");
			return names;

        case 75:
			strcpy(names.first, "Thrasarr");
			strcpy(names.second, "thrasarr");
			return names;

        case 76:
			strcpy(names.first, "Thridhi");
			strcpy(names.second, "thridhi");
			return names;

        case 77:
			strcpy(names.first, "Thriggi");
			strcpy(names.second, "thriggi");
			return names;

        case 78:
			strcpy(names.first, "Throttr");
			strcpy(names.second, "throttr");
			return names;

        case 79:
			strcpy(names.first, "Udhr");
			strcpy(names.second, "udhr");
			return names;

        case 80:
			strcpy(names.first, "Vafudhr");
			strcpy(names.second, "wafudhr");
			return names;

        case 81:
			strcpy(names.first, "Valfodhr");
			strcpy(names.second, "walfodhr");
			return names;

        case 82:
			strcpy(names.first, "Valgautr");
			strcpy(names.second, "walgautr");
			return names;

        case 83:
			strcpy(names.first, "Valkjosandi");
			strcpy(names.second, "walkjosandi");
			return names;

        case 84:
			strcpy(names.first, "Valtamr");
			strcpy(names.second, "waltamr");
			return names;

        case 85:
			strcpy(names.first, "Valtyr");
			strcpy(names.second, "waltir");
			return names;

        case 86:
			strcpy(names.first, "Valthognir");
			strcpy(names.second, "walthognir");
			return names;

        case 87:
			strcpy(names.first, "Vegtam");
			strcpy(names.second, "wegtam");
			return names;

        case 88:
			strcpy(names.first, "Veratyr");
			strcpy(names.second, "weratir");
			return names;

        case 89:
			strcpy(names.first, "Vidhfrager");
			strcpy(names.second, "widhfrager");
			return names;

        case 90:
			strcpy(names.first, "Vidhrir");
			strcpy(names.second, "widhrir");
			return names;

        case 91:
			strcpy(names.first, "Vidhrimnir");
			strcpy(names.second, "widhrimnir");
			return names;

        case 92:
			strcpy(names.first, "Vidhurr");
			strcpy(names.second, "widhurr");
			return names;

        case 93:
			strcpy(names.first, "Vingnir");
			strcpy(names.second, "wingnir");
			return names;

        case 94:
			strcpy(names.first, "Woden");
			strcpy(names.second, "woden");
			return names;

        case 95:
			strcpy(names.first, "Wotan");
			strcpy(names.second, "wotan");
			return names;
			
        default:
			strcpy(names.first, "Ole One Eye");
			strcpy(names.second, "ole one eie");
			return names;
	}
}

void loop() {
  // put your main code here, to run repeatedly:

  int rndNumber = rand() % 96; //Pick a number between 0 and 95
  //Randomly selected name so it doesn't look like your going down an alphabetical list
  rtnName = getTwoNames(rndNumber); 
  //Print Name in Roman Characters
  tft.loadFont(AA_FONT_LARGE);    // Must load the font first
  tft.setTextColor(TFT_WHITE, TFT_BLACK, true);
  tft.drawCentreString("                                  ", 160, 90, 4); //Write new text
  tft.drawCentreString(rtnName.first, 160, 90, 4);                        //Write new text
  tft.unloadFont(); // Remove the font to recover memory used
  
  //Print Name is Runic Characters
  tft.loadFont(AA_FONT_RUNIC);    // Must load the font first
  tft.setTextColor(TFT_RED, TFT_BLACK, true);
  tft.drawCentreString("                                  ", 160, 140, 4); //Clear old text
  tft.drawCentreString(rtnName.second, 160, 140, 4);                       //Write new text
  tft.unloadFont(); // Remove the font to recover memory used
  delay(2000); //wait 2 seconds and start over
}