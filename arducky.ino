/**********************************************************/
/* [+] Title:   Arduino Ducky Script Interpreter          */
/* [+] Author:  Baptiste M. (Creased)                     */
/* [+] Website: bmoine.fr                                 */
/* [+] Twitter: @Creased_                                 */
/**********************************************************/

/**
 * Libraries
 **/
// SD card read/write
#include <SPI.h>
#include <SD.h>

// Keyboard Message
#include <Keyboard.h>
#include <Arducky.h>

File myFile;                               // File data buffer
char *fileName = (char*)"script.txt";      // File containing payload placed on SD Card
const int LED = 17;                        // RX LED pin

/**
 * Functions
 **/
void setup() {
    // Initialize digital pin LED_BUILTIN as an output
    pinMode(LED, OUTPUT);

    // Initialize SD Card
    if (!SD.begin(4)) {
        for (int i=0; i <= 25; i++) {
            digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(100);                // wait for a second
            digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
            delay(100);                // wait for a second
        }
        return;
    }

    if (SD.exists(fileName)) {
        // Open the file for reading (fill myFile with char buffer)
        myFile = SD.open(fileName, FILE_READ);

        // Check if the file has successfully been opened and continue
        if (myFile) {
            // Initialize control over keyboard
            Keyboard.begin();

            // Process lines from file with LF EOL (0x0a), not CR+LF (0x0a+0x0d)
            String line = "";
            while (myFile.available()) {  // For each char in buffer
                // Read char from buffer
                char c = myFile.read();

                // Process char
                if ((int) c == 0x0a){         // Line ending (LF) reached
                    processLine(line);        // Process script line by reading command and payload
                    line = "";                // Clean the line to process next
                } else if((int) c != 0x0d) {  // If char isn't a carriage return (CR)
                    line += c;                // Put char into line
                }
            }

            // Close the file
            myFile.close();
        } else {  // File can't be loaded
            for (int i=0; i <= 25; i++) {
                digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
                delay(250);                // wait for a second
                digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
                delay(250);                // wait for a second
            }
        }

        // End control over keyboard
        Keyboard.end();
    } else {
        for (int i=0; i <= 25; i++) {
            digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(100);                // wait for a second
            digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
            delay(100);                // wait for a second
        }
    }
}

void loop() {
    // nothing happens after setup
}
