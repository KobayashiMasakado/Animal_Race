#pragma once

#include "Item.h"
#include "MeatEffect.h"

class Leaf : public Item
{
public:
	//�R���X�g���N�^
	Leaf();
	//�f�X�g���N�^
	~Leaf();
public:
	// ������
	void Initialize() override;
	//�X�V
	bool Update(const float elapsedTIme) override;
	//�`��
	void Render() override;
};