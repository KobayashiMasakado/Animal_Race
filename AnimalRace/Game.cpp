//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "ModelDate.h"
#include "TextureDate.h"
#include "InputManager.h"

#include "ADX2Le.h"

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;

using Microsoft::WRL::ComPtr;

Game::Game()
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
	m_effectManager = nullptr;

	m_acf = L"NewProject.acf";
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	MyLibrary::ADX2Le::GetInstance()->Initialize(m_acf);
	// キーボードの作成
	m_keyboard = std::make_unique<Keyboard>();

	// マウスの作成
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);

    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;

    // キーボードの状態を取得する
	Keyboard::State kb = Keyboard::Get().GetState();
	DirectX::Keyboard::KeyboardStateTracker* tracker =
		InputManager::GetInstance()->GetKeyTracker();

	tracker->Update(kb);

	if (kb.Escape)
	{
		//WM_QUITメッセージを送出する
		PostQuitMessage(0);
	}
	//タスクの更新処理
	m_taskManager.Update(elapsedTime);

	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->Update(timer);

}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	auto context = m_deviceResources->GetD3DDeviceContext();

	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->Render();
	// ここから描画処理を記述する
	
	context;

	m_taskManager.Render();

	m_deviceResources->PIXEndEvent();

	// ここまで
    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{

    m_deviceResources->PIXBeginEvent(L"Clear");
    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::DarkBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);
    // Set the viewport.
	//ビューポートの設定
	D3D11_VIEWPORT viewport = { 0.0f,0.0f,800.0f,600.0f,0.0f,1.0f };
	context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();
    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
	//スプライトバッチの作成
    ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context =  m_deviceResources->GetD3DDeviceContext();

	ModelDate* modelData = ModelDate::GetInstance();
	modelData->Create(device);

	TextureDate* textureDate = TextureDate::GetInstance();
	textureDate->Create(device, context);

	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->CreateDeviceDependentResources(this, m_deviceResources.get());

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);

	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);
}
// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
	// ウインドウサイズからアスペクト比を算出する
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		1000.0f
	);
	
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->CreateWindowSizeDependentResources(m_projection);
}

void Game::ChangeFullScreen(BOOL flag)
{
	m_deviceResources->GetSwapChain()->SetFullscreenState(flag, NULL);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->OnDeviceLost();

	// コモンステートの解放
	m_states.reset();

	// スプライトバッチの解放
	m_sprites.reset();

	// グリッドの床の解放
	m_gridFloor.reset();

	if (m_effectManager != nullptr) {
		m_effectManager->Lost();
		delete m_effectManager;
		m_effectManager = nullptr;
	}

	//音を削除
	MyLibrary::ADX2Le::GetInstance()->Finalize();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();
    CreateWindowSizeDependentResources();
}
#pragma endregion
