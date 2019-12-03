///-------------------------------------------------
/// CollisionSphere.cpp
/// 
/// ���E����������Obj3D�N���X
/// 
/// Day.6/26
/// Masakado Kobayashi
///-------------------------------------------------
#include "pch.h"
#include "CollisionSphere.h"
#include "Game.h"

void CollisionSphere::SetCollision(Collision::Sphere sphere)
{
	//�R���W�������̐ݒ�
	m_collision = sphere;

	if (m_game)
	{
		//�f�o�b�O�p�R���W�������f���̍쐬
		m_obj = std::make_unique<DebugSphere>(m_game->GetDevice(), m_collision.center,   //���E���̒��S 
			                                                       m_collision.r    //���a
			                                                       );
	}
}

Collision::Sphere CollisionSphere::GetCollision()
{
	Collision::Sphere sphere;
	//�R���W�����������[���h�s����g���Ĉړ�������
	sphere.center = DirectX::SimpleMath::Vector3::Transform(m_collision.center, m_world);
	sphere.r = m_collision.r;
	return sphere;
}

void CollisionSphere::DrawCollision()
{
	if (m_game)
	{
		//�f�o�b�O�p�R���W�����̕`��
		m_obj->Draw(m_game->GetContext(), *m_game->GetState()
			, m_world, m_game->GetView(), m_game->GetProjection());
	}
}
