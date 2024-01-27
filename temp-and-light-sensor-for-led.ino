#include <SevSeg.h>

SevSeg sevseg;  // Setting up the cool SevSeg library

const int lm35Pin = A0;      // The spot where we connect the LM35 temp sensor
const int photoresistorPin = A1;  // The place where the photoresistor hangs out

void setup() {
  Serial.begin(9600);  // Start chatting with the computer
  
  // Setting up pins for the 4-digit display
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};

  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
}

void loop() {
  // gets analog vibes from sensors
  int lm35Value = analogRead(lm35Pin);
  int photoresistorValue = analogRead(photoresistorPin);

  // Converting to real-world info
  float temperatureCelsius = (lm35Value * 5.0 / 1024.0) * 100.0;
  int lightIntensity = map(photoresistorValue, 0, 1023, 0, 100);  // Mapping to percentage

  // Shows  the results on the 4-digit display
  int tempDisplay = temperatureCelsius;
  if (tempDisplay < 0) {
    tempDisplay = 0;  // Avoiding negative temp display
  }

  sevseg.setNumber(tempDisplay, 1);  // Displaying the temp
  sevseg.refreshDisplay();            // Refreshing the  display

  delay(5000);  // waits for 5 seconds before the next reading
}