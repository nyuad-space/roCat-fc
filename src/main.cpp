#include <STM32FreeRTOS.h>
#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

#include <rocat_config.h>

Adafruit_NeoPixel LED(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

SFE_UBLOX_GNSS GNSS;



// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at any time.
SemaphoreHandle_t xSerialSemaphore;

void TaskGetLocation( void *pvParameters );
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
  Wire.setSCL(GNSS_I2C_SCL);
  Wire.setSDA(GNSS_I2C_SDA);
  Wire.begin();
  if (GNSS.begin() == false) //Connect to the u-blox module using Wire port
  {
    Serial.printf("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing...\n");
    while (1);
  }
  Serial.printf("u-blox GNSS detected\n");
  GNSS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output both NMEA and UBX messages
  GNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT);
  //GNSS.enableDebugging();
  Serial.printf("Tick Period: %u ms\n",portTICK_PERIOD_MS);
  Serial.printf("Tick Rate: %u\n", configTICK_RATE_HZ);
  Serial.printf("CPU Freq: %u\n", F_CPU);
  delay(200);

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
    TaskGetLocation
    ,  (const portCHAR *)"Boop"  // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
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

void TaskGetLocation( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  pinMode(BUZZER,OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    // read the input pin:
    tone(BUZZER,500,50);

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      //Serial.println("Buzzed");
      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }
    
    long latitude = GNSS.getLatitude();
    Serial.print(F("Lat: "));
    Serial.print(latitude);

    long longitude = GNSS.getLongitude();
    Serial.print(F(" Long: "));
    Serial.print(longitude);
    Serial.print(F(" (degrees * 10^-7)"));

    long altitude = GNSS.getAltitude();
    Serial.print(F(" Alt: "));
    Serial.print(altitude);
    Serial.print(F(" (mm)"));

    byte SIV = GNSS.getSIV();
    Serial.print(F(" SIV: "));
    Serial.print(SIV);

    Serial.print(F("   "));
    Serial.print(GNSS.getYear());
    Serial.print(F("-"));
    Serial.print(GNSS.getMonth());
    Serial.print(F("-"));
    Serial.print(GNSS.getDay());
    Serial.print(F(" "));
    Serial.print(GNSS.getHour());
    Serial.print(F(":"));
    Serial.print(GNSS.getMinute());
    Serial.print(F(":"));
    Serial.println(GNSS.getSecond());
    
    Serial.println();
    vTaskDelayUntil( &xLastWakeTime, 2000);
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
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 1;
  unsigned long lastCount = 0;
  int numTask = 0;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) // A Task shall never return or exit.
  {
    if((millis() - lastCount)>=1000){
      //Serial.printf("Tasks run: %u, TickRate: %i\n", numTask, configTICK_RATE_HZ);
      lastCount = millis();
      numTask = 0;
    }
    numTask++;
    vTaskDelayUntil( &xLastWakeTime, xFrequency);
  }
}
