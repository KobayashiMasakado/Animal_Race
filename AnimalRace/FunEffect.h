#pragma once

#include "ItemEffect.h"

class FunEffect : public ItemEffect
{
public:
	//コンストラクタ
	FunEffect();
	//デストラクタ
	~FunEffect();
public:
	//更新
	void Update(const DX::StepTimer & stepTimer, Character* chara) override;
	ItemEffect* Clone() override
	{
		return new FunEffect(*this);
	}
};