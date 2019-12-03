#include "pch.h"
#include "Player.h"
#include "FrontCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void FrontCommand::execute(Player * actor)
{
    //移動速度を取得
	Vector3 vec = actor->GetVec();
	Vector3 accel = actor->GetAccel();
	//速度にアクセルを入れて移動する
	if (vec.z < 0.5f)
	{
		vec.z += accel.z;
	}
	//移動速度を返す
	actor->SetVec(vec);
}