#pragma once
///-------------------------------------------------
/// CollisionSphere.h
/// 
/// ���E����������Obj3D�N���X
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
	//�R���W�������
	Collision::Sphere m_collision;

	//�R���W�����\���p�I�u�W�F�N�g
	std::unique_ptr<DebugSphere> m_obj;

public:
	//�R���W�������̐ݒ�֐�
	void SetCollision(Collision::Sphere sphere);

	//�R���W�������̎擾�֐�
	Collision::Sphere GetCollision();

	//�f�o�b�O�p�R���W�����\���֐�
	void DrawCollision();

};