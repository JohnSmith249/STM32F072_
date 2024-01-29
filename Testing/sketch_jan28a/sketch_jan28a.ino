#include <Versatile_RotaryEncoder.h>
<<<<<<< HEAD
#include <FlashStorage_STM32.h>
#include <Wire.h>
#include <TM1650.h>
#include <TM16xxDisplay.h>
=======
>>>>>>> 4c989665b95a53c504855d0f8b0c369e16e6741b

#define clk PB8
#define dt PB5
#define sw PB9

volatile int Pos = 0;
<<<<<<< HEAD
volatile int Write_Value;
volatile int Read_Value;
boolean But_stat = 0;
uint16_t address = 0;


void handleRotate(int8_t rotation);
void WriteData(int data);
=======
boolean But_stat = 0;

void handleRotate(int8_t rotation);
>>>>>>> 4c989665b95a53c504855d0f8b0c369e16e6741b
// void handlePress();
// void handleLongPress();
// void handleDoublePress();
// void handlePressRelease();
// void handleLongPressRelease();

HardwareSerial mySerial(PA1, PA0);
Versatile_RotaryEncoder *versatile_encoder;

<<<<<<< HEAD
TM1650 display1(PA10, //SCL
                PA9, //SDA
                4,
                true,
                7);

TM1650 display2(PA10, //SCL
                PB1, //SDA
                4,
                true,
                7);

TM16xxDisplay displayA(&display1, 4);
TM16xxDisplay displayB(&display2, 4);

=======
>>>>>>> 4c989665b95a53c504855d0f8b0c369e16e6741b
void setup() {

  mySerial.begin(115200);
  versatile_encoder = new Versatile_RotaryEncoder(clk, dt, sw);

  versatile_encoder->setHandleRotate(handleRotate);
  versatile_encoder->setHandlePress(handlePress);
  // versatile_encoder->setHandleDoublePress(handleDoublePress);
  // versatile_encoder->setHandlePressRelease(handlePressRelease);
  // versatile_encoder->setHandleLongPress(handleLongPress);
  // versatile_encoder->setHandleLongPressRelease(handleLongPressRelease);

  delay(1000);
  mySerial.println("Ready!");
}

void loop() {
  // delay(100);
    if (versatile_encoder->ReadEncoder()) {
      // mySerial.println(versatile_encoder->getRotary());
    }
    mySerial.print(Pos); mySerial.print(" ");
    mySerial.println(But_stat);
}

void handleRotate(int8_t rotation) {
  if (Pos<999 && Pos>0){
      if (rotation > 0)
	    Pos++;
    else
	    Pos--;
  } else if (Pos < 0){
    Pos = 0;
  } else if (Pos > 999){
    Pos = 999;
  } else if (Pos == 999){
    if (rotation < 0)
    Pos--;
  } else if (Pos == 0){
    if (rotation > 0){
      Pos++;
    }
  }
}

void handlePress() {
	// mySerial.println("Button Pressed");
  // delay(1000);
  if (But_stat == 0){
    But_stat = 1;
  } else if (But_stat == 1) {
    But_stat = 0;
  }
}

// void handleDoublePress() {
// 	Serial.println("#4.2 Double Pressed");
// }

// void handlePressRelease() {
// 	Serial.println("#5 Press released");
// }

// void handleLongPress() {
// 	Serial.println("#6 Long pressed");
// }

// void handleLongPressRelease() {
// 	Serial.println("#7 Long press released");
<<<<<<< HEAD
// }

void WriteData(uint16_t address, int data){
  EEPROM.put(address, (int)data);
  EEPROM.commit();
}

void ReadData(uint16_t address){
  EEPROM.get(address, number);
}

=======
// }
>>>>>>> 4c989665b95a53c504855d0f8b0c369e16e6741b
