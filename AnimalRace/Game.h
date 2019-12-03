﻿#pragma once
//
// Game.h
//
#include "pch.h"
#include "DeviceResources.h"

#include "DebugCamera.h"
#include "GridFloor.h"

#include"GameCamera.h"

#include "Obj3D.h"
#include "CollisionCapsule.h"
#include "Player.h"
#include "Enemy.h"
#include "Root.h" 

#include "SceneTitle.h"
#include "SceneSelect.h"
#include "ScenePlay.h"
#include "SceneResult.h"

#include "SceneManager.h"

#include "TaskManager.h"

#include "EffectManager.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

	//ゲッター関数
	//デバイスを取得する関数
	ID3D11Device* GetDevice()
	{
		return m_deviceResources->GetD3DDevice();
	}

	//コンテキストを取得する関数
	ID3D11DeviceContext* GetContext()
	{
		return m_deviceResources->GetD3DDeviceContext();
	}
	//コモンステートを取得する関数
	DirectX::CommonStates* GetState()
	{
		return m_states.get();
	}

	DX::DeviceResources* GetDeviceResources()
	{
		return m_deviceResources.get();
	}

	const DirectX::SimpleMath::Matrix& GetView()
	{
		return m_view;
	}

	void SetView(DirectX::SimpleMath::Matrix view)
	{
		m_view = view;
	}

	const DirectX::SimpleMath::Matrix& GetProjection()
	{
		return m_projection;
	}

public:
	//フルスクリーンモードに切り替える関数
	//(FALSEでウインドウモードに戻す)
	void ChangeFullScreen(BOOL flag);

private:

    void Update(DX::StepTimer const& timer);
    void Render();
	//void DrawSprite3D(DirectX::SimpleMath::Matrix world);
    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;
//	DX::DeviceResources* m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;

	// マウス
	std::unique_ptr<DirectX::Mouse> m_mouse;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;

	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

	// ゲームカメラ
	std::unique_ptr<GameCamera> m_gameCamera;

	// グリッドの床
	std::unique_ptr<GridFloor> m_gridFloor;

	// エフェクト
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	
	//シーン移動
	SceneBase* m_currentScene;

	//シーン
	std::unique_ptr<SceneTitle> m_sTitle;
	std::unique_ptr<SceneSelect> m_sSelect;
	std::unique_ptr<ScenePlay> m_sPlay;
	std::unique_ptr<SceneResult> m_sResult;

	//タスク
	TaskManager m_taskManager;

	EffectManager*							m_effectManager;

	const wchar_t* m_acf;
};