#include "DrawUtils.h"

// Define static members that couldn't be instantiated in header
unsigned char DrawUtils::__Gnbmp_image_offset = 0;
File DrawUtils::bmpFile;

uint16_t DrawUtils::read16(File f)
{
  uint16_t d;
  uint8_t b;
  b = f.read();
  d = f.read();
  d <<= 8;
  d |= b;
  return d;
}

uint32_t DrawUtils::read32(File f)
{
  uint32_t d;
  uint16_t b;

  b = read16(f);
  d = read16(f);
  d <<= 16;
  d |= b;
  return d;
}

void DrawUtils::bmpdraw(File f, int x, int y)
{
  bmpFile.seek(__Gnbmp_image_offset);

  uint8_t sdbuffer[BUFFPIXEL_X3];                 // 3 * pixels to buffer

  for (int i = 0; i < __Gnbmp_height; i++) {
    for (int j = 0; j < (240 / BUFFPIXEL); j++) {
      bmpFile.read(sdbuffer, BUFFPIXEL_X3);

      uint8_t buffidx = 0;
      int offset_x = j * BUFFPIXEL;
      unsigned int __color[BUFFPIXEL];

      for (int k = 0; k < BUFFPIXEL; k++) {
        __color[k] = sdbuffer[buffidx + 2] >> 3;                    // read
        __color[k] = __color[k] << 6 | (sdbuffer[buffidx + 1] >> 2); // green
        __color[k] = __color[k] << 5 | (sdbuffer[buffidx + 0] >> 3); // blue

        buffidx += 3;
      }

      Tft.lcd_set_cursor(offset_x, i);
      Tft.lcd_write_byte(0x22, LCD_CMD);
      __LCD_DC_SET();
      __LCD_CS_CLR();
      for (int m = 0; m < BUFFPIXEL; m ++) {
        __LCD_WRITE_BYTE(__color[m] >> 8);
        __LCD_WRITE_BYTE(__color[m] & 0xFF);
      }
      __LCD_CS_SET();
    }
  }
}

boolean DrawUtils::bmpReadHeader(File f)
{
  // read header
  // uint32_t tmp;
  // uint8_t bmpDepth;

  if (read16(f) != 0x4D42) {
    // magic bytes missing
    Serial.println("magic missing");
    return false;
  }

  // read & discard file size
  //tmp = read32(f);
  read32(f);

  // read and ignore creator bytes
  read32(f);

  __Gnbmp_image_offset = read32(f);

  // read & discard DIB header
  //tmp = read32(f);
  read32(f);

  int bmp_width = read32(f);
  int bmp_height = read32(f);

  if (bmp_width != __Gnbmp_width || bmp_height != __Gnbmp_height)  {   // if image is not 320x240, return false
    Serial.print("wrong size: ");
    Serial.print(bmp_width);
    Serial.print(" x ");
    Serial.println(bmp_height);
    return false;
  }

  if (read16(f) != 1)
  {  
    Serial.println("16 check");
    return false;
  }

  //bmpDepth = read16(f);
  read16(f);

  if (read32(f) != 0) {
    // compression not supported!
    Serial.println("compression");
    return false;
  }

  return true;
}

boolean DrawUtils::drawBmp(String pathname, int x, int y)
{
  // Attempt to open file
  bmpFile = SD.open(pathname.c_str());
  if (! bmpFile) {
    // TODO: Log failure elsewhere
    while (1)
      Serial.println("didnt find image");
  }

  // Verify header
  if (! bmpReadHeader(bmpFile)) {
    // TODO: Log failure
    Serial.println("bad bmp");
    return false;
  }

  // Draw
  bmpdraw(bmpFile, 0, 0);
  bmpFile.close();

  return true;
}

boolean DrawUtils::drawScreen(String pathname)
{
  return drawBmp(pathname, 0, 0);
}