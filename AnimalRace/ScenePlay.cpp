#include "pch.h"
#include "ScenePlay.h"
#include <time.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "ModelDate.h"
#include "GameCamera.h"
#include "Game.h"
#include "SceneManager.h"
#include <time.h>
#include <cstdio>
#include "ADX2Le.h"
#include "TextureDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;

const float EFFECT_DUST_LIMIT = 0.3f;

ScenePlay::ScenePlay()
{
	//Effectのマネージャー
	m_eUpManager = nullptr;
	m_eDownManager = nullptr;
	m_eShitManager  = nullptr;
	m_eDustManager = nullptr;
}

ScenePlay::~ScenePlay()
{
}

void ScenePlay::Initialize()
{
	//カウントダウンの初期化
	m_count = 0;
	//ミリ秒の初期化	
	m_miri = 0;
	m_miriHand = 0;
	//秒の初期化	
	m_sec = 0;
	//分の初期化	
	m_min = 0;
    //逆走防止判定の初期化	
	m_checkPoint = 0;
    //制限時間の初期化	
	m_second = 0;
	//リザルトに勝利したキャラを表示するためのデータの初期化
	m_winCharacter = 0;
	//デバッグカメラの初期化
	m_debugCamera = std::make_unique<DebugCamera>(800, 600);
	//生成
	CreateDeviceDependentResources();
	
	m_charaGoal = nullptr;

	m_resultRotation = 0;

	m_countResult = 0;
}

void ScenePlay::Update(const DX::StepTimer& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());
	// デバッグカメラの更新
	m_debugCamera->Update();
	// プレイヤーの更新
	m_player->Update(timer);
	//m_root->Update(elapsedTime);
	// アイテムの更新
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (m_item[i] != nullptr)
		{
			m_item[i]->Update(elapsedTime);
		}
	}
    //カウントダウン（処理はカウントアップ）
	m_count += 1;
	/////更新/////////////////////
	//ゴールの更新
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->Update(elapsedTime);
	}
	//コースの当たり判定の更新
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_outCose[i]->Update(elapsedTime);
	}
	m_skyCollision->Update(elapsedTime);
	m_courseWaterCollision->Update(elapsedTime);
	///////当たり判定////////////
	CollisionUpdate();
	Keyboard::State kb = Keyboard::Get().GetState();
	//カウントダウンが終わったら
	if (m_count > GAME_START_TIME)
	{
		//プレイヤーのゴール判定
		if (m_player->CharaGoal())
		{
			m_winCharacter = 1;
			m_charaGoal = m_player;
		}
		//CPUのゴール判定
		if (m_cpu->CharaGoal())
		{
			m_winCharacter = 2;
			m_charaGoal = m_cpu;
		}
		if (m_cpuS->CharaGoal())
		{
			m_winCharacter = 3;
			m_charaGoal = m_cpuS;
		}
		//ゴールしたら
		if (m_charaGoal != nullptr)
		{
			m_countResult += elapsedTime;
			if (m_countResult > 3.0f)
			{
				//シーン移動(リザルト)
				SceneManager* sc = SceneManager::GetInstance();
				sc->ChangeSceneID(SceneManager::SceneID::Result);
			}
		}
		else if (m_charaGoal == nullptr)
		{
			//制限時間の処理
			m_second++;
			m_player->PlayerCommand();
			if (m_player->GetVec().z > EFFECT_DUST_LIMIT)
			{
				m_player->EffectUpdate(timer);
			}
			//CPUの移動
			m_cpu->MoveFront();
			m_cpuS->MoveFront();
			//CPUの更新
			m_cpu->Update(timer);
			m_cpuS->Update(timer);
		}
		//キャラの移動
		m_player->PlayerAnimalType();
		
	}
	//秒のリセット
	if (m_sec >= 60) m_sec = 0;
}

