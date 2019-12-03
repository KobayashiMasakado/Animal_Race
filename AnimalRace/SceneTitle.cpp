#include "pch.h"
#include "SceneTitle.h"
#include <iostream>
#include "SceneManager.h"
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "Game.h"
#include "InputManager.h"
#include "ADX2Le.h"
#include "TextureDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;

SceneTitle::SceneTitle()
{
	//点滅の初期化
	m_blink = nullptr;
	m_blinkFlag = false;
	m_blinkTimer = 0;
	//選択の初期化
	m_select = 1;
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Initialize()
{
	//タイトルの初期位置
	m_titleX = 2000;
	m_titleY = 50;
	//点滅の設定
	m_blink->Initialize(30);
	m_blink->Start();

}

void SceneTitle::Update(const DX::StepTimer& timer)
{
	Keyboard::State kb = Keyboard::Get().GetState();
	DirectX::Keyboard::KeyboardStateTracker* tracker = 
		InputManager::GetInstance()->GetKeyTracker();
	//Enterキーを押す
	if (tracker->pressed.Enter)
	{
		//セレクト画面へ移行
		if (m_select == 1)
		{
			SceneManager* sceneManager = SceneManager::GetInstance();
			sceneManager->ChangeSceneID(SceneManager::SceneID::Select);
		}
		if (m_select == 2)
		{
			//WM_QUITメッセージを送出する
			PostQuitMessage(0);
		}	
	}
	//タイトルを動かす
	m_titleX -= 20;
	if (m_titleX < 100)
	{
		m_titleX = 100;
	}
	//右を押したら
	if (tracker->pressed.Right)
	{
		m_select = 1;
	}
	//左を押したら
	if (tracker->pressed.Left)
	{
		m_select = 2;
	}
	//---点滅の処理-----
	m_blinkTimer++;
	int a = m_blinkTimer % FLAG_SWITCH;
	if (a >= FLAG_SWITCH / 2)
	{
		m_blinkFlag = true;
	}
	else
	{
		m_blinkFlag = false;
	}
	//------------------
}

void SceneTitle::Render()
{
	auto context = m_game->GetContext();


	//2Dスプライトの描画
	m_sprites->Begin(SpriteSortMode_Deferred, m_game->GetState()->NonPremultiplied());
	m_sprites->Draw(m_tBackGround.Get(), Vector2(0, 0));
	m_sprites->Draw(m_tTitleRogo.Get(), Vector2(m_titleX, m_titleY));
	
	if (m_blinkFlag == true)
	{
		//startを選んだら
		if (m_select == 1)
		{
			m_sprites->Draw(m_tPushEnter.Get(), Vector2(500, 450));
		}
		//exitを選んだら
		else if (m_select == 2)
		{
			m_sprites->Draw(m_tExitEnter.Get(), Vector2(100, 450));
		}
		m_sprites->Draw(m_tDescription.Get(), Vector2(200, 550));
	}
	//選んでいない方は常に表示
	if (m_select == 1)
	{
		m_sprites->Draw(m_tExitEnter.Get(), Vector2(100, 450));

	}
	else if (m_select == 2)
	{
		m_sprites->Draw(m_tPushEnter.Get(), Vector2(500, 450));
	}
	m_sprites->End();
}

void SceneTitle::Finalize()
{
	delete m_blink;
	m_tBackGround.Reset();
	m_tTitleRogo.Reset();
	m_tPushEnter.Reset();
	m_tExitEnter.Reset();
	ADX2Le* adx2le = ADX2Le::GetInstance();
	adx2le->Stop();
}

void SceneTitle::CreateDeviceDependentResources()
{
	m_adx2le = MyLibrary::ADX2Le::GetInstance();
	m_adx2le->LoadAcb(L"SceneTitle.acb", L"SceneTitle.awb");
	m_criAtomExPlaybackId = m_adx2le->Play(0);

	//スプライトバッチの作成
	ID3D11Device* device = m_game->GetDevice();
	ID3D11DeviceContext* context = m_game->GetContext();
	//画像を入れている
	TextureSet();
	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);
	m_blink = new Blink();
}

void SceneTitle::Reset()
{
	m_blink->Reset(true);
}

//画像を入れている
void SceneTitle::TextureSet()
{
	TextureDate* textureDate = TextureDate::GetInstance();
	m_tBackGround  = textureDate->GetBackGround();
	m_tTitleRogo   = textureDate->GetTitleRogo();
	m_tPushEnter   = textureDate->GetPushEnter();
	m_tExitEnter   = textureDate->GetExitEnter();
	m_tDescription = textureDate->GetTitleDescription();
}

