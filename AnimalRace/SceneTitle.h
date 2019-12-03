#pragma once
#include "SceneBase.h"
#include "DeviceResources.h"
#include "DebugCamera.h"
#include "Blink.h"
#include "ADX2Le.h"

class SceneTitle : public SceneBase
{
public:
	static const int FLAG_SWITCH = 30;

private:
	DX::StepTimer m_timer;

	// Device resources.
	DX::DeviceResources* m_deviceResources;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;

	//点滅管理オブジェクト
	Blink* m_blink;

	// 点滅Flag
	bool m_blinkFlag;

	//点滅タイマー
	int m_blinkTimer;
	//タイトルの位置
	int m_titleX;
	int m_titleY;

	//2Dスプライト
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tBackGround;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTitleRogo;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPushEnter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tExitEnter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDescription;
	
	//カーソル位置で次の行動が変わる
	int m_select;
	//BGM
	MyLibrary::ADX2Le* m_adx2le;
	CriAtomExPlaybackId m_criAtomExPlaybackId;

public:
	SceneTitle();
	~SceneTitle();

	//初期化
	void Initialize() override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;
	//終了処理
	void Finalize() override;
	
	void CreateDeviceDependentResources();

	void Reset();
	//画像を入れている
	void TextureSet();
};