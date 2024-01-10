#include <STM32FreeRTOS.h>
#include <Wire.h>

HardwareSerial mySerial(PA10, PA9);
const uint8_t Analog_Pin_A = PA1;
const uint8_t Analog_Pin_B = PA2;


void setup() {
  mySerial.begin(115200);
  while(!Serial) {};
  pinMode(Analog_Pin_A, INPUT);
  pinMode(Analog_Pin_B, INPUT);
}

void loop() {
  mySerial.print(analogRead(Analog_Pin_A));
  mySerial.print(" ");
  mySerial.println(analogRead(Analog_Pin_B));
  delay(200);
}
