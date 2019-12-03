#include "pch.h"
#include "Enemy.h"
#include "Game.h"
#include <time.h>
#include "ModelDate.h"
#include "Root.h"

#include<stdio.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// �R���X�g���N�^
/// </summary>
Enemy::Enemy()
{
	
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
	
}

/// <summary>
/// CPU�����
/// </summary>
void Enemy::CPUCreate()
{
	Collision::Capsule capsuleCPU;
	//�����ʒu
	m_startPos = Vector3(-102.0f, 0, -10.0f);
	SetPosition(m_startPos);

	// �J�v�Z���^�̃R���W����������
	capsuleCPU.start = Vector3(0.3f, 0.0f, 0.2f);           //���E���̒��S
	capsuleCPU.end = Vector3(0.3f, 3.0f, 0.2f);		        //���E���̒��S
	capsuleCPU.r = 0.3f;                                    //���a
	SetCollision(capsuleCPU);
	ModelDate* modelDate = ModelDate::GetInstance();
	//���f���̍쐬
	switch (m_animalType)
	{
		//���H
	case ANIMAL_TYPE::CARNIVORE:
		m_model = modelDate->GetBodyCPU();
		m_modelLegL = modelDate->GetLegLCPU();
		m_modelLegR = modelDate->GetLegRCPU();
		break;
		//���H
	case ANIMAL_TYPE::HERBIVORE:
		m_model = modelDate->GetBodyCPU2();
		m_modelLegL = modelDate->GetLegLCPU2();
		m_modelLegR = modelDate->GetLegRCPU2();
		break;
		//�G�H
	case ANIMAL_TYPE::OMNIVOROUS:
		m_model = modelDate->GetPlayer();
		m_modelLegL = modelDate->GetLegLPlayer();
		m_modelLegR = modelDate->GetLegRPlayer();
		break;
	}
	m_shadow = modelDate->GetShadow();
	SetUpEffect();
	//���`�ړ����e�_�̍��W��ݒ肷��
	//�G�̈ړ�����ꏊ
	{
		m_CPUPoint[0] = m_startPos;
		m_CPUPoint[1] = Vector3(-102.0f, 0, 70);
		m_CPUPoint[2] = Vector3(-93.0f, 0, 93);
		m_CPUPoint[3] = Vector3(-70.0f, 0, 100);
		m_CPUPoint[4] = Vector3(-5, 10, 100);
		m_CPUPoint[5] = Vector3(20, 10, 100);
		
		m_CPUPoint[6] = Vector3(80.0f, 0, 100.0f);
		m_CPUPoint[7] = Vector3(102, 0, 90);
		m_CPUPoint[8] = Vector3(112, 0, 70);
		m_CPUPoint[9] = Vector3(112, 0, -90);
		m_CPUPoint[10] = Vector3(112, 0, -115);
		
		m_CPUPoint[11] = Vector3(60, 0, -118);
		m_CPUPoint[12] = Vector3(0, 0, -57);
		m_CPUPoint[13] = Vector3(-5, 0, -13);
		m_CPUPoint[14] = Vector3(40, 0, 35);
		m_CPUPoint[15] = Vector3(40, 0, 55);

		m_CPUPoint[16] = Vector3(30, 0, 65);
		m_CPUPoint[17] = Vector3(-10, 0, 55);
		m_CPUPoint[18] = Vector3(-24, 0, 50);
		m_CPUPoint[19] = Vector3(-27, 0, 33);
		m_CPUPoint[20] = Vector3(-27, 11, -23);

		m_CPUPoint[21] = Vector3(-27, 11, -33);
		m_CPUPoint[22] = Vector3(-27, 0, -93);
		m_CPUPoint[23] = Vector3(-57, 0, -130);
		m_CPUPoint[24] = Vector3(-78, 0, -130);
		m_CPUPoint[25] = Vector3(-102, 0, -93);
	}
	m_sphere.r = 5.0f;
	m_sphere.center = m_CPUPoint[m_targetElem];
}

void Enemy::Finalize()
{
}

//�O�i
void Enemy::MoveFront()
{
	switch (m_animalType)
	{
		//���H
	case ANIMAL_TYPE::HERBIVORE:
		m_vec.z = 0.5f;
		break;
		//���H
	case ANIMAL_TYPE::CARNIVORE:
		m_vec.z = 0.35f;
		break;
		//�G�H
	case ANIMAL_TYPE::OMNIVOROUS:
		m_vec.z = 0.4f;
		break;
	}
}

//�v���C���[�L�����̈Ⴂ
void Enemy::EnemyAnimalType()
{
	switch (m_animalType)
	{
		//���H(�ړ����x�͑����A���񑬓x�͒x��)
	case ANIMAL_TYPE::HERBIVORE:
		m_accel = Vector3(0, 0, 0.4f);
		m_dirS.y = 0.8;
		break;
		//���H(�ړ����x�͒x���A���񑬓x�͑���)
	case ANIMAL_TYPE::CARNIVORE:
		m_accel = Vector3(0, 0, 0.8f);
		m_dirS.y = 2.0;
		break;
		//�G�H(�ړ����x�͕��ʁA���񑬓x�͕���)
	case ANIMAL_TYPE::OMNIVOROUS:
		m_accel = Vector3(0, 0, 0.2f);
		m_dirS.y = 1.0;
		break;
	}
}
