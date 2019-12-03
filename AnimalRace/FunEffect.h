#pragma once

#include "ItemEffect.h"

class FunEffect : public ItemEffect
{
public:
	//�R���X�g���N�^
	FunEffect();
	//�f�X�g���N�^
	~FunEffect();
public:
	//�X�V
	void Update(const DX::StepTimer & stepTimer, Character* chara) override;
	ItemEffect* Clone() override
	{
		return new FunEffect(*this);
	}
};