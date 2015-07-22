#include "PaddleWar.h"

#include "Arduino.h"
#include "U8glib.h"

const void *score_fnt;

//defines for tracking keypresses
#define KEY_NONE 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4
    
//playfield area!
#define XMIN 0
#define XMAX 155
#define YMIN 12
#define YMIN_P 20
#define YMAX_P 82
#define YMAX 95

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
  
  ballDirX = 2;
  ballDirY = 2;
}

void PaddleWar::tick(uint8_t key) {
    
  //ball movement
  if (ballY >= YMAX_P) {
    ballDirY = -2;
  }
  else if(ballY <= YMIN_P) {
    ballDirY = 2;
  }
  ballY += ballDirY;
    
  if (ballX >= XMAX) {
    ballDirX = -2;
  }
  else if(ballX <= XMIN) {
    ballDirX = 2;
  }
  ballX += ballDirX;
  
    
  //player paddle movement
  if(key == KEY_RIGHT && cPos <= 148) {
    pPos += 3; 
    if (pPos > 148) {
      pPos = 148;
    }
  }
  else if(key == KEY_LEFT && cPos >= 0) {
    pPos -= 3;
    if (pPos < 0) {
      pPos = 0;
    }
  }
    
  //computer AI
  if (ballX > cPos + 5 && cPos <= 148) {
    cPos += 2;
    if (cPos > 148) {
      cPos = 148;
    }
  }
  else if (ballX < cPos - 5 && cPos >= 0) {
    cPos -= 2;
    if (cPos < 0) {
      cPos = 0;
    }
  }
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

  u8g.drawHLine(3, YMIN, u8g.getWidth() - 6);
  u8g.drawHLine(3, YMAX, u8g.getWidth() - 6);
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
