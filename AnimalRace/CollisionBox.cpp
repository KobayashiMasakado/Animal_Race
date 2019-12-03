#include "pch.h"
#include "CollisionBox.h"
#include "Game.h"
#include <math.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

void CollisionBox::SetCollision(Collision::Box box)
{
	//コリジョン情報の設定
	m_collision = box;

	if (m_game)
	{
		//デバッグ用コリジョンモデルの作成
		m_obj = std::make_unique<DebugBox>(m_game->GetDevice(), m_collision.center,
			m_collision.r);
	}
}

Collision::Box CollisionBox::GetCollision()
{
	Collision::Box box;
	//コリジョン情報をワールド行列を使って移動させる
	Matrix world = Matrix::CreateTranslation(m_position);
	box.center = DirectX::SimpleMath::Vector3::Transform(m_collision.center, m_world);
	box.r = m_collision.r;
	return box;
}

void CollisionBox::DrawCollision()
{
	if (m_game)
	{
		//デバッグ用コリジョンの描画
		Matrix world = Matrix::CreateTranslation(m_position);
		m_obj->Draw(m_game->GetContext(), *m_game->GetState()
			, world, m_game->GetView(), m_game->GetProjection());
	}
}
