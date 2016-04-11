//Draw.h

#ifndef Draw_h
#define Draw_h
#include "Arduino.h"

class Draw
{
	public:
	void DispLogo(); // Display IntrinsiForce Center of Screen
	void DispMenu(); // Display Main Menu
	void ClrMenu(); // Clear the Menu
	void DispPinchPrompt(); // Display ready to pinch
	void ClrPinchPrompt(); // Clear ready to pinch
	void DispPinchArea(int x); // Display which fingers to pinch together
	void ClrPinchArea(int x); // clear which ....
	void DispResult(int a, int u); //Display number a, u selects unit (1 - N, else lbf)
	void ClrResult(int a, int u); //clear previous result
	void DispProbe(int b); //show probe reading
	void ClrProbe(int b); //clear probe reading
	void StartTone();//Play tone when starting
	void EndTone();//Play tone when done


//	private:
//	void DrawMenu(uint16_t colour);
};

#endif
