/* MenuManager.cpp
 * Handles menu pages for the IntrinsiForce prototype.
 * @author Andrew Simpson, ahfergus1@gmail.com
 */

#include "MenuManager.h"
#include "Screen.h"

MenuManager::MenuManager()
{
  // Initialize screens
  ActionSet ac1(NEXT,NEXT,NEXT,NEXT,NEXT);
	screens[0] = Screen(BOOT,1,ac1);
  ActionSet ac2(NEXT,NONE,NEXT,NONE,NEXT);
  screens[1] = Screen(MAIN,1,ac2);
  ActionSet ac3(NEXT,STRT,DRAW,BACK,NONE);
  screens[2] = Screen(SESSION,10,ac3);
  ActionSet ac4(BACK,NONE,NONE,NONE,NONE);
  screens[3] = Screen(UPLOAD,1,ac4);
  ActionSet ac5(STRT,DRAW,BACK,NONE,NONE);
  screens[4] = Screen(MEAS,1,ac5);

  // Link screens
  for (int i=0; i<5; i++)
    screens[0].next[i] = 1;
  screens[1].next[0] = 2;
  screens[1].next[2] = 4;
  screens[1].next[4] = 3;
  screens[2].next[0] = 1;
  screens[2].back = 1;
  screens[3].back = 1;
  screens[4].back = 1;

  // Initialize other vars
  _screen = 0;
  _avgKg = 0.0;
  _pkKg = 0.0;
  _subScreen = 0;
  _lbf = true;
  _measured = false;
}

MenuManager::~MenuManager()
{

}

void MenuManager::begin()
{
  _dMan.begin();
}

Action MenuManager::buttonPress(int btn)
{
  Action act = screens[_screen].actions.set[btn];

  switch (act)
  {
  case NONE:
    // Do nothing
    break;
  case DRAW:
    // Redraw page
    if ((screens[_screen].type == SESSION || 
         screens[_screen].type == MEAS) &&
         _measured == true)
    {
      // Change units to whatever they're not
      _lbf = !_lbf;

      // Only print with one decimal place
      String reading;
      if (_lbf == true)
      {
        reading = "Avg: " + String(_avgKg*2.205,1) + 
                  " lb - Peak: " + String(_pkKg*2.205,1) +
                  " lb";
      }
      else
      {
        reading = "Avg: " + String(_avgKg,1) + 
                  " kg - Peak: " + String(_pkKg,1) +
                  " kg";
      }
      // Draw extra
      _dMan.updateExtra(reading);
    }
    break;
  case STRT:
    // More for caller
    if (screens[_screen].type == SESSION || 
        screens[_screen].type == MEAS)
    {
      // Raise flag that measurement has been taken
      _measured = true;
    }
    break;
  case NEXT:
    // Check if at end of subscreens
    if (_subScreen < screens[_screen].nSubScreen-1)
    {
      // Advance subscreen
      _subScreen++;
      // Draw page
      _dMan.drawPage(screens[_screen].type, _subScreen);
    }
    else
    {
      // Go to next page, redraw
      _subScreen = 0;
      _screen = screens[_screen].next[btn];
      // Draw page
      _dMan.drawPage(screens[_screen].type);
    }
    // Lower measured flag
    _measured = false;
    break;
  case BACK:
    // Go back, redraw
    _subScreen = 0;
    _screen = screens[_screen].back;
    // Lower measured flag
    _measured = false;
    // Draw page
    _dMan.drawPage(screens[_screen].type);
    break;
  // default:
  //   Serial.println("No case!");
  // No default to ensure every action has a case
  }
  // Let caller know what happened
  return act;
}

Page MenuManager::getPage()
{
  return screens[_screen].type;
}

int  MenuManager::getSubPage()
{
  return _subScreen;
}

void MenuManager::setAvgKg(float avgKg)
{
  _avgKg = avgKg;
}

void MenuManager::setPkKg(float pkKg)
{
  _pkKg = pkKg;
}

void MenuManager::setLbs(bool lbs)
{
  _lbf = lbs;
}

void MenuManager::updateExtra(String extra)
{
  _dMan.updateExtra(extra);
}