void ScenePlay::Render()
{
	auto context = m_game->GetContext();

	GameCamera* ganeCamera = GameCamera::GetInstance();
	//追従カメラ
	// ビュー行列の作成
	Vector3 cameraPos = Vector3(0.0f, 5.0f, -20.0f); //カメラの固定する位置
	Vector3 target;

	if (m_charaGoal == nullptr)
	{
		ganeCamera->ChaseCamera(m_player->GetPosition(), m_player->GetRotation());
	}
	else
	{
		m_resultRotation += XMConvertToRadians(1.0f);
		ganeCamera->ResultCamera(m_charaGoal->GetPosition(), m_resultRotation);
	}

	// 追従
	m_game->SetView(ganeCamera->GetViewMatrix());
	// デバッグカメラ
//	m_game->SetView(m_debugCamera->GetCameraMatrix()); 
	/////描画///////////////////
	//プレイヤーの描画
    m_player->Render();
	if (m_player->GetVec().z > EFFECT_DUST_LIMIT)
	{
		m_player->EffectRender();
	}
	//CPUの描画
	m_cpu->Render();
	m_cpuS->Render();
	//アイテムの描画
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (m_item[i] != nullptr)
		{
			m_item[i]->Render();
		}
	}
	//ゴールの描画
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->Render();
	}
	//当たり判定の描画
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_outCose[i]->Render();
	}
	m_skyCollision->Render();
	m_courseWaterCollision->Render();
	
	//////////////////////////////
	//3Dスプライト 
	Matrix worldGoal;
	worldGoal = Matrix::CreateScale(1.0f) * Matrix::CreateTranslation(Vector3(-103.5f, 0.0f, -12.0f));
	m_goalModel->Draw(context, *m_game->GetState(), worldGoal, m_game->GetView(), m_game->GetProjection());
	//草原
	Matrix worldPra;
	worldPra = Matrix::CreateScale(1.0f) * Matrix::CreateTranslation(Vector3(0.0f, 1.99f, 0.0f));
	m_prairie->Draw(context, *m_game->GetState(), worldPra, m_game->GetView(), m_game->GetProjection());
	/////////////////////////////////////////
	// 空
	Matrix worldSky;
	worldSky = Matrix::CreateScale(3.5f) * Matrix::CreateTranslation(Vector3(10.0f, -0.3f, -10.0f));
	m_skydome->Draw(context, *m_game->GetState(), worldSky, m_game->GetView(), m_game->GetProjection());
    /////////////////////////////////////////
	//道
	Matrix worldRoot;
	worldPra = Matrix::CreateTranslation(Vector3(0.0f, -0.0f, 0.0f));
	m_floorModel->Draw(context, *m_game->GetState(), worldRoot, m_game->GetView(), m_game->GetProjection());
	//////////////////////////////
	//水たまり
	Matrix worldCourseWater;
	worldCourseWater = Matrix::CreateTranslation(Vector3(110.0f, -0.7f, 0.0f));
	m_courseWater->Draw(context, *m_game->GetState(), worldCourseWater, m_game->GetView(), m_game->GetProjection());
	//////////////////////////////
	//レーダー
	Vector2 radarPlayerOrigin = Vector2(400.0f, 75.0f);
	Vector2 radarCpuOrigin = Vector2(4.0f, 4.0f);
	float rotation = 0.0f;
	//////////////////////////////
	//2Dスプライトの描画
	m_sprites->Begin(SpriteSortMode_Deferred, m_game->GetState()->NonPremultiplied());
	//タイム--------------------------------------
	//カウントダウン
	//ミリ秒
	if (m_charaGoal == nullptr)
	{
		m_miri = m_second;
		m_miriHand = m_miri % TIME_MINUTE;
		m_number[2].SetNum(m_miriHand);
		m_number[2].SetPos(Vector2(240, 0));
		m_number[2].Draw(m_sprites.get());
		//秒
		m_sec = m_miri / TIME_MINUTE;
		int sec = m_sec % TIME_MINUTE;
		m_number[1].SetNum(sec);
		m_number[1].SetPos(Vector2(120, 0));
		m_number[1].Draw(m_sprites.get());
		//分
		m_min = m_sec / TIME_MINUTE;
		int min = m_min % TIME_MINUTE;
		m_number[0].SetNum(min);
		m_number[0].SetPos(Vector2(0, 0));
		m_number[0].Draw(m_sprites.get());
		
		//タイム表示
		m_sprites->Draw(m_tCComma.Get(), Vector2(80, 0));
		m_sprites->Draw(m_tCComma.Get(), Vector2(200, 0));
		
	}
	//カウントダウンが終わったら
	if (m_count < 200)
	{
		//操作説明テキスト
		m_sprites->Draw(m_tOperation.Get(), Vector2(170, 75));
		//アイテム画像
		m_sprites->Draw(m_tLeaf.Get(), Vector2(350, 320));
		m_sprites->Draw(m_tMeat.Get(), Vector2(500, 320));
		m_sprites->Draw(m_tShit.Get(), Vector2(650, 320));
		//アイテム画像テキスト
		m_sprites->Draw(m_tLeafText.Get(), Vector2(350, 450));
		m_sprites->Draw(m_tMeatText.Get(), Vector2(500, 450));
		m_sprites->Draw(m_tShitText.Get(), Vector2(650, 450));
	}

	for (int i = 3; i > 0; i--)
	{
		if (m_count >  ((i * TIME_MINUTE) - GAME_START_TIME) * -1 &&
			m_count < (((i * TIME_MINUTE) - GAME_START_TIME) * -1) + (TIME_MINUTE - 1))
		{
			//カウントダウン表示
			m_sprites->Draw(m_tCountDown[i-1].Get(), Vector2(350, 200));
		}
	}

	if (m_count > GAME_START_TIME && m_count < 200)
	{
		//カウントダウン終了時の掛け声
		m_sprites->Draw(m_tCGo.Get(), Vector2(280, 200));
	}
	//ゴール判定
	if (m_player->CharaGoal() || m_cpu->CharaGoal() || m_cpuS->CharaGoal())
	{
		m_sprites->Draw(m_tGameEnd.Get(), Vector2(150, 150));
	}
	///////////////////////////////////////
	//レーダーの描画
	m_sprites->Draw(m_tRadar.Get(), Vector2(0, 320));
	//レーダーのプレイヤーの描画                                                 位置  
	m_sprites->Draw(m_tRPlayer.Get(), Vector2(m_player->GetPosition().x + 130, m_player->GetPosition().z + 470));
	//レーダーのプレイヤーの描画                                                 位置  
	m_sprites->Draw(m_tREnemy.Get(), Vector2(m_cpu->GetPosition().x + 130, m_cpu->GetPosition().z + 470));
	//レーダーのプレイヤーの描画                                                 位置  
	m_sprites->Draw(m_tREnemyS.Get(), Vector2(m_cpuS->GetPosition().x + 130, m_cpuS->GetPosition().z + 470));
	///////////////////////////////////////
	m_sprites->End();
}

