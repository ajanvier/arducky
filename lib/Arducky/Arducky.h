#ifndef ARDUCKY_h
#define ARDUCKY_h

/**
 * Variables
 **/
#define KEY_MENU          0xED
#define KEY_PAUSE         0xD0
#define KEY_NUMLOCK       0xDB
#define KEY_PRINTSCREEN   0xCE
#define KEY_SCROLLLOCK    0xCF
#define KEY_SPACE         0xB4
#define KEY_BACKSPACE     0xB2

/**
 * Functions
 **/
void processLine(String line);
void processCommand(String command);
void processPayload(char *payload[]);

#endif
