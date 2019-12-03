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
		// ���ʂ��؂ꂽ���̏���
	}
	else
	{
		
		Fun(chara);
			
		// �G�t�F�N�g
		if (m_effectManager != nullptr)
		{
			m_effectManager->Update(stepTimer);
		}
	}
	// ���ʎ��Ԃ�i�߂�
	m_time--;
}
