#pragma once
///------------------------------------------- 
/// Player.h
/// 
/// プレイヤーを司るクラス
/// Date.6/27
/// MasakadoKobayashi
///------------------------------------------- 
#include "pch.h"
#include "DeviceResources.h"
#include "SceneSelect.h"
#include "InputHandler.h"
#include "Character.h"
#include "Shadow.h"

class Item;

class Player : public Character
{
public:
	const float FRICTION = 0.9f;
private:
	int m_state;
	InputHandler m_inputHandle;
	float m_y;
	//セレクトシーンで選んだ動物の情報を取得する
	SceneSelect* m_sSelect;
	//モデルの足
	DirectX::Model* m_modelLegL;
	DirectX::Model* m_modelLegR;
	//足を動かす
	DirectX::SimpleMath::Quaternion m_rot;

	DirectX::Model* m_shadow;
	EffectManager* m_effectManagerbuf;
	EffectManager* m_effectManager;

public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
	//更新
	bool Update(const DX::StepTimer& stepTimer);
	//描画
	void Render();
	void Finalize();

	//エフェクトの設定関数
	void SetUpEffect();
	void SetEffectManager(EffectManager* effectManagerbuf)
	{
		m_effectManagerbuf = effectManagerbuf;
	}
	// アイテムの効果
	void SetItemEffect(ItemEffect* itemEffect)
	{
		if (m_itemEffect != nullptr)
		{
			delete m_itemEffect;
			m_itemEffect = nullptr;
		}
		m_itemEffect = itemEffect;
	}
	//プレイヤーを生成
	void PlayerCreate();
	void OutCose();
	//プレイヤーの操作
	void PlayerCommand();
	//キャラクターの違い
	void PlayerAnimalType();
	//足のモデルの描画
	void LegModelRender(DirectX::SimpleMath::Matrix& world, float r, DirectX::SimpleMath::Vector3 posdif);

	void EffectUpdate(const DX::StepTimer& stepTimer);
	void EffectRender();
};