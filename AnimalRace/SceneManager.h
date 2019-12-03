#pragma once
#include "Utility.h"
#include "SceneBase.h"

class SceneTitle;
class SceneSelect;
class ScenePlay;
class SceneResult;

class Game;
class SceneManager : public SingletonBase<SceneManager>
{
public:
	enum SceneID
	{
		NONE = -1,
		Title,
		Select,
		Play,
		Result,

		Max
	};
private:
	// Device resources.
	DX::DeviceResources*    m_deviceResources;

	// シーン
	SceneTitle* m_sTitle;
	SceneSelect* m_sSelect;
	ScenePlay* m_sPlay;
	SceneResult* m_sResult;

	//シーン移動
	Game* m_game;
	SceneID m_currentSceneID;
	SceneID m_changeSceneID;
	SceneBase* m_currentScene;
	//投影させる
	DirectX::SimpleMath::Matrix m_projection;

public:	
	SceneManager();

	//初期化
	void Initialize();
	//更新
	void Update(const DX::StepTimer& timer);
	//描画
	void Render();
	//終了処理
	void Finalize();

	void ChangeSceneID(SceneID id)
	{
		m_changeSceneID = id;
	}

	void CreateDeviceDependentResources(Game* game, DX::DeviceResources* deviceResources);
	void CreateWindowSizeDependentResources(const DirectX::SimpleMath::Matrix& projection);
	void OnDeviceLost();

	SceneTitle* GetSceneTitle() const
	{
		return m_sTitle;
	}
	SceneSelect* GetSceneSelect() const
	{
		return m_sSelect;
	}
	ScenePlay* GetScenePlay() const
	{
		return m_sPlay;
	}

private:
	void ChangeScene();
};