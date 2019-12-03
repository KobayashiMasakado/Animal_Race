#include "pch.h"
#include "ItemEffect.h"
#include "Character.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

ItemEffect::ItemEffect()
	:
	m_time(0),
	m_effectManagerbuf{ nullptr }
{
	m_effectManager = m_effectManagerbuf[0];
}

ItemEffect::~ItemEffect()
{
}

void ItemEffect::Render(bool selectFlag)
{
	// �G�t�F�N�g
	if (m_effectManager != nullptr &&
		m_time > 0)
	{
		m_effectManager->Render(selectFlag);
	}
}
// ���x���グ����ʏ���
void ItemEffect::UpSpeed(Character* Chara)
{
	Vector3 vec = Chara->GetVec();
	vec.z += 0.15f;
	Chara->SetVec(vec);
	m_effectManager = m_effectManagerbuf[0];
}
// ���x���グ����ʏ���
void ItemEffect::DownSpeed(Character* Chara)
{
	Vector3 vec = Chara->GetVec();
	vec.z *= 0.5f;
	Chara->SetVec(vec);
	m_effectManager = m_effectManagerbuf[1];
}
// Fun�̌��ʏ���(���x��������)
void ItemEffect::Fun(Character* Chara)
{
	Vector3 vec = Chara->GetVec();
	vec.z = -0.8f;
	Chara->SetVec(vec);
	m_effectManager = m_effectManagerbuf[2];
}

