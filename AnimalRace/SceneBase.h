#pragma once
#include "DeviceResources.h"

class Game;

class SceneBase
{
protected:
	Game* m_game;

public:
	SceneBase():m_game(nullptr) {};
	~SceneBase() {};
	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual void Update(const DX::StepTimer& timer) = 0;
	//描画
	virtual void Render() = 0;
	//終了処理
	virtual void Finalize() = 0;
	//ゲームでいるものを作る
	virtual void CreateDeviceDependentResources() = 0;

	//ゲームオブジェクトを設定する関数
	void SetGame(Game* game)
	{
		m_game = game;
	}
};