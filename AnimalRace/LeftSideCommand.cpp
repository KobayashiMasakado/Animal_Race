#include "pch.h"
#include "Player.h"
#include "LeftSideCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void LeftSideCommand::execute(Player * actor)
{
	//回転を取得
	Vector3 upDir = Vector3::Transform(Vector3(0.0f, 1.0f, 0.0f), actor->GetRotation());
	//回転速度を取得
	Vector3 dirSpeed = actor->GetDirV();
	//左に旋回する
	Quaternion dir = actor->GetRotation() * Quaternion::CreateFromAxisAngle(upDir, XMConvertToRadians(dirSpeed.y));
	//回転速度を返す
	actor->SetRotation(dir);
}