#pragma once
#include "Graphic.h"

class Camera
{
public:
	DirectX::XMMATRIX GetMatrix()const noexcept;
	void SpawnControlWindow() noexcept;
	void Reset() noexcept;
private:
	//control camera in space
	float r = 20.0f;
	float theta = 0.0f;//rotation around x
	float phi = 0.0f;//rotation around y

	//pitch yaw roll the camera
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
};