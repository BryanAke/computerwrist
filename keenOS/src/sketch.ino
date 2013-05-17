

//U8glib setup. include header file, and device definition.
#include "U8glib.h"

//other modes for device.
//U8GLIB_DOGXL160_BW u8g(10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_2X_BW u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
U8GLIB_DOGXL160_2X_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9


#include "fonts/keen.c"
#include "fonts/keentitle.c"

void draw(void) {
  u8g_uint_t mx, my;
  
  mx = u8g.getWidth();
  mx >>= 1;
  
  my = u8g.getHeight();
  my >>= 1;
  
  u8g.drawHLine(3,5, 7);
  u8g.drawHLine(3,6, 7);

  u8g.drawHLine(68,5, u8g.getWidth() - 71);
  u8g.drawHLine(68,6, u8g.getWidth() - 71);

  u8g.setFont(keentitle);
  u8g.drawStr( 11, 10, "MAIN MENU");
  u8g.setFont(keen);

  u8g.drawStr( 41, 20, "+NEW GAME");
  u8g.drawStr( 41, 28, "+LOAD GAME");
  u8g.drawStr( 41, 36, "-SAVE GAME");
  u8g.drawStr( 41, 44, "+CONFIGURE");
  u8g.drawStr( 41, 52, "-RETURN TO GAME");
  u8g.drawStr( 41, 60, "+END GAME");
  u8g.drawStr( 41, 68, "+PADDLE WAR");
  u8g.drawStr( 41, 76, "+QUIT");


  u8g.drawHLine(3,84, u8g.getWidth() - 6);
  u8g.drawHLine(3,85, u8g.getWidth() - 6);
}

void setup(void) {
  u8g.setFont(keen);
}

void loop(void) {
  
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(100);
}
