#ifndef PADDLE_H
#define PADDLE_H

#include "Arduino.h"
#include "U8glib.h"
#include "u8g.h"

class PaddleWar 
{
  public:
    PaddleWar();
    ~PaddleWar();
    
    //Drawing methods:
    void draw(U8GLIB_DOGXL160_2X_GR u8g);
    void drawBall(U8GLIB_DOGXL160_2X_GR u8g);
    void drawPaddles(U8GLIB_DOGXL160_2X_GR u8g);
    
    //getters and setters

  private:
    int pScore;
    int cScore;

    int pPos;
    int cPos;
    
    
    int ballX;
    int ballY;
};

#endif/stop

