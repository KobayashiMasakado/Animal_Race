#pragma once
///------------------------------------------- 
/// Item.h
/// 
/// �A�C�e���i��N���X
/// Day.7/5
/// Masakado Kobayashi
///------------------------------------------- 
#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"
#include "EffectManager.h"

// �O���錾
class EffectManager;
class ItemEffect;

class Item : public CollisionCapsule
{
public:
	static const int ITEM_SET_NUM = 2;

private:
	ItemEffect* m_itemEffect;
public:
	//�R���X�g���N�^
	Item(ItemEffect* itemEffect);
	//�f�X�g���N�^
	virtual ~Item();
	// ������
	virtual void Initialize() = 0;
	//�X�V
	virtual bool Update(const float elapsedTIme) = 0;
	//�`��
	virtual void Render() = 0;
	//�G�t�F�N�g�̐ݒ�֐�
	void SetUpEffect();
	//	�Z�b�^�[
	void SetEffectManager(EffectManager* effectManager0, EffectManager* effectManager1, EffectManager* effectManager2);
	ItemEffect* CreateItemEffect();
};
