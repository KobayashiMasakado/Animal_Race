#include "pch.h"
#include "Character.h"
#include "ItemEffect.h"

Character::Character()
{
	m_itemEffect = nullptr;
	for (int i = 0; i < GOAL_NUM; i++)
	{
		m_charaCheckFlag[i] = false;
	}
}

Character::~Character()
{
	if (m_itemEffect != nullptr)
	{
		delete m_itemEffect;
		m_itemEffect = nullptr;
	}
}

bool Character::Update(const DX::StepTimer & stepTimer)
{
	if (m_itemEffect != nullptr)
	{
		m_itemEffect->Update(stepTimer, this);
	}
	return true;
}

void Character::RenderEffect(bool selectFlag)
{
	if (m_itemEffect != nullptr)
	{
		m_itemEffect->Render(selectFlag);
	}
}

void Character::Finalize()
{
	delete m_itemEffect;
}
//キャラがゴールしたら
bool Character::CharaGoal()
{
	for (int i = 0; i < GOAL_NUM; i++)
	{
		if (m_charaCheckFlag[i] == false)
		{
			return false;
		}
	}
	return true;
}
//ゴールのチェックポイント
void Character::CheckPoint(int num)
{
	if (num < 0) return;
	if (num > GOAL_NUM) return;
		m_charaCheckFlag[num] = true;
}
