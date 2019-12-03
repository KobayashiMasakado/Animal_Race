#pragma once
#include "CollisionCapsule.h"
#include "Item.h"

enum ANIMAL_TYPE
{
	ANIMAL_NONE = -1,
	HERBIVORE,	// 草食
	CARNIVORE,	// 肉食
	OMNIVOROUS, // 雑食

	ANIMAL_MAX
};

class Character : public CollisionCapsule
{
public:
	static const int GOAL_NUM = 6;
	
protected:
	ItemEffect* m_itemEffect;
	ANIMAL_TYPE m_animalType;
	//ゴールのチェックポイント
	bool m_charaCheckFlag[GOAL_NUM];
public:
	Character();
	virtual ~Character();

	//更新
	bool Update(const DX::StepTimer& stepTimer);
	//描画
	void RenderEffect(bool selectFlag);

	void Finalize();
	// アイテムの効果
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
	//キャラがゴールしたら
	bool CharaGoal();
	//ゴールのチェックポイント
	void CheckPoint(int num);
};