void ScenePlay::Finalize()
{ 
	delete m_player;
	delete m_cpu;
	delete m_cpuS;
	m_skydome.reset();
	m_goalModel.reset();
	m_skyCollision.reset();
	m_courseWaterCollision.reset();
	m_prairie.reset();
	m_floorModel.reset();
	m_floorMesh.reset();
	m_courseWater.reset();
	m_sprites.reset();
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i].reset();
	}
	for (int i = 0; i < ITEM_MAX; i++)
	{
		m_item[i].reset();
	}
	m_tTime.Reset();
	m_tPlayerGoal.Reset();
	m_tCPUGoal.Reset();
	m_tRadar.Reset();
	m_tRPlayer.Reset();
	m_tREnemy.Reset();
	m_tREnemyS.Reset();
	for (int i = 0; i < 10; i++)
	{
		m_tCNum[i].Reset();
	}
	for (int i = 0; i < 3; i++)
	{
		m_tCountDown[i].Reset();
	}
	m_tCComma.Reset();
	m_tCCommaS.Reset();
	
	m_tCGo.Reset();
	m_tFlipGoal.Reset();
	m_tOperation.Reset();
	m_tGameEnd.Reset();
	m_tLeaf.Reset();
	m_tLeafText.Reset();
	m_tMeat.Reset();
	m_tMeatText.Reset();
	m_tShit.Reset();
	m_tShitText.Reset();
	/*for (int i = 0; i < TIME_SET_NUM; i++)
	{
		delete &m_number[i];
	}*/
	if (m_eShitManager)
	{
		m_eShitManager->Lost();
		delete m_eShitManager;
	}
	if (m_eUpManager)
	{
		m_eUpManager->Lost();
		delete m_eUpManager;
	}
	if (m_eDownManager)
	{
		m_eDownManager->Lost();
		delete m_eDownManager;
	}
	if (m_eDustManager)
	{
		m_eDustManager->Lost();
		delete m_eDustManager;
	}
	ADX2Le* adx2le = ADX2Le::GetInstance();
	adx2le->Stop();
}

