#define Input_Data_pin_A A4
#define Input_Data_pin_B A5

void setup() {
  pinMode(Input_Data_pin_A, INPUT);
  pinMode(Input_Data_pin_B, INPUT);
  Serial.begin(9600);

}

void loop() {
  Serial.print(analogRead(Input_Data_pin_A));
  Serial.print(" ");
  Serial.println(analogRead(Input_Data_pin_B));
  delay(500);
}
