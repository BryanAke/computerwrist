

//U8glib setup. include header file, and device definition.
#include "U8glib.h"

//other modes for device.
//U8GLIB_DOGXL160_BW u8g(10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_2X_BW u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
U8GLIB_DOGXL160_2X_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9

#include "fonts/keen.c"
#include "fonts/keentitle.c"
#include "menu.h"

//defines for tracking keypresses
#define KEY_NONE 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4

uint8_t uiKeyCodeFirst = KEY_NONE;
uint8_t uiKeyCodeSecond = KEY_NONE;
uint8_t uiKeyCode = KEY_NONE;

uint8_t last_key_code = KEY_NONE;

//set up pins for buttons.
//up/down -- flat buttons in middle of left side
const int up_pin = 6;
const int down_pin = 5;

//left/right -- round buttons on bottom-left corner.
const int left_pin = 7;
const int right_pin = 8;

int redraw_required = 0;



void setup(void) {
  //setup input pins

  //four buttons
  pinMode(up_pin, INPUT);
  pinMode(down_pin, INPUT);
  pinMode(left_pin, INPUT);
  pinMode(right_pin, INPUT);

  //set font to default font
  u8g.setFont(keen);
  u8g.setColorIndex(2);
  redraw_required = 1;
}

void checkInput(void) {
  uiKeyCodeSecond = uiKeyCodeFirst;
  if ( digitalRead(up_pin) == LOW )
    uiKeyCodeFirst = KEY_UP;
  else if ( digitalRead(down_pin) == LOW )
    uiKeyCodeFirst = KEY_DOWN;
  else if ( digitalRead(left_pin) == LOW )
    uiKeyCodeFirst = KEY_LEFT;
  else if ( digitalRead(right_pin) == LOW )
    uiKeyCodeFirst = KEY_RIGHT;
  else 
    uiKeyCodeFirst = KEY_NONE;
  
  if ( uiKeyCodeSecond == uiKeyCodeFirst )
    uiKeyCode = uiKeyCodeFirst;
  else
    uiKeyCode = KEY_NONE;
}

void processInput(void) {
  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;
  
  switch ( uiKeyCode ) {
    case KEY_UP:
      selected++;
      if ( selected >= 8 )
        selected = 0;
      redraw_required = 1;
      break;
    case KEY_DOWN:
      if ( selected == 0 )
        selected = 8;
      selected--;
      redraw_required = 1;
      break;
  }
}


void loop(void) {
  checkInput();
  processInput();
  if (  redraw_required != 0 ) {
    // picture loop
    u8g.firstPage();  
    do {
      
      drawMenu(mainMenu);
    } while( u8g.nextPage() );
    redraw_required = 0;
  }
  
  // rebuild the picture after some delay
  //delay(100);
}
