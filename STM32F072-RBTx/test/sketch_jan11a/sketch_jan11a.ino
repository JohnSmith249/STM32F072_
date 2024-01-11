#include <Wire.h>
#include <TM1650.h>
#include <STM32FreeRTOS.h>
#include <Wire.h>
#include <FlashStorage_STM32.h>

#define encoder0PinA PB8
#define encoder0PinB PB9
#define SignPin PB5

volatile int encoder0Pos = 0;
volatile int encoder0Pos_old = 0;
char display_data[5];
String value;
String Sign = "-";
boolean but_status = 1;

HardwareSerial mySerial(PA10, PA9);
TM1650 d;

TaskHandle_t readEncoder_1;
TaskHandle_t displayEncoder1Data;
TaskHandle_t flashWrite;

//------------------------------------------------------------------------------

static void vReadEncoder_1(void *pvParameters){
  UNSUED(pvParameters);
  for(;;){
    
  }
}

//------------------------------------------------------------------------------

void setup() {
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  pinMode(SignPin, INPUT);
  attachInterrupt(encoder0PinA, doEncoderA, CHANGE);
  attachInterrupt(encoder0PinB, doEncoderB, CHANGE);
  attachInterrupt(SignPin, resetStatus, FALLING);
  Wire.begin();
  mySerial.begin(115200);
  d.init();
  d.displayOff();
  d.displayString("____");
  d.setBrightness(TM1650_MIN_BRIGHT);
  d.displayOn();
  delay(1000);
}

void loop() {
  if (but_status == 0) {
    reSign();
    Filter_data();
    d.displayString((display_data));
  }
  if (encoder0Pos != encoder0Pos_old) {
    d.clear();
    if (encoder0Pos > 999) {
      encoder0Pos = 999;
      Filter_data();
    } else if (encoder0Pos < 0) {
      encoder0Pos = 0;
      Filter_data();
    } else {
      Filter_data();
    }
    d.displayString((display_data));
    encoder0Pos_old = encoder0Pos;
    d.displayOn();
    d.setBrightness(TM1650_MAX_BRIGHT);
  }
}

void Filter_data() {
  int first_digit = encoder0Pos / 100;
  int second_digit = (encoder0Pos - (100 * first_digit)) / 10;
  int third_digit = encoder0Pos - (100 * first_digit) - (10 * second_digit);
  value = Sign + String(first_digit) + String(second_digit) + String(third_digit);
  value.toCharArray(display_data, 5);
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