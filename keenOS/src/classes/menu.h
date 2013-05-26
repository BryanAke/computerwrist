#ifndef MENU_H
#define MENU_H

#include "Arduino.h"
#include "U8glib.h"
#include "../display.h"

//fonts
#include "../fonts/keen.c"
#include "../fonts/keentitle.c"

/*

typedef struct Menu {
    char* title;
    char* options[8];
    int usable[8];
    int destination[8];
    struct Menu* back;
    int length;
    
  } Menu;
  */

class Menu {
public:
	Menu();
	~Menu();
	void draw();
	int getLength();
	
private:
	int length;
  char* title;
  char* options[8];
  int usable[8];
  int destination[8];
  

};

void drawMenuItem(int index, char text[], boolean highlight, boolean usable);
void drawHeader(char title[]);

#endif
