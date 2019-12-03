#pragma once
#include <sys/timeb.h>
#include "DeviceResources.h"
#include "CollisionCapsule.h"
#include "DebugCapsule.h"

#include "Character.h"
#include "Item.h"
class EnemyBoss : public Character
{
public:
	//アイテムの設置数
	static const int ITEM_SET_NUM = 2;
	//AIの最初の位置
	static const int WARP_ZERO = 0;
	//AIの最終位置
	static const int WARP_MAX = 26;


	//敵の現在位置
	DirectX::SimpleMath::Vector3 m_startPos;
	//敵の次の位置
	DirectX::SimpleMath::Vector3 m_targetPos;
	//AIポジティブの設定変数
	DirectX::SimpleMath::Vector3 m_CPUPoint[WARP_MAX];

	//アイテムを取得したか
	bool m_itemCPUCheck;
	bool m_itemCPUBadCheck;
	bool m_itemCPUFunCheck;

	//CPUがワープする場所
	DirectX::SimpleMath::Vector3 m_cpuSetPos[WARP_MAX];
	//CPUがワープした場所の当たり判定Flag
	int m_targetElem;

	//球の変数
	Collision::Sphere m_sphere;
	std::unique_ptr<DebugCapsule> m_debug;

	//キャラクターの足のモデル
	DirectX::Model* m_modelLegL;
	DirectX::Model* m_modelLegR;
	//キャラクターの影のモデル
	DirectX::Model* m_shadow;

public:
	//コンストラクタ
	EnemyBoss();
	//デストラクタ
	~EnemyBoss();
	//更新
	 bool Update(const DX::StepTimer& stepTimer);
	//描画
	void Render();
	//CPU作成

	void Finalize();

	bool GetItemCPU() const { return m_itemCPUCheck; }
	bool GetItemCPUBad() const { return m_itemCPUBadCheck; }
	bool GetItemCPUFun() const { return m_itemCPUFunCheck; }

	//エフェクトの設定関数
	void SetUpEffect();

	// アイテムの効果
	void SetItemEffect(ItemEffect* itemEffect)
	{
		if (m_itemEffect != nullptr)
		{
			delete m_itemEffect;
		}
		m_itemEffect = itemEffect;
	}

	//左旋回する
	void Left();
	//右旋回する
	void Right();
	//足のモデルの描画
	void LegModelRender(DirectX::SimpleMath::Matrix& world, float r, DirectX::SimpleMath::Vector3 posdif);

};
