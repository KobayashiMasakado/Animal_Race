#pragma once
#include "CollisionCapsule.h"
#include "Item.h"

enum ANIMAL_TYPE
{
	ANIMAL_NONE = -1,
	HERBIVORE,	// ���H
	CARNIVORE,	// ���H
	OMNIVOROUS, // �G�H

	ANIMAL_MAX
};

class Character : public CollisionCapsule
{
public:
	static const int GOAL_NUM = 6;
	
protected:
	ItemEffect* m_itemEffect;
	ANIMAL_TYPE m_animalType;
	//�S�[���̃`�F�b�N�|�C���g
	bool m_charaCheckFlag[GOAL_NUM];
public:
	Character();
	virtual ~Character();

	//�X�V
	bool Update(const DX::StepTimer& stepTimer);
	//�`��
	void RenderEffect(bool selectFlag);

	void Finalize();
	// �A�C�e���̌���
	void SetItemEffect(ItemEffect* itemEffect)
	{
		if (m_itemEffect != nullptr)
		{
			delete m_itemEffect;
			m_itemEffect = nullptr;
		}
		m_itemEffect = itemEffect;
	}

	ANIMAL_TYPE GetAnimalType() const
	{
		return m_animalType;
	}

	void SetAnimalType(ANIMAL_TYPE animalType)
	{
		m_animalType = animalType;
	}
	//�L�������S�[��������
	bool CharaGoal();
	//�S�[���̃`�F�b�N�|�C���g
	void CheckPoint(int num);
};
