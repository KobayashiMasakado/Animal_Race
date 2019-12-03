#include "pch.h"
#include "Player.h"
#include "FrontCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void FrontCommand::execute(Player * actor)
{
    //�ړ����x���擾
	Vector3 vec = actor->GetVec();
	Vector3 accel = actor->GetAccel();
	//���x�ɃA�N�Z�������Ĉړ�����
	if (vec.z < 0.5f)
	{
		vec.z += accel.z;
	}
	//�ړ����x��Ԃ�
	actor->SetVec(vec);
}