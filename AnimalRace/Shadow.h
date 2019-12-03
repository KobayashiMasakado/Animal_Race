#pragma once
#include "CollisionCapsule.h"
class Shadow : public CollisionCapsule
{
private:

	// 表示フラグ
	bool m_active;
	// ブレンドステート
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;

public:
	// コンストラクタ
	Shadow();

	// 初期化関数
	void Initialize();

	bool Update();

	// 描画関数
	void Render();

	// 表示のON/OFFする関数
	void Active(bool flag) { m_active = flag; }
};
