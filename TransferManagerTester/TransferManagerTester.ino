#include <SD.h>
#include <SPI.h>
#include "TransferManager.h"
//#include <Streaming.h>

const int PIN_TP_CS = 4;
const int PIN_SD_CS = 5;
const int PIN_LCD_CS = 10;
const int PIN_LED_ST = 14;

TransferManager tm;

const int SETS = 2;
const int BUFFER_LENGTH = 20;
float readings [SETS*BUFFER_LENGTH];
char ver[] = "v0.1";
char id[] = "12346";
char date[] = "040516";
char uname[] = "Jake Tryon";
float freq = 100;

void setup()
{
  // Signal that Teensy is on
  pinMode(PIN_LED_ST,OUTPUT);
  digitalWrite(PIN_LED_ST,HIGH);
  
  // Start serial
  Serial.begin(115200);
  Serial.println("Starting");

  // Drive all chip selects high
  pinMode(PIN_TP_CS, OUTPUT);
  digitalWrite(PIN_TP_CS, HIGH);
  pinMode(PIN_SD_CS, OUTPUT);
  digitalWrite(PIN_SD_CS, HIGH);
  pinMode(PIN_LCD_CS, OUTPUT);
  digitalWrite(PIN_LCD_CS, HIGH);

  // Start SD Card
  if (!SD.begin(PIN_SD_CS)) {
    //while (1)
      Serial.println("SD CONNECTION FAILURE!");
  }

  // Get SPI going pretty fast (12 MHz)
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();

  // Let user know that things are good
  Serial.println("Setup complete!");

  // Write a fake session to file
  for (long i = 0; i < SETS*BUFFER_LENGTH; i++)
    readings[i] = i;
  tm.writePatient(ver,id,uname);
  tm.writeSession(ver,id,date,freq,readings,SETS,BUFFER_LENGTH);
}

void loop()
{
  digitalWrite(PIN_LED_ST,(bool)((millis()/200)%2));
  if (Serial.available() > 0)
    tm.procInput((char)Serial.read(),false);
    
}

