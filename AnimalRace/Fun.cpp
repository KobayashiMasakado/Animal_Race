#include "pch.h"
#include "Fun.h"
#include "ModelDate.h"
#include "Game.h"
#include "FunEffect.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Fun::Fun()
	:
	Item(new FunEffect())
{
}

Fun::~Fun()
{
}

void Fun::Initialize()
{
	// モデルの読み込み
	ModelDate* modelDate = ModelDate::GetInstance();
	m_model = modelDate->GetItemFun();

	m_model->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ライトの影響をなくす
			lights->SetAmbientLightColor(Vector3(1.0f, 1.0f, 1.0f));
			lights->SetLightEnabled(0, true);
			lights->SetLightEnabled(1, true);
			lights->SetLightEnabled(2, true);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// エミッション色を白に設定する 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
	SetUpEffect();

	Collision::Capsule capsule;
	capsule.r = 1.5f;
	SetCollision(capsule);
}

bool Fun::Update(float elapsedTIme)
{
	//ワールド行列を作成する
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);
	return true;
}

void Fun::Render()
{
	if (m_game && m_model)
	{
		//モデルの描画
		m_model->Draw(m_game->GetContext(),
			*m_game->GetState(),
			m_world, m_game->GetView(),
			m_game->GetProjection());
	}
}