void ScenePlay::CreateDeviceDependentResources()
{
	//音
	m_adx2le = MyLibrary::ADX2Le::GetInstance();
	m_adx2le->LoadAcb(L"FightRace.acb", L"FightRace.awb");
	m_criAtomExPlaybackId = m_adx2le->Play(0);

	//スプライトバッチの作成
	ID3D11Device* device = m_game->GetDevice();
	ID3D11DeviceContext* context = m_game->GetContext();
	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);
	//画像を入れている
	TextureSet();
	//数字の描画--------------------------------
	for (int i = 0; i < TIME_SET_NUM; i++)
	{
		for (int j = 0; j < TIME_TYPE_NUM; j++)
		{
			m_number[i].SetTexture(j, m_tCNum[j].Get());
		}
	}
	//-------------------------------------------
	// モデルの読み込み
	ModelDate* modelDate = ModelDate::GetInstance();
	SceneManager* sceneManager = SceneManager::GetInstance();
	// プレイヤーの作成
	m_player = new Player();
	m_player->SetGame(m_game);
	m_player->SetAnimalType(sceneManager->GetSceneSelect()->GetPlayerAnimalType());
	m_player->PlayerCreate();
	// CPUの作成
	m_cpu = new Enemy();
	m_cpu->SetGame(m_game);
	m_cpu->SetAnimalType(sceneManager->GetSceneSelect()->GetCPUAnimalType());
	m_cpu->CPUCreate();
	m_cpuS = new CPU();
	m_cpuS->SetGame(m_game);
	m_cpuS->SetAnimalType(sceneManager->GetSceneSelect()->GetCPUSAnimalType());
	m_cpuS->CPUCreate();

	//-------------エフェクト-------------
	RECT outputSize = m_game->GetDeviceResources()->GetOutputSize();
	UINT backBufferWidth = std::max<UINT>(outputSize.right - outputSize.left, 1);
	UINT backBufferHeight = std::max<UINT>(outputSize.bottom - outputSize.top, 1);
	Vector3 camera = Vector3(0, 0, -5);
	Matrix view = Matrix::CreateLookAt(camera,
		Vector3::Zero, Vector3::UnitY);
	Matrix proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(backBufferWidth) / float(backBufferHeight), 0.1f, 1000.f);
	//アイテム(UP)
	m_eUpManager = new EffectManager();
	m_eUpManager->Create(m_game->GetDeviceResources(), L"Textures\\gameW.png", 5);
	m_eUpManager->InitializeBut(0.05f, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	m_eUpManager->SetRenderState(camera, view, proj);
	//アイテム(DOWN)
	m_eDownManager = new EffectManager();
    m_eDownManager->Create(m_game->GetDeviceResources(), L"Textures\\gameB.png", 4);
	m_eDownManager->InitializeBut(0.03f, Vector3(0.0f, 0.9f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
	m_eDownManager->SetRenderState(camera, view, proj);
	//アイテム(Shit)
	m_eShitManager = new EffectManager();
	m_eShitManager->Create(m_game->GetDeviceResources(), L"Textures\\gameB.png", 4);
	m_eShitManager->InitializeBut(0.03f, Vector3(0.0f, 0.9f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
	m_eShitManager->SetRenderState(camera, view, proj);
	//dust
	m_eDustManager = new EffectManager();
	m_eDustManager->Create(m_game->GetDeviceResources(), L"Textures\\gameF.png", 4);
	m_eDustManager->InitializeBut(0.2f, Vector3(0.0f, -0.1f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
	m_eDustManager->SetRenderState(camera, view, proj);

	// モデルを読み込み
	// エフェクトファクトリー 
	EffectFactory fx(device);
	// モデルのテクスチャの入っているフォルダを指定する 
	fx.SetDirectory(L"Resources\\Models");      //テクスチャ付きのcmoがある場合上に持ってくる
	//アイテムの生成
	CreateItem();
	
	m_player->SetEffectManager(m_eDustManager);
	//ゴール作成
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i] = std::make_unique<Goal>();
		m_goal[i]->GoalCreate(i);
	}
	//スカイドームコリジョン作成
	m_skyCollision = std::make_unique<CollisionSphere>();
	m_skyCollision->SetGame(m_game);
	Collision::Sphere sphereSky;
	ModelDate* modelDateSky = ModelDate::GetInstance();
	sphereSky.center = Vector3(10.0f, -0.3f, -10.0f);
	sphereSky.r = 170.0f;
	m_skyCollision->SetCollision(sphereSky);
	//水たまりコリジョン作成
	m_courseWaterCollision = std::make_unique<CollisionSphere>();
	m_courseWaterCollision->SetGame(m_game);
	Collision::Sphere sphereCourseWater;
	ModelDate* modelDateCourseWater = ModelDate::GetInstance();
	sphereCourseWater.center = Vector3(110.0f, 0.0f, 0.0f);
	sphereCourseWater.r = 8.0f;
	m_courseWaterCollision->SetCollision(sphereCourseWater);
	//山の外に出ないようにする
	 for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_outCose[i] = std::make_unique<CollisionCapsule>();
		m_outCose[i]->SetGame(m_game);
		Collision::Capsule capsule[ENEMY_HITCHECK_NUM];
		ModelDate* modelDate = ModelDate::GetInstance();
		capsule[i].r = 1.0f;
		switch (i)
		{
			//一つ目の山
		case 0:
			m_outCose[i]->SetPosition(Vector3(-4.0f, 12.0f, 88.0f));
			capsule[i].start = Vector3(  0.0f,  0.0f, 0.0f);
			capsule[i].end   = Vector3(-65.0f, -12.0f, 0.0f);
			break;
		case 1:
			m_outCose[i]->SetPosition(Vector3(6.0f, 12.0f, 88.0f));
			capsule[i].start = Vector3( 10.0f, 0.0f, 0.0f);
			capsule[i].end   = Vector3(-10.0f, 0.0f, 0.0f);
			break;
		case 2:
			m_outCose[i]->SetPosition(Vector3(16.0f, 12.0f, 88.0f));
			capsule[i].start = Vector3( 0.0f,   0.0f, 0.0f);
			capsule[i].end   = Vector3(65.0f, -12.0f, 0.0f);
			break;
		case 3:
			m_outCose[i]->SetPosition(Vector3(-4.0f, 12.0f, 112.0f));
			capsule[i].start = Vector3( 0.0f,   0.0f, 0.0f);
			capsule[i].end   = Vector3(-65.0f, -12.0f, 0.0f);
			break;
		case 4:
			m_outCose[i]->SetPosition(Vector3(6.0f, 12.0f, 112.0f));
			capsule[i].start = Vector3( 10.0f, 0.0f, 0.0f);
			capsule[i].end   = Vector3(-10.0f, 0.0f, 0.0f);
			break;
		case 5:
			m_outCose[i]->SetPosition(Vector3(16.0f, 12.0f, 112.0f));
			capsule[i].start = Vector3( 0.0f,   0.0f, 0.0f);
			capsule[i].end   = Vector3(65.0f, -12.0f, 0.0f);
			break;
		case 6:
			m_outCose[i]->SetPosition(Vector3(0.0f, 0.0f, 88.0f));
			capsule[i].start = Vector3( 65.0f, 0.0f, 0.0f);
			capsule[i].end   = Vector3(-65.0f, 0.0f, 0.0f);
			break;
		case 7:
			m_outCose[i]->SetPosition(Vector3(0.0f, 0.0f, 112.0f));
			capsule[i].start = Vector3( 65.0f, 0.0f, 0.0f);
			capsule[i].end   = Vector3(-65.0f, 0.0f, 0.0f);
			break;
			//二つ目の山
		case 8:
			m_outCose[i]->SetPosition(Vector3(-20.0f, 0.0f, 30.0f));
			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[i].end = Vector3(0.0f, 10.0f, -49.0f);
			break;
		case 9:
			m_outCose[i]->SetPosition(Vector3(-20.0f, 10.0f, -29.0f));
			capsule[i].end = Vector3(0.0f, 0.0f, 10.0f);
			capsule[i].start = Vector3(0.0f, 0.0f, -10.0f);
			break;
		case 10:
			m_outCose[i]->SetPosition(Vector3(-20.0f, 0.0f, -90.0f));
			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[i].end = Vector3(0.0f, 10.0f, 49.0f);
			break;
		case 11:
			m_outCose[i]->SetPosition(Vector3(-43.0f, 0.0f, 30.0f));
			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[i].end = Vector3(0.0f, 10.0f, -49.0f);
			break;
		case 12:
			m_outCose[i]->SetPosition(Vector3(-43.0f, 10.0f, -29.0f));
			capsule[i].end   = Vector3(0.0f, 0.0f,  10.0f);
			capsule[i].start = Vector3(0.0f, 0.0f, -10.0f);
			break;
		case 13:
			m_outCose[i]->SetPosition(Vector3(-43.0f, 0.0f, -90.0f));
			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[i].end = Vector3(0.0f, 10.0f, 49.0f);
			break;
		case 14:
			m_outCose[i]->SetPosition(Vector3(-20.0f, 0.0f, -30.0f));
			capsule[i].end   = Vector3(0.0f, 0.0f,  50.0f);
			capsule[i].start = Vector3(0.0f, 0.0f, -50.0f);
			break;
		case 15:
			m_outCose[i]->SetPosition(Vector3(-45.0f, 0.0f, -30.0f));
			capsule[i].end   = Vector3(0.0f, 0.0f,  50.0f);
			capsule[i].start = Vector3(0.0f, 0.0f, -50.0f);
			break;
		}
		m_outCose[i]->SetCollision(capsule[i]);
	}
	
	m_goalModel = Model::CreateFromCMO(device, L"Resources\\Models\\RaceGoal.cmo", fx);
	//空
	m_skydome = Model::CreateFromCMO(device, L"Resources\\Models\\savanna.cmo", fx);
	m_skydome->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ライトの影響をなくす
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false); lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// エミッション色を白に設定する 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
	//地面
	m_prairie = Model::CreateFromCMO(device, L"Resources\\Models\\newSavanna.cmo", fx);
	m_prairie->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ライトの影響をなくす
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false); 
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// エミッション色を白に設定する 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
	
	m_floorModel = Model::CreateFromCMO(device, L"Resources\\Models\\Root.cmo", fx);
	m_floorModel->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ライトの影響をなくす
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false); 
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// エミッション色を白に設定する 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
	//地面
	m_courseWater = Model::CreateFromCMO(device, L"Resources\\Models\\puddle.cmo", fx);
	m_courseWater->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ライトの影響をなくす
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false);
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// エミッション色を白に設定する 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});

	//床のコリジョンメッシュを作成
	m_floorMesh = std::make_unique<CollisionMesh>(device, L"FBX\\Root.obj");
	m_floorMesh->SetGame(m_game);

}

