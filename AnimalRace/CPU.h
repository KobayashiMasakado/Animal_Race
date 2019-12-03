#pragma once
///-------------------------------------------- 
/// CPU.h
/// 
/// 敵を司るクラス
/// Masakado Kobayashi
///-------------------------------------------
#include "EnemyBoss.h"

class CPU : public EnemyBoss
{
public:
	//コンストラクタ
	CPU();
	//デストラクタ
	~CPU();

	//CPU作成
	void CPUCreate();

	void Finalize();

	//前進
	void MoveFront();
	
	//プレイヤーキャラの違い
	void CPUAnimalType();
};