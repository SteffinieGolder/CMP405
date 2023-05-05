#pragma once

struct InputCommands
{
	//Camera movement directional bools.
	bool forward;
	bool back;
	bool right;
	bool left;
	//Bool which controls if camera should rotate. 
	bool rotate;
	//Current and previous mouse positions.
	int mousePosX;
	int prevMouseX;
	int mousePosY;
	int prevMouseY;
	//Bool which signals if right mouse button is down.
	bool mouse_LB_Down;
	//Bool which controls if camera should focus on selected object.
	bool focusOnSelected;
	//Bool which signals if one vs multiple objects have been selected. 
	bool selectMultiple;
};
