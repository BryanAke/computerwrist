

//U8glib setup. include header file, and device definition.
#include "U8glib.h"

//other modes for device.
//U8GLIB_DOGXL160_BW u8g(10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_2X_BW u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
U8GLIB_DOGXL160_2X_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9


#include "fonts/keen.c"
#include "fonts/keentitle.c"

void drawHeader(char title[]) {
  //draw lines to left of title
  u8g.drawHLine(3,5, 7);
  u8g.drawHLine(3,6, 7);

  u8g.setFont(keentitle);
  u8g.drawStr( 11, 10, title);

  u8g_uint_t title_width = u8g.getStrWidth(title);

  u8g_uint_t line_x = title_width + 11;
  
  u8g.drawHLine(line_x ,5, u8g.getWidth() - (line_x + 3) );
  u8g.drawHLine(line_x ,6, u8g.getWidth() - (line_x + 3) );

  //reset the font to the one used for the menu
  u8g.setFont(keen);

}

void draw(int pinStatus) {
  //u8g_uint_t mx, my;
  
  //mx = u8g.getWidth();
  //mx >>= 1;
  
  //my = u8g.getHeight();
  //my >>= 1;
  
  drawHeader("MAIN MENU");

  u8g.drawStr( 41, 20, "+NEW GAME");
  u8g.drawStr( 41, 28, "+LOAD GAME");
  u8g.drawStr( 41, 36, "-SAVE GAME");
  u8g.drawStr( 41, 44, "+CONFIGURE");
  u8g.drawStr( 41, 52, "-RETURN TO GAME");
  u8g.drawStr( 41, 60, "-END GAME");
  u8g.drawStr( 41, 68, "+PADDLE WAR");
  u8g.drawStr( 41, 76, "+QUIT");

  if (pinStatus == LOW) {
    u8g.drawStr( 15, 15, "LOW");

  } else {

    u8g.drawStr( 15, 15, "HIGH");

  }

  u8g.drawHLine(3,84, u8g.getWidth() - 6);
  u8g.drawHLine(3,85, u8g.getWidth() - 6);

  
  u8g.drawStr( 6, 93, "Arrows move      Enter selects");
  u8g.drawStr( 51, 100, "ESC to quit");
}
//set up pins for buttons.
//up/down -- flat buttons in middle of left side
const int up_pin = 5;
const int down_pin = 6;

//left/right -- round buttons on bottom-left corner.
const int left_pin = 7;
const int right_pin = 8;

void setup(void) {
  //setup input pins

  //four buttons
  pinMode(up_pin, INPUT);
  pinMode(down_pin, INPUT);
  pinMode(left_pin, INPUT);
  pinMode(right_pin, INPUT);

  //set font to default font
  u8g.setFont(keen);
}

void loop(void) {
  int pinStatus = digitalRead(5);
  // picture loop
  u8g.firstPage();  
  do {
    
    draw(pinStatus);
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  //delay(100);
}
