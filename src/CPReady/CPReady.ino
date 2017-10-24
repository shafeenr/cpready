#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define fsrPin 0

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int fsrReading;
int fsrMin = 1023;
int fsrMax = 0;

long fsrPreviousMillis = 0;
long fsrInterval = 250;

long buzzerPreviousMillis = 0;
long buzzerInterval = 1200;

void setup() {
  pinMode(8, OUTPUT);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("PRESS HARD NOW");
  lcd.setCursor(0, 1);
  lcd.print("CALIBRATING...");

  while (millis() < 5000) {
    fsrReading = analogRead(fsrPin);

    if (fsrReading > fsrMax) {
      fsrMax = fsrReading;
    }

    if (fsrReading < fsrMin) {
      fsrMin = fsrReading;
    }
  }

}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - fsrPreviousMillis > fsrInterval) {
    fsrPreviousMillis = currentMillis;
    fsrReading = constrain((map((analogRead(fsrPin)), fsrMin, fsrMax, 0.0, 10.0)), 0.0, 10.0);
    lcd.clear();
    lcd.print("AIM FOR 10");
    lcd.setCursor(0, 1);
    lcd.print("Pressure: ");
    lcd.print(fsrReading);
  }

  if (currentMillis - buzzerPreviousMillis > buzzerInterval) {
    buzzerPreviousMillis = currentMillis;
    tone(12, 220, 600);
  }
}
