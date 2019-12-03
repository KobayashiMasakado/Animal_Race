#include "pch.h"
#include "MeatEffect.h"
#include "Character.h"

MeatEffect::MeatEffect()
{
	m_time = 60;
}

MeatEffect::~MeatEffect()
{

}

void MeatEffect::Update(const DX::StepTimer & stepTimer,Character * chara)
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
			DownSpeed(chara);
			break;
		case ANIMAL_TYPE::CARNIVORE:
			UpSpeed(chara);
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
