/* DrawManager.h
 * Draws menu pages and data to screen for the IntrinsiForce prototype.
 * @author Andrew Simpson, ahfergus1@gmail.com
 */

#ifndef _DRAWMANAGER_H
#define _DRAWMANAGER_H

#include "Draw.h"
#include "Screen.h"

class DrawManager
{
public:
  DrawManager();
  ~DrawManager();
  void begin();
  Page getPage();
  void drawPage(Page page);
  void drawPage(Page page, int subPage);
  void drawPage(Page page, String extra);
  void drawPage(Page page, const char* extra);
  void drawPage(Page page, int subPage, String extra);
  void drawPage(Page page, int subPage, const char* extra);
  void updateExtra(String extra);
  void updateExtra(const char* extra);

private:
  Page page;
  int subPage;
  String extra;
  Draw drawer;

  // Draws page, subPage, and extra
  void _drawPage(uint16_t colour);
  // Draws subPage and extra
  void _drawSubPage(uint16_t colour);
  // Draws extra
  void _drawExtra(uint16_t colour);
  // void _erasePage(uint16_t colour);
};

//extern DrawManager DM;

#endif