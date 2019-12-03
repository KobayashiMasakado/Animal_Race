#include "pch.h"
#include "Game.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "ScenePlay.h"
#include "SceneResult.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

SceneManager::SceneManager()
	:
	m_deviceResources(nullptr),
	m_currentScene(nullptr),
	m_game(nullptr),
	m_sTitle(new SceneTitle()),
	m_sSelect(new SceneSelect()),
	m_sPlay(new ScenePlay()),
	m_sResult(new SceneResult()),
	m_changeSceneID(SceneID::NONE),
	m_currentSceneID(SceneID::NONE)
{
}

void SceneManager::Initialize()
{
	//今のシーンのInitializeへ
	if (m_currentScene != nullptr)
	{
		m_currentScene->Initialize();
	}
}

void SceneManager::Update(const DX::StepTimer& timer)
{
	//今のシーンのUpdateへ
	if (m_currentScene != nullptr)
	{
		m_currentScene->Update(timer);
	}
	//シーン切り替え
	if (m_currentSceneID != m_changeSceneID)
	{
		ChangeScene();
	}
}

void SceneManager::Render()
{
	//今のシーンのRenderへ
	if (m_currentScene != nullptr)
	{
		m_currentScene->Render();
	}
}

void SceneManager::Finalize()
{
	//今のシーンのFinalizeへ
	if (m_currentScene != nullptr)
	{
		m_currentScene->Finalize();
	}
	if (m_sTitle)
	{
		delete m_sTitle;
	}
	if (m_sSelect)
	{
		delete m_sSelect;
	}
	if (m_sPlay)
	{
		delete m_sPlay;
	}
	if (m_sResult)
	{
		delete m_sResult;
	}
}

void SceneManager::ChangeScene()
{
	// 現在のシーンを終了させる
	if (m_currentScene != nullptr)
	{
		m_currentScene->Finalize();
	}

	switch (m_changeSceneID)
	{
	case SceneManager::Title:
		m_currentScene = m_sTitle;
		break;	
	case SceneManager::Select:
		m_currentScene = m_sSelect;
		break;
	case SceneManager::Play:
		m_currentScene = m_sPlay;
		break;
	case SceneManager::Result:
		m_currentScene = m_sResult;
		break;
	}
	m_currentSceneID = m_changeSceneID;

	if (m_currentScene != nullptr)
	{
		m_currentScene->SetGame(m_game);
		m_currentScene->CreateDeviceDependentResources();
		m_currentScene->Initialize();
	}
}

void SceneManager::CreateDeviceDependentResources(Game* game, DX::DeviceResources* deviceResources)
{
	m_game = game;
	m_deviceResources = deviceResources;

	m_changeSceneID = SceneID::Title;
	ChangeScene();
}

void SceneManager::CreateWindowSizeDependentResources(const DirectX::SimpleMath::Matrix& projection)
{
	m_projection = projection;
}

void SceneManager::OnDeviceLost()
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->Finalize();
		delete m_currentScene;
	}
}
