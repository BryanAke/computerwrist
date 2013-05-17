

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
  
  u8g.drawStr( mx, my, "Ag");
  u8g.drawStr90( mx, my, "Ag");
  u8g.drawStr180( mx, my, "Ag");
  u8g.drawStr270( mx, my, "Ag");
}

void setup(void) {
  u8g.setFont(keen);
}

void change_font_pos(void) {
  static  uint8_t dir = 0;
  static  unsigned long next = 0;

  if ( next < millis() )
  {
    switch(dir) {
      case 0: u8g.setFontPosBottom(); break;
      case 1: u8g.setFontPosBaseline(); break;
      case 2: u8g.setFontPosCenter(); break;
      case 3: u8g.setFontPosTop(); break;
    }
    
    dir++;
    dir &= 3;
    next = millis();
    next += 1000;
  }
}

void loop(void) {
  // change the font position  
  change_font_pos();
  
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(100);
}
