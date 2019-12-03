#pragma once

#include "Item.h"
#include "MeatEffect.h"

class Fun : public Item
{
public:
	//コンストラクタ
	Fun();
	//デストラクタ
	~Fun();
public:
	// 初期化
	void Initialize() override;
	//更新
	bool Update(const float elapsedTIme) override;
	//描画
	void Render() override;
};