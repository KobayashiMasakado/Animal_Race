#include "pch.h"
#include "CollisionBox.h"
#include "Game.h"
#include <math.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

void CollisionBox::SetCollision(Collision::Box box)
{
	//�R���W�������̐ݒ�
	m_collision = box;

	if (m_game)
	{
		//�f�o�b�O�p�R���W�������f���̍쐬
		m_obj = std::make_unique<DebugBox>(m_game->GetDevice(), m_collision.center,
			m_collision.r);
	}
}

Collision::Box CollisionBox::GetCollision()
{
	Collision::Box box;
	//�R���W�����������[���h�s����g���Ĉړ�������
	Matrix world = Matrix::CreateTranslation(m_position);
	box.center = DirectX::SimpleMath::Vector3::Transform(m_collision.center, m_world);
	box.r = m_collision.r;
	return box;
}

void CollisionBox::DrawCollision()
{
	if (m_game)
	{
		//�f�o�b�O�p�R���W�����̕`��
		Matrix world = Matrix::CreateTranslation(m_position);
		m_obj->Draw(m_game->GetContext(), *m_game->GetState()
			, world, m_game->GetView(), m_game->GetProjection());
	}
}
