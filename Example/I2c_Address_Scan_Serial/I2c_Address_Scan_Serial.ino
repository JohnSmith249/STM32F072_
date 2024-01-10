/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
HardwareSerial mySerial(PA10, PA9);

void setup() {
  Wire.begin();
  mySerial.begin(115200);
  mySerial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices;
  mySerial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      mySerial.print("I2C device found at address 0x");
      if (address < 16) {
        mySerial.print("0");
      }
      mySerial.println(address, HEX);
      nDevices++;
    } else if (error == 4) {
      mySerial.print("Unknow error at address 0x");
      if (address < 16) {
        mySerial.print("0");
      }
      mySerial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    mySerial.println("No I2C devices found\n");
  } else {
    mySerial.println("done\n");
  }
  delay(1000);
}