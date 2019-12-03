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
		// 効果が切れた時の処理
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
		// エフェクト
		if (m_effectManager != nullptr)
		{
			m_effectManager->Update(stepTimer);
		}
	}
	// 効果時間を進める
	m_time--;
}