/// <summary>
/// アイテムの作成
/// </summary>
void ScenePlay::CreateItem()
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	//アイテム作成(草)
	m_item[0] = std::make_unique<Leaf>();
	//アイテムの位置
	m_item[0]->SetPosition(Vector3(-80.0f, 0, 97.0f));
	//ゲームオブジェトの設定
	m_item[0]->SetGame(m_game);
	//プレイヤーが当たった時のエフェクト
	m_item[0]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//アイテムの初期化
	m_item[0]->Initialize();
	//----------------------------
	//アイテム作成(草)
	m_item[1] = std::make_unique<Leaf>();
	//アイテムの位置
	m_item[1]->SetPosition(Vector3(-33.0f, 0.0f, 50.0f));
	//ゲームオブジェトの設定
	m_item[1]->SetGame(m_game);
	//プレイヤーが当たった時のエフェクト
	m_item[1]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//アイテムの初期化
	m_item[1]->Initialize();
	//-------------------------------------------------------------------------------
	//アイテム作成(肉)
	m_item[2] = std::make_unique<Meat>();
	//アイテムの位置
	m_item[2]->SetPosition(Vector3(-80.0f, 0, 103.0f));
	//ゲームオブジェトの設定
	m_item[2]->SetGame(m_game);
	//プレイヤーが当たった時のエフェクト
	m_item[2]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//アイテムの初期化
	m_item[2]->Initialize();
	//----------------------------
	//アイテム作成(肉)
	m_item[3] = std::make_unique<Meat>();
	//アイテムの位置
	m_item[3]->SetPosition(Vector3(-27.0f, 0.0f, 50.0f));
	//ゲームオブジェトの設定
	m_item[3]->SetGame(m_game);
	//プレイヤーが当たった時のエフェクト
	m_item[3]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//アイテムの初期化
	m_item[3]->Initialize();
	//-------------------------------------------------------------------------------
	//アイテム作成(Fun)
	m_item[4] = std::make_unique<Fun>();
	//アイテムの位置
	m_item[4]->SetPosition(Vector3(0, 0, -8));
	//ゲームオブジェトの設定
	m_item[4]->SetGame(m_game);	   
	//プレイヤーが当たった時のエフェクト
	m_item[4]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//アイテムの初期化
	m_item[4]->Initialize();
	//----------------------------
	//アイテム作成(Fun)
	m_item[5] = std::make_unique<Fun>();
	//アイテムの位置
	m_item[5]->SetPosition(Vector3(-10, 0, 67));
	//ゲームオブジェトの設定
	m_item[5]->SetGame(m_game);
	//プレイヤーが当たった時のエフェクト
	m_item[5]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//アイテムの初期化
	m_item[5]->Initialize();
}

