#pragma once
#include "Item.h"

class Character;

class ItemEffect
{
public:
	int m_time;
	EffectManager* m_effectManagerbuf[3];
	EffectManager* m_effectManager;
public:
	/// <summary>
	/// アイテムの効果処理のクラス
	/// </summary>
	ItemEffect();
	virtual ~ItemEffect();
public:
	// 更新処理(効果の処理)
	virtual void Update(const DX::StepTimer & stepTimer, Character* chara) = 0;
	void Render(bool selectFlag);
	void SetEffectManager(EffectManager* effectManager0, EffectManager* effectManager1, EffectManager* effectManager2)
	{
		m_effectManagerbuf[0] = effectManager0;
		m_effectManagerbuf[1] = effectManager1;
		m_effectManagerbuf[2] = effectManager2;
	}
	virtual ItemEffect* Clone() = 0;
protected:
	// 速度を上げる効果処理
	void UpSpeed(Character* chara);
	// 速度を上げる効果処理
	void DownSpeed(Character* chara);
	// Funの効果処理(速度を下げる)
	void Fun(Character* chara);
};