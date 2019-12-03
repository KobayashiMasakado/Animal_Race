#include "pch.h"
#include "Player.h"
#include "LeftSideCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void LeftSideCommand::execute(Player * actor)
{
	//‰ñ“]‚ðŽæ“¾
	Vector3 upDir = Vector3::Transform(Vector3(0.0f, 1.0f, 0.0f), actor->GetRotation());
	//‰ñ“]‘¬“x‚ðŽæ“¾
	Vector3 dirSpeed = actor->GetDirV();
	//¶‚Éù‰ñ‚·‚é
	Quaternion dir = actor->GetRotation() * Quaternion::CreateFromAxisAngle(upDir, XMConvertToRadians(dirSpeed.y));
	//‰ñ“]‘¬“x‚ð•Ô‚·
	actor->SetRotation(dir);
}