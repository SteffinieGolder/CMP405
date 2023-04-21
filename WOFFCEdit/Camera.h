#pragma once
#include "pch.h"
#include "StepTimer.h"
#include "InputCommands.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Update(DX::StepTimer const& timer);

	void SetInputCommand(InputCommands* input);

	DirectX::SimpleMath::Matrix GetCameraViewMatrix();
	DirectX::SimpleMath::Vector3 GetCameraPosition();

private:
	float m_moveSpeed;
	float m_camSensitivity;
	DirectX::SimpleMath::Vector3 m_camPosition;
	DirectX::SimpleMath::Vector3 m_camOrientation;
	DirectX::SimpleMath::Vector3 m_camLookAt;
	DirectX::SimpleMath::Vector3 m_camLookDirection;
	DirectX::SimpleMath::Vector3 m_camRight;

	DirectX::SimpleMath::Matrix m_viewMatrix;

	InputCommands* m_inputCommands;
};

