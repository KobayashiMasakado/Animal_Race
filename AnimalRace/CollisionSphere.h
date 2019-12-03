#pragma once
///-------------------------------------------------
/// CollisionSphere.h
/// 
/// 境界球をもったObj3Dクラス
/// 
/// Day.6/26
/// Masakado Kobayashi
///-------------------------------------------------
#include "Obj3D.h"
#include "Collision.h"
#include "DebugSphere.h"

class CollisionSphere : public Obj3D
{
private:
	//コリジョン情報
	Collision::Sphere m_collision;

	//コリジョン表示用オブジェクト
	std::unique_ptr<DebugSphere> m_obj;

public:
	//コリジョン情報の設定関数
	void SetCollision(Collision::Sphere sphere);

	//コリジョン情報の取得関数
	Collision::Sphere GetCollision();

	//デバッグ用コリジョン表示関数
	void DrawCollision();

};