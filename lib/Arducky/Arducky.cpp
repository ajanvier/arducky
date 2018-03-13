/**********************************************************/
/* [+] Title:   Arduino Ducky Script Library              */
/* [+] Author:  Baptiste M. (Creased)                     */
/* [+] Website: bmoine.fr                                 */
/* [+] Twitter: @Creased_                                 */
/**********************************************************/

#include <Arduino.h>
#include <Keyboard.h>
#include "Arducky.h"

/**
 * Functions
 **/
void processPayload(char *payload[]) {
    // Process Arducky payload
    String line = "";
    for (int i = 0; payload[i] != NULL; i++) {  // For each line in buffer
        line = payload[i];  // Get line from payload
        processLine(line);  // Process script line by reading command and payload
    }
}

void processLine(String line) {
    /*
     * Process Ducky Script according to the official documentation (see https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Duckyscript).
     *
     * (1) Commands without payload:
     *  - ENTER
     *  - MENU <=> APP
     *  - DOWNARROW <=> DOWN
     *  - LEFTARROW <=> LEFT
     *  - RIGHTARROW <=> RIGHT
     *  - UPARROW <=> UP
     *  - BREAK <=> PAUSE
     *  - CAPSLOCK
     *  - DELETE
     *  - END
     *  - ESC <=> ESCAPE
     *  - HOME
     *  - INSERT
     *  - NUMLOCK
     *  - PAGEUP
     *  - PAGEDOWN
     *  - PRINTSCREEN
     *  - SCROLLLOCK
     *  - SPACE
     *  - TAB
     *  - REPLAY (global commands aren't implemented)
     *
     * (2) Commands with payload:
     *  - DEFAULT_DELAY <=> DEFAULTDELAY (global commands aren't implemented.)
     *  - DELAY (+int)
     *  - STRING (+string)
     *  - GUI <=> WINDOWS (+char)
     *  - SHIFT (+char or key)
     *  - ALT (+char or key)
     *  - CTRL <=> CONTROL (+char or key)
     *  - REM (+string)
     *
     */

    int space = line.indexOf(' ');  // Find the first 'space' that'll be used to separate the payload from the command
    String command = "";
    String payload = "";

    if (space == -1) {  // There is no space -> (1)
        if (
            line == "ENTER" ||
            line == "MENU" || line == "APP" |
            line == "DOWNARROW" || line == "DOWN" ||
            line == "LEFTARROW" || line == "LEFT" ||
            line == "RIGHTARROW" || line == "RIGHT" ||
            line == "UPARROW" || line == "UP" ||
            line == "BREAK" || line == "PAUSE" ||
            line == "CAPSLOCK" ||
            line == "DELETE" ||
            line == "END" ||
            line == "ESC" || line == "ESCAPE" ||
            line == "HOME" ||
            line == "INSERT" ||
            line == "NUMLOCK" ||
            line == "PAGEUP" ||
            line == "PAGEDOWN" ||
            line == "PRINTSCREEN" ||
            line == "SCROLLLOCK" ||
            line == "SPACE" ||
            line == "TAB"
        ) {
            command = line;
        }
    } else {  // Has a space -> (2)
        command = line.substring(0, space);   // Get chars in line from start to space position
        payload = line.substring(space + 1);  // Get chars in line from after space position to EOL

        if (
            command == "DELAY" ||
            command == "STRING" ||
            command == "GUI" || command == "WINDOWS" ||
            command == "SHIFT" ||
            command == "ALT" ||
            command == "CTRL" || command == "CONTROL" ||
            command == "REM"
         ) { } else {
            // Invalid command
            command = "";
            payload = "";
         }
    }

    if (payload == "" && command != "") {                       // Command from (1)
        processCommand(command);                                // Process command
    } else if (command == "DELAY") {                            // Delay before the next commande
        delay((int) payload.toInt());                           // Convert payload to integer and make pause for 'payload' time
    } else if (command == "STRING") {                           // String processing
        Keyboard.print(payload);                                // Type-in the payload
    } else if (command == "REM") {                              // Comment
    } else if (command != "") {                                 // Command from (2)
        String remaining = line;                                // Prepare commands to run
        while (remaining.length() > 0) {                        // For command in remaining commands
            int space = remaining.indexOf(' ');                 // Find the first 'space' that'll be used to separate commands
            if (space != -1) {                                  // If this isn't the last command
                processCommand(remaining.substring(0, space));  // Process command
                remaining = remaining.substring(space + 1);     // Pop command from remaining commands
            } else {                                            // If this is the last command
                processCommand(remaining);                      // Pop command from remaining commands
                remaining = "";                                 // Clear commands (end of loop)
            }
        }
    } else {
        // Invalid command
    }

    Keyboard.releaseAll();
}

