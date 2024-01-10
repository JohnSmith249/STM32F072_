/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Wire.begin();
  // Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      lcd.setCursor(0, 1);
      lcd.print("I2C device founded");
      if (address < 16) {
        lcd.setCursor(0, 2);
        lcd.print("at 0x0");
      }
      lcd.setCursor(0, 2);
      lcd.print("at 0x");
      lcd.print(address, HEX);
      nDevices++;
    } else if (error == 4) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Unknow error");
      if (address < 16) {
        lcd.setCursor(0, 2);
        lcd.print("at 0x0");
      }
      lcd.setCursor(0, 2);
      lcd.print("at 0x");
      lcd.print(address, HEX);
    }
  }
  if (nDevices == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("No I2C devices found");
  } else {
    // lcd.clear();
    lcd.setCursor(0, 3);
    lcd.print("done");
  }
  delay(5000);
}