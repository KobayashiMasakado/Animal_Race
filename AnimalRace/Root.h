#pragma once
///------------------------------------------- 
/// Root.h
/// 
/// ルートを司るクラス
/// Day.7/5
/// MasakadoKobayashi
///------------------------------------------- 
#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"
#include "Player.h"
#include "Enemy.h"

class Root : public CollisionCapsule
{
public:
	static const int ENEMY_HITCHECK_NUM = 16;
private:
	bool m_hitPlayerFlag;
	CollisionCapsule* m_outCose[ENEMY_HITCHECK_NUM];
public:
	//コンストラクタ
	Root();
	//デストラクタ
	~Root();
	//更新
	bool Update(const float elapsedTIme);
	//描画
	void Render();
	//エフェクトの設定関数
	void SetUpEffect();
	void Finalize();

	/*void NoOutMountein(CollisionCapsule* outCose);

	void NoOutPlayer(Player* player);*/
};