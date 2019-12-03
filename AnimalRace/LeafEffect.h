#pragma once

#include "ItemEffect.h"

class LeafEffect : public ItemEffect
{
public:
	//�R���X�g���N�^
	LeafEffect();
	//�f�X�g���N�^
	~LeafEffect();
public:
	//�X�V
	void Update(const DX::StepTimer & stepTimer, Character* chara) override;
	ItemEffect* Clone() override
	{
		return new LeafEffect(*this);
	}
};