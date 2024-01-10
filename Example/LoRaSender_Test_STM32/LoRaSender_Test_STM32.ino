#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>

#define SS PA15
#define RST PB7
#define DI0 PB6
#define BAND 433E6
#define LORA_PCTR PB14
SoftwareSerial mySerial(PA5, PA8);


int counter = 0;
void setup() {
  pinMode(DI0, OUTPUT);
  pinMode(RST, OUTPUT);
  pinMode(LORA_PCTR, OUTPUT);
  digitalWrite(LORA_PCTR, HIGH);
  delay(1000);
  mySerial.begin(4800);
  // while (!Serial);
  // mySerial.println('here');
  mySerial.println("LoRa Sender");
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(BAND)) {
    mySerial.println("Starting LoRa failed!");
    while (1)
      ;
  }
}

void loop() {
  mySerial.print("Sending packet: ");
  // mySerial.println(counter);
  uint8_t test[600];
  // for (int i =0; i<10; i++){
  //   test[i] = (char)i;
  for (int i = 0; i < 600; i++) {
    // uint8_t test_item = i%10;
    // mySerial.print(test_item);
    test[i] = (i % 10);
  }
  // mySerial.println(test);
  LoRa.beginPacket();
  // LoRa.print(test);
  LoRa.write(&test[0],500);
  for (int i=0; i< 600; i++){
    mySerial.print(test[i]);
  }
  mySerial.println();
  LoRa.endPacket();

  counter++;

  delay(500);
}
