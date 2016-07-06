/* Action.h
 * An action defines what a button does in the IntrinsiForce interface.
 * @author Andrew Simpson, @email ahfergus1@gmail.com
 */

#ifndef _ACTION_H
#define _ACTION_H

#define ACTION_SET_SIZE 5

enum Action
{
  NONE,  // Do nothing
  DRAW,  // Redraw entire page to be safe
  STRT,  // Start process for page
  NEXT,  // Go to next subpage (1st) or page (2nd)
  BACK   // Go "Back" - main menu usually
};

struct ActionSet
{
  Action set[ACTION_SET_SIZE];

  ActionSet()
  {
    for (int i = 0; i < ACTION_SET_SIZE; ++i)
    {
      set[i] = NONE;
    }
  }

  ActionSet(Action b1, Action b2, Action b3, Action b4, Action b5)
  {
    set[0] = b1;
    set[1] = b2;
    set[2] = b3;
    set[3] = b4;
    set[4] = b5;
  }

  ActionSet(const ActionSet& ac)
  {
    for (int i=0; i<ACTION_SET_SIZE; i++)
      this->set[i] = ac.set[i];
  }

  ActionSet& operator=(const ActionSet& other)
  {
    for (int i=0; i<ACTION_SET_SIZE; i++)
      set[i] = other.set[i];
    return *this;
  }
};

#endif
