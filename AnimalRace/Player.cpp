#include "pch.h"
#include "Player.h"
#include "Game.h"
#include "Item.h"
#include "ModelDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	: m_effectManagerbuf{ nullptr }
{
	m_itemEffect = nullptr;
	m_y = 0;
	//モデルの作成
	m_accel = Vector3::Zero;
	m_dirS = Vector3::Zero;
	m_effectManager = m_effectManagerbuf;
}
/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
}
bool Player::Update(const DX::StepTimer & stepTimer)
{
	Character::Update(stepTimer);
	
	// 摩擦
	m_vec.z *= FRICTION;
	m_vec.x *= FRICTION;
	// 座標の移動
	Vector3 vec = Vector3::Transform(m_vec, m_rotation);
	m_position += vec;
	static float rot = 0.0f;
	rot++;
	float r = XMConvertToRadians(45.0f) * sinf(XMConvertToRadians(rot));
	//平行移動行列
	Matrix trans = Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);
	return true;
}
/// <summary>
/// 描画
/// </summary>
void Player::Render()
{
	m_effectManager = m_effectManagerbuf;
	Character::RenderEffect(true);
	//モデルの描画
	//体
	m_model->Draw(m_game->GetContext(), *m_game->GetState(),
		m_world, m_game->GetView(), m_game->GetProjection());
	//足
	static float rot = 0.0f;
	rot++;
	float r = XMConvertToRadians(25.0f) * sinf(XMConvertToRadians(rot*m_vec.z));
	Matrix world;
	switch (m_animalType)
	{
		//肉食の足
	case ANIMAL_TYPE::CARNIVORE:
		LegModelRender(world, r, Vector3(0, 1, 0));
		break;
		//草食の足
	case ANIMAL_TYPE::HERBIVORE:
		LegModelRender(world, r, Vector3(0, 2, 0));
		break;
		//雑食の足
	case ANIMAL_TYPE::OMNIVOROUS:
		LegModelRender(world, r, Vector3(0, 2, 0));
		break;
	}
	world = Matrix::CreateScale(2.0f)*Matrix::CreateRotationX(0.0f)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (Vector3(0, 0.0f, 0)));
	m_shadow->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
}

void Player::Finalize()
{
	delete m_sSelect;
}

//プレイヤーを生成
void Player::PlayerCreate()
{
	Collision::Capsule capsulePlayer;
	SetPosition(Vector3(-95.0f, m_y, -10.0f));
	//カプセル型のコリジョンをつける
	capsulePlayer.start = Vector3(0.3f, 0.0f, 0.2f); 		//境界球の中心
	capsulePlayer.end = Vector3(0.3f, 3.0f, 0.2f); 		    //境界球の中心
	capsulePlayer.r = 0.6f;							     	//半径
	SetCollision(capsulePlayer);
	ModelDate* modelDate = ModelDate::GetInstance();
	//モデルの作成
	switch (m_animalType)
	{
		//肉食
	case ANIMAL_TYPE::CARNIVORE:
		m_model = modelDate->GetBodyCPU();        //胴体
		m_modelLegL = modelDate->GetLegLCPU();    //左足
		m_modelLegR = modelDate->GetLegRCPU();    //右足
		break;
		//草食
	case ANIMAL_TYPE::HERBIVORE:
		m_model = modelDate->GetBodyCPU2();       //胴体
		m_modelLegL = modelDate->GetLegLCPU2();	  //左足
		m_modelLegR = modelDate->GetLegRCPU2();	  //右足
		break;
		//雑食
	case ANIMAL_TYPE::OMNIVOROUS:
		m_model = modelDate->GetPlayer();         //胴体
		m_modelLegL = modelDate->GetLegLPlayer(); //左足
		m_modelLegR = modelDate->GetLegRPlayer(); //右足
		break;
	}
	m_shadow = modelDate->GetShadow();
	SetUpEffect();
	//ワールド行列を作成する
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);
}

void Player::EffectRender()
{
	m_effectManager->Render(false);
}

void Player::OutCose()
{
	m_vec.z -= 2.0f;
}
/// <summary>
/// プレイヤーの操作
/// </summary>
void Player::PlayerCommand()
{
	std::list<Command*> command = m_inputHandle.HandleInput();
	for (std::list<Command*>::iterator ite = command.begin(); ite != command.end(); ite++)
	{
		(*ite)->execute(this);
	}
}
/// <summary>
/// プレイヤーキャラの違い
/// </summary>
void Player::PlayerAnimalType()
{
	switch (m_animalType)
	{
		//肉食
	case ANIMAL_TYPE::CARNIVORE:
		m_accel = Vector3(0, 0, 0.1f);
		m_dirS.y = 2.0f;
		break;
		//草食
	case ANIMAL_TYPE::HERBIVORE:
		m_accel = Vector3(0, 0, 0.4f);
		m_dirS.y = 0.9f;
		break;
		//雑食
	case ANIMAL_TYPE::OMNIVOROUS:
		m_accel = Vector3(0, 0, 0.2f);
		m_dirS.y = 1.1f;
		break;
	}
}
//足のモデルの描画
void Player::LegModelRender(Matrix& world, float r, Vector3 posdif)
{
	//左足
	world = Matrix::CreateRotationX(r)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (posdif));
	m_modelLegL->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
	//右足
	world = Matrix::CreateRotationX(-r)*Matrix::CreateFromQuaternion(m_rotation) *Matrix::CreateTranslation(m_position + (posdif));
	m_modelLegR->Draw(m_game->GetContext(), *m_game->GetState(), world, m_game->GetView(), m_game->GetProjection());
}

void Player::EffectUpdate(const DX::StepTimer& stepTimer)
{
	m_effectManager->Update(stepTimer);
}

void Player::SetUpEffect()
{
	m_model->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ライトの影響をなくす
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false);
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// エミッション色を白に設定する 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
}
