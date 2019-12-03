#include "pch.h"
#include "Player.h"
#include "RightSideCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void RightSideCommand::execute(Player * actor)
{
	//��]���擾
	Vector3 upDir = Vector3::Transform(Vector3(0.0f, 1.0f, 0.0f), actor->GetRotation());
	//��]���x���擾
	Vector3 dirSpeed = actor->GetDirV();
	//�E�ɐ��񂷂�
	Quaternion dir = actor->GetRotation() * Quaternion::CreateFromAxisAngle(upDir, XMConvertToRadians(-1.0f*dirSpeed.y));
	//��]���x��Ԃ�
	actor->SetRotation(dir);
}