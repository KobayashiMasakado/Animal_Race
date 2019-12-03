#pragma once

#include "ItemEffect.h"

class MeatEffect : public ItemEffect
{
public:
	//コンストラクタ
	MeatEffect();
	//デストラクタ
	~MeatEffect();
public:
	//更新
	void Update(const DX::StepTimer & stepTimer,Character* chara) override;

	ItemEffect* Clone() override
	{
		return new MeatEffect(*this);
	}
};