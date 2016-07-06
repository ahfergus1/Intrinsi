/* DrawManager.cpp
 * Draws menu pages and data to screen for the IntrinsiForce prototype.
 * @author Andrew Simpson, ahfergus1@gmail.com
 */

#include "DrawManager.h"
//#include "LCD.h"
#include "DrawUtils.h"

DrawManager::DrawManager()
{
  // Draw BOOT page first
  this->page = BOOT;
  this->subPage = 0;
  this->extra = "";
  // Drawer does not need to be initialized
  // Can't draw yet in case SPI isn't initialized
}

DrawManager::~DrawManager()
{

}

void DrawManager::begin()
{
  drawer.init();
  _drawPage(BLACK);
  // drawPage(MAIN);
}

Page DrawManager::getPage()
{
  return this->page;
}

void DrawManager::drawPage(Page page)
{
  // Use other one
  drawPage(page, 0, "");
}

void DrawManager::drawPage(Page page, int subPage)
{
  drawPage(page, subPage, "");
}

void DrawManager::drawPage(Page page, const char* extra)
{
  drawPage(page, 0, String(extra));
}

void DrawManager::drawPage(Page page, String extra)
{
  // Use more complicated version
  drawPage(page, 0, extra);
}

void DrawManager::drawPage(Page page, int subPage, String extra)
{
  // Erase old page if needed
  if (this->page != page)
  {
    // Erase old page
    _drawPage(WHITE);
    this->page = page;
    this->subPage = subPage;
    this->extra = extra;
    _drawPage(BLACK);
  }
  else if (this->subPage != subPage)
  {
    // Update subpage
    _drawSubPage(WHITE);
    this->subPage = subPage;
    this->extra = extra;
    _drawSubPage(BLACK);
  }
  else
  {
    // Only update extra
    updateExtra(extra);
  }
}

void DrawManager::drawPage(Page page, int subPage, const char* extra)
{
  drawPage(page, subPage, String(extra));
}

void DrawManager::updateExtra(String extra)
{
  if (this->extra.compareTo(extra) != 0)
  {
    _drawExtra(WHITE);
    this->extra = extra;
    _drawExtra(BLACK);
  }
}

void DrawManager::updateExtra(const char *extra)
{
  updateExtra(String(extra));
}

void DrawManager::_drawPage(uint16_t colour)
{
  switch (page)
  {
  case BOOT:
    if (colour == BLACK)
      DrawUtils::drawScreen("Logo.bmp");
    else
      DrawUtils::drawScreen("Back.bmp");
    break;
  case MAIN:
    drawer.menu(colour);
    break;
  case SESSION:
    drawer.pinchPrompt(colour);
    break;
  case HISTORY:
    // TODO: Implement
    break;
  case MEAS:
    drawer.measurePrompt(colour);
    break;
  case CALIBRATION:
    // TODO: Implement
    break;
  case UPLOAD:
    if (colour == BLACK)
    {
      // Draw Bluetooth symbol
      DrawUtils::drawScreen("BSend.bmp");
      // Write text second
      drawer.uploadPrompt(colour);
    }
    else
    {
      // Erase Bluetooth symbol
      DrawUtils::drawScreen("ClrSend.bmp");
      // Probably not needed
      drawer.uploadPrompt(colour);
    }
    break;
  default:
    // Do nothing
    break;
  }
  _drawSubPage(colour);
}

void DrawManager::_drawSubPage(uint16_t colour)
{
  switch (page)
  {
  case SESSION:
    drawer.pinchArea(subPage, colour);
    break;
  default:
    // Do nothing
    break;
  }
  _drawExtra(colour);
}

void DrawManager::_drawExtra(uint16_t colour)
{
  switch (page)
  {
  case SESSION:
    drawer.sessionReading(extra, colour);
    break;
  case MEAS:
    drawer.sessionReading(extra, colour);
  default:
    // Do nothing
    break;
  }
}

// void DrawManager::erasePage(uint16_t colour)
// {
//   _drawPage(colour);
//   _drawSubPage(colour);
//   _drawExtra(colour);
// }