void processCommand(String command) {
    /*
     * Process commands by pressing corresponding key
     * (see https://www.arduino.cc/en/Reference/KeyboardModifiers or
     *      http://www.usb.org/developers/hidpage/Hut1_12v2.pdf#page=53)
     */

    if (command.length() == 1) {     // Process key (used for example for WIN L command)
        char c = (char) command[0];  // Convert string (1-char length) to char
        Keyboard.press(c);           // Press the key on keyboard
    } else if (command == "ENTER") {
        Keyboard.press(KEY_RETURN);
    } else if (command == "MENU" || command == "APP") {
        Keyboard.press(KEY_MENU);
    } else if (command == "DOWNARROW" || command == "DOWN") {
        Keyboard.press(KEY_DOWN_ARROW);
    } else if (command == "LEFTARROW" || command == "LEFT") {
        Keyboard.press(KEY_LEFT_ARROW);
    } else if (command == "RIGHTARROW" || command == "RIGHT") {
        Keyboard.press(KEY_RIGHT_ARROW);
    } else if (command == "UPARROW" || command == "UP") {
        Keyboard.press(KEY_UP_ARROW);
    } else if (command == "BREAK" || command == "PAUSE") {
        Keyboard.press(KEY_PAUSE);
    } else if (command == "CAPSLOCK") {
        Keyboard.press(KEY_CAPS_LOCK);
    } else if (command == "DELETE" || command == "DEL") {
        Keyboard.press(KEY_DELETE);
    } else if (command == "END") {
        Keyboard.press(KEY_END);
    } else if (command == "ESC" || command == "ESCAPE") {
        Keyboard.press(KEY_ESC);
    } else if (command == "HOME") {
        Keyboard.press(KEY_HOME);
    } else if (command == "INSERT") {
        Keyboard.press(KEY_INSERT);
    } else if (command == "NUMLOCK") {
        Keyboard.press(KEY_NUMLOCK);
    } else if (command == "PAGEUP") {
        Keyboard.press(KEY_PAGE_UP);
    } else if (command == "PAGEDOWN") {
        Keyboard.press(KEY_PAGE_DOWN);
    } else if (command == "PRINTSCREEN") {
        Keyboard.press(KEY_PRINTSCREEN);
    } else if (command == "SCROLLLOCK") {
        Keyboard.press(KEY_SCROLLLOCK);
    } else if (command == "SPACE") {
        Keyboard.press(KEY_SPACE);
    } else if (command == "BACKSPACE") {
        Keyboard.press(KEY_BACKSPACE);
    } else if (command == "TAB") {
        Keyboard.press(KEY_TAB);
    } else if (command == "GUI" || command == "WINDOWS") {
        Keyboard.press(KEY_LEFT_GUI);
    } else if (command == "SHIFT") {
        Keyboard.press(KEY_RIGHT_SHIFT);
    } else if (command == "ALT") {
        Keyboard.press(KEY_LEFT_ALT);
    } else if (command == "CTRL" || command == "CONTROL") {
        Keyboard.press(KEY_LEFT_CTRL);
    } else if (command == "F1" || command == "FUNCTION1") {
        Keyboard.press(KEY_F1);
    } else if (command == "F2" || command == "FUNCTION2") {
        Keyboard.press(KEY_F2);
    } else if (command == "F3" || command == "FUNCTION3") {
        Keyboard.press(KEY_F3);
    } else if (command == "F4" || command == "FUNCTION4") {
        Keyboard.press(KEY_F4);
    } else if (command == "F5" || command == "FUNCTION5") {
        Keyboard.press(KEY_F5);
    } else if (command == "F6" || command == "FUNCTION6") {
        Keyboard.press(KEY_F6);
    } else if (command == "F7" || command == "FUNCTION7") {
        Keyboard.press(KEY_F7);
    } else if (command == "F8" || command == "FUNCTION8") {
        Keyboard.press(KEY_F8);
    } else if (command == "F9" || command == "FUNCTION9") {
        Keyboard.press(KEY_F9);
    } else if (command == "F10" || command == "FUNCTION10") {
        Keyboard.press(KEY_F10);
    } else if (command == "F11" || command == "FUNCTION11") {
        Keyboard.press(KEY_F11);
    } else if (command == "F12" || command == "FUNCTION12") {
        Keyboard.press(KEY_F12);
    }
}
