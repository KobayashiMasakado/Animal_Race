#include "pch.h"
#include "FunEffect.h"
#include "Character.h"

FunEffect::FunEffect()
{
	m_time = 10;
}

FunEffect::~FunEffect()
{
}

void FunEffect::Update(const DX::StepTimer & stepTimer, Character * chara)
{
	if (m_time < 0)
	{
		m_time = 0;
		// 効果が切れた時の処理
	}
	else
	{
		
		Fun(chara);
			
		// エフェクト
		if (m_effectManager != nullptr)
		{
			m_effectManager->Update(stepTimer);
		}
	}
	// 効果時間を進める
	m_time--;
}
