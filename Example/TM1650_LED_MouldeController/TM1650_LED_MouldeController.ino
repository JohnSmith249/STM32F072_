#include <TM1650.h>
#include <TM16xxDisplay.h>
// #include

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

  void setup() {
}

void loop() {
  byte digit;
  unsigned int segments;
  byte intensity;

  // segment on each digit controll --------------------------//
  // for (digit = 0; digit < 4; digit++) {
  //   for (segments = 0; segments <= 0xFF; segments = segments * 2 + 1) {
  //     display1.setSegments(segments,
  //                          digit);
  //     delay(100);
  //   }
  // }

  // dim light intensity controll --------------------------//
  // display1.setupDisplay(false, 7);
  // delay(1000);

  // for (intensity = 0; intensity < 8; intensity++) {
  //   display1.setupDisplay(true, intensity);
  //   delay(500);
  // }
  // display1.clearDisplay();

  long n;
  int pos;
  byte dp;

  // Control position of each digit
  // for (pos = 0; pos < 4; pos++){
  //   for (n = 0; n<=9 ; n++){
  //     display1.setDisplayDigit(n, pos, n%2);
  //     delay(500);
  //   }
  //   display1.clearDisplayDigit(pos, false);
  // }

  // display decimal and control dot position -------------------------------
  // for (dp=B00000001; dp < B00100000; dp = dp *2){
  //   for(n=9; n<=9999; n=n*10+9){
  //     display1.setDisplayToDecNumber(n, dp);
  //     delay(500);
  //   }
  // }

  // display1.clearDisplay();

  // Display String ---------------------------------------------------------------
  // display1.setDisplayToString("ERR", B0010, 0);
  // delay(1000);
  displayA.setDisplayToSignedDecNumber(88, B0000, false);
  delay(1000);
  displayB.setDisplayToSignedDecNumber(999, B0010, false);
  delay(1000);
}
