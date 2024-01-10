/******************************************************************************************************************************************
  FlashStoreAndRetrieve.ino
  For STM32 using Flash emulated-EEPROM

  The FlashStorage_STM32 library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory
  of STM32F/L/H/G/WB/MP1. It's using the buffered read and write to minimize the access to Flash.
  It now supports writing and reading the whole object, not just byte-and-byte.

  Inspired by Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_STM32
  Licensed under MIT license
 ******************************************************************************************************************************************/

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <FlashStorage_STM32.h>
HardwareSerial mySerial(PA10, PA9);

uint16_t address = 0;
int number;

void setup() {
  mySerial.begin(115200);
  while (!Serial)
    ;

  delay(200);

  mySerial.print(F("\nStart FlashStoreAndRetrieve on "));
  mySerial.println(BOARD_NAME);
  mySerial.println(FLASH_STORAGE_STM32_VERSION);

  mySerial.print("EEPROM length: ");
  mySerial.println(EEPROM.length());

  // Read the content of emulated-EEPROM
  EEPROM.get(address, number);

  // Print the current number on the serial monitor
  // mySerial.print("Number = 0x");
  // mySerial.println(number, HEX);

  // Save into emulated-EEPROM the number increased by 1 for the next run of the sketch
  // EEPROM.put(address, (int)(number + 1));
  // EEPROM.commit();

  mySerial.println("Done writing to emulated EEPROM. You can reset now");
}

void loop() {
  mySerial.println(number);
  mySerial.println(number);
  delay(500);
}
