#pragma once
///------------------------------------------- 
/// Item.h
/// 
/// アイテム司るクラス
/// Day.7/5
/// Masakado Kobayashi
///------------------------------------------- 
#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"
#include "EffectManager.h"

// 前方宣言
class EffectManager;
class ItemEffect;

class Item : public CollisionCapsule
{
public:
	static const int ITEM_SET_NUM = 2;

private:
	ItemEffect* m_itemEffect;
public:
	//コンストラクタ
	Item(ItemEffect* itemEffect);
	//デストラクタ
	virtual ~Item();
	// 初期化
	virtual void Initialize() = 0;
	//更新
	virtual bool Update(const float elapsedTIme) = 0;
	//描画
	virtual void Render() = 0;
	//エフェクトの設定関数
	void SetUpEffect();
	//	セッター
	void SetEffectManager(EffectManager* effectManager0, EffectManager* effectManager1, EffectManager* effectManager2);
	ItemEffect* CreateItemEffect();
};
