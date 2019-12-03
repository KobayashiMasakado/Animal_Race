#pragma once

#include "Item.h"
#include "MeatEffect.h"

class Leaf : public Item
{
public:
	//コンストラクタ
	Leaf();
	//デストラクタ
	~Leaf();
public:
	// 初期化
	void Initialize() override;
	//更新
	bool Update(const float elapsedTIme) override;
	//描画
	void Render() override;
};