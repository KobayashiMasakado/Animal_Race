#pragma once
/// /// <summary>
/// Obj3D
/// 
/// 3Dオブジェクトを描画するためのクラス
/// Day.6/256/25
/// Masakado Kobayashi
#include "pch.h"
class Game;
#include "TaskManager.h"

class Obj3D : public Task
{
protected:
	//ゲームオブジェクトへのポインタ
	Game* m_game;
	//モデルハンドル
	DirectX::Model* m_model;
	ID3D11ShaderResourceView* m_texture;

	// 速度
	DirectX::SimpleMath::Vector3 m_vec;

	//位置
	DirectX::SimpleMath::Vector3 m_position;

	//回転
	DirectX::SimpleMath::Quaternion m_rotation;

	//回転
	DirectX::SimpleMath::Quaternion m_rotationZ;

	//加速度
	DirectX::SimpleMath::Vector3 m_accel;

	//角度
	DirectX::SimpleMath::Quaternion m_dirSpeed;
	DirectX::SimpleMath::Vector3 m_dirS;

	//ワールド行列
	DirectX::SimpleMath::Matrix m_world;

public:
	//コンストラクタ
	Obj3D();
	//更新
	virtual bool Update(const float elapsedTime);

	//描画
	virtual void Render();

	// セッター関数
	//ゲームオブジェクトを設定する関数
	void SetGame(Game* game)
	{
		m_game = game;
	}

	//モデルハンドルを設定する関数
	void SetModel(DirectX::Model* model)
	{
		m_model = model;
	}

	//モデルハンドルを設定する関数
	void SetTexture(ID3D11ShaderResourceView* texture)
	{
		m_texture = texture;
	}
	
	// 速度を設定する関数
	void SetVec(DirectX::SimpleMath::Vector3 vec)
	{
		m_vec = vec;
	}

	// 加速度を設定する関数
	void SetAccel(DirectX::SimpleMath::Vector3 accel)
	{
		m_accel = accel;
	}

	// 角度を設定する関数
	void SetDir(DirectX::SimpleMath::Quaternion dirS)
	{
		m_dirSpeed = dirS;
	}
	void SetDir(DirectX::SimpleMath::Vector3 dirS)
	{
		m_dirS = dirS;
	}

	//位置設定する関数
	void SetPosition(DirectX::SimpleMath::Vector3 position)
	{
		m_position = position;
	}

	//回転設定する関数
	void SetRotation(DirectX::SimpleMath::Quaternion rotation)
	{
		m_rotation = rotation;
	}

	// ゲッター
	//ゲームオブジェクトを設定する関数
	Game* GetGame()
	{
		return m_game;
	}

	//モデルハンドルを設定する関数
	DirectX::Model* GetModel()
	{
		return m_model;
	}

	
	ID3D11ShaderResourceView* GetTexture()
	{
		return m_texture;
	}
	// 速度を設定する関数
	const DirectX::SimpleMath::Vector3& GetVec()
	{
		return m_vec;
	}

	// 加速度を設定する関数
	const DirectX::SimpleMath::Vector3& GetAccel()
	{
		return m_accel;
	}

	// 角度を設定する関数
	const DirectX::SimpleMath::Quaternion& GetDirQ()
	{
		return m_dirSpeed;
	}
	const DirectX::SimpleMath::Vector3& GetDirV()
	{
		return m_dirS;
	}

	//位置設定する関数
	const DirectX::SimpleMath::Vector3& GetPosition()
	{
		return m_position;
	}

	//回転設定する関数
	const DirectX::SimpleMath::Quaternion& GetRotation()
	{
		return m_rotation;
	}
};