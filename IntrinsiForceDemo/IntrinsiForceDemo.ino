#include <SD.h>
#include <SPI.h>
#include <LCD.h>
#include "Draw.h"
#include "DrawUtils.h"
#include "TransferManager.h"
//#include <Streaming.h>

//***********************************************
// Jake's Header
unsigned int butt1Pin = 16;
unsigned int butt2Pin = 17;
unsigned int Ts = 10;
unsigned int treatTime = 5000;  //5 seconds
unsigned long treatStartTime = 0;
unsigned int prevReadTime = 0;
unsigned int currReadTime = 0;
unsigned int firstPress = 0;
bool butt1Press = 1;
bool treatStart = 0;
bool treatLoop = 0;
bool unitSelect = 0;
unsigned int maxRead = 0;
unsigned int probePin = A9;
unsigned int buzzerPin = 15;
float forceData[500];
int forceindex = 0;
float calib = 0.22;
float forceAvg = 0;
float forcePk = 0;
unsigned int forceSum = 0;
float forceAvglbs = 0;
float forceAvgkg = 0;
float forcePklbs = 0;
float forcePkkg = 0;
unsigned int startTone = 1047;
unsigned endTone = 1319;
float refV = 3.3 / 3.3;
float refV12Bit = 4095 * refV;
//***********************************************

const int PIN_TP_CS = 4;
const int PIN_SD_CS = 5;
const int PIN_LCD_CS = 10;
const int PIN_LED_ST = 14;

TransferManager tm;

const int SETS = 2;
const int BUFFER_LENGTH = 20;
float readings [SETS * BUFFER_LENGTH];
char ver[] = "v0.1";
char id[] = "12346";
char date[] = "040516";
char uname[] = "Jake Tryon";
float freq = 100;

Draw draw;

int state;

long screenTime;
const int screenPeriod = 333;

float lastResult;

void setup()
{
  //*********************************************
  // Jake setup
  for (int i = 0; i < 500; i++)
  {
    forceData[i] = 0;
  }

  pinMode(butt1Pin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(115200);

  analogWriteResolution(12);
  analogWrite(A14, (int)refV12Bit);
  //*********************************************

  // Signal that Teensy is on
  pinMode(PIN_LED_ST, OUTPUT);
  digitalWrite(PIN_LED_ST, HIGH);

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

  Tft.lcd_init();
  StartUp();  

  //  // Write a fake session to file
  //  for (long i = 0; i < SETS * BUFFER_LENGTH; i++)
  //    readings[i] = i;
  //  tm.writePatient(ver, id, uname);
  //  tm.writeSession(ver, id, date, freq, readings, SETS, BUFFER_LENGTH);

  state = 1;
  screenTime = millis();
  lastResult = 0;
}

void loop()
{
  //digitalWrite(PIN_LED_ST,(bool)((millis()/400)%2));
  if (Serial.available() > 0)
    tm.procInput((char)Serial.read(), false);

  // State update
  if (millis() - screenTime > screenPeriod)
  {
    // Get time
    screenTime = millis();

    // Erase last run
    draw.ClrResult(lastResult,0);
    
    float reading = analogRead(probePin);
    if (reading < -pow(0.3045,2)/4/0.5169)
    {
            reading = -pow(0.3045,2)/4/0.5169;
    }
    reading = (-0.3045+sqrt(pow(0.3045,2)+4*0.5169*reading))/(2*0.5169);
    
    lastResult = reading; // Convert to int and store for next itr

    // Draw
    draw.DispResult(lastResult, 0);

//    //*******************************************
//    // Jake state work
//    // Do state stuff, update
//    butt1Press = digitalRead(butt1Pin);
//
//    if ((!butt1Press) && (state == 1))
//    {
//      treatStart = 1;
//      
//      // Clear old state
//      updateState(2,0,0,0,0);
//    }
//
//    if (treatStart)
//    {
//      forceAvg = 0;
//      forcePk = 0;
//      forceAvglbs = 0;
//      forceAvgkg = 0;
//      forcePklbs = 0;
//      forcePkkg = 0;
//      forceSum = 0;
//      maxRead = 0;
//
//      //display treatment start stuff
//      tone(buzzerPin, startTone, 500);
//      noTone(buzzerPin);
//
//      treatLoop = 1;
//      while (treatLoop)
//      {
//        currReadTime = millis();
//        if (currReadTime - prevReadTime > Ts)
//        {
//          forceData[forceindex] = analogRead(probePin)*0.225;
//
//          forceSum = forceSum + forceData[forceindex];
//          if (forceData[forceindex] > maxRead)
//            maxRead = forceData[forceindex];
//
//          prevReadTime = currReadTime;
//          forceindex = forceindex + 1;
//        }
//        if (forceindex == 500)
//        {
//          forceindex = 0;
//          treatLoop = 0;
//        }
//      }
//
//      forceAvg = (forceSum / 5000);
//      forceAvglbs = forceAvg * 0.224808943871;
//      forceAvgkg = forceAvglbs * 0.453592;
//
//      forcePk = maxRead;
//      forcePklbs = forcePk * 0.224808943871;
//      forcePkkg = forcePkkg * 0.453592;
//
//      tone(buzzerPin, endTone, 500);
//      noTone(buzzerPin);
//
//      //send away data
//      //  tm.writePatient(ver, id, uname);
//      tm.writePatient(ver, id, uname);
//      //  tm.writeSession(ver, id, date, freq, readings, SETS, BUFFER_LENGTH);
//      tm.writeSession(ver, id, date, (float)100, forceData, 1, 500);
//
//      treatStart = 0;
//
//      // Move to next state
//      updateState(3,0,forceAvg,0,0);
//    }
//
//    if ((!digitalRead(butt2Pin)) && state == 3)
//    {
//      if (firstPress == 0);
//      {
//        firstPress = 1;
//        if (unitSelect)
//        {
//          //display forceAvglbs forcePklbs
//          unitSelect = 0;
//          updateState(3,forceAvg,forceAvglbs,!unitSelect,unitSelect);
//        }
//        else
//        {
//          // display forceAvgkg forcePkkg
//          unitSelect = 1;
//          updateState(3,forceAvglbs,forceAvg,!unitSelect,unitSelect);
//        }
//      }
//    }
//    else
//    {
//      firstPress = 0;
//      float force;
//      if (unitSelect)
//        force = forceAvglbs;
//      else
//        force = forceAvg;
//      updateState(1,force,0,unitSelect,0);
//    }
    //*******************************************
  }
  //  draw.StartTone();
  //  draw.EndTone();
}

void updateState(int newState, int oldReading, int newReading, int oldUnit, int newUnit)
{
  endState(state, oldReading, oldUnit);
  state = newState;
  startState(state, newReading, newUnit);
}

void endState(int i, int reading, int unitSelect)
{
  if (state == 0)
    draw.ClrMenu();
  else if (state == 1)
    draw.ClrPinchPrompt();
  else if (state == 2)
    draw.ClrPinchArea(0);
  else if (state == 3)
    draw.ClrResult(reading, unitSelect);
  else if (state == 4)
    draw.ClrProbe(10);
  else
    ClrStream();
}

void startState(int i, int reading, int unit)
{
  if (state == 0)
    draw.DispMenu();
  else if (state == 1)
    draw.DispPinchPrompt();
  else if (state == 2)
    draw.DispPinchArea(i);
  else if (state == 3)
    draw.DispResult(reading, unit);
  else if (state == 4)
    draw.DispProbe(10);
  else
    DispStream();
}

