#pragma once
///-------------------------------------------- 
/// CPU.h
/// 
/// �G���i��N���X
/// Masakado Kobayashi
///-------------------------------------------
#include "EnemyBoss.h"

class CPU : public EnemyBoss
{
public:
	//�R���X�g���N�^
	CPU();
	//�f�X�g���N�^
	~CPU();

	//CPU�쐬
	void CPUCreate();

	void Finalize();

	//�O�i
	void MoveFront();
	
	//�v���C���[�L�����̈Ⴂ
	void CPUAnimalType();
};