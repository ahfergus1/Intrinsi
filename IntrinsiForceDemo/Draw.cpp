//Draw.cpp
#include "Arduino.h"
#include "Draw.h"
#include <LCD.h>
#include <SD.h>
#include <SPI.h>

#define MAX_NLENGTH  10

void Draw::DispLogo()
{
  Tft.lcd_display_string(68, 145, (const uint8_t *)"IntrinsiForce", FONT_1608, BLACK);
  delay(2000);
  Tft.lcd_display_string(68, 145, (const uint8_t *)"IntrinsiForce", FONT_1608, WHITE);
}

void Draw::DispMenu()
{
  Tft.lcd_display_string(80,  75, (const uint8_t *)"Menu", FONT_1608, BLACK);
  Tft.lcd_display_string(25,  90, (const uint8_t *)"------------------------", FONT_1608, BLACK);
  Tft.lcd_display_string(35, 105, (const uint8_t *)"1. New Session", FONT_1608, BLACK);
  Tft.lcd_display_string(35, 120, (const uint8_t *)"2. Session History", FONT_1608, BLACK);
  Tft.lcd_display_string(35, 135, (const uint8_t *)"3. New Patient", FONT_1608, BLACK);
  Tft.lcd_display_string(35, 150, (const uint8_t *)"4. Probe Calibration", FONT_1608, BLACK);
  Tft.lcd_display_string(35, 165, (const uint8_t *)"5. Bluetooth Streamer", FONT_1608, BLACK);
  Tft.lcd_display_string(25, 180, (const uint8_t *)"------------------------", FONT_1608, BLACK);
}

void Draw::ClrMenu()
{
  Tft.lcd_display_string(80,  75, (const uint8_t *)"Menu", FONT_1608, WHITE);
  Tft.lcd_display_string(25,  90, (const uint8_t *)"------------------------", FONT_1608, WHITE);
  Tft.lcd_display_string(35, 105, (const uint8_t *)"1. New Session", FONT_1608, WHITE);
  Tft.lcd_display_string(35, 120, (const uint8_t *)"2. Session History", FONT_1608, WHITE);
  Tft.lcd_display_string(35, 135, (const uint8_t *)"3. New Patient", FONT_1608, WHITE);
  Tft.lcd_display_string(35, 150, (const uint8_t *)"4. Probe Calibration", FONT_1608, WHITE);
  Tft.lcd_display_string(35, 165, (const uint8_t *)"5. Bluetooth Streamer", FONT_1608, WHITE);
  Tft.lcd_display_string(25, 180, (const uint8_t *)"------------------------", FONT_1608, WHITE);
}

void Draw::DispPinchPrompt()
{
  Tft.lcd_display_string(40, 140, (const uint8_t *)"Please Squeeze Probe", FONT_1608, BLACK);
}

void Draw::ClrPinchPrompt()
{
  Tft.lcd_display_string(40, 140, (const uint8_t *)"Please Squeeze Probe", FONT_1608, WHITE);
}

void Draw::DispPinchArea(int x) {
  if (x == 0) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Little & Ring Finger", FONT_1608, BLACK);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, BLACK);
  }
  if (x == 1) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Ring & Middle Finger", FONT_1608, BLACK);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, BLACK);
  }
  if (x == 2) {
    Tft.lcd_display_string(0, 155, (const uint8_t *)"Between Middle & Index Finger", FONT_1608, BLACK);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, BLACK);
  }
  if (x == 3) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Index Finger & Thumb", FONT_1608, BLACK);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, BLACK);
  }
  if (x == 4) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Thumb & Index Finger", FONT_1608, BLACK);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, BLACK);
  }
  if (x == 5) {
    Tft.lcd_display_string(0, 155, (const uint8_t *)"Between Index & Middle Finger", FONT_1608, BLACK);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, BLACK);
  }
  if (x == 6) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Middle & Ring Finger", FONT_1608, BLACK);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, BLACK);
  }
  if (x == 7) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Ring & Little Finger", FONT_1608, BLACK);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, BLACK);
  }
  if (x == 8) {
    Tft.lcd_display_string(30, 155, (const uint8_t *)"Between Your Thumbs", FONT_1608, BLACK);
    Tft.lcd_display_string(70, 170, (const uint8_t *)"On Both Hands", FONT_1608, BLACK);
  }
  if (x == 9) {
    Tft.lcd_display_string(20, 155, (const uint8_t *)"Between Your Little Fingers", FONT_1608, BLACK);
    Tft.lcd_display_string(70, 170, (const uint8_t *)"On Both Hands", FONT_1608, BLACK);
  }
}

