
#include "Arduino.h"
#include "U8glib.h"
#include "menu.h"

int selected = 0;

Menu mainMenu = {
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
  {true, true, false, true, false, false, true, true}
};

void drawMenu(Menu menu) {
  //u8g_uint_t mx, my;
  
  //mx = u8g.getWidth();
  //mx >>= 1;
  
  //my = u8g.getHeight();
  //my >>= 1;
  
  u8g.setColorIndex(2);
  drawHeader(menu.title);
  u8g.setColorIndex(1);
  int i;
  for (i=0; i< 8; i = i+1) {
    drawMenuItem(i, menu.options[i], selected == i, menu.usable[i]);
  }
  u8g.setColorIndex(2);

  //u8g.drawHLine(3,84, u8g.getWidth() - 6);
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