/// <summary>
/// 当たり判定
/// </summary>
void ScenePlay::CollisionUpdate()
{
	///当たり判定////////////
	//プレイヤーとコースの当たり判定
	static int id;
	Vector3 s;
	Vector3 playerPos = m_player->GetPosition();
	Vector3 cpuPos = m_cpu->GetPosition();
	Vector3 cpuSPos = m_cpuS->GetPosition();
	Vector3 pV[2] = { Vector3(playerPos.x,100,playerPos.z),Vector3(playerPos.x,-1,playerPos.z) };
	Vector3 cV[2] = { Vector3(cpuPos.x,100,cpuPos.z),Vector3(cpuPos.x,-1,cpuPos.z) };
	Vector3 cSV[2] = { Vector3(cpuSPos.x,100,cpuSPos.z),Vector3(cpuSPos.x,-1,cpuSPos.z) };

	if (m_floorMesh->HitCheck_Segment(pV[0], pV[1], &id, &s))
	{
		// 重力
		s.y -= 0.1f;
		m_player->SetPosition(s);
	}
	else
	{
		// 速度を下げる(コース外)
		Vector3 vec = m_player->GetVec();
		vec.z *= -0.01f;
		m_player->SetVec(vec);
	}
	//スカイドームから出ようとしたか	
	if (Collision::HitCheck_Sphere2Capsule(m_skyCollision->GetCollision(),
		m_player->GetCollision()) == true)
	{
		//--出ない--
		//コース（山）から出ようとしたら
		for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
		{
			if (Collision::HitCheck_Capsule2Capsule(m_outCose[i]->GetCollision()
				, m_player->GetCollision()) == true)
			{
				//出ないようにする
				m_player->OutCose();
			}
		}
		if (Collision::HitCheck_Sphere2Capsule(m_courseWaterCollision->GetCollision(),
			m_player->GetCollision()) == true)
		{
			Vector3 vec = m_player->GetVec();
			vec.z *= 0.1f;
			m_player->SetVec(vec);
		}
		//CPU
		if (m_floorMesh->HitCheck_Segment(cV[0], cV[1], &id, &s))
		{
			// 重力
			s.y -= 0.1f;
			m_cpu->SetPosition(s);
		}
		else
		{
			// 速度を下げる(コース外)
			Vector3 vec = m_cpu->GetVec();
			vec.z *= 0.5f;
			m_cpu->SetVec(vec);
		}
		if (m_floorMesh->HitCheck_Segment(cSV[0], cSV[1], &id, &s))
		{
			// 重力
			s.y -= 0.1f;
			m_cpuS->SetPosition(s);
		}
		else
		{
			// 速度を下げる(コース外)
			Vector3 vec = m_cpuS->GetVec();
			vec.z *= 0.5f;
			m_cpuS->SetVec(vec);
		}
		for (int i = 0; i < ITEM_MAX; i++)
		{
			// ポインタがない場合は飛ばして次に進む
			if (m_item[i] == nullptr)
			{
				continue;
			}
			// アイテムの当たり判定(player)
			if (Collision::HitCheck_Capsule2Capsule(m_item[i]->GetCollision(), m_player->GetCollision()))
			{
				ItemEffect* itemEffect = m_item[i]->CreateItemEffect();
				m_player->SetItemEffect(itemEffect);
			}
		}
		for (int i = 0; i < GOAL_SET_NUM; i++)
		{
			//ゴールとプレイヤーの当たり判定をする
			if (Collision::HitCheck_Capsule2Capsule(m_goal[i]->GetCollision()
				, m_player->GetCollision()) == true)
			{
				if (m_checkPoint == i)
				{
					m_player->CheckPoint(i);
					m_checkPoint = i + 1;
				}
			}
			//ゴールとCPUの当たり判定をする
			if (Collision::HitCheck_Capsule2Capsule
			    (m_goal[i]->GetCollision(),m_cpu->GetCollision()) == true)
			{
				m_cpu->CheckPoint(i);
			}

			if (Collision::HitCheck_Capsule2Capsule
			(m_goal[i]->GetCollision(), m_cpuS->GetCollision()) == true)
			{
				m_cpuS->CheckPoint(i);
			}
		}
	}
	else
	{
		//--出る--
		//出ないようにする
		Vector3 vec = m_player->GetVec();
		vec.z -= 1.3f;
		m_player->SetVec(vec);
	}
}

