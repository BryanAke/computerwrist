#include "PaddleWar.h"

#include "Arduino.h"
#include "U8glib.h"

const void *score_fnt;

#define paddlewar_logo_width 37
#define paddlewar_logo_height 8
static unsigned char paddlewar_logo_bits[] U8G_PROGMEM = {
  0x0F, 0x00, 0x40, 0x04, 0x10, 0x11, 0x00, 0x40, 0x04, 0x10, 0x11, 0x00, 
  0x40, 0x04, 0x10, 0x2F, 0x33, 0x59, 0x24, 0x13, 0x51, 0x55, 0x49, 0x54, 
  0x15, 0x71, 0x55, 0x59, 0x75, 0x13, 0x51, 0x55, 0xC9, 0x56, 0x05, 0x51, 
  0x33, 0x5B, 0x54, 0x15, };

PaddleWar::~PaddleWar() {
  //nada here
}

PaddleWar::PaddleWar() {
  pPos = 40;
  cPos = 40;
  ballX = 40;
  ballY = 40;
  
  ballDirX = 1;
  ballDirY = 1;
}

void PaddleWar::draw(U8GLIB_DOGXL160_2X_GR u8g) {
  //draw the header
  drawHeader(u8g);
  
  //actual game
  drawBall(u8g);
  drawPaddles(u8g);
}

void PaddleWar::drawHeader(U8GLIB_DOGXL160_2X_GR u8g) {
  //set up font for header
  u8g.setColorIndex(2);
  
  u8g.drawXBMP(62, 1, paddlewar_logo_width, paddlewar_logo_height, paddlewar_logo_bits);
  
  u8g.setFont((const u8g_fntpgm_uint8_t*)score_fnt);
  u8g.drawStr( 8, 8, "KEEN:0");
  u8g.drawStr( 110, 8, "COMP:0");

  u8g.drawHLine(3,11, u8g.getWidth() - 6);
  u8g.drawHLine(3,100, u8g.getWidth() - 6);
}

void PaddleWar::drawBall(U8GLIB_DOGXL160_2X_GR u8g) {
  //set up font for header..
  u8g.setColorIndex(2);
  u8g.drawBox(ballX,ballY, 5, 5);
  u8g.setColorIndex(1);
  u8g.drawPixel(ballX, ballY);
  u8g.drawPixel(ballX + 4, ballY);
  u8g.drawPixel(ballX, ballY + 4);
  u8g.drawPixel(ballX + 4, ballY + 4);
  
  /*
  ballX += ballDirX;
  
  if(ballX > 60) {
    ballDirX = -1;
  }
  
  if(ballX < 30) {
    ballDirX = 1;
  }
  */
}

void PaddleWar::drawPaddles(U8GLIB_DOGXL160_2X_GR u8g) {
  
  //draw computer paddle
  u8g.setColorIndex(2);
  u8g.drawBox(cPos, 17, 12, 3);
  
  u8g.setColorIndex(1);
  u8g.drawPixel(cPos, 17);
  u8g.drawPixel(cPos + 11, 17);
  u8g.drawPixel(cPos, 19);
  u8g.drawPixel(cPos + 11, 19);
  
  
  //draw player paddle
  u8g.setColorIndex(2);
  u8g.drawBox(pPos, 87, 12, 3);
  
  u8g.setColorIndex(1);
  u8g.drawPixel(pPos, 87);
  u8g.drawPixel(pPos + 11, 87);
  u8g.drawPixel(pPos, 89);
  u8g.drawPixel(pPos + 11, 89);
  
}

void setFontsPW(const void* menu_fnt) {
  score_fnt = menu_fnt;
}
