#pragma once
///-------------------------------------------------
/// CollisionCapsule.h
/// 
/// カプセルをもったクラス
/// 
/// Day.7/5
/// Masakado Kobayashi
///-------------------------------------------------

#include "Obj3D.h"
#include "Collision.h"
#include "DebugCapsule.h"

class CollisionCapsule : public Obj3D
{
private:
	//コリジョン情報
	Collision::Capsule m_collision;

	//コリジョン表示用オブジェクト
	std::unique_ptr<DebugCapsule> m_obj;

public:
	//コリジョン情報のSet関数
	void SetCollision(Collision::Capsule capsule);

	//コリジョン情報のGet関数
	Collision::Capsule GetCollision();

	//デバッグ用コリジョン表示関数
	void DrawCollision();
};