#pragma once
///-------------------------------------------- 
/// Enemy.h
/// 
/// �G���i��N���X
/// Masakado Kobayashi
///-------------------------------------------
#include "EnemyBoss.h" 

class Enemy : public EnemyBoss
{
public:
	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();
	
	//CPU�쐬
	void CPUCreate();

	void Finalize();
	
	//�O�i
	void MoveFront();
	
	//�v���C���[�L�����̈Ⴂ
	void EnemyAnimalType();
};