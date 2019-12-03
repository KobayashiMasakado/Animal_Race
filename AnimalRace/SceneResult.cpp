#include "pch.h"
#include "SceneResult.h"
#include <iostream>

#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "ModelDate.h"
#include "Game.h"
#include "InputManager.h"

#include "ADX2Le.h"


#include "TextureDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;

SceneResult::SceneResult()
{
	m_blink = nullptr;
	m_blinkFlag = false;
	m_blinkTimer = 0;
}

SceneResult::~SceneResult()
{
}

void SceneResult::Initialize()
{
	m_blink->Initialize(30);
	m_blink->Start();
}

void SceneResult::Update(const DX::StepTimer& timer)
{
	Keyboard::State kb = Keyboard::Get().GetState();
	DirectX::Keyboard::KeyboardStateTracker* tracker =
		InputManager::GetInstance()->GetKeyTracker();

	if (tracker->pressed.Enter)
	{
		SceneManager* sc = SceneManager::GetInstance();
		sc->ChangeSceneID(SceneManager::SceneID::Title);
	}
}

void SceneResult::Render()
{
	auto context = m_game->GetContext();
	//2Dスプライトの描画
	m_sprites->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());
	SceneManager* sceneManager = SceneManager::GetInstance();

	m_sprites->Draw(m_tBackGround.Get(), Vector2(0, 0));
	m_sprites->Draw(m_tDecision.Get(), Vector2(300, 550));
	//ミリ秒
	m_number[2].SetNum(sceneManager->GetScenePlay()->GetMiriHand());
	m_number[2].SetPos(Vector2(240, 0));
	m_number[2].Draw(m_sprites.get());
	//秒
	m_number[1].SetNum(sceneManager->GetScenePlay()->GetSec());
	m_number[1].SetPos(Vector2(120, 0));
	m_number[1].Draw(m_sprites.get());
	//分
	m_number[0].SetNum(sceneManager->GetScenePlay()->GetMin());
	m_number[0].SetPos(Vector2(0, 0));
	m_number[0].Draw(m_sprites.get());
	//タイムの：
	m_sprites->Draw(m_tCComma.Get(), Vector2(80, 0));
	m_sprites->Draw(m_tCCommaS.Get(), Vector2(200, 0));

	m_blinkTimer++;
	int brinkInterval = m_blinkTimer % 30;
	if (brinkInterval >= 30 / 2)
	{
		m_blinkFlag = true;
	}
	else
	{
		m_blinkFlag = false;
	}

	if (sceneManager->GetScenePlay()->GetWinCharacter() == 1)
	{
		if (sceneManager->GetSceneSelect()->GetPlayerAnimalType() == ANIMAL_TYPE::HERBIVORE)
		{
			m_sprites->Draw(m_tHerbivore.Get(), Vector2(350, 250));
			m_sprites->Draw(m_tDCarnivore.Get(), Vector2(550, 300));
			m_sprites->Draw(m_tDOmnivorous.Get(), Vector2(200, 300));
		}
		else if (sceneManager->GetSceneSelect()->GetPlayerAnimalType() == ANIMAL_TYPE::CARNIVORE)
		{
			m_sprites->Draw(m_tCarnivore.Get(), Vector2(350, 250));
			m_sprites->Draw(m_tDOmnivorous.Get(), Vector2(550, 300));
			m_sprites->Draw(m_tDHerbivore.Get(), Vector2(200, 300));
		}
		else if (sceneManager->GetSceneSelect()->GetPlayerAnimalType() == ANIMAL_TYPE::OMNIVOROUS)
		{
			m_sprites->Draw(m_tOmnivorous.Get(), Vector2(350, 250));
			m_sprites->Draw(m_tDHerbivore.Get(), Vector2(550, 300));
			m_sprites->Draw(m_tDCarnivore.Get(), Vector2(200, 300));
		}

		if (m_blinkFlag == true)
		{
			m_sprites->Draw(m_tPlayerWin.Get(), Vector2(50, 150));
		}
		m_sprites->Draw(m_tYouWin.Get(), Vector2(600, 550));
	}
	else if (sceneManager->GetScenePlay()->GetWinCharacter() == 2)
	{
		if (sceneManager->GetSceneSelect()->GetCPUAnimalType() == ANIMAL_TYPE::HERBIVORE)
		{
			m_sprites->Draw(m_tHerbivore.Get(), Vector2(350, 250));
			m_sprites->Draw(m_tDCarnivore.Get(), Vector2(550, 300));
			m_sprites->Draw(m_tDOmnivorous.Get(), Vector2(200, 300));
		}
		else if (sceneManager->GetSceneSelect()->GetCPUAnimalType() == ANIMAL_TYPE::CARNIVORE)
		{
			m_sprites->Draw(m_tCarnivore.Get(), Vector2(350, 250));
			m_sprites->Draw(m_tDOmnivorous.Get(), Vector2(550, 300));
			m_sprites->Draw(m_tDHerbivore.Get(), Vector2(200, 300));
		}
		else if (sceneManager->GetSceneSelect()->GetCPUAnimalType() == ANIMAL_TYPE::OMNIVOROUS)
		{
			m_sprites->Draw(m_tOmnivorous.Get(), Vector2(350, 250));
			m_sprites->Draw(m_tDHerbivore.Get(), Vector2(550, 300));
			m_sprites->Draw(m_tDCarnivore.Get(), Vector2(200, 300));
		}
		if (m_blinkFlag == true)
		{
			m_sprites->Draw(m_tCpuWin.Get(), Vector2(150, 150));
		}
		m_sprites->Draw(m_tYouLose.Get(), Vector2(550, 550));
	}
	else if (sceneManager->GetScenePlay()->GetWinCharacter() == 3)
	{
		if (sceneManager->GetSceneSelect()->GetCPUSAnimalType() == ANIMAL_TYPE::HERBIVORE)
		{
			m_sprites->Draw(m_tHerbivore.Get(), Vector2(350, 250));
			m_sprites->Draw(m_tDCarnivore.Get(), Vector2(550, 300));
			m_sprites->Draw(m_tDOmnivorous.Get(), Vector2(200, 300));
		}
		else if (sceneManager->GetSceneSelect()->GetCPUSAnimalType() == ANIMAL_TYPE::CARNIVORE)
		{
			m_sprites->Draw(m_tCarnivore.Get(), Vector2(350, 250));
			m_sprites->Draw(m_tDOmnivorous.Get(), Vector2(550, 300));
			m_sprites->Draw(m_tDHerbivore.Get(), Vector2(200, 300));
		}
		else if (sceneManager->GetSceneSelect()->GetCPUSAnimalType() == ANIMAL_TYPE::OMNIVOROUS)
		{
			m_sprites->Draw(m_tOmnivorous.Get(), Vector2(350, 250));
			m_sprites->Draw(m_tDHerbivore.Get(), Vector2(550, 300));
			m_sprites->Draw(m_tDCarnivore.Get(), Vector2(200, 300));
		}
		if (m_blinkFlag == true)
		{
			m_sprites->Draw(m_tCpuWin.Get(), Vector2(150, 150));
		}
		m_sprites->Draw(m_tYouLose.Get(), Vector2(550, 550));
	}
	
	m_sprites->End();
}

