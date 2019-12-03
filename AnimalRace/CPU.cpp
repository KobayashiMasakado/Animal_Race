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
/// �R���X�g���N�^
/// </summary>
CPU::CPU()
{
	
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CPU::~CPU()
{

}
/// <summary>
/// CPU�����
/// </summary>
void CPU::CPUCreate()
{
	Collision::Capsule capsuleCPU;

	m_startPos = Vector3(-110.0f, 0, -10.0f);
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

	// ���`�ړ����e�_�̍��W��ݒ肷��
	//�G�̈ړ�����ꏊ
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

//�O�i
void CPU::MoveFront()
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
void CPU::CPUAnimalType()
{
	switch (m_animalType)
	{
		//���H(�ړ����x�͑����A���񑬓x�͒x��)
	case ANIMAL_TYPE::HERBIVORE:
		m_accel = Vector3(0, 0, 0.1f);
		m_dirS.y = 0.8;
		break;
		//���H(�ړ����x�͒x���A���񑬓x�͑���)
	case ANIMAL_TYPE::CARNIVORE:
		m_accel = Vector3(0, 0, 0.8f);
		m_dirS.y = 2.0;
		break;
		//�G�H(�ړ����x�͕��ʁA���񑬓x�͕���)
	case ANIMAL_TYPE::OMNIVOROUS:
		m_accel = Vector3(0, 0, 0.1f);
		m_dirS.y = 1.0;
		break;
	}
}
