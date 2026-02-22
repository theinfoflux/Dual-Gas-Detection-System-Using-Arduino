#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD address 0x27, 16 chars, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// MQ Sensors Pins
const int mq2Pin = A0;
const int mq9Pin = A1;

// Buzzer Pin
const int buzzerPin = 8;

// Define Threshold Values (Analog)
const int mq2Threshold = 300; // Adjust according to environment
const int mq9Threshold = 250; // Adjust according to environment

void setup() {
  lcd.init();      // Initialize the LCD
  lcd.backlight(); // Turn on backlight

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Gas Monitoring System Start");
  delay(2000);
  lcd.clear();
}

void loop() {
  int mq2Value = analogRead(mq2Pin);
  int mq9Value = analogRead(mq9Pin);

  // Display Values on LCD
  lcd.setCursor(0, 0);
  lcd.print("MQ2:");
  lcd.print(mq2Value);
  lcd.print("   "); // Clear extra chars

  lcd.setCursor(0, 1);
  lcd.print("MQ9:");
  lcd.print(mq9Value);
  lcd.print("   "); // Clear extra chars

  // Check thresholds
  if (mq2Value > mq2Threshold || mq9Value > mq9Threshold) {
    digitalWrite(buzzerPin, HIGH); // Turn on buzzer
    delay(5000);
  } else {
    digitalWrite(buzzerPin, LOW);  // Turn off buzzer
  }

  delay(500); // Refresh every 0.5 sec
}
