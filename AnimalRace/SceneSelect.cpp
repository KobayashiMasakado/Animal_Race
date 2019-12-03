#include "pch.h"
#include "SceneSelect.h"
#include <iostream>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "Game.h"
#include "ModelDate.h"
#include "InputManager.h"

#include "TextureDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

SceneSelect::SceneSelect() :
	m_x(CURSOR_MAX),
	m_y(320),
	m_playerType(ANIMAL_TYPE::ANIMAL_NONE),
	m_charaNum(0),
	m_charaSerect(0),
	m_blink(nullptr),
	m_blinkFlag(false),
    m_blinkTimer(0),
	m_blinkInterval(30)
{
}

SceneSelect::~SceneSelect()
{
}

void SceneSelect::Initialize()
{
	m_blink->Initialize(m_blinkInterval);
	m_blink->Start();
}

void SceneSelect::Update(const DX::StepTimer& timer)
{
	// キーボードの状態を取得する
	Keyboard::State kb = Keyboard::Get().GetState();
	DirectX::Keyboard::KeyboardStateTracker* tracker =
		InputManager::GetInstance()->GetKeyTracker();
	//キャラクター選択したら
	if (tracker->pressed.Enter)
	{
		//プレイヤーやCPUに動物を設置する
		SceneManager* sceneManager = SceneManager::GetInstance();
		switch (m_charaSerect)
		{
		case 0: //プレイヤーがラクダを選んだ場合
			m_playerType = ANIMAL_TYPE::HERBIVORE;
			m_cpuType = ANIMAL_TYPE::CARNIVORE;
			m_cpuSType = ANIMAL_TYPE::OMNIVOROUS;
			break;
		case 1: //プレイヤーがトラを選んだ場合
			m_playerType = ANIMAL_TYPE::CARNIVORE;
			m_cpuType = ANIMAL_TYPE::OMNIVOROUS;
			m_cpuSType = ANIMAL_TYPE::HERBIVORE;
			break;
		case 2: //プレイヤーがダチョウを選んだ場合
			m_playerType = ANIMAL_TYPE::OMNIVOROUS;
			m_cpuType = ANIMAL_TYPE::HERBIVORE;
			m_cpuSType = ANIMAL_TYPE::CARNIVORE;
			break;
		}
		//プレイ画面へ移動
		sceneManager->ChangeSceneID(SceneManager::SceneID::Play);
	}
	//左キーを押した時
	if (tracker->pressed.Left)
	{
		if (m_x > CURSOR_MAX)
		{
			m_x = m_x - CURSOR_MOVE;
			m_charaSerect -= 1;
		}
	}
	//右キーを押した時
	if (tracker->pressed.Right)
	{
		if (m_x < CURSOR_MIX)
		{
			m_x = m_x + CURSOR_MOVE;
			m_charaSerect += 1;
		}
	}
	//---点滅の処理-----
	m_blinkTimer++;
	int blinktime = m_blinkTimer % m_blinkInterval;
	if (blinktime >= m_blinkInterval / 2)
	{
		m_blinkFlag = true;
	}
	else
	{
		m_blinkFlag = false;
	}
	//------------------
}

void SceneSelect::Render()
{
	auto context = m_game->GetContext();
	//2Dスプライトの描画
	m_sprites->Begin(SpriteSortMode_Deferred, m_game->GetState()->NonPremultiplied());
	m_sprites->Draw(m_tBackGround.Get(), Vector2(0, 0));
	m_sprites->Draw(m_tCamel.Get(), Vector2(90, m_y));
	m_sprites->Draw(m_tTiger.Get(), Vector2(363, m_y));
	m_sprites->Draw(m_tOstrich.Get(), Vector2(636, m_y));	
	m_sprites->Draw(m_tCamelParameter.Get(),   Vector2(50,  10));
	m_sprites->Draw(m_tTigerParameter.Get(),   Vector2(320, 10));
	m_sprites->Draw(m_tOstrichParameter.Get(), Vector2(590, 10));

	if (m_blinkFlag == true)
	{
		m_sprites->Draw(m_tSelectPointer.Get(), Vector2(m_x, m_y));
		m_sprites->Draw(m_tDescription.Get(), Vector2(200, 550));
	}

	m_sprites->End();
}

void SceneSelect::CreateDeviceDependentResources()
{
	//スプライトバッチの作成
	ID3D11Device* device = m_game->GetDevice();
	ID3D11DeviceContext* context = m_game->GetContext();
	
	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);
	//画像を入れている
	TextureSet();
	m_blink = new Blink();
}

void SceneSelect::Finalize()
{
	delete m_blink;
	m_tBackGround.Reset();
	m_tCamel.Reset();
	m_tTiger .Reset();
	m_tOstrich.Reset();
	m_tSelectPointer.Reset();
	m_tDescription.Reset();
	m_tTigerParameter.Reset();
	m_tCamelParameter.Reset();
	m_tOstrichParameter.Reset();
}

void SceneSelect::Reset()
{
	m_blink->Reset(true);
}
//画像を入れている
void SceneSelect::TextureSet()
{
	TextureDate* textureDate = TextureDate::GetInstance();
	m_tBackGround = textureDate->GetBackGround();
	m_tCamel = textureDate->GetCamel();
	m_tTiger = textureDate->GetTiger();
	m_tOstrich = textureDate->GetOstrich();
	m_tSelectPointer = textureDate->GetSelectPointer();
	m_tDescription = textureDate->GetSelectDescription();
	m_tTigerParameter = textureDate->GetTigerParameter();
	m_tCamelParameter = textureDate->GetCamelParameter();
	m_tOstrichParameter = textureDate->GetOstrichParameter();
}

