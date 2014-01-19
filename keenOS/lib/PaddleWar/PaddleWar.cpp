#include "PaddleWar.h"

#include "Arduino.h"
#include "U8glib.h"

const void *pw_font; 

PaddleWar::~PaddleWar() {
  //nada here
}

PaddleWar::PaddleWar() {
  pPos = 40;
}

void PaddleWar::draw(U8GLIB_DOGXL160_2X_GR u8g) {
  //set up font for header..
  u8g.setColorIndex(2);
  u8g.setFont((const u8g_fntpgm_uint8_t*)pw_font);
  u8g.drawHLine(10,10, 30);
  
}


void PaddleWar::drawBall(U8GLIB_DOGXL160_2X_GR u8g) {
  //set up font for header..
  u8g.setColorIndex(2);
  u8g.setFont((const u8g_fntpgm_uint8_t*)pw_font);
  u8g.drawHLine(10,10, 30);
  
}

void PaddleWar::drawPaddles(U8GLIB_DOGXL160_2X_GR u8g) {
  //set up font for header..
  u8g.setColorIndex(2);
  u8g.setFont((const u8g_fntpgm_uint8_t*)pw_font);
  u8g.drawHLine(10,10, 30);
  
}