void Draw::ClrPinchArea(int x) {
  if (x == 0) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Little & Ring Finger", FONT_1608, WHITE);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, WHITE);
  }
  if (x == 1) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Ring & Middle Finger", FONT_1608, WHITE);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, WHITE);
  }
  if (x == 2) {
    Tft.lcd_display_string(0, 155, (const uint8_t *)"Between Middle & Index Finger", FONT_1608, WHITE);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, WHITE);
  }
  if (x == 3) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Index Finger & Thumb", FONT_1608, WHITE);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, WHITE);
  }
  if (x == 4) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Thumb & Index Finger", FONT_1608, WHITE);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, WHITE);
  }
  if (x == 5) {
    Tft.lcd_display_string(0, 155, (const uint8_t *)"Between Index & Middle Finger", FONT_1608, WHITE);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, WHITE);
  }
  if (x == 6) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Middle & Ring Finger", FONT_1608, WHITE);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, WHITE);
  }
  if (x == 7) {
    Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Ring & Little Finger", FONT_1608, WHITE);
    Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, WHITE);
  }
  if (x == 8) {
    Tft.lcd_display_string(30, 155, (const uint8_t *)"Between Your Thumbs", FONT_1608, WHITE);
    Tft.lcd_display_string(70, 170, (const uint8_t *)"On Both Hands", FONT_1608, WHITE);
  }
  if (x == 9) {
    Tft.lcd_display_string(20, 155, (const uint8_t *)"Between Your Little Fingers", FONT_1608, WHITE);
    Tft.lcd_display_string(70, 170, (const uint8_t *)"On Both Hands", FONT_1608, WHITE);
  }
}

void Draw::DispResult(int a, int u) { // a displays number, u switches btwn units
  Tft.lcd_display_string(50, 105 + 15, (const uint8_t *)"Force Produced is", FONT_1608, BLACK);
  if (u == 0) {
    Tft.lcd_display_num(52, 120 + 15, a, MAX_NLENGTH, FONT_1608, BLACK);
    Tft.lcd_display_string(116, 135 + 15, (const uint8_t *)"N", FONT_1608, BLACK);
  }
  else
  {
    Tft.lcd_display_num(48, 120 + 15, a * 2.20462, MAX_NLENGTH, FONT_1608, BLACK);
    Tft.lcd_display_string(90, 135 + 15, (const uint8_t *)"lbf", FONT_1608, BLACK);
  }
}

void Draw::ClrResult(int a, int u) { // a displays number, u switches btwn units
  Tft.lcd_display_string(50, 105 + 15, (const uint8_t *)"Force Produced is", FONT_1608, WHITE);
  if (u == 0) {
    Tft.lcd_display_num(52, 120 + 15, a, MAX_NLENGTH, FONT_1608, WHITE);
    Tft.lcd_display_string(116, 135 + 15, (const uint8_t *)"N", FONT_1608, WHITE);
  }
  else {
    Tft.lcd_display_num(48, 120 + 15, a * 2.20462, MAX_NLENGTH, FONT_1608, WHITE);
    Tft.lcd_display_string(90, 135 + 15, (const uint8_t *)"lbf", FONT_1608, WHITE);
  }
}

void Draw::DispProbe(int b) {
  Tft.lcd_display_string(50, 105 + 15, (const uint8_t *)"Probe reading is", FONT_1608, BLACK);
  Tft.lcd_display_num(48, 120 + 15, b, MAX_NLENGTH, FONT_1608, BLACK);
}

void Draw::ClrProbe(int b) {
  Tft.lcd_display_string(50, 105 + 15, (const uint8_t *)"Probe reading is", FONT_1608, WHITE);
  Tft.lcd_display_num(48, 120 + 15, b, MAX_NLENGTH, FONT_1608, WHITE);
}
void Draw::StartTone() {
  tone(15, 1480, 500);// pin, melody, duration
  noTone(15);
}
void Draw::EndTone() {
  tone(15, 1740, 500);// pin, melody, duration
  noTone(15);
}

//{
//  Tft.lcd_display_string(80,  75, (const uint8_t *)"Menu", FONT_1608, colour);
//  Tft.lcd_display_string(25,  90, (const uint8_t *)"------------------------", FONT_1608, colour);
//  Tft.lcd_display_string(35, 105, (const uint8_t *)"1. New Session", FONT_1608, colour);
//  Tft.lcd_display_string(35, 120, (const uint8_t *)"2. Session History", FONT_1608, colour);
//  Tft.lcd_display_string(35, 135, (const uint8_t *)"3. New Patient", FONT_1608, colour);
//  Tft.lcd_display_string(35, 150, (const uint8_t *)"4. Probe Calibration", FONT_1608, colour);
//  Tft.lcd_display_string(35, 165, (const uint8_t *)"5. Bluetooth Streamer", FONT_1608, colour);
//  Tft.lcd_display_string(25, 180, (const uint8_t *)"------------------------", FONT_1608, colour);
//}

