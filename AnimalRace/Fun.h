#pragma once

#include "Item.h"
#include "MeatEffect.h"

class Fun : public Item
{
public:
	//�R���X�g���N�^
	Fun();
	//�f�X�g���N�^
	~Fun();
public:
	// ������
	void Initialize() override;
	//�X�V
	bool Update(const float elapsedTIme) override;
	//�`��
	void Render() override;
};