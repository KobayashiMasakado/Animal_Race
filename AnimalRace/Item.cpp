#include "pch.h"
#include "Item.h"
#include <Effects.h> 
#include <PrimitiveBatch.h>
#include <VertexTypes.h> 
#include <SimpleMath.h>
#include "Game.h"
#include "ModelDate.h"
#include "EffectManager.h"
#include "ItemEffect.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Item::Item(ItemEffect* itemEffect)
{
	m_itemEffect = itemEffect;
}
/// <summary>
/// デストラクタ
/// </summary>
Item::~Item()
{
	delete m_itemEffect;
}
//エフェクトの設定関数
void Item::SetUpEffect()
{
	m_model->UpdateEffects([&](IEffect* effect)
	{
		auto lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			lights->SetPerPixelLighting(true);
		}
	});
}

void Item::SetEffectManager(EffectManager * effectManager0, EffectManager* effectManager1, EffectManager* effectManager2)
{
	m_itemEffect->SetEffectManager(effectManager0, effectManager1, effectManager2);
}

ItemEffect * Item::CreateItemEffect()
{
	return m_itemEffect->Clone();
}

