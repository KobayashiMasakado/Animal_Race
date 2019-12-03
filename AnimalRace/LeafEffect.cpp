#include "pch.h"
#include "LeafEffect.h"
#include "Character.h"

LeafEffect::LeafEffect()
{
	m_time = 60;
}

LeafEffect::~LeafEffect()
{
}

void LeafEffect::Update(const DX::StepTimer & stepTimer, Character * chara)
{
	if (m_time < 0)
	{
		m_time = 0;
		// ���ʂ��؂ꂽ���̏���
	}
	else
	{
		switch (chara->GetAnimalType())
		{
		case ANIMAL_TYPE::HERBIVORE:
			UpSpeed(chara);
			break;
		case ANIMAL_TYPE::CARNIVORE:
			DownSpeed(chara);
			break;
		case ANIMAL_TYPE::OMNIVOROUS:
			UpSpeed(chara);
			break;
		}
		// �G�t�F�N�g
		if (m_effectManager != nullptr)
		{
			m_effectManager->Update(stepTimer);
		}
	}
	// ���ʎ��Ԃ�i�߂�
	m_time--;
}
