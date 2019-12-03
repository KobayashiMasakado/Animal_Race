#pragma once

#include "SceneBase.h"
#include "DeviceResources.h"
#include "DebugCamera.h"
#include "ScenePlay.h"
#include "Number.h"

class SceneResult : public SceneBase
{
private:
	DX::StepTimer                           m_timer;

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
	//テクスチャ
	//背景
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tBackGround;
	//勝利した草食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tHerbivore;
	//勝利した肉食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCarnivore;
	//勝利した雑食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOmnivorous;
	//敗北した草食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDHerbivore;
	//敗北した肉食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDCarnivore;
	//敗北した雑食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDOmnivorous;
	//playerwinと出す
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPlayerWin;
	//cpuwinと出す
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCpuWin;
	//youwinと出す
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tYouWin;
	//youloseと出す
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tYouLose;
	//操作説明
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDecision;
	//:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCComma;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCCommaS;
	//数字
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCNum[10];
	//数字を出す
	Number m_number[3];

	//点滅管理オブジェクト
	Blink* m_blink;

	// 点滅Flag
	bool m_blinkFlag;

	//点滅タイマー
	int m_blinkTimer;

	//音
	MyLibrary::ADX2Le* m_adx2le;
	CriAtomExPlaybackId m_criAtomExPlaybackId;
public:
	SceneResult();
	~SceneResult();

	//初期化
	void Initialize() override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画;
	void Render() override;

	void CreateDeviceDependentResources();

	//終了処理
	void Finalize() override;

	void Reset();
	//画像を入れている
	void TextureSet();

	//Set関数
	//ゲッター関数
	//デバイスを取得する関数
	ID3D11Device* GetDevice() const
	{
		return m_deviceResources->GetD3DDevice();
	}

	//コンテキストを取得する関数
	ID3D11DeviceContext* GetContext() const
	{
		return m_deviceResources->GetD3DDeviceContext();
	}
	//コモンステートを取得する関数
	DirectX::CommonStates* GetState() const
	{
		return m_states.get();
	}
	//ビュー行列を取得する関数
	const DirectX::SimpleMath::Matrix& GetView() const
	{
		return m_view;
	}
	//射影行列を取得する関数
	const DirectX::SimpleMath::Matrix& GetProjection() const
	{
		return m_projection;
	}
	//Set関数
	void SetDeviceResources(DX::DeviceResources* deviceResources)
	{
		this->m_deviceResources = deviceResources;
	}
	void SetProjection(const DirectX::SimpleMath::Matrix& projection)
	{
		this->m_projection = projection;
	}
};