void SceneResult::CreateDeviceDependentResources()
{
	m_adx2le = MyLibrary::ADX2Le::GetInstance();

	m_adx2le->LoadAcb(L"EndRace.acb", L"EndRace.awb");

	m_criAtomExPlaybackId = m_adx2le->Play(0);
	//スプライトバッチの作成
	ID3D11Device* device = m_game->GetDevice();
	ID3D11DeviceContext* context = m_game->GetContext();

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);

	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);
	TextureSet();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
      			m_number[i].SetTexture(j, m_tCNum[j].Get());
		}
	}
	m_blink = new Blink();
}

void SceneResult::Finalize()
{
	delete m_blink;

	m_tBackGround.Reset();
	m_tOmnivorous.Reset();
	m_tPlayerWin.Reset();
	m_tCarnivore.Reset();
	m_tCpuWin.Reset();
	m_tYouWin.Reset();
	m_tYouLose.Reset();
	m_tHerbivore.Reset();
	m_tDHerbivore.Reset();
	m_tDCarnivore.Reset();
	m_tDOmnivorous.Reset();
	m_tDecision.Reset();
	for (int i = 0; i < 10; i++)
	{
		m_tCNum[i].Reset();
	}
	m_tCComma.Reset();
	m_tCCommaS.Reset();
	ADX2Le* adx2le = ADX2Le::GetInstance();
	adx2le->Stop();
}

void SceneResult::Reset()
{
	m_blink->Reset(true);
}

void SceneResult::TextureSet()
{
	TextureDate* textureDate = TextureDate::GetInstance();
	m_tBackGround  = textureDate->GetBackGround();
	m_tHerbivore   = textureDate->GetHerbivore();
	m_tCarnivore   = textureDate->GetCarnivore();
	m_tOmnivorous  = textureDate->GetOmnivorous();
	m_tDHerbivore  = textureDate->GetDHerbivore();
	m_tDCarnivore  = textureDate->GetDCarnivore();
	m_tDOmnivorous = textureDate->GetDOmnivorous();
	m_tPlayerWin   = textureDate->GetPlayerWin();
	m_tCpuWin      = textureDate->GetCpuWin();
	m_tYouWin      = textureDate->GetYouWin();
	m_tYouLose     = textureDate->GetYouLose();
	m_tDecision    = textureDate->GetDecision();
	m_tCComma      = textureDate->GetCComma();
	m_tCCommaS     = textureDate->GetCComma();
	for (int i = 0; i < 10; i++)
	{
		m_tCNum[i] = textureDate->GetCNum(i);
	}
}
