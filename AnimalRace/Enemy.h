#pragma once
///-------------------------------------------- 
/// Enemy.h
/// 
/// 敵を司るクラス
/// Masakado Kobayashi
///-------------------------------------------
#include "EnemyBoss.h" 

class Enemy : public EnemyBoss
{
public:
	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();
	
	//CPU作成
	void CPUCreate();

	void Finalize();
	
	//前進
	void MoveFront();
	
	//プレイヤーキャラの違い
	void EnemyAnimalType();
};