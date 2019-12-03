#pragma once
///------------------------------------------- 
/// Root.h
/// 
/// ���[�g���i��N���X
/// Day.7/5
/// MasakadoKobayashi
///------------------------------------------- 
#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"
#include "Player.h"
#include "Enemy.h"

class Root : public CollisionCapsule
{
public:
	static const int ENEMY_HITCHECK_NUM = 16;
private:
	bool m_hitPlayerFlag;
	CollisionCapsule* m_outCose[ENEMY_HITCHECK_NUM];
public:
	//�R���X�g���N�^
	Root();
	//�f�X�g���N�^
	~Root();
	//�X�V
	bool Update(const float elapsedTIme);
	//�`��
	void Render();
	//�G�t�F�N�g�̐ݒ�֐�
	void SetUpEffect();
	void Finalize();

	/*void NoOutMountein(CollisionCapsule* outCose);

	void NoOutPlayer(Player* player);*/
};