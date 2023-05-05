#pragma once
#include "pch.h"
#include "StepTimer.h"
#include "InputCommands.h"
#include "DisplayObject.h"

/*Class for the camera functionality.
* Camera can rotate with mouse click and drag
* and focus on an object selected by the user.
*/

class Camera
{
public:
	Camera();
	~Camera();

	void Update(DX::StepTimer const& timer);

	void SetInputCommand(InputCommands* input);

	//Functions to return the camera view and position.
	DirectX::SimpleMath::Matrix GetCameraViewMatrix();
	DirectX::SimpleMath::Vector3 GetCameraPosition();
	//Function used by Game.cpp to pass in the selected Object to focus the camera on.
	void SetFocusObject(DisplayObject* selectedObject);

private:
	//Move speed and sensitivity values.
	float m_moveSpeed;
	float m_camSensitivity;

	//Camera vectors.
	DirectX::SimpleMath::Vector3 m_camPosition;
	DirectX::SimpleMath::Vector3 m_camOrientation;
	DirectX::SimpleMath::Vector3 m_camLookAt;
	DirectX::SimpleMath::Vector3 m_camLookDirection;
	DirectX::SimpleMath::Vector3 m_camRight;

	//Cam view matrix.
	DirectX::SimpleMath::Matrix m_viewMatrix;

	//Input commands.
	InputCommands* m_inputCommands;
	//Selected object reference. 
	DisplayObject* m_selectedObj;
};

