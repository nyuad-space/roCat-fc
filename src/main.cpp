#include <STM32FreeRTOS.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN PF10      // PF10
#define NUM_LEDS 1

Adafruit_NeoPixel LED(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

#define BUZZER PD1


// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at any time.
SemaphoreHandle_t xSerialSemaphore;

void TaskBeep( void *pvParameters );
void TaskBlink( void *pvParemeters);
void TaskCount( void *pvParemeters);

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication:
  Serial.begin(115200);

  while (!Serial) {
    delay(10); // wait for serial port to connect.
  }
  delay(100);
  Serial.println(portTICK_PERIOD_MS);
  Serial.println(configTICK_RATE_HZ);
  Serial.println(F_CPU);

  // Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can set it up here.
  if ( xSerialSemaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

  // Now set up two Tasks to run independently.
  xTaskCreate(
    TaskBeep
    ,  (const portCHAR *)"Boop"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskBlink
    ,  (const portCHAR *)"Blink"  // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );
  
  xTaskCreate(
    TaskCount
    ,  (const portCHAR *)"Count"  // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  // start scheduler
  vTaskStartScheduler();
  Serial.println("Insufficient RAM");
  while(1);
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBeep( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  pinMode(BUZZER,OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    // read the input pin:
    tone(BUZZER,500,200);

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      //Serial.println("Buzzed");

      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }

    vTaskDelay(5000);
  }
}

void TaskBlink( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  pinMode(LED_PIN,OUTPUT);
  LED.begin();
  LED.show();
  for (;;) // A Task shall never return or exit.
  {
    LED.setPixelColor(0, random(50), random(50), random(50));
    LED.show();
    vTaskDelay(2500);
    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      //Serial.println("Blinked");

      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }
    LED.setPixelColor(0, 0, 0, 0);
    LED.show();
    vTaskDelay(2500);
  }
}

void TaskCount( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  unsigned long lastCount = 0;
  int numTask = 0;
  for (;;) // A Task shall never return or exit.
  {
    if((millis() - lastCount)>=1000){
      Serial.printf("Tasks run: %u \n", numTask);
      lastCount = millis();
      numTask = 0;
    }
    numTask++;
    vTaskDelay(0);
  }
}
