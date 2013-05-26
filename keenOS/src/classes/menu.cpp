#include "menu.h"


Menu::Menu() {
  //pass
  length = 8;
  title = "MAIN MENU";
  options = {
    "NEW GAME", 
    "LOAD GAME", 
    "SAVE GAME", 
    "CONFIGURE", 
    "RETURN TO GAME",
    "END GAME", 
    "PADDLE WAR", 
    "QUIT"
  };
  usable = {true, true, false, true, false, false, true, true};
  destination = {MODE_NEWGAME, MODE_LOADGAME, MODE_NONE, MODE_CONFIG, MODE_NONE, MODE_NONE, MODE_PADDLE, MODE_QUIT};
}

Menu::~Menu() {
  //nada here
  
}

void Menu::draw() {
  
  u8g.setColorIndex(2);
  drawHeader(title);
  u8g.setColorIndex(1);
  int i;
  for (i=0; i< length; i = i+1) {
    drawMenuItem(i, options[i], selected == i, usable[i]);
  }
  u8g.setColorIndex(2);

  u8g.drawHLine(3,85, u8g.getWidth() - 6);

  u8g.setColorIndex(1);
  
  u8g.drawStr( 6, 93, "Arrows move      Enter selects");
  u8g.drawStr( 51, 100, "ESC to quit");
  u8g.setColorIndex(2);
}

int Menu::getLength() {
  return length;
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

