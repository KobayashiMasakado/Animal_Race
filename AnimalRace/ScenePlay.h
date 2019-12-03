#pragma once

#include "SceneBase.h"
#include "Obj3D.h"
#include "CollisionCapsule.h"
#include "CollisionSphere.h"
#include "Player.h"
#include "Enemy.h"
#include "CPU.h"
#include "Item.h"
#include "Meat.h"
#include "Leaf.h"
#include "Fun.h"
#include "Root.h" 
#include "DebugCamera.h"
#include "GameCamera.h"
#include "TaskManager.h"
#include "CollisionMesh.h"
#include "Goal.h"
#include "ObjectCreate.h"
#include "Number.h"
#include "MyEffect.h"
#include "EffectManager.h"
#include "SceneSelect.h"
#include "Radar.h"
#include "ADX2Le.h"

class ScenePlay : public SceneBase
{
public:
	static const int ENEMY_HITCHECK_NUM = 16;
	static const int GOAL_SET_NUM = 6;
	static const int ITEM_SET_NUM = 2;
	static const int ITEM_MAX = 6;
	static const int TIME_SET_NUM = 3;
	static const int TIME_TYPE_NUM = 10;
	static const int GAME_START_TIME = 180;
	static const int TIME_MINUTE = 60;
	static const int TIME_MIRI = 100;
	static const int GOAL_CHARA = 3;
private:
	DX::StepTimer                           m_timer;
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;
	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;
	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	//3Dスプライト///////////////////////////////////////////
	//空
	std::unique_ptr<CollisionMesh> m_skydomeMesh;
	std::unique_ptr<DirectX::Model> m_skydome;
	// 草原
	std::unique_ptr<DirectX::Model> m_prairie;
	// 草原
	std::unique_ptr<DirectX::Model> m_courseWater;
	//プレイヤー
	Player* m_player;
	//CPU
	Enemy* m_cpu;
	CPU* m_cpuS;
	std::unique_ptr<CollisionCapsule> m_outCose[ENEMY_HITCHECK_NUM];
	std::unique_ptr<CollisionSphere>  m_skyCollision;
	std::unique_ptr<CollisionSphere>  m_courseWaterCollision;
	Root* m_root;
	//道のモデル
	std::unique_ptr<DirectX::Model> m_rootModel;
	//ゴールのモデル
	std::unique_ptr<DirectX::Model> m_goalModel;
	//ゴール
	std::unique_ptr<Goal> m_goal[GOAL_SET_NUM];
	Character* m_charaGoal;
	//アイテム
	std::unique_ptr<Item> m_item[ITEM_MAX];
	//アイテム描画
	bool m_itemDis;
	//2Dスプライト/////////////////////////////
	//テクスチャハンドル
	//制限時間
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTime;
	
	//GOAL!!
	//プレイヤー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPlayerGoal;
	//CPU
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCPUGoal;
	//CPU
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCPUSGoal;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tFlipGoal;;
	//カウントダウン
	//GO!
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCGo;
	//:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCComma;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCCommaS;
	//数字
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCNum[TIME_TYPE_NUM];
	//数字
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCountDown[3];
	//操作説明
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOperation;
	//マップ
	
	//レーダーのテクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tRadar;
	//レーダーのプレイヤーのテクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tRPlayer;
	//レーダーの敵のテクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tREnemy;
	//レーダーの敵2のテクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tREnemyS;
	//ゴールした後勝負あり
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tGameEnd;
	//アイテム解説草
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tLeaf;
	//アイテム解説草Text
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tLeafText;
	//アイテム解説肉
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tMeat;
	//アイテム解説肉Text
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tMeatText;
	//アイテム解説フン
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tShit;
	//アイテム解説フンText
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tShitText;

	Number m_number[TIME_SET_NUM];
	//タイム
	int m_second;
	//カウントダウン
	int m_count;
	int m_miri;
	int m_miriHand;
	//秒
	int m_sec;
	//分
	int m_min;
	//ゴールのチェックポイント
	int m_checkPoint;
	std::unique_ptr<CollisionMesh> m_floorMesh;
	std::unique_ptr<DirectX::Model> m_floorModel;
	//エフェクト
	EffectManager* m_eUpManager;
	EffectManager* m_eDownManager;
	EffectManager* m_eShitManager;
	EffectManager* m_eDustManager;
	int m_winCharacter;
	Radar* m_radar;

	float m_resultRotation;

	float m_countResult;

	MyLibrary::ADX2Le* m_adx2le;
	CriAtomExPlaybackId m_criAtomExPlaybackId;
public:
	ScenePlay();
	~ScenePlay();
	//初期化
	void Initialize() override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;
	void Finalize() override;
	void CreateDeviceDependentResources();
	// アイテムの作成
	void CreateItem();
	void CollisionUpdate();
	//ゲームをSet
	void GameSeter();
	//Get関数
	int GetWinCharacter() const{ return m_winCharacter; }
	Player* GetPlayer() const{ return m_player;  }
	int GetSecond() const{ return m_second; }
	int GetMiri() const{ return m_miri; };
	int GetMiriHand() const{ return m_miriHand; };
	int GetSec() const{ return m_sec; };
	int GetMin() const{ return m_min; };
	//アイテム取得時のEffect
	void CreateEffectManager(EffectManager* effectManager,const wchar_t* name ,int count, float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir,
		DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//画像を入れている
	void TextureSet();
};