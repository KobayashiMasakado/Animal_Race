#pragma once

#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"

class Goal : public CollisionCapsule
{
private:

public:
	//�R���X�g���N�^
	Goal();
	//�f�X�g���N�^
	~Goal();
	//�X�V
	bool Update(const float elapsedTIme);
	//�`��
	void Render();
	//�G�t�F�N�g�̐ݒ�֐�
	void SetUpEffect();

	void GoalCreate(int goal);
};