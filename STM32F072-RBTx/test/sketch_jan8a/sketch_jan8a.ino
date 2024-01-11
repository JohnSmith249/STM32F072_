#define encoder0PinA PA8
#define encoder0PinB PA9

#include <Wire.h>
#include <TM1650.h>

volatile int encoder0Pos = 0;
volatile int encoder0Pos_old = 0;
char display_data[5];
String value;
String Sign = "-";
HardwareSerial mySerial(PA10, PA9);
TM1650 d;

void Filter_data() {
  int first_digit = encoder0Pos / 100;
  int second_digit = (encoder0Pos - (100 * first_digit)) / 10;
  int third_digit = encoder0Pos - (100 * first_digit) - (10 * second_digit);
  value = Sign + String(first_digit) + String(second_digit) + String(third_digit);
  value.toCharArray(display_data, 5);
}

void setup() {
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  attachInterrupt(encoder0PinA, doEncoderA, CHANGE);
  attachInterrupt(encoder0PinB, doEncoderB, CHANGE);
  Wire.begin();
  mySerial.begin(115200);  // Back up Serial Port for debug

  d.init();
  d.displayOff();
  delay(200);
  d.displayString("____");
  d.setBrightness(TM1650_MIN_BRIGHT);
  d.displayOn();
  delay(200);
}

void loop() {
  if (encoder0Pos != encoder0Pos_old) {
    d.clear();
    if (encoder0Pos > 999) {
      value = Sign + "000";
      value.toCharArray(display_data, 5);
      d.displayString(display_data);
      mySerial.println(display_data);
    } else {
      Filter_data();
      d.displayString((display_data));
      mySerial.println(display_data);
    }
    encoder0Pos_old = encoder0Pos;
    d.displayOn();
    d.setBrightness(TM1650_MAX_BRIGHT);
  }
}

void doEncoderA() {
  if (digitalRead(encoder0PinA) == HIGH) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;  // CW
    } else {
      encoder0Pos = encoder0Pos - 1;  // CCW
    }
  } else {
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;  // CW
    } else {
      encoder0Pos = encoder0Pos - 1;  // CCW
    }
  }
}

void doEncoderB() {
  if (digitalRead(encoder0PinB) == HIGH) {
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;  // CW
    } else {
      encoder0Pos = encoder0Pos - 1;  // CCW
    }
  }

  else {
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;  // CW
    } else {
      encoder0Pos = encoder0Pos - 1;  // CCW
    }
  }
}

