#include "SevSeg.h"

// declare const variable
const int milliSecondsPerSecond = 1000;
const int secondsPerMinute = 60;

// declare pin
const int ledStop_PIN = A0;
const int ledStart_PIN = A1;
const int timerAdjust_PIN = A2;
const int pushButtonInterrupt_PIN = 2;

//Instantiate a seven segment controller object
SevSeg sevseg;

//Global Flag
bool reset;
bool initTimer;

//State Machine in Enum
enum STATE {
  SETUP,
  RUNNING,
  FINISH
};
STATE state;

void setup() {
  //Initialize 7 segment LED DISPLAY
  byte numDigits = 4;
  byte digitPins[] = {1, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  // Declare Input, Output and Interrupt PIN
  pinMode(ledStop_PIN, OUTPUT);
  pinMode(ledStart_PIN, OUTPUT);
  //pinMode(timerAdjust_PIN, INPUT);
  pinMode(pushButtonInterrupt_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pushButtonInterrupt_PIN), myISR, FALLING); // trigger when button pressed, but not when released.

  //Declare initialize state
  state = SETUP;
}

void loop() {
  // Declare static variable so they no longer initialize after the first time.
  static unsigned long timer = millis();
  static int minutesCount = 1;
  static int totalSeconds = minutesCount * secondsPerMinute;

  switch (state) {
    case SETUP:
      digitalWrite(ledStart_PIN, LOW);
      digitalWrite(ledStop_PIN, LOW);
      minutesCount = analogRead(timerAdjust_PIN) * (60.0 / 1024); // convert to minutes
      totalSeconds = minutesCount * secondsPerMinute;
      changeDisplayTime(totalSeconds);
      break;
    case RUNNING:
      if (initTimer == true)
      {
        timer = millis();
        initTimer = false;
      }
      if (totalSeconds != 0)
      {
        digitalWrite(ledStart_PIN, HIGH);
      }

      if (millis() - timer >= 1000) {
        timer += 1000;

        if (totalSeconds > 0)
        {
          totalSeconds -= 1;
          changeDisplayTime(totalSeconds);
        }

        if (totalSeconds == 0) {
          changeDisplayTime(totalSeconds);
          //totalSeconds = minutesCount * secondsPerMinute;
          digitalWrite(ledStart_PIN, LOW);
          digitalWrite(ledStop_PIN, HIGH);
          state = FINISH;
        }
      }

      if (reset == true)
      {
        Serial.print("Resetting");
        totalSeconds = minutesCount * secondsPerMinute;
        digitalWrite(ledStop_PIN, LOW);
        reset = false;
      }
      break;
  }
  // Cannot touch this one, must constant update the display.
  sevseg.refreshDisplay();
}

void myISR() {
  if (state == SETUP)
  {
    state = RUNNING;
    initTimer = true;
  }
  else if (state == RUNNING)
  {
    reset = true;
    // note: LOW == false == 0, HIGH == true == 1, so inverting the boolean is the same as switching between LOW and HIGH.
  }
  else if (state == FINISH)
    state = SETUP;
}

// Function to display the time on the 7-segment display
void changeDisplayTime(int seconds) {
  int displayMinutes = seconds / secondsPerMinute;
  int displaySeconds = seconds % secondsPerMinute;

  // Display the time on the 7-segment display
  sevseg.setNumber(displayMinutes * 100 + displaySeconds, 2); // Display minutes
}

/// END ///
