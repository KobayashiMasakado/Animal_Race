#pragma once

//-------------------------
//File:	Radar.h
//
//Name:	
//Date:	2018/11/30
//-------------------------

//#include "Sprite2D.h"

#include "DeviceResources.h"

#include "Player.h"
#include "Enemy.h"

class Radar : public Obj3D
{
public:

	// コンストラクタ
	Radar();

	// 初期化
	void Initialize();

	// 描画
	void Render();
	//プレイヤーの設定関数
	void SetPlayer(Player* player) { m_player = player; };
	//敵の設定関数
	void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

private:
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;

	ID3D11Device* m_device;
	DX::DeviceResources* m_deviceResources;

	// レーダーのアイコンの位置
	const float RADAR_POS_X = 699.5f;
	const float RADAR_POS_Y = 100.5f;

	// レーダーに映る距離
	const float RADAR_SENSING_DISTANCE = 85.0f;

	// レーダーのテクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_radarTexture;

	// レーダーのプレイヤーのテクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_radarPlayerTexture;

	// レーダーの敵のテクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_radarEnemyTexture;

	// プレイヤーへのポインタ
	Player* m_player;

	// 敵へのポインタ
	Enemy* m_enemy;


};