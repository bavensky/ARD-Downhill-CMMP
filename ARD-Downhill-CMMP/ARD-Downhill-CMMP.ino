#include "LedControlMS.h"
#define NBR_MTX 4
#define line1 A0
#define line2 A1
#define laser1 9
#define laser2 8

LedControl lc = LedControl(12, 11, 10, NBR_MTX);

String scrollString = "   MAKER PARTY 2017    ";
int stringLength = scrollString.length();
char ch0, ch1, ch2, ch3;
int nextCharIndex = 0;

void mainDisplay() {
  lc.displayChar(0, lc.getCharArrayPosition(ch3));
  lc.displayChar(1, lc.getCharArrayPosition(ch2));
  lc.displayChar(2, lc.getCharArrayPosition(ch1));
  lc.displayChar(3, lc.getCharArrayPosition(ch0));

  ch0 = ch1;
  ch1 = ch2;
  ch2 = ch3;
  ch3 = scrollString[nextCharIndex++];
  if (nextCharIndex >= stringLength) nextCharIndex = 0;
  delay(100);
  lc.clearAll();
}
void setup() {

  Serial.begin (9600);
  Serial.println("Setup");
  Serial.println(scrollString);
  Serial.println(stringLength);
  pinMode(laser1, OUTPUT);
  pinMode(laser2, OUTPUT);
  digitalWrite(laser1, HIGH);
  digitalWrite(laser2, HIGH);

  for (int i = 0; i < NBR_MTX; i++) {
    lc.shutdown(i, false);
    /* Set the brightness to a low value */
    lc.setIntensity(i, 1);
    /* and clear the display */
    lc.clearDisplay(i);
  }
  delay(100);
  lc.clearAll();
  ch0 = scrollString[0];
  ch1 = scrollString[1];
  ch2 = scrollString[2];
  ch3 = scrollString[3];
  nextCharIndex = 4;
}

void loop() {
  Serial.print(analogRead(line1));
  Serial.print("    ");
  Serial.println(analogRead(line2));
  
  mainDisplay();
}
