#ifndef DISPLAY_H
#define DISPLAY_H

//other modes for device.
//U8GLIB_DOGXL160_BW u8g(10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_2X_BW u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
U8GLIB_DOGXL160_2X_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9

//defines for mode of display
#define MODE_NONE -1
#define MODE_SLEEP 0
#define MODE_MAIN 1
#define MODE_NEWGAME 2
#define MODE_LOADGAME 3
#define MODE_CONFIG 4
#define MODE_PADDLE 5
#define MODE_QUIT 6

int selected = 0;

#endif
