#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;
	bool rotate;
	int mousePosX;
	int prevMouseX;
	int mousePosY;
	int prevMouseY;
	bool mouse_LB_Down;
	bool focusOnSelected;

	/*bool rotRight;
	bool rotLeft;*/
};
