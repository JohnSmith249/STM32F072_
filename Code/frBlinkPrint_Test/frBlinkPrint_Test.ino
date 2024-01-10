// Simple demo of three threads
// LED blink thread, print thread, and idle loop
#include <STM32FreeRTOS.h>
#include <Wire.h>
#include <FlashStorage_STM32.h>

HardwareSerial mySerial(PA10, PA9); //RX, TX
// FlashStorage(Data_slot, int);
uint16_t address = 0;
int number = 0;

const uint8_t LED_PIN = PC6;
const uint8_t Analog_Pin_A = PA1;
const uint8_t Analog_Pin_B = PA2;

volatile uint32_t count = 0;
// volatile uint32_t index = 0;

// handle for blink task
TaskHandle_t blink;
TaskHandle_t read;
TaskHandle_t flashWrite;

//------------------------------------------------------------------------------
// high priority for blinking LED
static void vLEDFlashTask(void *pvParameters) {
  UNUSED(pvParameters);
  pinMode(LED_PIN, OUTPUT);

  // Flash led every 200 ms.
  for (;;) {
    // Turn LED on.
    digitalWrite(LED_PIN, HIGH);

    // Sleep for 50 milliseconds.
    vTaskDelay((50L * configTICK_RATE_HZ) / 1000L);

    // Turn LED off.
    digitalWrite(LED_PIN, LOW);

    // Sleep for 150 milliseconds.
    vTaskDelay((150L * configTICK_RATE_HZ) / 1000L);
  }
}
//------------------------------------------------------------------------------
static void vPrintTask(void *pvParameters) {
  UNUSED(pvParameters);
  while (1) {
    // Sleep for one second.
    vTaskDelay(configTICK_RATE_HZ); 
    // Print count for previous second.
    mySerial.print(F("Count: "));
    // mySerial.print(count);
    mySerial.println(count);
    count +=1;

    // Print unused stack for threads.
    // mySerial.print(F(", Unused Stack: "));
    // mySerial.print(uxTaskGetStackHighWaterMark(blink));
    // mySerial.print(' ');
    // mySerial.print(uxTaskGetStackHighWaterMark(0));
    // mySerial.print(' ');
    // mySerial.println(uxTaskGetStackHighWaterMark(xTaskGetIdleTaskHandle()));

    // Zero count.
    // count = 0;
  }
}

static void vREADAnalogTask(void *pvParameters) {
  UNUSED(pvParameters);
  // pinMode(Analog_Pin_A, INPUT);
  // pinMode(Analog_Pin_B, INPUT);
  for (;;) {
    mySerial.print(analogRead(PA3));
    mySerial.print(" ");
    mySerial.println(analogRead(PA1));
    vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
  }
}

static void vFlashLogTask(void *pvParameters){
  UNUSED(pvParameters);
  int temp;
  for(;;) {
    EEPROM.get(address, number);
    mySerial.println(number);
    vTaskDelay((100L*configTICK_RATE_HZ) / 1000L);
    EEPROM.put(address, (int) (number + 1));
    EEPROM.commit();
    vTaskDelay((3600L*configTICK_RATE_HZ));
    count = 0;
  }
}

//------------------------------------------------------------------------------
void setup() {
  mySerial.begin(115200);
  // wait for Leonardo
  while(!Serial) {}

  // create blink task
  xTaskCreate(vLEDFlashTask,
    "Task1",
    configMINIMAL_STACK_SIZE + 50,
    NULL,
    tskIDLE_PRIORITY + 2,
    &blink);

  // create print task
  xTaskCreate(vPrintTask,
    "Task2",
    configMINIMAL_STACK_SIZE + 100,
    NULL,
    tskIDLE_PRIORITY + 1,
    NULL);

  // xTaskCreate(vREADAnalogTask,
  //   "Task3",
  //   configMINIMAL_STACK_SIZE + 50,
  //   NULL,
  //   tskIDLE_PRIORITY + 3,
  //   &read);

  xTaskCreate(vFlashLogTask,
    "Task4",
    configMINIMAL_STACK_SIZE + 100,
    NULL,
    tskIDLE_PRIORITY + 3,
    &flashWrite);

  // start FreeRTOS
  vTaskStartScheduler();

  // should never return
  mySerial.println(F("Die"));
  while(1);
}
//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
  while(1) {
    // must insure increment is atomic
    // in case of context switch for print
    noInterrupts();
    // count++;
    interrupts();
  }
}
