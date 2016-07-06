/* MenuManager.h
 * Handles menu pages for the IntrinsiForce prototype.
 * @author Andrew Simpson, ahfergus1@gmail.com
 */

#ifndef _MENUMANAGER_H
#define _MENUMANAGER_H

#include "DrawManager.h"
#include "Screen.h"

class MenuManager
{
public:
  MenuManager();
  ~MenuManager();
  void begin();
  Action buttonPress(int btn);
  Page getPage();
  int  getSubPage();
  void setAvgKg(float avgKg);
  void setPkKg(float pkKg);
  void setLbs(bool lbs);
  void updateExtra(String extra);
  
private:
  Screen screens[5];
  int _screen;
  DrawManager _dMan;
  float _avgKg;
  float _pkKg;
  int _subScreen;
  bool _lbf;
  bool _measured;
};

#endif
