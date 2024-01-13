#define encoder0PinA PB8
#define encoder0PinB PB9
#define SignPin PB5
#include <Wire.h>
#include <TM1650.h>
#include <TM16xxDisplay.h>

volatile int encoder0Pos = 0;
volatile int encoder0Pos_old = 0;

long n;
int pos;
byte dp;
byte digit;
unsigned int segments;
byte intensity;

// char display_data[5];
String value;
String Sign = "-";
boolean but_status = 1;

HardwareSerial mySerial(PA10, PA9);
TM1650 display1(PB7,
                PB6,
                4,
                true,
                7);

TM1650 display2(PB4,
                PB6,
                4,
                true,
                7);

TM16xxDisplay displayA(&display1, 4);
TM16xxDisplay displayB(&display2, 4);

void display_data(void){
  if (Sign=="0"){
    displayA.setDisplayToSignedDecNumber(encoder0Pos, B0000, false);
  } else if (Sign =="-") {
    displayA.setDisplayToSignedDecNumber(encoder0Pos*(-1), B0000, false);
  }
}

void setup() {

  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  pinMode(SignPin, INPUT);

  attachInterrupt(encoder0PinA, doEncoderA, CHANGE);
  attachInterrupt(encoder0PinB, doEncoderB, CHANGE);
  attachInterrupt(SignPin, resetStatus, FALLING);
  // Wire.begin();
  mySerial.begin(115200);
  // d.init();
  // d.displayOff();
  // d.displayString("____");
  // d.setBrightness(TM1650_MIN_BRIGHT);
  // d.displayOn();
  delay(1000);
}

void loop() {
  if (but_status == 0) {
    reSign();
    display_data();
  }
  if (encoder0Pos != encoder0Pos_old) {
    // d.clear();
    if (encoder0Pos > 999) {
      encoder0Pos = 999;
    } else if (encoder0Pos < 0) {
      encoder0Pos = 0;
    } else {
    }
    display_data();
    encoder0Pos_old = encoder0Pos;
    // d.displayOn();
    // d.setBrightness(TM1650_MAX_BRIGHT);
  }
}

void doEncoderA() {
  if (digitalRead(encoder0PinA) == HIGH) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;  // CW
    } else {
      encoder0Pos = encoder0Pos - 1;  // CCW
    }
  }

  else {
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
  } else {
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;  // CW
    } else {
      encoder0Pos = encoder0Pos - 1;  // CCW
    }
  }
}

void resetStatus() {
  mySerial.println("Trigger");
  if (but_status == 1) {
    but_status = 0;
  }
}

void reSign() {
  delay(90);
  if (digitalRead(SignPin) != but_status && digitalRead(SignPin) == 1) {
    if (Sign == "-") {
      Sign = "0";
    } else {
      Sign = "-";
    }
    but_status = 1;
  }
}
