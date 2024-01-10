#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
HardwareSerial mySerial(PA10, PA9);

void setup() {
  lcd.init();
  lcd.backlight();
  // mySerial.begin(115200);
  pinMode(PA1, INPUT);
  pinMode(PA0, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("LCD Begin");
  delay(5000);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Poten_1: ");
  // lcd.setCursor(0,1);
  lcd.print(analogRead(PA1));
  lcd.setCursor(0,2);
  lcd.print("Poten_2: ");
  // lcd.setCursor(0,3);
  lcd.print(analogRead(PA0));
  // mySerial.print(analogRead(PA1));
  // mySerial.print(" ");
  // mySerial.println(analogRead(PA0));
  delay(200);
}
