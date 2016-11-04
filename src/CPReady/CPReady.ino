int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrMin = 1023;        // minimum sensor value
int fsrMax = 0;           // maximum sensor value
 #include <LiquidCrystal.h>  //call the LCD library
 LiquidCrystal lcd(12,11,5,4,3,2);   //LCD connected to these pins

// NB: ALL NOTES DEFINED WITH STANDARD ENGLISH NAMES, EXCEPT FROM "A" 
//THAT IS CALLED WITH THE ITALIAN NAME "LA" BECAUSE A0,A1...ARE THE ANALOG PINS ON ARDUINO.
// (Ab IS CALLED Ab AND NOT LAb)
#define LA3 220.00
// DURATION OF THE NOTES 
#define BPM 120    //  you can change this value changing all the others
#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4 
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4

void setup(void) {     
pinMode(8, OUTPUT);   
pinMode(9, OUTPUT);       
digitalWrite(9,LOW);
lcd.begin(16, 2);   //Turn on the LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Coded by Shafeen");
    lcd.setCursor(0,1);
    // calibrate during the first five seconds DON'T FORGET TO PUSH THE FSR HARD!!!
  while (millis() < 5000) {
    fsrReading = analogRead(fsrPin);

    // record the maximum sensor value
    if (fsrReading > fsrMax) {
      fsrMax = fsrReading;
    }

    // record the minimum sensor value
    if (fsrReading < fsrMin) {
      fsrMin = fsrReading;
    }
  }
}

// the loop routine runs over and over again forever:
void loop(void) {
fsrReading = analogRead(fsrPin);    
  fsrReading = map(fsrReading, fsrMin, fsrMax, 0.0, 10.0);   //FSR pressure mapped on a scale of 1-10.  
  // Scale could be adjusted for more accurate force output when calibration is more controlled.
  fsrReading = constrain(fsrReading, 0.0, 10.0);   // no readings above or below the 0-10 scale
  
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Aim for 10");
  
  lcd.setCursor(0,1); //output will be on lower line of LCD
 
  lcd.print("Pressure = ");
  lcd.print(fsrReading);  // LCD will display the pressure reading
  delay(250);  // Time between reading updates. 
  // LCD has trouble at really fast intervals. Use serial for that.  
  
  //tone(pin, note, duration)
    tone(8,LA3,Q); 
    delay(1+H); //delay duration should always be 1 ms more than the note in order to separate them.
}
