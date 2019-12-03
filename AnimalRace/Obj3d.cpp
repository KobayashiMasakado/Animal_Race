#include "pch.h"
#include "Obj3D.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


Obj3D::Obj3D()
	:
	m_game(nullptr),
	m_model(nullptr),
//	m_modelChara(nullptr),
	m_accel(0, 0, 0),
	m_dirS(0,0,0)
{
}

bool Obj3D::Update(float elapsedTime)
{
	//ワールド行列を作成
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}

void Obj3D::Render()
{
	if (m_model && m_game/* && m_modelChara*/)
	{
		//モデルの描画
		m_model->Draw(m_game->GetContext(), *m_game->GetState(),
			m_world, m_game->GetView(), m_game->GetProjection());
		//モデルの描画
		//m_modelChara->Draw(m_game->GetContext(), *m_game->GetState(),
		//	m_world, m_game->GetView(), m_game->GetProjection());
	}
}

