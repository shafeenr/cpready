#include <LiquidCrystal.h>

int fsrPin = 0;
int fsrReading;
int fsrVoltage;
unsigned long fsrResistance;
float fsrConductance;
float fsrForce;

LiquidCrystal lcd(12,11,5,4,3,2); //LCD connected to these pins

void setup(void)
{
  lcd.begin(16,2); //since we are using 16x2 lcd
}

void loop()
{
  fsrReading = analogRead(fsrPin); //read from A0
  fsrVoltage = map(fsrReading, 0, 1023, 0, 5000); //convert the reading into mV
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("V. Read.:");
  lcd.print(fsrVoltage);
  lcd.setCursor(18,0);
  lcd.print("mV");

  if (fsrVoltage != 0) //if fsrVoltage does not equal to 0mV
  {
    fsrResistance = 5000 - fsrVoltage; //this formula is derived by using voltage divider rule
    fsrResistance *= 10000;
    fsrResistance /= fsrVoltage;
    lcd.setCursor(0,1);
    lcd.print("FSR R:");
    lcd.print(fsrResistance);
    lcd.setCursor(17,1);
    lcd.print("ohm");

    fsrConductance = 1; //conductance is the reciprocal of resistance
    fsrConductance /= fsrResistance; 
    lcd.setCursor(0,2);
    lcd.print("FSR C:");
    lcd.print(fsrConductance,6); //display the value of conductance up to 6 decimal places
    lcd.setCursor(17,2);
    lcd.print("mho");

    //the formula is derived based on the graph of resistance against force
    //break the parabolic curve down into two linear slopes
    if (fsrResistance <= 600)
    {
       fsrForce = (fsrConductance-0.00075)/0.00000032639;
       lcd.setCursor(0,3);
       lcd.print("Force:");
       lcd.print(fsrForce,6); //display the value of force up to 6 decimal places
       lcd.setCursor(19,3);
       lcd.print("g");
    }
    else
    {
      fsrForce = fsrConductance/0.000000642857;
      lcd.setCursor(0,3);
      lcd.print("Force:");
      lcd.print(fsrForce,6); //display the value of force up to 6 decimal places
      lcd.setCursor(19,3);
      lcd.print("g");
    }
  }
  else //if the voltage equals to 0
  {
    lcd.setCursor(0,1);
    lcd.print("No Pressure");
  }
  delay(1000); //delay for 1s
}

