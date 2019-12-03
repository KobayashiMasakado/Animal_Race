#include "pch.h"
#include "GameCamera.h"

class Character;

using namespace DirectX;
using namespace DirectX::SimpleMath;
GameCamera::GameCamera()
{
	//何も
}

void GameCamera::ChaseCamera(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Quaternion rot)
{
	Vector3 cameraPos = Vector3(0.0f, 5.0f, -20.0f); //カメラの固定する位置

	Matrix rotY = Matrix::CreateFromQuaternion(rot);
	cameraPos = Vector3::Transform(cameraPos, rotY);
	Vector3 target = pos;
	SetTarget(target);
	SetEye(target + cameraPos);
}

void GameCamera::ResultCamera(Vector3 pos, float rot)
{
	Vector3 cameraPos = Vector3(0.0f, 5.0f, -20.0f); //カメラの固定する位置
	cameraPos = Vector3::Transform(cameraPos, Quaternion::CreateFromAxisAngle(Vector3::Up,rot));
	Vector3 target = pos;
	SetTarget(target);
	SetEye(target + cameraPos);
}
