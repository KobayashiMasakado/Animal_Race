#include "pch.h"
#include "Player.h"
#include "LeftSideCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void LeftSideCommand::execute(Player * actor)
{
	//��]���擾
	Vector3 upDir = Vector3::Transform(Vector3(0.0f, 1.0f, 0.0f), actor->GetRotation());
	//��]���x���擾
	Vector3 dirSpeed = actor->GetDirV();
	//���ɐ��񂷂�
	Quaternion dir = actor->GetRotation() * Quaternion::CreateFromAxisAngle(upDir, XMConvertToRadians(dirSpeed.y));
	//��]���x��Ԃ�
	actor->SetRotation(dir);
}