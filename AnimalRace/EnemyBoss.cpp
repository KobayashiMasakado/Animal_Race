#include "pch.h"
#include "EnemyBoss.h"

#include "Game.h"
#include <time.h>
#include "ModelDate.h"
#include "Root.h"

#include<stdio.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
EnemyBoss::EnemyBoss()
{
	m_targetElem = WARP_ZERO;
	m_itemCPUCheck = false;
	m_itemEffect = nullptr;
	//当たり判定の設定
	m_sphere.r = 0.0f;
	m_sphere.center = Vector3(0, 0, 0);
}
/// <summary>
/// デストラクタ
/// </summary>
EnemyBoss::~EnemyBoss()
{
	m_debug.reset();
}
/// <summary>
/// 更新
/// </summary>
bool EnemyBoss::Update(const DX::StepTimer & stepTimer)
{
	//---AIの処理(次の目的地までの角度を計算する)---------
	// 目的地に到着
	if (Collision::HitCheck_Sphere2Capsule(m_sphere, GetCollision()))
	{
		//目的地を変更する
		m_targetElem++;
		//次の目的地を割り出す
		m_sphere.center = m_CPUPoint[m_targetElem % WARP_MAX];
	}
	//今いる地点から目的地までの距離を求める
	Vector3 targetVec = m_CPUPoint[m_targetElem % WARP_MAX] - m_position;
	//上記の値を正規化する
	targetVec.Normalize();
	//右の値(方向）を求める
	Vector3 right = Vector3::Transform(Vector3::Right, m_rotation);
	//内積を求める
	float cosine = targetVec.Dot(right);
	//cosineが1を超えないようにする
	if (cosine > 1.0f)
	{
		cosine = 1.0f;
	}
	//角度を求める
	float degree = XMConvertToDegrees(cosine);
	//絶対値を求め一定値以上で回転する
	if (abs(degree) > 5.0f)
	{
		//正面から左方向に向いたら
		if (cosine > 0.0f)
		{
			Left();      // 左に旋回
		}
		else
		{
			Right();     // 右に旋回
		}
	}
	//-----------------
	Character::Update(stepTimer);

	Vector3 vec = Vector3::Transform(m_vec, m_rotation);
	m_position += vec;
	return true;
}

void EnemyBoss::Render()
{
	Character::RenderEffect(true);
	if (m_game && m_model)
	{
		//モデルの描画
		//体
		m_model->Draw(m_game->GetContext(), *m_game->GetState(),
			m_world, m_game->GetView(), m_game->GetProjection());
		//ワールド行列を作成する
		m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);
		m_model->Draw(m_game->GetContext(), *m_game->GetState(), m_world, m_game->GetView(), m_game->GetProjection());
		//足
		static float rot = 0.0f;
		rot++;
		float r = XMConvertToRadians(25.0f) * sinf(XMConvertToRadians(rot*m_vec.z));
		Matrix world;
		switch (m_animalType)
		{
		case ANIMAL_TYPE::CARNIVORE:
			LegModelRender(world, r, Vector3(0, 1, 0));
			break;
		case ANIMAL_TYPE::HERBIVORE:
			LegModelRender(world, r, Vector3(0, 2, 0));
			break;
		case ANIMAL_TYPE::OMNIVOROUS:
			LegModelRender(world, r, Vector3(0, 2, 0));
			break;
		}
		world = Matrix::CreateScale(2.0f)*Matrix::CreateRotationX(0.0f)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (Vector3(0, 0.0f, 0)));
		m_shadow->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
	}
}

void EnemyBoss::Finalize()
{
}

void EnemyBoss::SetUpEffect()
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
//左旋回する
void EnemyBoss::Left()
{
	Vector3 up = Vector3::Transform(Vector3::Up, m_rotation);
	m_rotation *= Quaternion::CreateFromAxisAngle(up, XMConvertToRadians(10.0f));

}
//右旋回する
void EnemyBoss::Right()
{
	Vector3 up = Vector3::Transform(Vector3::Up, m_rotation);
	m_rotation *= Quaternion::CreateFromAxisAngle(up, XMConvertToRadians(-10.0f));
}

void EnemyBoss::LegModelRender(DirectX::SimpleMath::Matrix& world, float r, DirectX::SimpleMath::Vector3 posdif)
{
	//左足
	world = Matrix::CreateRotationX(r)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (posdif));
	m_modelLegL->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
	//右足
	world = Matrix::CreateRotationX(-r)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (posdif));
	m_modelLegR->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
}
