#pragma once

#include "Item.h"
#include "MeatEffect.h"

class Meat : public Item
{
public:
	//�R���X�g���N�^
	Meat();
	//�f�X�g���N�^
	~Meat();

public:
	// ������
	void Initialize() override;
	//�X�V
	bool Update(const float elapsedTIme) override;
	//�`��
	void Render() override;
};