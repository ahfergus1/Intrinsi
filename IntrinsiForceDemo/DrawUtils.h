#ifndef _DRAWUTILS_H
#define _DRAWUTILS_H

#include <SD.h>
#include <SPI.h>
//#include <Streaming.h>
#include "Draw.h"
#include "HX8347D/LCD.h"

/*********************************************/
// This procedure reads a bitmap and draws it to the screen
// its sped up by reading many pixels worth of data at a time
// instead of just one pixel at a time. increading the buffer takes
// more RAM but makes the drawing a little faster. 20 pixels' worth
// is probably a good place

#define BUFFPIXEL       60                      // must be a divisor of 240 
#define BUFFPIXEL_X3    180                     // BUFFPIXELx3
#define MAX_BMP         10                      // bmp file num
#define FILENAME_LEN    20                      // max file name length

class DrawUtils
{
private:
  static const int __Gnbmp_height = 320;                 // bmp hight
  static const int __Gnbmp_width  = 240;                 // bmp width
  static unsigned char __Gnbmp_image_offset;        // offset
  // static int __Gnfile_num = 4;                           // num of file
  // static char __Gsbmp_files[4][FILENAME_LEN] =           // add file name here
  // {
  //   "Back.bmp",
  //   "BSend.bmp",
  //   "ClrSend.bmp",
  //   "Logo.bmp",
  // };

  static File bmpFile;

  /*********************************************/
  // These read data from the SD card file and convert them to big endian
  // (the data is stored in little endian format!)

  // LITTLE ENDIAN!
  static uint16_t read16(File f);

  // LITTLE ENDIAN!
  static uint32_t read32(File f);

  static void bmpdraw(File f, int x, int y);

  static boolean bmpReadHeader(File f);

public:
  static boolean drawBmp(String pathname, int x, int y);
  static boolean drawScreen(String pathname);

  // static void startUp() { // displays logo & loads background
  //   // for(unsigned char i=0; i<__Gnfile_num; i++) {
  //   bmpFile = SD.open(__Gsbmp_files[3]);
  //   if (! bmpFile) {
  //     Serial.println("didnt find image");
  //     while (1);
  //   }

  //   if (! bmpReadHeader(bmpFile)) {
  //     Serial.println("bad bmp");
  //     return;
  //   }
  //   bmpdraw(bmpFile, 0, 0);
  //   bmpFile.close();

  //   bmpFile = SD.open(__Gsbmp_files[0]);
  //   if (! bmpFile) {
  //     Serial.println("didnt find image");
  //     while (1);
  //   }

  //   if (! bmpReadHeader(bmpFile)) {
  //     Serial.println("bad bmp");
  //     return;
  //   }
  //   bmpdraw(bmpFile, 0, 0);
  //   bmpFile.close();
  // }

  // static void dispStream()
  // { // loads bluetooth stream picture
  //   bmpFile = SD.open(__Gsbmp_files[1]);
  //   if (! bmpFile) {
  //     Serial.println("didnt find image");
  //     while (1);
  //   }

  //   if (! bmpReadHeader(bmpFile)) {
  //     Serial.println("bad bmp");
  //     return;
  //   }
  //   bmpdraw(bmpFile, 0, 0);
  //   bmpFile.close();
  //   //delay(1000);
  // }

  // static void clrStream()
  // { // clears bluetooth stream picture
  //   bmpFile = SD.open(__Gsbmp_files[2]);
  //   if (! bmpFile) {
  //     Serial.println("didnt find image");
  //     while (1);
  //   }

  //   if (! bmpReadHeader(bmpFile)) {
  //     Serial.println("bad bmp");
  //     return;
  //   }
  //   bmpdraw(bmpFile, 0, 0);
  //   bmpFile.close();
  //   //delay(1000);
  // }
};

#endif
