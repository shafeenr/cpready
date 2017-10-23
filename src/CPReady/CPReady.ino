#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LA3 220.00
#define BPM 100
#define Q 60000 / BPM
#define H 2*Q

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int fsrPin = 0;
int fsrReading;
int fsrMin = 1023;
int fsrMax = 0;

void setup() {
  pinMode(8, OUTPUT);

  lcd.begin(16, 2);
  lcd.backlight();

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
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AIM FOR 10");

  fsrReading = analogRead(fsrPin);
  fsrReading = map(fsrReading, fsrMin, fsrMax, 0.0, 10.0);
  fsrReading = constrain(fsrReading, 0.0, 10.0);
  lcd.setCursor(0, 1);
  lcd.print("Pressure: ");
  lcd.print(fsrReading);
  delay(250);

  tone(8, LA3, Q);
  delay(1 + H);
}
