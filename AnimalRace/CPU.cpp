#include "pch.h"
#include "CPU.h"
#include <time.h>
#include "Game.h"
#include "ModelDate.h"
#include "Root.h"

#include<stdio.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
CPU::CPU()
{
	
}
/// <summary>
/// デストラクタ
/// </summary>
CPU::~CPU()
{

}
/// <summary>
/// CPUを作る
/// </summary>
void CPU::CPUCreate()
{
	Collision::Capsule capsuleCPU;

	m_startPos = Vector3(-110.0f, 0, -10.0f);
	SetPosition(m_startPos);

	// カプセル型のコリジョンをつける
	capsuleCPU.start = Vector3(0.3f, 0.0f, 0.2f);           //境界球の中心
	capsuleCPU.end = Vector3(0.3f, 3.0f, 0.2f);		        //境界球の中心
	capsuleCPU.r = 0.3f;                                    //半径
	SetCollision(capsuleCPU);
	ModelDate* modelDate = ModelDate::GetInstance();
	//モデルの作成
	switch (m_animalType)
	{
		//肉食
	case ANIMAL_TYPE::CARNIVORE:
		m_model = modelDate->GetBodyCPU();
		m_modelLegL = modelDate->GetLegLCPU();
		m_modelLegR = modelDate->GetLegRCPU();
		break;
		//草食
	case ANIMAL_TYPE::HERBIVORE:
		m_model = modelDate->GetBodyCPU2();
		m_modelLegL = modelDate->GetLegLCPU2();
		m_modelLegR = modelDate->GetLegRCPU2();
		break;
		//雑食
	case ANIMAL_TYPE::OMNIVOROUS:
		m_model = modelDate->GetPlayer();
		m_modelLegL = modelDate->GetLegLPlayer();
		m_modelLegR = modelDate->GetLegRPlayer();
		break;
	}
	m_shadow = modelDate->GetShadow();
	SetUpEffect();

	// 線形移動す各点の座標を設定する
	//敵の移動する場所
	{
		m_CPUPoint[0] = m_startPos;
		m_CPUPoint[1] = Vector3(-110.0f, 0, 70);
		m_CPUPoint[2] = Vector3(-95.0f, 0, 95);
		m_CPUPoint[3] = Vector3(-70.0f, 0, 105);
		m_CPUPoint[4] = Vector3(-5, 10, 105);
		m_CPUPoint[5] = Vector3(20, 10, 105);

		m_CPUPoint[6] = Vector3(80.0f, 0, 105.0f);
		m_CPUPoint[7] = Vector3(110, 0, 90);
		m_CPUPoint[8] = Vector3(120, 0, 70);
		m_CPUPoint[9] = Vector3(120, 0, -90);
		m_CPUPoint[10] = Vector3(95, 0, -125);

		m_CPUPoint[11] = Vector3(60, 0, -123);
		m_CPUPoint[12] = Vector3(0, 0, -60);
		m_CPUPoint[13] = Vector3(-5, 0, -15);
		m_CPUPoint[14] = Vector3(40, 0, 25);
		m_CPUPoint[15] = Vector3(40, 0, 45);

		m_CPUPoint[16] = Vector3(30, 0, 55);
		m_CPUPoint[17] = Vector3(-10, 0, 55);
		m_CPUPoint[18] = Vector3(-20, 0, 50);
		m_CPUPoint[19] = Vector3(-25, 0, 33);
		m_CPUPoint[20] = Vector3(-25, 11, -23);

		m_CPUPoint[21] = Vector3(-25, 11, -33);
		m_CPUPoint[22] = Vector3(-25, 0, -93);
		m_CPUPoint[23] = Vector3(-55, 0, -130);
		m_CPUPoint[24] = Vector3(-80, 0, -130);
		m_CPUPoint[25] = Vector3(-110, 0, -93);
	}

	m_sphere.r = 5.0f;
	m_sphere.center = m_CPUPoint[m_targetElem];
}

void CPU::Finalize()
{
}

//前進
void CPU::MoveFront()
{
	switch (m_animalType)
	{
		//肉食
	case ANIMAL_TYPE::HERBIVORE:
		m_vec.z = 0.5f;
		break;
		//草食
	case ANIMAL_TYPE::CARNIVORE:
		m_vec.z = 0.35f;
		break;
		//雑食
	case ANIMAL_TYPE::OMNIVOROUS:
		m_vec.z = 0.4f;
		break;
	}
}

//プレイヤーキャラの違い
void CPU::CPUAnimalType()
{
	switch (m_animalType)
	{
		//草食(移動速度は速い、旋回速度は遅い)
	case ANIMAL_TYPE::HERBIVORE:
		m_accel = Vector3(0, 0, 0.1f);
		m_dirS.y = 0.8;
		break;
		//肉食(移動速度は遅い、旋回速度は速い)
	case ANIMAL_TYPE::CARNIVORE:
		m_accel = Vector3(0, 0, 0.8f);
		m_dirS.y = 2.0;
		break;
		//雑食(移動速度は普通、旋回速度は普通)
	case ANIMAL_TYPE::OMNIVOROUS:
		m_accel = Vector3(0, 0, 0.1f);
		m_dirS.y = 1.0;
		break;
	}
}
