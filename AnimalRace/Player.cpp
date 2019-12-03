#include "pch.h"
#include "Player.h"
#include "Game.h"
#include "Item.h"
#include "ModelDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
	: m_effectManagerbuf{ nullptr }
{
	m_itemEffect = nullptr;
	m_y = 0;
	//���f���̍쐬
	m_accel = Vector3::Zero;
	m_dirS = Vector3::Zero;
	m_effectManager = m_effectManagerbuf;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
}
bool Player::Update(const DX::StepTimer & stepTimer)
{
	Character::Update(stepTimer);
	
	// ���C
	m_vec.z *= FRICTION;
	m_vec.x *= FRICTION;
	// ���W�̈ړ�
	Vector3 vec = Vector3::Transform(m_vec, m_rotation);
	m_position += vec;
	static float rot = 0.0f;
	rot++;
	float r = XMConvertToRadians(45.0f) * sinf(XMConvertToRadians(rot));
	//���s�ړ��s��
	Matrix trans = Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);
	return true;
}
/// <summary>
/// �`��
/// </summary>
void Player::Render()
{
	m_effectManager = m_effectManagerbuf;
	Character::RenderEffect(true);
	//���f���̕`��
	//��
	m_model->Draw(m_game->GetContext(), *m_game->GetState(),
		m_world, m_game->GetView(), m_game->GetProjection());
	//��
	static float rot = 0.0f;
	rot++;
	float r = XMConvertToRadians(25.0f) * sinf(XMConvertToRadians(rot*m_vec.z));
	Matrix world;
	switch (m_animalType)
	{
		//���H�̑�
	case ANIMAL_TYPE::CARNIVORE:
		LegModelRender(world, r, Vector3(0, 1, 0));
		break;
		//���H�̑�
	case ANIMAL_TYPE::HERBIVORE:
		LegModelRender(world, r, Vector3(0, 2, 0));
		break;
		//�G�H�̑�
	case ANIMAL_TYPE::OMNIVOROUS:
		LegModelRender(world, r, Vector3(0, 2, 0));
		break;
	}
	world = Matrix::CreateScale(2.0f)*Matrix::CreateRotationX(0.0f)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (Vector3(0, 0.0f, 0)));
	m_shadow->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
}

void Player::Finalize()
{
	delete m_sSelect;
}

//�v���C���[�𐶐�
void Player::PlayerCreate()
{
	Collision::Capsule capsulePlayer;
	SetPosition(Vector3(-95.0f, m_y, -10.0f));
	//�J�v�Z���^�̃R���W����������
	capsulePlayer.start = Vector3(0.3f, 0.0f, 0.2f); 		//���E���̒��S
	capsulePlayer.end = Vector3(0.3f, 3.0f, 0.2f); 		    //���E���̒��S
	capsulePlayer.r = 0.6f;							     	//���a
	SetCollision(capsulePlayer);
	ModelDate* modelDate = ModelDate::GetInstance();
	//���f���̍쐬
	switch (m_animalType)
	{
		//���H
	case ANIMAL_TYPE::CARNIVORE:
		m_model = modelDate->GetBodyCPU();        //����
		m_modelLegL = modelDate->GetLegLCPU();    //����
		m_modelLegR = modelDate->GetLegRCPU();    //�E��
		break;
		//���H
	case ANIMAL_TYPE::HERBIVORE:
		m_model = modelDate->GetBodyCPU2();       //����
		m_modelLegL = modelDate->GetLegLCPU2();	  //����
		m_modelLegR = modelDate->GetLegRCPU2();	  //�E��
		break;
		//�G�H
	case ANIMAL_TYPE::OMNIVOROUS:
		m_model = modelDate->GetPlayer();         //����
		m_modelLegL = modelDate->GetLegLPlayer(); //����
		m_modelLegR = modelDate->GetLegRPlayer(); //�E��
		break;
	}
	m_shadow = modelDate->GetShadow();
	SetUpEffect();
	//���[���h�s����쐬����
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);
}

void Player::EffectRender()
{
	m_effectManager->Render(false);
}

void Player::OutCose()
{
	m_vec.z -= 2.0f;
}
/// <summary>
/// �v���C���[�̑���
/// </summary>
void Player::PlayerCommand()
{
	std::list<Command*> command = m_inputHandle.HandleInput();
	for (std::list<Command*>::iterator ite = command.begin(); ite != command.end(); ite++)
	{
		(*ite)->execute(this);
	}
}
/// <summary>
/// �v���C���[�L�����̈Ⴂ
/// </summary>
void Player::PlayerAnimalType()
{
	switch (m_animalType)
	{
		//���H
	case ANIMAL_TYPE::CARNIVORE:
		m_accel = Vector3(0, 0, 0.1f);
		m_dirS.y = 2.0f;
		break;
		//���H
	case ANIMAL_TYPE::HERBIVORE:
		m_accel = Vector3(0, 0, 0.4f);
		m_dirS.y = 0.9f;
		break;
		//�G�H
	case ANIMAL_TYPE::OMNIVOROUS:
		m_accel = Vector3(0, 0, 0.2f);
		m_dirS.y = 1.1f;
		break;
	}
}
//���̃��f���̕`��
void Player::LegModelRender(Matrix& world, float r, Vector3 posdif)
{
	//����
	world = Matrix::CreateRotationX(r)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (posdif));
	m_modelLegL->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
	//�E��
	world = Matrix::CreateRotationX(-r)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (posdif));
	m_modelLegR->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
}

void Player::EffectUpdate(const DX::StepTimer& stepTimer)
{
	m_effectManager->Update(stepTimer);
}

void Player::SetUpEffect()
{
	m_model->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ���C�g�̉e�����Ȃ���
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false);
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// �G�~�b�V�����F�𔒂ɐݒ肷�� 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
}
