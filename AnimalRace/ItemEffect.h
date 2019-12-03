#pragma once
#include "Item.h"

class Character;

class ItemEffect
{
public:
	int m_time;
	EffectManager* m_effectManagerbuf[3];
	EffectManager* m_effectManager;
public:
	/// <summary>
	/// �A�C�e���̌��ʏ����̃N���X
	/// </summary>
	ItemEffect();
	virtual ~ItemEffect();
public:
	// �X�V����(���ʂ̏���)
	virtual void Update(const DX::StepTimer & stepTimer, Character* chara) = 0;
	void Render(bool selectFlag);
	void SetEffectManager(EffectManager* effectManager0, EffectManager* effectManager1, EffectManager* effectManager2)
	{
		m_effectManagerbuf[0] = effectManager0;
		m_effectManagerbuf[1] = effectManager1;
		m_effectManagerbuf[2] = effectManager2;
	}
	virtual ItemEffect* Clone() = 0;
protected:
	// ���x���グ����ʏ���
	void UpSpeed(Character* chara);
	// ���x���グ����ʏ���
	void DownSpeed(Character* chara);
	// Fun�̌��ʏ���(���x��������)
	void Fun(Character* chara);
};