void ScenePlay::GameSeter()
{
	//アイテムのゲームオブジェクトを設定
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_item[i]->SetGame(m_game);
	}
	//ゴールのゲームオブジェクトを設定
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->SetGame(m_game);
	}
	//AIルートのゲームオブジェクトを設定
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_outCose[i]->SetGame(m_game);
	}
	//空のゲームオブジェクトを設定
	m_skyCollision->SetGame(m_game);
	//プレイヤーのゲームオブジェクトを設定
	m_player->SetGame(m_game);
	//CPUのゲームオブジェクトを設定
	m_cpu->SetGame(m_game);
	m_cpuS->SetGame(m_game);
}
//アイテム取得時のEffect
void ScenePlay::CreateEffectManager(EffectManager * effectManager, 
	const wchar_t * name, int count, float life, Vector3 pos, 
	Vector3 dir ,Vector3 camera, Matrix view, Matrix proj)
{
	effectManager = new EffectManager();
	effectManager->Create(m_game->GetDeviceResources(), name, count);
	effectManager->InitializeBut(life, pos, dir);
	effectManager->SetRenderState(camera, view, proj);
}
//画像を入れている
void ScenePlay::TextureSet()
{
	TextureDate* textureDate = TextureDate::GetInstance();
	m_tTime = textureDate->GetTime();
	m_tPlayerGoal = textureDate->GetPlayerGoal();
	m_tCPUGoal = textureDate->GetCPUGoal();
	m_tCPUSGoal = textureDate->GetCPUSGoal();
	m_tFlipGoal = textureDate->GetFlipGoal();
	m_tCGo = textureDate->GetCGo();
	for (int i = 0; i < 3; i++)
	{
		m_tCountDown[i] = textureDate->GetCountDown(i);
	}
	m_tOperation = textureDate->GetOperation();
	m_tRadar = textureDate->GetRadar();
	m_tRPlayer = textureDate->GetRPlayer();
	m_tREnemy = textureDate->GetREnemy();
	m_tREnemyS = textureDate->GetREnemyS();
	m_tGameEnd = textureDate->GetGameEnd();
	m_tLeaf = textureDate->GetLeaf();
	m_tLeafText = textureDate->GetLeafText();
	m_tMeat = textureDate->GetMeat();
	m_tMeatText = textureDate->GetMeatText();
	m_tShit = textureDate->GetShit();
	m_tShitText = textureDate->GetShitText();
	m_tCComma = textureDate->GetCComma();
	m_tCCommaS = textureDate->GetCComma();
	for (int i = 0; i < 10; i++)
	{
		m_tCNum[i] = textureDate->GetCNum(i);
	}
}

