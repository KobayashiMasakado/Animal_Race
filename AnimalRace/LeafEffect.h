#pragma once

#include "ItemEffect.h"

class LeafEffect : public ItemEffect
{
public:
	//コンストラクタ
	LeafEffect();
	//デストラクタ
	~LeafEffect();
public:
	//更新
	void Update(const DX::StepTimer & stepTimer, Character* chara) override;
	ItemEffect* Clone() override
	{
		return new LeafEffect(*this);
	}
};