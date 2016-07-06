/* Screen.h
 * Struct for screens for the IntrinsiForce prototype.
 * @author Andrew Simpson, ahfergus1@gmail.com
 */

#ifndef _SCREEN_H
#define _SCREEN_H

#include "Action.h"

enum Page
{
  BOOT,
  MAIN,
  SESSION,
  HISTORY,
  MEAS,
  CALIBRATION,
  UPLOAD
};

struct Screen
{
  Page type;
  ActionSet actions;
  int nSubScreen; // Number of subscreens
  int next[5];
  int back;

  Screen()
  {
    type = BOOT;
    nSubScreen = 1;
    for (int i = 0; i < 5; ++i)
    {
      next[i] = 0;
    }
    back = 0;
  }

  Screen(Page type, int nSubScreen, ActionSet ac) :
    actions(ac)
  {
    this->type = type;
    this->nSubScreen = nSubScreen;
    for (int i=0; i<5; i++)
      this->next[i] = 0;
    this->back = 0;
  }

  Screen& operator=(const Screen& other)
  {
    type = other.type;
    actions = other.actions;
    nSubScreen = other.nSubScreen;
    for (int i=0; i<5; i++)
      next[i] = other.next[i];
    back = other.back;
    return *this;
  }
};

#endif