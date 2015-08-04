#ifndef PADDLE_H
#define PADDLE_H

#include "Arduino.h"
#include <SPI.h>
#include "U8glib.h"

class PaddleWar 
{
  public:
    PaddleWar();
    ~PaddleWar();
    
    //Drawing methods:
    void draw(U8GLIB_DOGXL160_2X_GR u8g);
    void drawHeader(U8GLIB_DOGXL160_2X_GR u8g);
    void drawBall(U8GLIB_DOGXL160_2X_GR u8g);
    void drawPaddles(U8GLIB_DOGXL160_2X_GR u8g);
    
    //tick update
    void tick(uint8_t key);
    
    //getters and setters

  private:
    int pScore;
    int cScore;

    int pPos;
    int cPos;
    
    
    int ballX;
    int ballY;
    
    int ballDirX;
    int ballDirY;
};

void setFontsPW(const void* menu_fnt);
#endif/stop

