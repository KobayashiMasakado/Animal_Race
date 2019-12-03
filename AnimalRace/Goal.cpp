#include "pch.h"
#include "Goal.h"

#include <Effects.h> 
#include <PrimitiveBatch.h>
#include <VertexTypes.h> 
#include <SimpleMath.h>
#include "Game.h"

#include "ModelDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Goal::Goal()
{
}

Goal::~Goal()
{
}

bool Goal::Update(const float elapsedTIme)
{
	//���[���h�s����쐬����
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}

void Goal::Render()
{
	if (m_game && m_model)
	{
		//���f���̕`��
		m_model->Draw(m_game->GetContext(),
			*m_game->GetState(),
			m_world, m_game->GetView(),
			m_game->GetProjection());
		//�f�o�b�O�p�R���W�������f���̕`��
		DrawCollision();
	}
}

void Goal::SetUpEffect()
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

//�S�[���쐬
void Goal::GoalCreate(int goal)
{
	Collision::Capsule capsule;
	ModelDate* modelDate = ModelDate::GetInstance();
	capsule.r = 0.6f;
	// �J�v�Z���^�̃R���W����������
	switch (goal)
	{
	case 0:
		SetPosition(Vector3(-105.0f, 0, 0.0f));
		capsule.start = Vector3(12.0f, 0.0f, 0.0f);           //���E���̒��S
		capsule.end  = Vector3(-12.0f, 0.0f, 0.0f);		    //���E���̒��S
		break;
	case 1:
		SetPosition(Vector3(10, 10, 100.0f));
		capsule.start = Vector3(0.0f, 0.0f, 12.0f);           //���E���̒��S
		capsule.end  = Vector3(0.0f, 0.0f, -12.0f);		    //���E���̒��S
		break;
	case 2:
		SetPosition(Vector3(115.0f, 0, 0.0f));
		capsule.start = Vector3(12.0f, 0.0f, 0.0f);           //���E���̒��S
		capsule.end  = Vector3(-12.0f, 0.0f, 0.0f);		    //���E���̒��S
		break;
	case 3:
		SetPosition(Vector3(-5.0f, 0, -40));
		capsule.start = Vector3(12.0f, 0.0f, 0.0f);           //���E���̒��S
		capsule.end  = Vector3(-12.0f, 0.0f, 0.0f);		    //���E���̒��S
		break;
	case 4:
		SetPosition(Vector3(-32.0f, 10, -30));
		capsule.start = Vector3(12.0f, 0.0f, 0.0f);           //���E���̒��S
		capsule.end  = Vector3(-12.0f, 0.0f, 0.0f);		    //���E���̒��S
		break;
	case 5:
		SetPosition(Vector3(-105.0f, 0, -12.0f));
		capsule.start = Vector3(12.0f, 0.0f, 0.0f);           //���E���̒��S
		capsule.end  = Vector3(-12.0f, 0.0f, 0.0f);		    //���E���̒��S
		break;
	}

	SetCollision(capsule);
}

