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
	// エフェクト
	if (m_effectManager != nullptr &&
		m_time > 0)
	{
		m_effectManager->Render(selectFlag);
	}
}
// 速度を上げる効果処理
void ItemEffect::UpSpeed(Character* Chara)
{
	Vector3 vec = Chara->GetVec();
	vec.z += 0.15f;
	Chara->SetVec(vec);
	m_effectManager = m_effectManagerbuf[0];
}
// 速度を上げる効果処理
void ItemEffect::DownSpeed(Character* Chara)
{
	Vector3 vec = Chara->GetVec();
	vec.z *= 0.5f;
	Chara->SetVec(vec);
	m_effectManager = m_effectManagerbuf[1];
}
// Funの効果処理(速度を下げる)
void ItemEffect::Fun(Character* Chara)
{
	Vector3 vec = Chara->GetVec();
	vec.z = -0.8f;
	Chara->SetVec(vec);
	m_effectManager = m_effectManagerbuf[2];
}

