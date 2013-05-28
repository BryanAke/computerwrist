#include "KeenMenu.h"

#include "Arduino.h"
#include "U8glib.h"

const void *menu_font; 
const void *title_font; 

Menu::Menu(char* t) : title(), options(), usable(), destination() {
  this->length = 0;
  //strcpy(this->title, t);

}

void Menu::setTitle(char* title_str) {
  strncpy(title, title_str, 20);
  //title = "MAIN M";
}

void Menu::addOption(char* text, int u, int dest) {
  if (length < 8) {
    options[length] = text;
    usable[length] = u;
    destination[length] = dest;
    length++;
  }

}

Menu::~Menu() {
  //nada here
}

Menu::Menu() {
  //nada here
  length = 0;
  xPos = 41;
}

void Menu::draw(U8GLIB_DOGXL160_2X_GR u8g, int selected) {
  //set up font for header..
  u8g.setColorIndex(2);
  u8g.setFont((const u8g_fntpgm_uint8_t*)title_font);
  drawHeader(u8g, title);
  //reset the font to the one used for the menu
  u8g.setColorIndex(1);
  u8g.setFont((const u8g_fntpgm_uint8_t*)menu_font);

  //char bffr[10];
  //u8g.drawStr(20, 20, itoa(selected, bffr, 10));
  
  int i;
  int width;
  for (i=0; i< length; i = i+1) {
    drawMenuItem(u8g, xPos, i, options[i], selected == i, usable[i]);
  }
  u8g.setColorIndex(2);

  u8g.drawHLine(3,85, u8g.getWidth() - 6);

  u8g.setColorIndex(1);
  
  u8g.drawStr( 6, 93, "Arrows move      Enter selects");
  if (back > 0) {
    width = (160 - u8g.getStrWidth("ESC to back out")) / 2;
    u8g.drawStr( width, 100, "ESC to back out");
  } else {
    width = (160 - u8g.getStrWidth("ESC to quit")) / 2;
    u8g.drawStr( width, 100, "ESC to quit");
  }
  u8g.setColorIndex(2);
}


void Menu::setBack(int back_mode) {
  back = back_mode;
}

void Menu::setXPos(int xpos) {
  xPos = xpos;
}


int Menu::getLength() {
  return length;
}

int Menu::getBack() {
  return back;
}

int Menu::getDestination(int selected) {
  if (selected < length) {
    return destination[selected];
  }
  return -1;
  
}


/*
 * drawHeader(title)
 * ----
 * will draw a header for a menu or info page on the top of the screen using the title font
 * with a line continuing around it.
 */
void drawHeader(U8GLIB_DOGXL160_2X_GR u8g, char title[]) {
  //draw lines to left of title
  //u8g.drawHLine(3,5, 7);
  u8g.drawHLine(3,6, 7);

  u8g.drawStr( 11, 10, title);

  u8g_uint_t title_width = u8g.getStrWidth(title);

  u8g_uint_t line_x = title_width + 11;
  
  //u8g.drawHLine(line_x ,5, u8g.getWidth() - (line_x + 3) );
  u8g.drawHLine(line_x ,6, u8g.getWidth() - (line_x + 3) );

}

void drawMenuItem(U8GLIB_DOGXL160_2X_GR u8g, int xPos, int index, char text[], bool highlight, int usable) {
  //draw the menu option with the given parameters..
  char* icon = "+";
  if (!usable) {
    icon = "-";
  }

  if (highlight) {
    //up the brightness..
    u8g.setColorIndex(2);
    u8g.drawStr(xPos, 20 + index*8, icon);
    u8g.drawStr(xPos + 5, 20 + index*8, text);
    u8g.setColorIndex(1);      
  } else {
    u8g.drawStr(xPos, 20 + index*8, icon);
    u8g.drawStr(xPos + 5, 20 + index*8, text);
  }
}

void setFonts(const void* menu_fnt, const void* title_fnt) {
  menu_font = menu_fnt;
  title_font = title_fnt;
}
