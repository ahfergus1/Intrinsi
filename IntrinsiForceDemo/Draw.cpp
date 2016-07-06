//Draw.cpp
#include "Arduino.h"
#include "Draw.h"
#include "HX8347D/LCD.h"  // LCD driver
#include <SD.h>
#include <SPI.h>

#define MAX_NLENGTH  10

void Draw::init()
{
  Tft.lcd_init();
}

// void Draw::logo()
// {
//   Tft.lcd_display_string(68, 145, (const uint8_t *)"IntrinsiForce", FONT_1608, BLACK);
//   delay(2000);
//   Tft.lcd_display_string(68, 145, (const uint8_t *)"IntrinsiForce", FONT_1608, WHITE);
// }

void Draw::menu(uint16_t colour)
{
  // Tft.lcd_display_string(80,  75, (const uint8_t *)"Menu", FONT_1608, colour);
  centerStr(75, "Main Menu", colour);
  // Tft.lcd_display_string(25,  90, (const uint8_t *)"------------------------", FONT_1608, colour);
  centerStr(90, "------------------------", colour);
  Tft.lcd_display_string(35, 105, (const uint8_t *)"1. New Session", FONT_1608, colour);
  Tft.lcd_display_string(35, 120, (const uint8_t *)"X. New Patient", FONT_1608, colour);
  Tft.lcd_display_string(35, 135, (const uint8_t *)"3. Measure", FONT_1608, colour);
  Tft.lcd_display_string(35, 150, (const uint8_t *)"X. Probe Calibration", FONT_1608, colour);
  Tft.lcd_display_string(35, 165, (const uint8_t *)"5. Upload", FONT_1608, colour);
  centerStr(180, "------------------------", colour);
}

void Draw::pinchPrompt(uint16_t colour)
{
  centerStr(45, "------------------------", colour);
  Tft.lcd_display_string(35, 60, (const uint8_t*)"1.", FONT_1608, colour);
  // Depends on subpage...
  Tft.lcd_display_string(35, 75, (const uint8_t*)"2.", FONT_1608, colour);
  centerStr(75, "Start", colour);
  Tft.lcd_display_string(35, 90, (const uint8_t*)"3.", FONT_1608, colour);
  centerStr(90, "Toggle Units", colour);
  Tft.lcd_display_string(35, 105, (const uint8_t*)"4.", FONT_1608, colour);
  centerStr(105, "Main Menu", colour);
  centerStr(120, "------------------------", colour);
  Tft.lcd_display_string(centerX(20), 150, (const uint8_t *)"Please Squeeze Probe", FONT_1608, colour);
}

void Draw::pinchArea(int idx, uint16_t colour) {
  if (idx != 9)
    centerStr(60, "Next", colour);
  else 
    centerStr(60, "Finish", colour);

  if (idx == 0) {
    centerStr(165, "Between Little & Ring Finger", colour);
    centerStr(180, "On Your Left Hand", colour);
  }
  if (idx == 1) {
    centerStr(165, "Between Ring & Middle Finger", colour);
    centerStr(180, "On Your Left Hand", colour);
  }
  if (idx == 2) {
    centerStr(165, "Between Middle & Index Finger", colour);
    centerStr(180, "On Your Left Hand", colour);
  }
  if (idx == 3) {
    centerStr(165, "Between Index Finger & Thumb", colour);
    centerStr(180, "On Your Left Hand", colour);
  }
  if (idx == 4) {
    centerStr(165, "Between Thumb & Index Finger", colour);
    centerStr(180, "On Your Right Hand", colour);
  }
  if (idx == 5) {
    centerStr(165, "Between Index & Middle Finger", colour);
    centerStr(180, "On Your Right Hand", colour);
  }
  if (idx == 6) {
    centerStr(165, "Between Middle & Ring Finger", colour);
    centerStr(180, "On Your Right Hand", colour);
  }
  if (idx == 7) {
    centerStr(165, "Between Ring & Little Finger", colour);
    centerStr(180, "On Your Right Hand", colour);
  }
  if (idx == 8) {
    centerStr(165, "Between Your Thumbs", colour);
    centerStr(180, "On Both Hands", colour);
  }
  if (idx == 9) {
    centerStr(165, "Between Your Little Fingers", colour);
    centerStr(180, "On Both Hands", colour);
  }
}

void Draw::measurePrompt(uint16_t colour)
{
  centerStr(45, "------------------------", colour);
  Tft.lcd_display_string(35, 60, (const uint8_t*)"1.", FONT_1608, colour);
  centerStr(60, "Start", colour);
  Tft.lcd_display_string(35, 75, (const uint8_t*)"2.", FONT_1608, colour);
  centerStr(75, "Toggle Units", colour);
  Tft.lcd_display_string(35, 90, (const uint8_t*)"3.", FONT_1608, colour);
  centerStr(90, "Main Menu", colour);
  centerStr(105, "------------------------", colour);
  Tft.lcd_display_string(centerX(20), 150, (const uint8_t *)"Please Squeeze Probe", FONT_1608, colour);
}

void Draw::uploadPrompt(uint16_t colour)
{
  centerStr(45, "------------------------", colour);
  centerStr(60, "Frozen when uploading", colour);
  Tft.lcd_display_string(35, 75, (const uint8_t*)"1.", FONT_1608, colour);
  centerStr(75, "Main Menu", colour);
  centerStr(90, "------------------------", colour);
}

// /* @function results
//  * @args: val - measurement in N, unit - 0 for N, other for lbf
//  */
// void Draw::result(int val, int unit, uint16_t colour) { // a displays number, unit switches btwn units
//   Tft.lcd_display_string(50, 105 + 15, (const uint8_t *)"Force Produced is", FONT_1608, colour);
//   if (unit == 0) {
//     Tft.lcd_display_num(52, 120 + 15, val, MAX_NLENGTH, FONT_1608, colour);
//     Tft.lcd_display_string(116, 135 + 15, (const uint8_t *)"N", FONT_1608, colour);
//   }
//   else
//   {
//     Tft.lcd_display_num(48, 120 + 15, val * 2.20462, MAX_NLENGTH, FONT_1608, colour);
//     Tft.lcd_display_string(90, 135 + 15, (const uint8_t *)"lbf", FONT_1608, colour);
//   }
// }

void Draw::sessionReading(String s, uint16_t colour)
{
  Tft.lcd_display_string(centerX(s.length()), 210, (uint8_t *)s.c_str(), FONT_1608, colour);
}

void Draw::probe(int b, uint16_t colour) {
  Tft.lcd_display_string(50, 105 + 15, (const uint8_t *)"Probe reading is", FONT_1608, colour);
  Tft.lcd_display_num(48, 120 + 15, b, MAX_NLENGTH, FONT_1608, colour);
}

// void Draw::startTone() {
//   tone(15, 1480, 500);// pin, melody, duration
//   noTone(15);
// }

// void Draw::endTone() {
//   tone(15, 1740, 500);// pin, melody, duration
//   noTone(15);
// }

int Draw::centerX(int len)
{
  // 240 pix wide
  // 120 / half
  // 8 pix / char
  // half of string on left
  return 240/2 - (8*len)/2;
}

void Draw::centerStr(int y, const char *str, uint16_t colour)
{
  Tft.lcd_display_string(centerX(strlen(str)), y, (const uint8_t*)str, FONT_1608, colour);
}
