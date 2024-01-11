#define encoder0PinA PB8
#define encoder0PinB PB9

volatile int encoder0Pos = 0;
volatile int encoder0Pos_old = 0;
volatile int Pos = 0;
HardwareSerial mySerial(PA10, PA9);

void setup() {
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  // attachInterrupt(encoder0PinA, doEncoderA, CHANGE);
  // attachInterrupt(encoder0PinB, doEncoderB, CHANGE);
  encoder0Pos_old = digitalRead(encoder0PinA);
  mySerial.begin(115200);
}

void loop() {
  // encoder0Pos = digitalRead(encoder0PinA);
  // if (encoder0Pos != encoder0Pos_old){
  //   if(digitalRead(encoder0PinB) != encoder0Pos){
  //     Pos++;
  //   } else{
  //     Pos --;
  //   }
  //   mySerial.print("Position: ");
  //   mySerial.println(Pos);
  // }
  // encoder0Pos = encoder0Pos_old;
  mySerial.print(digitalRead(encoder0PinA));
  mySerial.print(" ");
  mySerial.println(digitalRead(encoder0PinB));
  delay(200);
}

void doEncoderA(){
  if (digitalRead(encoder0PinA) == HIGH){
    mySerial.println(" Pin A HIGH");
  }
  else{
    mySerial.println(" Pin A LOW");
  }
  delay(500);
}

void doEncoderB(){
  if (digitalRead(encoder0PinB) == HIGH){
    mySerial.println(" Pin B HIGH");
  }
  else{
    mySerial.println(" Pin B LOW");
  }
  delay(500);
}