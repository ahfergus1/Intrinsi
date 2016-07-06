#include <SD.h>
#include <SPI.h>
//#include "HX8347D/LCD.h"  // Include display driver
#include "TransferManager.h"
#include "MenuManager.h"
//#include <Streaming.h>

//***********************************************
// Jake's Header
unsigned int buttPin[5] = { 16, 17, 20, 21, 22 };
unsigned int Ts = 10;
// unsigned int treatTime = 5000;  //5 seconds
unsigned long treatStartTime = 0;
// unsigned int firstPress = 0;
bool buttState[5];
// bool buttEdge[5] = { false, false, false, false, false };
// bool treatStart = 0;
// bool treatLoop = 0;
// unsigned int maxRead = 0;
unsigned int probePin = A9;
unsigned int buzzerPin = 15;
#define SAMP_LEN 300
float forceData[SAMP_LEN];
int forceindex = 0;
// unsigned int forceSum = 0;
// float forceAvg = 0;
// float forcePk = 0;
// float forceAvglbs = 0;
// float forceAvgkg = 0;
// float forcePklbs = 0;
// float forcePkkg = 0;
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
MenuManager mm;
Page lastPage;

const int SETS = 10;
const int BUFFER_LENGTH = SAMP_LEN;
float readings [SETS * BUFFER_LENGTH];
String ver = "v0.2";
String id = "00001234";
String date = "040516";
String uname = "Jake Tryon";
float freq = 1.0/(float(Ts)/1000.0);

Draw draw;

int state;

long screenTime;
const int screenPeriod = 100;

void setup()
{
  // Start serial for its many uses
  Serial.begin(115200);
  Serial.println("Starting");
  
  //*********************************************
  // Measurement setup
  for (int i = 0; i < SAMP_LEN; i++)
  {
    forceData[i] = 0;
  }
  analogWriteResolution(12);
  analogWrite(A14, (int)refV12Bit);
  //*********************************************

  //**********************************************
  // Button and buzzer setup
  for (int i=0; i<5; i++)
  {
    pinMode(buttPin[i], INPUT_PULLUP);
    int sum = 0;
    for (int j=0; j<10; j++)
      sum += !digitalRead(buttPin[i]);
    if (sum >= 5)
      buttState[i] = true;
    else
      buttState[i] = false;
  }
  pinMode(buzzerPin, OUTPUT);
  //*********************************************

  // Signal that Teensy is on
  pinMode(PIN_LED_ST, OUTPUT);
  digitalWrite(PIN_LED_ST, HIGH);

  // Drive all chip selects high
  pinMode(PIN_TP_CS, OUTPUT);
  digitalWrite(PIN_TP_CS, HIGH);
  pinMode(PIN_SD_CS, OUTPUT);
  digitalWrite(PIN_SD_CS, HIGH);
  pinMode(PIN_LCD_CS, OUTPUT);
  digitalWrite(PIN_LCD_CS, HIGH);

  // Get SPI going pretty fast (12 MHz)
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();

  // Start SD Card
  if (!SD.begin(PIN_SD_CS)) {
    while (1)
      Serial.println("SD CONNECTION FAILURE!");
  }

  // Let user know that things are good
  //Serial.println("Setup complete!");

  // Start Menu Manager
  mm.begin();

  //  // Write a fake session to file
  //  for (long i = 0; i < SETS * BUFFER_LENGTH; i++)
  //    readings[i] = i;
  //  tm.writePatient(ver, id, uname);
  //  tm.writeSession(ver, id, date, freq, readings, SETS, BUFFER_LENGTH);

  screenTime = millis();
  // lastResult = 0;

  // Let user see beautiful logo
  delay(1000);

  // Say that a button was pressed to move to the main menu
  mm.buttonPress(1);
  lastPage = MAIN;
}

