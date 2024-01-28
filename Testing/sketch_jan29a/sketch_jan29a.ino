#include <Versatile_RotaryEncoder.h>
#include <FlashStorage_STM32.h>
#include <Wire.h>
#include <TM1650.h>
#include <TM16xxDisplay.h>

#define clk_A PB8
#define dt_A PB5
#define sw_A PB9

#define clk_B PB6
#define dt_B PB4
#define sw_B PB7

#define Mode_Pin PA11

#define displaySCL_A PA9
#define displaySDA_A PA10

#define displaySCL_B PB1
#define displaySDA_B PA10

volatile int Pos = 0;
volatile int Write_Value;
volatile int Read_Value;
boolean But_stat = 0;
uint16_t address = 0;


void handleRotate(int8_t rotation);
void WriteData(int data);
// void handlePress();
// void handleLongPress();
// void handleDoublePress();
// void handlePressRelease();
// void handleLongPressRelease();

HardwareSerial mySerial(PA1, PA0);
Versatile_RotaryEncoder *versatile_encoder_A;

TM1650 display1(displaySDA_A, //SDA
                displaySCL_A, //SCL
                4,
                true,
                7);

TM1650 display2(displaySDA_B, //SDA
                 displaySCL_B, //SCL
                4,
                true,
                7);

TM16xxDisplay displayA(&display1, 4);
TM16xxDisplay displayB(&display2, 4);

void setup() {

  mySerial.begin(115200);
  versatile_encoder_A = new Versatile_RotaryEncoder(clk, dt, sw);

  versatile_encoder_A->setHandleRotate(handleRotate);
  versatile_encoder_A->setHandlePress(handlePress);
  // versatile_encoder_A->setHandleDoublePress(handleDoublePress);
  // versatile_encoder_A->setHandlePressRelease(handlePressRelease);
  // versatile_encoder_A->setHandleLongPress(handleLongPress);
  // versatile_encoder_A->setHandleLongPressRelease(handleLongPressRelease);

  delay(1000);
  mySerial.println("Ready!");
}

void loop() {
  // delay(100);
    if (versatile_encoder_A->ReadEncoder()) {
      // mySerial.println(versatile_encoder_A->getRotary());
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
// }

void WriteData(uint16_t address, int data){
  EEPROM.put(address, (int)data);
  EEPROM.commit();
}

void ReadData(uint16_t address){
  EEPROM.get(address, number);
}

