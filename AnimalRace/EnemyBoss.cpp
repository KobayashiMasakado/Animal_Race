#include "pch.h"
#include "EnemyBoss.h"

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
EnemyBoss::EnemyBoss()
{
	m_targetElem = WARP_ZERO;
	m_itemCPUCheck = false;
	m_itemEffect = nullptr;
	//�����蔻��̐ݒ�
	m_sphere.r = 0.0f;
	m_sphere.center = Vector3(0, 0, 0);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBoss::~EnemyBoss()
{
	m_debug.reset();
}
/// <summary>
/// �X�V
/// </summary>
bool EnemyBoss::Update(const DX::StepTimer & stepTimer)
{
	//---AI�̏���(���̖ړI�n�܂ł̊p�x���v�Z����)---------
	// �ړI�n�ɓ���
	if (Collision::HitCheck_Sphere2Capsule(m_sphere, GetCollision()))
	{
		//�ړI�n��ύX����
		m_targetElem++;
		//���̖ړI�n������o��
		m_sphere.center = m_CPUPoint[m_targetElem % WARP_MAX];
	}
	//������n�_����ړI�n�܂ł̋��������߂�
	Vector3 targetVec = m_CPUPoint[m_targetElem % WARP_MAX] - m_position;
	//��L�̒l�𐳋K������
	targetVec.Normalize();
	//�E�̒l(�����j�����߂�
	Vector3 right = Vector3::Transform(Vector3::Right, m_rotation);
	//���ς����߂�
	float cosine = targetVec.Dot(right);
	//cosine��1�𒴂��Ȃ��悤�ɂ���
	if (cosine > 1.0f)
	{
		cosine = 1.0f;
	}
	//�p�x�����߂�
	float degree = XMConvertToDegrees(cosine);
	//��Βl�����߈��l�ȏ�ŉ�]����
	if (abs(degree) > 5.0f)
	{
		//���ʂ��獶�����Ɍ�������
		if (cosine > 0.0f)
		{
			Left();      // ���ɐ���
		}
		else
		{
			Right();     // �E�ɐ���
		}
	}
	//-----------------
	Character::Update(stepTimer);

	Vector3 vec = Vector3::Transform(m_vec, m_rotation);
	m_position += vec;
	return true;
}

void EnemyBoss::Render()
{
	Character::RenderEffect(true);
	if (m_game && m_model)
	{
		//���f���̕`��
		//��
		m_model->Draw(m_game->GetContext(), *m_game->GetState(),
			m_world, m_game->GetView(), m_game->GetProjection());
		//���[���h�s����쐬����
		m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);
		m_model->Draw(m_game->GetContext(), *m_game->GetState(), m_world, m_game->GetView(), m_game->GetProjection());
		//��
		static float rot = 0.0f;
		rot++;
		float r = XMConvertToRadians(25.0f) * sinf(XMConvertToRadians(rot*m_vec.z));
		Matrix world;
		switch (m_animalType)
		{
		case ANIMAL_TYPE::CARNIVORE:
			LegModelRender(world, r, Vector3(0, 1, 0));
			break;
		case ANIMAL_TYPE::HERBIVORE:
			LegModelRender(world, r, Vector3(0, 2, 0));
			break;
		case ANIMAL_TYPE::OMNIVOROUS:
			LegModelRender(world, r, Vector3(0, 2, 0));
			break;
		}
		world = Matrix::CreateScale(2.0f)*Matrix::CreateRotationX(0.0f)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (Vector3(0, 0.0f, 0)));
		m_shadow->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
	}
}

void EnemyBoss::Finalize()
{
}

void EnemyBoss::SetUpEffect()
{
	m_model->UpdateEffects([&](IEffect* effect)
	{
		auto lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			lights->SetPerPixelLighting(true);
		}
	});
}
//�����񂷂�
void EnemyBoss::Left()
{
	Vector3 up = Vector3::Transform(Vector3::Up, m_rotation);
	m_rotation *= Quaternion::CreateFromAxisAngle(up, XMConvertToRadians(10.0f));

}
//�E���񂷂�
void EnemyBoss::Right()
{
	Vector3 up = Vector3::Transform(Vector3::Up, m_rotation);
	m_rotation *= Quaternion::CreateFromAxisAngle(up, XMConvertToRadians(-10.0f));
}

void EnemyBoss::LegModelRender(DirectX::SimpleMath::Matrix& world, float r, DirectX::SimpleMath::Vector3 posdif)
{
	//����
	world = Matrix::CreateRotationX(r)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (posdif));
	m_modelLegL->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
	//�E��
	world = Matrix::CreateRotationX(-r)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (posdif));
	m_modelLegR->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
}
