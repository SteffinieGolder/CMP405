#include "Camera.h"
#include "InputCommands.h"

using namespace DirectX::SimpleMath;

Camera::Camera()
{
	//functional
	m_moveSpeed = 0.30f;
	m_camSensitivity = 0.2f;

	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;

	m_selectedObj = NULL;
}

Camera::~Camera()
{
}

void Camera::Update(DX::StepTimer const& timer)
{
	if (m_inputCommands->rotate && m_inputCommands->prevMouseX !=0 && m_inputCommands->prevMouseY !=0)
	{
		float xChange = m_inputCommands->mousePosX - m_inputCommands->prevMouseX;
		float yChange = m_inputCommands->mousePosY - m_inputCommands->prevMouseY;

		xChange *= m_camSensitivity;
		yChange *= m_camSensitivity;

		m_camOrientation.x -= yChange;
		m_camOrientation.y += xChange;

		if (m_camOrientation.x > 90.0f)
		{
			m_camOrientation.x = 90.0f;
		}

		if (m_camOrientation.x < -90.0f)
		{
			m_camOrientation.x = -90.0f;
		}
	}

	if (m_inputCommands->focusOnSelected && m_selectedObj)
	{
		float xChange = m_camPosition.x - m_selectedObj->m_position.x;
		float yChange = m_camPosition.y - m_selectedObj->m_position.y;
		float zChange = m_camPosition.z - m_selectedObj->m_position.z;

		xChange *= m_camSensitivity;
		yChange *= m_camSensitivity;
		zChange *= m_camSensitivity;

		float dist = sqrt(xChange * xChange + zChange * zChange);
		m_camOrientation.x = atan(yChange / dist);
		m_camOrientation.y = atan(xChange / zChange);
	}

	//create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = cos((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.y = sin((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.z = sin((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);

	m_camLookDirection.Normalize();
	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);

	//camera motion is on a plane, so kill the 7 component of the look direction
	Vector3 planarMotionVector = m_camLookDirection;
	planarMotionVector.y = 0.0;

	//process input and update stuff
	if (m_inputCommands->forward)
	{
		m_camPosition += m_camLookDirection * m_moveSpeed;
	}
	if (m_inputCommands->back)
	{
		m_camPosition -= m_camLookDirection * m_moveSpeed;
	}
	if (m_inputCommands->right)
	{
		m_camPosition += m_camRight * m_moveSpeed;
	}
	if (m_inputCommands->left)
	{
		m_camPosition -= m_camRight * m_moveSpeed;
	}

	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection;
	//apply camera vectors
	m_viewMatrix = Matrix::CreateLookAt(m_camPosition, m_camLookAt, Vector3::UnitY);

	if (m_inputCommands->focusOnSelected)
	{
		if (m_selectedObj)
		{
			DirectX::SimpleMath::Vector3 initialPos = m_camPosition;
			DirectX::SimpleMath::Vector3 focusPos;
			float distance = 1.5f;

			focusPos = initialPos + (m_selectedObj->m_position - m_camLookAt);
			focusPos += (focusPos - m_selectedObj->m_position) * distance;

			m_camPosition = DirectX::XMVectorLerp(initialPos, focusPos, 0.2f);
		}
	}

	if (m_camPosition.y < 1.0f)
	{
		m_camPosition.y = 1.0f;
	}
}

void Camera::SetInputCommand(InputCommands* input)
{
	m_inputCommands = input;
}

DirectX::SimpleMath::Matrix Camera::GetCameraViewMatrix()
{
	return m_viewMatrix;
}

DirectX::SimpleMath::Vector3 Camera::GetCameraPosition() 
{
	return m_camPosition;
}

void Camera::SetFocusObject(DisplayObject* selectedObject)
{
	m_selectedObj = selectedObject;
}
