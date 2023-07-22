// I'm using the ARDUINO MEGA 2560 board, a breadboard, a lcd display, 
// a potentioneter for the display and three resistors and few rgb led with common cathode

// Import the Liquid Crystal module to control the LCD Display
// Also import the CVZONE module to receive data from the python code
// Note: You'll find the CVZONE package on this repository inside the "packages" folder called as cvzone
// You'll have to install this package on your ARDUINO IDE to make this code functional and without errors
#include <LiquidCrystal.h>
#include <cvzone.h>

// Prepare a serial data object to receive three values (3) of 1 char long (1), the value will be an ARRAY
// The array will have the 0 index for the R (Red), the index 1 for the G (Green) and the inde 2 for the R (Red) -> [int R, int G, int B]
SerialData serialData(3,1);
int valsRec[3];

// Prepare the PINS on arduino board
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Define Pins for RGB LEDs
#define BLUE 3
#define GREEN 5
#define RED 6

// Start the setup
void setup() {
  // Begin the serial data to get data from python code
  serialData.begin();

  // Begin the LCD display and set columns and rows (in my case it is 16x2)
  lcd.begin(16, 2);

  // Set the cursor on the display and a sample text (i'm italian, put your language)
  lcd.setCursor(0, 0);
  lcd.print("Colore LED RGB:");

  // Setup the PINs of the RGB channels of the LED
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

// Prepare the RGB values and a "String" color to send it later on the display
int redValue = 0;
int greenValue = 0;
int blueValue = 0;
String color = "";

void loop() {
  // Get the input from PYHTON, remember that it will be an array like this [int R, int G, int B]
  serialData.Get(valsRec);

  // Check the first index of the array (RED), if it is is one it will be full red (redValue=255) otherwise it'll be switched off
  if (valsRec[0] == 1) {
    redValue = 255;
  } else {
    redValue = 0;
  }

  // Check the second index of the array (GREEN), if it is is one it will be full green (greenValue=255) otherwise it'll be switched off
  if (valsRec[1] == 1) {
    greenValue = 255;
  } else {
    greenValue = 0;  
  }

  // Check the third index of the array (BLUE), if it is is one it will be full blue (blueValue=255) otherwise it'll be switched off
  if (valsRec[2] == 1) {
    blueValue = 255;
  } else {
    blueValue = 0;
  }

  // Send the relative value to each RGB pin
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);

  // Now check the input received but to name the color
  // I'm italian, so here's the translation in order of rows:
  // "Spento"-> "Switched off"
  // "Rosso" -> "Red"
  // "Verde" -> "Green"
  // "Blu" -> "Blue"
  if (valsRec[0] == 0 && valsRec[1] == 0 && valsRec[2] == 0) { color = ""; color = "Spento"; }
  if (valsRec[0] == 1 && valsRec[1] == 0 && valsRec[2] == 0) { color = ""; color = "Rosso"; }
  if (valsRec[0] == 0 && valsRec[1] == 1 && valsRec[2] == 0) { color = ""; color = "Verde"; }
  if (valsRec[0] == 0 && valsRec[1] == 0 && valsRec[2] == 1) { color = ""; color = "Blu"; }

  // Restart the lcd with 16x2 columns and rows
  lcd.begin(16,2);

  // Set the cursor and text we set up on void setup() before
  lcd.setCursor(0, 0);
  lcd.print("Colore LED RGB:");

  // Now print on the second row of the display the received color
  lcd.setCursor(0, 1);
  lcd.print(color);

  // Set up a short delay of 0.5 secondn(500 milliseconds)
  delay(500);
}
