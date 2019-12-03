#pragma once
///------------------------------------------- 
/// Player.h
/// 
/// �v���C���[���i��N���X
/// Date.6/27
/// MasakadoKobayashi
///------------------------------------------- 
#include "pch.h"
#include "DeviceResources.h"
#include "SceneSelect.h"
#include "InputHandler.h"
#include "Character.h"
#include "Shadow.h"

class Item;

class Player : public Character
{
public:
	const float FRICTION = 0.9f;
private:
	int m_state;
	InputHandler m_inputHandle;
	float m_y;
	//�Z���N�g�V�[���őI�񂾓����̏����擾����
	SceneSelect* m_sSelect;
	//���f���̑�
	DirectX::Model* m_modelLegL;
	DirectX::Model* m_modelLegR;
	//���𓮂���
	DirectX::SimpleMath::Quaternion m_rot;

	DirectX::Model* m_shadow;
	EffectManager* m_effectManagerbuf;
	EffectManager* m_effectManager;

public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//�X�V
	bool Update(const DX::StepTimer& stepTimer);
	//�`��
	void Render();
	void Finalize();

	//�G�t�F�N�g�̐ݒ�֐�
	void SetUpEffect();
	void SetEffectManager(EffectManager* effectManagerbuf)
	{
		m_effectManagerbuf = effectManagerbuf;
	}
	// �A�C�e���̌���
	void SetItemEffect(ItemEffect* itemEffect)
	{
		if (m_itemEffect != nullptr)
		{
			delete m_itemEffect;
			m_itemEffect = nullptr;
		}
		m_itemEffect = itemEffect;
	}
	//�v���C���[�𐶐�
	void PlayerCreate();
	void OutCose();
	//�v���C���[�̑���
	void PlayerCommand();
	//�L�����N�^�[�̈Ⴂ
	void PlayerAnimalType();
	//���̃��f���̕`��
	void LegModelRender(DirectX::SimpleMath::Matrix& world, float r, DirectX::SimpleMath::Vector3 posdif);

	void EffectUpdate(const DX::StepTimer& stepTimer);
	void EffectRender();
};