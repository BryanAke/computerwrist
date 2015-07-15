//U8glib setup. include header file, and device definition.
#include <U8glib.h>
#include <KeenMenu.h>
#include <PaddleWar.h>

//fonts
#include "fonts/keen.c"
#include "fonts/keentitle.c"


//defines for mode of display
#define MODE_NONE -1
#define MODE_SLEEP 0
#define MODE_MAIN 1
#define MODE_NEWGAME 2
#define MODE_LOADGAME 3
#define MODE_CONFIG 4
#define MODE_PADDLE 5
#define MODE_QUIT 6

//defines for tracking keypresses
#define KEY_NONE 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4

//U8GLIB_DOGXL160_BW u8g(10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_2X_BW u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
U8GLIB_DOGXL160_2X_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9

uint8_t current_mode;

uint8_t uiKeyCodeFirst = KEY_NONE;
uint8_t uiKeyCodeSecond = KEY_NONE;
uint8_t uiKeyCode = KEY_NONE;

uint8_t last_key_code = KEY_NONE;

//set up pins for buttons.
//up/down -- flat buttons in middle of left side
const int up_pin = 5;
const int down_pin = 6;

//left/right -- round buttons on bottom-left corner.
const int left_pin = 7;
const int right_pin = 8;

int redraw_required = 0;

Menu* current_menu;

Menu mainMenu;
Menu newMenu;
Menu loadMenu;
Menu configMenu;

PaddleWar paddleWar;

int selected = 0;

void buildMainMenu() {
  mainMenu.setTitle("MAIN MENU");
  mainMenu.setBack(MODE_NONE);

  mainMenu.addOption("NEW GAME", 1, MODE_NEWGAME);
  mainMenu.addOption("LOAD GAME", 1, MODE_LOADGAME);
  mainMenu.addOption("SAVE GAME", 0, 0);
  mainMenu.addOption("CONFIGURE", 1, MODE_CONFIG);
  mainMenu.addOption("RETURN TO GAME", 0, 0);
  mainMenu.addOption("END GAME", 0, 0);
  mainMenu.addOption("PADDLE WAR", 1, MODE_PADDLE);
  mainMenu.addOption("QUIT", 1, 0);
}

void buildNewMenu() {
  newMenu.setTitle("NEW GAME");
  newMenu.setBack(MODE_MAIN);
  newMenu.setXPos(20);

  newMenu.addOption("BEGIN EASY GAME", 0, -1);
  newMenu.addOption("BEGIN NORMAL GAME", 0, -1);
  newMenu.addOption("BEGIN HARD GAME", 0, -1);
}

void buildLoadMenu() {
  loadMenu.setTitle("LOAD GAME");
  loadMenu.setBack(MODE_MAIN);
  loadMenu.setXPos(20);

  loadMenu.addOption("Empty", 0, -1);
  loadMenu.addOption("Empty", 0, -1);
  loadMenu.addOption("Empty", 0, -1);
  loadMenu.addOption("Empty", 0, -1);
  loadMenu.addOption("Empty", 0, -1);
  loadMenu.addOption("Empty", 0, -1);
}

void buildConfigMenu() {
  configMenu.setTitle("CONFIGURE");
  configMenu.setBack(MODE_MAIN);
  configMenu.setXPos(10);
  configMenu.setSpacePos(2);

  configMenu.addOption("SOUND", 1, -1);
  configMenu.addOption("MUSIC", 0, -1);
  configMenu.addOption("OPTIONS", 1, -1);
  configMenu.addOption("USE KEYBOARD", 1, -1);
  configMenu.addOption("USE JOYSTICK #1", 0, -1);
  configMenu.addOption("USE JOYSTICK #2", 0, -1);
  configMenu.addOption("USE GRAVIS GAMEPAD (OFF)", 0, -1);
  configMenu.addOption("CONTROL: KEYBOARD", 2, -1);
}

void getMenuByMode(int modeID) {
  //Serial.println(modeID);
  switch (modeID) {
    case MODE_MAIN:
      current_menu = &mainMenu;
      break;
    case MODE_LOADGAME:
      current_menu = &loadMenu;
      break;
    case MODE_NEWGAME:
      current_menu = &newMenu;
      break;
    case MODE_CONFIG:
      current_menu = &configMenu;
      break;
    default:
      current_menu = &mainMenu;
      break;
  }
}

void setup(void) {
  Serial.begin(9600);
  u8g.setFont(keen);
  
  buildMainMenu();  
  buildNewMenu();
  buildLoadMenu();
  buildConfigMenu();

  //four buttons
  pinMode(up_pin, INPUT);
  pinMode(down_pin, INPUT);
  pinMode(left_pin, INPUT);
  pinMode(right_pin, INPUT);

  //set font to default font
  u8g.setFont(keen);
  u8g.setColorIndex(2);
  redraw_required = 1;
  
  current_menu = &mainMenu;
  setFonts(keen, keentitle);
  setFontsPW(keen);
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
  
  int nextMode = MODE_NONE;
  
  if (current_mode < 5) {
    //Menu - up/down change selection
    //left/right change menu/mode
    switch ( uiKeyCode ) {
      case KEY_UP:
        if (selected < current_menu->getLength() -1) {
          selected++;
          redraw_required = 1;
        }
        break;
      case KEY_DOWN:
        if ( selected != 0 ) {
          selected--;
          redraw_required = 1;
        }
        break;
      case KEY_LEFT:
        //go back in current menu..
        if (current_mode < MODE_PADDLE) {
          nextMode = current_menu->getBack();
        
        } else {
          nextMode = MODE_MAIN;
        }
        if (nextMode != MODE_NONE) {
          //if we have somewhere to go back to...
          current_mode = nextMode;
          
          getMenuByMode(nextMode);
          redraw_required = 1;
        }
        break;
      case KEY_RIGHT:
        //go forward in the current menu.
        nextMode = current_menu->getDestination(selected);
        
        if (nextMode != MODE_NONE && nextMode < MODE_PADDLE) {
          //next mode is a menu
          current_mode = nextMode;
          getMenuByMode(current_menu->getDestination(selected));
          
          selected = 0;
          redraw_required = 1;
        } else if(nextMode == MODE_PADDLE) {
          current_mode = nextMode;
          redraw_required = 1;
          
        } else if(nextMode == MODE_QUIT) {
          //current_mode = nextMode;
        
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
      if (current_mode < MODE_PADDLE) {
        current_menu->draw(u8g, selected);
      }
      else if (current_mode == MODE_PADDLE) {
        (&paddleWar)->draw(u8g);
      }
      else if (current_mode == MODE_QUIT) {
        
      }
    } while( u8g.nextPage() );
    if (current_mode != MODE_PADDLE) {
        redraw_required = 0;
    }
  }
  
  // rebuild the picture after some delay
  //delay(100);
}
