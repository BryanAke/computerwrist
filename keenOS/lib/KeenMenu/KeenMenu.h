#ifndef MENU_H
#define MENU_H

#include "Arduino.h"
#include "U8glib.h"
#include "u8g.h"

class Menu 
{
  public:
    Menu();
    Menu(char* t);
    ~Menu();
    void draw(U8GLIB_DOGXL160_2X_GR u8g, int selected);

    //adders and setters
    void addOption(char* text, int u, int dest);
    void setTitle(char* title_str);
    void setBack(int back_mode);
    void setXPos(int xpos);

    //getters
    int getLength();
    int getBack();
    int getDestination(int selected);

  private:
    int length;
    char title[20];
    char* options[8];
    int usable[8];
    int destination[8];
    int back;

    int xPos;
};

#endif

void drawMenuItem(U8GLIB_DOGXL160_2X_GR u8g, int xPos, int index, char text[], bool highlight, int usable);
void drawHeader(U8GLIB_DOGXL160_2X_GR u8g, char title[]);

void setFonts(const void* menu_fnt, const void* title_fnt);
