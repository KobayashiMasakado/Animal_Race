#pragma once

#include "SceneBase.h"
#include "DeviceResources.h"
#include "DebugCamera.h"
#include "Character.h"
#include "Item.h"
#include "Blink.h"

class Player;
class SceneSelect : public SceneBase
{
private:
	//カーソルの移動量
	static const int CURSOR_MOVE = 273;
	//カーソルの移動限界
	static const int CURSOR_MAX = 90;
	static const int CURSOR_MIX = 440;
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

	//カーソル移動
	int m_x;
	int m_y;

	//キャラ選択
	int m_charaNum;

	//点滅の間隔
	int m_blinkInterval;

	//動物を選択
	int m_charaSerect;
	//選んだ動物をプレイヤーにする
	ANIMAL_TYPE m_playerType;
	ANIMAL_TYPE m_cpuType;
	ANIMAL_TYPE m_cpuSType;

	//テクスチャ
	//背景
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tBackGround;
	//ラクダの絵
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCamel;
	//トラの絵
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTiger;
	//ダチョウの絵
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOstrich;
	//ラクダのパラメータ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCamelParameter;
	//トラのパラメータ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTigerParameter;
	//ダチョウのパラメータ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOstrichParameter;
	//選択のカッコ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tSelectPointer;
	//操作説明
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDescription;
	
	//点滅管理オブジェクト
	Blink* m_blink;
	// 点滅Flag
	bool m_blinkFlag;

	//点滅タイマー
	int m_blinkTimer;

public:
	SceneSelect();
	~SceneSelect();

	//初期化
	void Initialize() override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;
	void CreateDeviceDependentResources();
	//終了処理
	void Finalize() override;

	void Reset();
	int GetCharaSelect(){ return m_charaSerect;}

	//Set関数
	//ゲッター関数
	ANIMAL_TYPE GetPlayerAnimalType() const
	{
		return m_playerType;
	}
	ANIMAL_TYPE GetCPUAnimalType() const
	{
		return m_cpuType;
	}
	ANIMAL_TYPE GetCPUSAnimalType() const
	{
		return m_cpuSType;
	}

	void TextureSet();

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