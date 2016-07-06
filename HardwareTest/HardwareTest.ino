unsigned int butt1Pin = 16;
unsigned int butt2Pin = 17;
unsigned int Ts = 10;   //measurment peroid
unsigned int treatTime = 5000;  //5 seconds
unsigned long treatStartTime = 0;
unsigned int prevReadTime = 0;
unsigned int currReadTime = 0;
unsigned int firstPress = 1;    //used to latch button press for unit select

bool butt1Press = true;
bool butt2Press = true;
bool treat = false;
//bool treatLoop  = false;
bool unitSelect = false;    //tracks which unit should be displayed

unsigned int maxRead = 0;

unsigned int probePin  = A9;
unsigned int buzzerPin = 15;

float forceData[500];     //hold individual data points
int forceindex = 0;

float forceAvg = 0;
float forcePk = 0;
float forceSum = 0;

float forceAvglbs = 0;
float forceAvgkg = 0;

float forcePklbs = 0;
float forcePkkg = 0;

unsigned int startTone = 1047;     //tone pitches
unsigned endTone = 1319;

float refV = 3.3 / 3.3;  //DAC values
float refV12Bit = 4095 * refV;

void setup()
{
  //initalize array with zeros
  for (int i = 0; i < 500; i++)
  {
    forceData[i] = 0;
  }

  pinMode(butt1Pin, INPUT_PULLUP);
  pinMode(butt2Pin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(115200);

  //setup dac for measurment circuit refrence voltage
  analogWriteResolution(12);
  analogWrite(A14, (int)refV12Bit);

  //******display setup stuff???

}

void loop()
{
  //treatment starts when user presses button 1 (leftmost button)
  butt1Press = digitalRead(butt1Pin);
  if (!butt1Press)
    treat = true;

  if (treat == true)
  {
    //set all measured values as 0 to start
    forceAvg = 0;
    forcePk = 0;
    forceAvglbs = 0;
    forceAvgkg = 0;
    forcePklbs = 0;
    forcePkkg = 0;
    forceSum = 0;
    maxRead = 0;

    //******display treatment start stuff???

    //play start tone to alter user to squeeze
    tone(buzzerPin, startTone, 500);

    //inside while loop 500 data points are collected at a fixed rate
    while (treat == true)
    {
      currReadTime = millis();
      if (currReadTime - prevReadTime > Ts)
      {
        float reading = analogRead(probePin);  //read alanog pin

        //correction formula to convert ADC value into Newtons (determined experimentally)
        if (reading < -pow(0.3045, 2) / 4 / 0.5169)
        {
          reading = -pow(0.3045, 2) / 4 / 0.5169;
        }
        reading = (-0.3045 + sqrt(pow(0.3045, 2) + 4 * 0.5169 * reading)) / (2 * 0.5169);

        forceData[forceindex] = reading;      //put individual reading in array

        forceSum = forceSum + forceData[forceindex];    //sum calculated for average later
        if (forceData[forceindex] > maxRead)    //check for peak force
          maxRead = forceData[forceindex];

        prevReadTime = currReadTime;
        forceindex++;
      }
      if (forceindex == 500)    //after 500 readings reset index and stop loop
      {
        forceindex = 0;
        treat = false;
      }
    }

    //calculate average force and convert from N to lbs and kg
    forceAvg = (forceSum / 500);
    forceAvglbs = forceAvg * 0.224808943871;
    forceAvgkg = forceAvglbs * 0.453592;

    //convert peak from N to lbs and kg
    forcePk = maxRead;
    forcePklbs = forcePk * 0.224808943871;
    forcePkkg = forcePklbs * 0.453592;

    //play end tone so paitent knows they can stop squeezing
    tone(buzzerPin, endTone, 500);

    //********send away data to SD card???

    //*******display values to screen
    Serial.print(forceAvglbs);
    Serial.print("\t");
    Serial.println(forcePklbs);
  }

  //when button 2 (second from left) is pressed it toggles units
  butt2Press = digitalRead(butt2Pin);
  if (butt2Press == false && firstPress == true) // Check if 2 is pressed and 1 is not
  {
    if (firstPress == true)    // firstpress used to latch button input so if held down units only switch once
    {                       // if you want an edge it should be done elsewhere
      if (unitSelect == true)
      {
        //*********display forceAvglbs forcePklbs

        Serial.print(forceAvglbs);
        Serial.print("\t");
        Serial.println(forcePklbs);
        unitSelect = false;
      }
      else if (unitSelect == false) // redundant for a boolean
      {
        //********display forceAvgkg forcePkkg

        Serial.print(forceAvgkg);
        Serial.print("\t");
        Serial.println(forcePkkg);
        unitSelect = true;
      }
    }
    firstPress = false;
  }
  else if (butt2Press) // if released reset edge flag
    firstPress = true;
}
