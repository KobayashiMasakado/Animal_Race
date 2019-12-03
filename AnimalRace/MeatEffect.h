#pragma once

#include "ItemEffect.h"

class MeatEffect : public ItemEffect
{
public:
	//�R���X�g���N�^
	MeatEffect();
	//�f�X�g���N�^
	~MeatEffect();
public:
	//�X�V
	void Update(const DX::StepTimer & stepTimer,Character* chara) override;

	ItemEffect* Clone() override
	{
		return new MeatEffect(*this);
	}
};