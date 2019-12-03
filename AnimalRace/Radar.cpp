//-------------------------
//File:	Radar.cpp
//
//Name:	
//Date:	2018/11/30
//-------------------------

#include "pch.h"
#include "Radar.h"
#include "Game.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Radar::Radar()
{
}

/// <summary>
/// ������
/// </summary>
void Radar::Initialize()
{
	m_device = m_game->GetDevice();
	//// �e�N�X�`���̃��[�h
	CreateWICTextureFromFile(m_device, L"Resources\\Textures\\uoCorse.PNG", nullptr, m_radarTexture.GetAddressOf());
	CreateWICTextureFromFile(m_device, L"Resources\\Textures\\mapPlayer.png", nullptr, m_radarPlayerTexture.GetAddressOf());
	CreateWICTextureFromFile(m_device, L"Resources\\Textures\\mapCpu.png", nullptr, m_radarEnemyTexture.GetAddressOf());
}

/// <summary>
/// �`��
/// </summary>
void Radar::Render()
{
	Vector2 radarPlayerOrigin = Vector2(400.0f, 75.0f);
	Vector2 radarCpuOrigin = Vector2(4.0f, 4.0f);
	float rotation = 0.0f;
}
