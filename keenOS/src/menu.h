//Main Menu - options to draw on the main menu.

#ifndef MENU_H
#define MENU_H
typedef struct {
    char* title;
    char* options[8];
    int usable[8];
  } Menu;

void drawMenu(Menu menu) ;

/*
 * drawHeader(title)
 * ----
 * will draw a header for a menu or info page on the top of the screen using the title font
 * with a line continuing around it.
 */
void drawHeader(char title[]);

void drawMenuItem(int index, char text[], boolean highlight, boolean usable);

#endif

