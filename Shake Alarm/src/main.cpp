#include <Arduino.h>

const int shakeSensorPin = 53; // shake sensor
const int ldrPin = A1;        //  LDR
const int basicLedPin = 2;    // basic LED
const int blueLed1Pin = 3;    // first blue LED
const int blueLed2Pin = 5;    // second blue LED
const int yellowLedPin = 4;   // yellow LED
const int resetButtonPin = 51; // reset button

// Thresholds
const int ldrThreshold = 800; 

bool alarmTriggered = false;

void setup() {
  pinMode(shakeSensorPin, INPUT);
  pinMode(basicLedPin, OUTPUT);
  pinMode(blueLed1Pin, OUTPUT);
  pinMode(blueLed2Pin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(resetButtonPin, INPUT_PULLUP); 

  Serial.begin(9600);
}

void loop() {
  // Check if the reset button is pressed
  if (digitalRead(resetButtonPin) == LOW) {
    // Reset the alarm
    alarmTriggered = false;
    digitalWrite(basicLedPin, LOW);
    digitalWrite(blueLed1Pin, LOW);
    digitalWrite(blueLed2Pin, LOW);
    digitalWrite(yellowLedPin, LOW);
    return;
  }

  // Read the shake sensor
  int shakeValue = digitalRead(shakeSensorPin);
  if (shakeValue == HIGH) {
    digitalWrite(basicLedPin, HIGH);

    // Read the LDR value
    int ldrValue = analogRead(ldrPin);
    Serial.print("LDR Value: ");
    Serial.println(ldrValue);

    // Check if the LDR value exceeds the threshold
    if (ldrValue > ldrThreshold) {
      alarmTriggered = true;
    }
  }

  // If the alarm is triggered, make the LEDs blink(ALARM)
  if (alarmTriggered) {
    digitalWrite(blueLed1Pin, HIGH);
    digitalWrite(blueLed2Pin, HIGH);
    digitalWrite(yellowLedPin, HIGH);
    delay(500); 
    digitalWrite(blueLed1Pin, LOW);
    digitalWrite(blueLed2Pin, LOW);
    digitalWrite(yellowLedPin, LOW);
    delay(500);
  }

  // Small delay to debounce the shake sensor
  delay(100);
}