void loop()
{
  // Heart beat
  //digitalWrite(PIN_LED_ST,(bool)((millis()/400)%2));

  // Check for requests from a host, reply if not busy
  if (Serial.available() > 0)
  {
    bool busy = mm.getPage() != UPLOAD;
    tm.procInput((char)Serial.read(), busy);
  }

  // State update
  if (millis() - screenTime > screenPeriod)
  {
    // Get time
    screenTime = millis();

    // // DEBUG
    // // Clear away cmd
    // for (int i=0; i<4; ++i)
    //   Serial.println("");

    // Check button states
    // Do not check directly elsewhere!
    // Only allows one press per itr
    // Other presses will have to wait for next itr
    int pressedButton = -1;
    for (int i=0; i<5; i++)
    {
      // Get button state
      bool state = !digitalRead(buttPin[i]);
      // Only show edge if state has changed and no other press
      if (state != buttState[i])
      {
        // Update state
        buttState[i] = state;
        // buttEdge[i] = true;
        // Only trigger on rising edge
        if ((state == true) && (pressedButton < 0))
          pressedButton = i;
      }
      else
      {
        // Don't update state
        // Make sure edge is false
        // buttEdge[i] = false;
      }
    }

//    // DEBUG flow
//    Serial.print("Pressed button: ");
//    Serial.println(pressedButton);
//    Serial.print("Page: ");
//    Serial.println(mm.getPage());
//    Serial.print("Subpage: ");
//    Serial.println(mm.getSubPage());

    // Update menu manager
    if (pressedButton > -1)
    {
      Action act = mm.buttonPress(pressedButton);
      Page page = mm.getPage();
      int subPage = mm.getSubPage();
      
      // Wipe recorded data on entry to session
      if (page == SESSION && page != lastPage)
      {
        for (long i = 0; i < SETS * BUFFER_LENGTH; i++)
            readings[i] = 0.0;
      }

      // Save data at end of recording
      if (page == SESSION && subPage == 9 && act == NEXT)
      {
        // If patient does not exist create them
        if (!tm.patientExists(id));
          tm.writePatient(ver, id, uname);
        tm.writeSession(ver, id, date, freq, readings, SETS, BUFFER_LENGTH);
      }

      // Record data on command
      if ((page == SESSION || page == MEAS) && act == STRT)
      {
        // Do readings
        // Play start tone to alter user to squeeze
        tone(buzzerPin, startTone, SAMP_LEN);

        // Inside while loop 500 data points are collected at a fixed rate
        float forceSum = 0.0;
        float maxRead = 0.0;
        unsigned long currReadTime;
        unsigned long prevReadTime = 0;
        for (int forceIdx = 0; forceIdx < SAMP_LEN; forceIdx++)
        {
          // Output progress for fun
          // Every 20th of the readings (5%)
          if (forceIdx%(SAMP_LEN/20) == 0)
            mm.updateExtra(String(100*forceIdx/SAMP_LEN) + "%");
          // Burn time until the next sample
          do
          {
            currReadTime = millis();
          } while (currReadTime - prevReadTime < Ts);          

          // Read alanog pin
          float reading = analogRead(probePin);

          // Convert ADC value into Newtons (determined experimentally)
          if (reading < -pow(0.3045,2)/4/0.5169)
          {
            reading = -pow(0.3045,2)/4/0.5169;
          }
          reading = (-0.3045+sqrt(pow(0.3045,2)+4*0.5169*reading))/(2*0.5169);

          // Put individual reading in array
          forceData[forceindex] = reading;

          // Sum calculated for average later
          forceSum = forceSum + reading;
          // Check for peak force
          if (reading > maxRead)
            maxRead = reading;

          // Log old time and advance index
          prevReadTime = currReadTime;
        }

        // Calculate average force and convert from N to lbs and kg
        float forceAvg = (forceSum / 500);
        float forceAvglbs = forceAvg * 0.224808943871;
        float forceAvgkg = forceAvglbs * 0.453592;

        // Convert peak from N to lbs and kg
        float forcePk = maxRead;
        float forcePklbs = forcePk * 0.224808943871;
        float forcePkkg = forcePklbs * 0.453592;

        // Play end tone so patient knows they can stop squeezing
        tone(buzzerPin, endTone, 500);

        // Update menu manager's stats
        mm.setAvgKg(forceAvgkg);
        mm.setPkKg(forcePkkg);

        if (page == SESSION)
        {
          // Store data for write to SD
          int set = subPage;
          for (int i=0; i<SAMP_LEN; i++)
          {
            readings[i+SAMP_LEN*set] = forceData[i];
          }
          // Display stats by forcing redraw without button press
          mm.setLbs(false);  // Set kg before toggling
          mm.buttonPress(2);  // Press 3rd button for user
        }
        else if (page == MEAS)
        {
          // Nothing to save
          // Display stats by forcing redraw without button press
          mm.setLbs(false);  // Set kg before toggling
          mm.buttonPress(1);  // Press 3rd button for user
        }
      }

      lastPage = page;
    }

    // float reading = analogRead(probePin);
    // if (reading < -pow(0.3045,2)/4/0.5169)
    // {
    //   reading = -pow(0.3045,2)/4/0.5169;
    // }
    // reading = (-0.3045+sqrt(pow(0.3045,2)+4*0.5169*reading))/(2*0.5169);

    // lastResult = reading; // Convert to int and store for next itr

    // // Draw
    // String sReading = String(reading, 1); // One decimal place
    // String tail(" N");
    // mm.updateExtra(sReading + tail);
  }
}




// void updateState(int newState, int oldReading, int newReading, int oldUnit, int newUnit)
// {
//   endState(state, oldReading, oldUnit);
//   state = newState;
//   startState(state, newReading, newUnit);
// }

// void endState(int i, int reading, int unitSelect)
// {
//   if (state == 0)
//     draw.ClrMenu();
//   else if (state == 1)
//     draw.ClrPinchPrompt();
//   else if (state == 2)
//     draw.ClrPinchArea(0);
//   else if (state == 3)
//     draw.ClrResult(reading, unitSelect);
//   else if (state == 4)
//     draw.ClrProbe(10);
//   else
//     ClrStream();
// }

// void startState(int i, int reading, int unit)
// {
//   if (state == 0)
//     draw.DispMenu();
//   else if (state == 1)
//     draw.DispPinchPrompt();
//   else if (state == 2)
//     draw.DispPinchArea(i);
//   else if (state == 3)
//     draw.DispResult(reading, unit);
//   else if (state == 4)
//     draw.DispProbe(10);
//   else
//     DispStream();
// }

