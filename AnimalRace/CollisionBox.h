#pragma once
///-------------------------------------------------
/// CollisionBox.h
/// 
/// 境界球をもったObj3Dクラス
/// 
/// Day.7/9
/// Masakado Kobayashi
///-------------------------------------------------
#include "Obj3D.h"
#include "Collision.h"
#include "DebugBox.h"

class CollisionBox : public Obj3D
{
private:
	//コリジョン情報
	Collision::Box m_collision;

	//コリジョン表示用オブジェクト
	std::unique_ptr<DebugBox> m_obj;

public:
	//コリジョン情報の設定関数
	void SetCollision(Collision::Box box);

	//コリジョン情報の取得関数
	Collision::Box GetCollision();

	//デバッグ用コリジョン表示関数
	void DrawCollision();

};