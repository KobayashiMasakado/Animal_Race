#pragma once
///-------------------------------------------------
/// CollisionBox.h
/// 
/// ���E����������Obj3D�N���X
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
	//�R���W�������
	Collision::Box m_collision;

	//�R���W�����\���p�I�u�W�F�N�g
	std::unique_ptr<DebugBox> m_obj;

public:
	//�R���W�������̐ݒ�֐�
	void SetCollision(Collision::Box box);

	//�R���W�������̎擾�֐�
	Collision::Box GetCollision();

	//�f�o�b�O�p�R���W�����\���֐�
	void DrawCollision();

};