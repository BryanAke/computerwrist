//U8glib setup. include header file, and device definition.
#include "U8glib.h"

//other modes for device.
//U8GLIB_DOGXL160_BW u8g(10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_2X_BW u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
U8GLIB_DOGXL160_2X_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9

#include "fonts/keen.c"
#include "fonts/keentitle.c"

//defines for tracking keypresses
#define KEY_NONE 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4

//defines for mode of display
#define MODE_NONE -1
#define MODE_SLEEP 0
#define MODE_MAIN 1
#define MODE_NEWGAME 2
#define MODE_LOADGAME 3
#define MODE_CONFIG 4
#define MODE_PADDLE 5
#define MODE_QUIT 6

uint8_t current_mode;

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


int selected = 0;

typedef struct Menu {
    char* title;
    char* options[8];
    int usable[8];
    int destination[8];
    struct Menu* back;
    int length;
    
  } Menu;
  
struct Menu current_menu;

struct Menu mainMenu = {
  "MAIN MENU",
  {
    "NEW GAME", 
    "LOAD GAME", 
    "SAVE GAME", 
    "CONFIGURE", 
    "RETURN TO GAME",
    "END GAME", 
    "PADDLE WAR", 
    "QUIT"
  },
  {true, true, false, true, false, false, true, true},
  {MODE_NEWGAME, MODE_LOADGAME, MODE_NONE, MODE_CONFIG, MODE_NONE, MODE_NONE, MODE_PADDLE, MODE_QUIT},
  NULL,
  8
};

void drawMenu(struct Menu menu) {
  
  u8g.setColorIndex(2);
  drawHeader(menu.title);
  u8g.setColorIndex(1);
  int i;
  for (i=0; i< menu.length; i = i+1) {
    drawMenuItem(i, menu.options[i], selected == i, menu.usable[i]);
  }
  u8g.setColorIndex(2);

  u8g.drawHLine(3,85, u8g.getWidth() - 6);

  u8g.setColorIndex(1);
  
  u8g.drawStr( 6, 93, "Arrows move      Enter selects");
  u8g.drawStr( 51, 100, "ESC to quit");
  u8g.setColorIndex(2);
}

/*
 * drawHeader(title)
 * ----
 * will draw a header for a menu or info page on the top of the screen using the title font
 * with a line continuing around it.
 */
void drawHeader(char title[]) {
  //draw lines to left of title
  //u8g.drawHLine(3,5, 7);
  u8g.drawHLine(3,6, 7);

  u8g.setFont(keentitle);
  u8g.drawStr( 11, 10, title);

  u8g_uint_t title_width = u8g.getStrWidth(title);

  u8g_uint_t line_x = title_width + 11;
  
  //u8g.drawHLine(line_x ,5, u8g.getWidth() - (line_x + 3) );
  u8g.drawHLine(line_x ,6, u8g.getWidth() - (line_x + 3) );

  //reset the font to the one used for the menu
  u8g.setFont(keen);

}

void drawMenuItem(int index, char text[], boolean highlight, boolean usable) {
  //draw the menu option with the given parameters..
  char* icon = "+";
  if (!usable) {
    icon = "-";
  }

  if (highlight) {
    //up the brightness..
    u8g.setColorIndex(2);
    u8g.drawStr(41, 20 + index*8, icon);
    u8g.drawStr(46, 20 + index*8, text);
    u8g.setColorIndex(1);      
  } else {
    u8g.drawStr(41, 20 + index*8, icon);
    u8g.drawStr(46, 20 + index*8, text);
  }
}

void linkMenus(void) {
  current_menu = mainMenu;
}

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
  linkMenus();
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
  
  if (current_mode < 5) {
    //Menu - up/down change selection
    //left/right change menu/mode
    switch ( uiKeyCode ) {
      case KEY_UP:
        selected++;
        if ( selected >= current_menu.length )
          selected = 0;
        redraw_required = 1;
        break;
      case KEY_DOWN:
        if ( selected == 0 )
          selected = current_menu.length;
        selected--;
        redraw_required = 1;
        break;
      case KEY_LEFT:
        //go back in current menu..
        if (current_menu.back != NULL) {
          //if we have somewhere to go back to...
          current_menu = *current_menu.back;
        
        }
        break;
    }
  
  
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
