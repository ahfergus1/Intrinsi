//Draw.h

#ifndef Draw_h
#define Draw_h
#include "Arduino.h"

class Draw
{
public:
  void init(); // Start display driver
  // void logo(); // Display IntrinsiForce Center of Screen
  void menu(uint16_t colour); // Display Main Menu
  void pinchPrompt(uint16_t colour); // Display ready to pinch
  void pinchArea(int idx, uint16_t colour); // Display which fingers to pinch together
  void measurePrompt(uint16_t colour); // Display prompt to pinch
  void uploadPrompt(uint16_t colour); // Display frozen warning
  //void result(int a, int u); //Display number a, u selects unit (1 - N, else lbf)
  void sessionReading(String s, uint16_t colour); // Displays "%s" below prompt to pinch
  void probe(int b, uint16_t colour); //show probe reading
  // void startTone();//Play tone when starting
  // void endTone();//Play tone when done
private:
  int centerX(int len);
  void centerStr(int y, const char* str, uint16_t colour);
};

#endif
