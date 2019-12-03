///-------------------------------------------------
/// CollisionSphere.cpp
/// 
/// 境界球をもったObj3Dクラス
/// 
/// Day.6/26
/// Masakado Kobayashi
///-------------------------------------------------
#include "pch.h"
#include "CollisionSphere.h"
#include "Game.h"

void CollisionSphere::SetCollision(Collision::Sphere sphere)
{
	//コリジョン情報の設定
	m_collision = sphere;

	if (m_game)
	{
		//デバッグ用コリジョンモデルの作成
		m_obj = std::make_unique<DebugSphere>(m_game->GetDevice(), m_collision.center,   //境界球の中心 
			                                                       m_collision.r    //半径
			                                                       );
	}
}

Collision::Sphere CollisionSphere::GetCollision()
{
	Collision::Sphere sphere;
	//コリジョン情報をワールド行列を使って移動させる
	sphere.center = DirectX::SimpleMath::Vector3::Transform(m_collision.center, m_world);
	sphere.r = m_collision.r;
	return sphere;
}

void CollisionSphere::DrawCollision()
{
	if (m_game)
	{
		//デバッグ用コリジョンの描画
		m_obj->Draw(m_game->GetContext(), *m_game->GetState()
			, m_world, m_game->GetView(), m_game->GetProjection());
	}
}
