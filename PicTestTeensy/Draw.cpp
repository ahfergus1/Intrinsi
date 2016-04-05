//Draw.cpp
#include "Arduino.h"
#include "Draw.h"
#include <LCD.h>
#include <SD.h>
#include <SPI.h>
#include <Streaming.h>

void Draw::DispLogo()
{
  Tft.lcd_display_string(68, 145, (const uint8_t *)"IntrinsiForce", FONT_1608, MAGENTA);
  delay(2000);
  Tft.lcd_display_string(68, 145, (const uint8_t *)"IntrinsiForce", FONT_1608, WHITE);
}

void Draw::DispMenu()
{
  Tft.lcd_display_string(80,  75, (const uint8_t *)"Menu", FONT_1608, MAGENTA);
  Tft.lcd_display_string(25,  90, (const uint8_t *)"------------------------", FONT_1608, MAGENTA);
  Tft.lcd_display_string(35, 105, (const uint8_t *)"1. New Session", FONT_1608, MAGENTA);
  Tft.lcd_display_string(35, 120, (const uint8_t *)"2. Session History", FONT_1608, MAGENTA);
  Tft.lcd_display_string(35, 135, (const uint8_t *)"3. New Patient", FONT_1608, MAGENTA);
  Tft.lcd_display_string(35, 150, (const uint8_t *)"4. Probe Calibration", FONT_1608, MAGENTA);
  Tft.lcd_display_string(35, 165, (const uint8_t *)"5. Bluetooth Streamer", FONT_1608, MAGENTA);
  Tft.lcd_display_string(25, 180, (const uint8_t *)"------------------------", FONT_1608, MAGENTA);
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
Tft.lcd_display_string(40, 140, (const uint8_t *)"Please Squeeze Probe", FONT_1608, MAGENTA);
}
 
void Draw::ClrPinchPrompt()
{
Tft.lcd_display_string(40, 140, (const uint8_t *)"Please Squeeze Probe", FONT_1608, WHITE);
}

void Draw::DispPinchArea(int x){
if (x == 0){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Little & Ring Finger", FONT_1608, MAGENTA);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, MAGENTA);
}
if (x == 1){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Ring & Middle Finger", FONT_1608, MAGENTA);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, MAGENTA);
}
if (x == 2){
Tft.lcd_display_string(0, 155, (const uint8_t *)"Between Middle & Index Finger", FONT_1608, MAGENTA);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, MAGENTA);
}
if (x == 3){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Index Finger & Thumb", FONT_1608, MAGENTA);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, MAGENTA);
}
if (x == 4){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Thumb & Index Finger", FONT_1608, MAGENTA);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, MAGENTA);
}
if (x == 5){
Tft.lcd_display_string(0, 155, (const uint8_t *)"Between Index & Middle Finger", FONT_1608, MAGENTA);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, MAGENTA);
}
if (x == 6){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Middle & Ring Finger", FONT_1608, MAGENTA);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, MAGENTA);
}
if (x == 7){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Ring & Little Finger", FONT_1608, MAGENTA);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, MAGENTA);
}
if (x == 8){
Tft.lcd_display_string(30, 155, (const uint8_t *)"Between Your Thumbs", FONT_1608, MAGENTA);
Tft.lcd_display_string(70, 170, (const uint8_t *)"On Both Hands", FONT_1608, MAGENTA);
}
if (x == 9){
Tft.lcd_display_string(20, 155, (const uint8_t *)"Between Your Little Fingers", FONT_1608, MAGENTA);
Tft.lcd_display_string(70, 170, (const uint8_t *)"On Both Hands", FONT_1608, MAGENTA);
}
}

void Draw::ClrPinchArea(int x){
if (x == 0){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Little & Ring Finger", FONT_1608, WHITE);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, WHITE);
}
if (x == 1){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Ring & Middle Finger", FONT_1608, WHITE);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, WHITE);
}
if (x == 2){
Tft.lcd_display_string(0, 155, (const uint8_t *)"Between Middle & Index Finger", FONT_1608, WHITE);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, WHITE);
}
if (x == 3){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Index Finger & Thumb", FONT_1608, WHITE);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Left Hand", FONT_1608, WHITE);
}
if (x == 4){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Thumb & Index Finger", FONT_1608, WHITE);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, WHITE);
}
if (x == 5){
Tft.lcd_display_string(0, 155, (const uint8_t *)"Between Index & Middle Finger", FONT_1608, WHITE);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, WHITE);
}
if (x == 6){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Middle & Ring Finger", FONT_1608, WHITE);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, WHITE);
}
if (x == 7){
Tft.lcd_display_string(10, 155, (const uint8_t *)"Between Ring & Little Finger", FONT_1608, WHITE);
Tft.lcd_display_string(50, 170, (const uint8_t *)"On Your Right Hand", FONT_1608, WHITE);
}
if (x == 8){
Tft.lcd_display_string(30, 155, (const uint8_t *)"Between Your Thumbs", FONT_1608, WHITE);
Tft.lcd_display_string(70, 170, (const uint8_t *)"On Both Hands", FONT_1608, WHITE);
}
if (x == 9){
Tft.lcd_display_string(20, 155, (const uint8_t *)"Between Your Little Fingers", FONT_1608, WHITE);
Tft.lcd_display_string(70, 170, (const uint8_t *)"On Both Hands", FONT_1608, WHITE);
}
}

void Draw::DispResult(){ // sel to choose between previous and current measurement
 Tft.lcd_display_string(50, 105+15, (const uint8_t *)"Force Produced is", FONT_1608, MAGENTA);
 Tft.lcd_display_num(48, 120+15, 25, MAX_NLENGTH, FONT_1608, MAGENTA);
 Tft.lcd_display_string(90, 135+15, (const uint8_t *)"newtons", FONT_1608, MAGENTA);
}

void Draw::ClrResult(){ // sel to choose between previous and current measurement
 Tft.lcd_display_string(50, 105+15, (const uint8_t *)"Force Produced is", FONT_1608, WHITE);
 Tft.lcd_display_num(48, 120+15, 25, MAX_NLENGTH, FONT_1608, WHITE);
 Tft.lcd_display_string(90, 135+15, (const uint8_t *)"newtons", FONT_1608, WHITE);
}

void Draw::DispProbe(){
 Tft.lcd_display_string(50, 105+15, (const uint8_t *)"Probe reading is", FONT_1608, MAGENTA);
 Tft.lcd_display_num(48, 120+15, 25, MAX_NLENGTH, FONT_1608, MAGENTA);
}

void Draw::ClrProbe(){ 
 Tft.lcd_display_string(50, 105+15, (const uint8_t *)"Probe reading is", FONT_1608, WHITE);
 Tft.lcd_display_num(48, 120+15, 25, MAX_NLENGTH, FONT_1608, WHITE);
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

