#include "pch.h"
#include "Root.h"

#include <Effects.h> 
#include <PrimitiveBatch.h>
#include <VertexTypes.h> 
#include <SimpleMath.h>
#include "Game.h"

#include "ModelDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
Root::Root()
{
	m_hitPlayerFlag = false;
}
/// <summary>
/// デストラクタ
/// </summary>
Root::~Root()
{
}
/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTIme"></param>
/// <returns></returns>
bool Root::Update(float elapsedTIme)
{
	/*for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_outCose[i]->Update(elapsedTIme);
	}*/
	//ワールド行列を作成する
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}
/// <summary>
/// 描画
/// </summary>
void Root::Render()
{
	if (m_game && m_model)
	{
		//モデルの描画
		m_model->Draw(m_game->GetContext(),
			*m_game->GetState(),
			m_world, m_game->GetView(),
			m_game->GetProjection());
		//デバッグ用コリジョンモデルの描画
		DrawCollision();
	}
}

void Root::SetUpEffect()
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

void Root::Finalize()
{
}

//void Root::NoOutMountein(CollisionCapsule* outCose)
//{
//	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
//	{
//		outCose = new CollisionCapsule();
//		Collision::Capsule capsule[ENEMY_HITCHECK_NUM];
//		ModelDate* modelDate = ModelDate::GetInstance();
//		capsule[i].r = 1.0f;
//		switch (i)
//		{
//			//一つ目の山
//		case 0:
//			outCose->SetPosition(Vector3(-4.0f, 12.0f, 88.0f));
//			capsule[i].start = Vector3(  0.0f,  0.0f, 0.0f);
//			capsule[i].end   = Vector3(-65.0f, -12.0f, 0.0f);
//			break;
//		case 1:
//			outCose->SetPosition(Vector3(6.0f, 12.0f, 88.0f));
//			capsule[i].start = Vector3( 10.0f, 0.0f, 0.0f);
//			capsule[i].end   = Vector3(-10.0f, 0.0f, 0.0f);
//			break;
//		case 2:
//			outCose->SetPosition(Vector3(16.0f, 12.0f, 88.0f));
//			capsule[i].start = Vector3( 0.0f,   0.0f, 0.0f);
//			capsule[i].end   = Vector3(65.0f, -12.0f, 0.0f);
//			break;
//		case 3:
//			outCose->SetPosition(Vector3(-4.0f, 12.0f, 112.0f));
//			capsule[i].start = Vector3( 0.0f,   0.0f, 0.0f);
//			capsule[i].end   = Vector3(-65.0f, -12.0f, 0.0f);
//			break;
//		case 4:
//			outCose->SetPosition(Vector3(6.0f, 12.0f, 112.0f));
//			capsule[i].start = Vector3( 10.0f, 0.0f, 0.0f);
//			capsule[i].end   = Vector3(-10.0f, 0.0f, 0.0f);
//			break;
//		case 5:
//			outCose->SetPosition(Vector3(16.0f, 12.0f, 112.0f));
//			capsule[i].start = Vector3( 0.0f,   0.0f, 0.0f);
//			capsule[i].end   = Vector3(65.0f, -12.0f, 0.0f);
//			break;
//		case 6:
//			outCose->SetPosition(Vector3(0.0f, 0.0f, 88.0f));
//			capsule[i].start = Vector3( 65.0f, 0.0f, 0.0f);
//			capsule[i].end   = Vector3(-65.0f, 0.0f, 0.0f);
//			break;
//		case 7:
//			outCose->SetPosition(Vector3(0.0f, 0.0f, 112.0f));
//			capsule[i].start = Vector3( 65.0f, 0.0f, 0.0f);
//			capsule[i].end   = Vector3(-65.0f, 0.0f, 0.0f);
//			break;
//			//二つ目の山
//		case 8:
//			outCose->SetPosition(Vector3(-20.0f, 0.0f, 30.0f));
//			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
//			capsule[i].end = Vector3(0.0f, 10.0f, -49.0f);
//			break;
//		case 9:
//			outCose->SetPosition(Vector3(-20.0f, 10.0f, -29.0f));
//			capsule[i].end = Vector3(0.0f, 0.0f, 10.0f);
//			capsule[i].start = Vector3(0.0f, 0.0f, -10.0f);
//			break;
//		case 10:
//			outCose->SetPosition(Vector3(-20.0f, 0.0f, -90.0f));
//			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
//			capsule[i].end = Vector3(0.0f, 10.0f, 49.0f);
//			break;
//		case 11:
//			outCose->SetPosition(Vector3(-43.0f, 0.0f, 30.0f));
//			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
//			capsule[i].end = Vector3(0.0f, 10.0f, -49.0f);
//			break;
//		case 12:
//			outCose->SetPosition(Vector3(-43.0f, 10.0f, -29.0f));
//			capsule[i].end   = Vector3(0.0f, 0.0f,  10.0f);
//			capsule[i].start = Vector3(0.0f, 0.0f, -10.0f);
//			break;
//		case 13:
//			outCose->SetPosition(Vector3(-43.0f, 0.0f, -90.0f));
//			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
//			capsule[i].end = Vector3(0.0f, 10.0f, 49.0f);
//			break;
//		case 14:
//			outCose->SetPosition(Vector3(-20.0f, 0.0f, -30.0f));
//			capsule[i].end   = Vector3(0.0f, 0.0f,  50.0f);
//			capsule[i].start = Vector3(0.0f, 0.0f, -50.0f);
//			break;
//		case 15:
//			outCose->SetPosition(Vector3(-45.0f, 0.0f, -30.0f));
//			capsule[i].end   = Vector3(0.0f, 0.0f,  50.0f);
//			capsule[i].start = Vector3(0.0f, 0.0f, -50.0f);
//			break;
//		}
//		outCose->SetCollision(capsule[i]);
//	}
//}

//void Root::NoOutPlayer(Player* player)
//{
//	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
//	{
//		if (Collision::HitCheck_Capsule2Capsule(m_outCose[i]->GetCollision()
//			, player->GetCollision()) == true)
//		{
//			//出ないようにする
//			player->OutCose();
//		}
//	}
//}
