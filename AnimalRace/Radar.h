#pragma once

//-------------------------
//File:	Radar.h
//
//Name:	
//Date:	2018/11/30
//-------------------------

//#include "Sprite2D.h"

#include "DeviceResources.h"

#include "Player.h"
#include "Enemy.h"

class Radar : public Obj3D
{
public:

	// �R���X�g���N�^
	Radar();

	// ������
	void Initialize();

	// �`��
	void Render();
	//�v���C���[�̐ݒ�֐�
	void SetPlayer(Player* player) { m_player = player; };
	//�G�̐ݒ�֐�
	void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

private:
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;

	ID3D11Device* m_device;
	DX::DeviceResources* m_deviceResources;

	// ���[�_�[�̃A�C�R���̈ʒu
	const float RADAR_POS_X = 699.5f;
	const float RADAR_POS_Y = 100.5f;

	// ���[�_�[�ɉf�鋗��
	const float RADAR_SENSING_DISTANCE = 85.0f;

	// ���[�_�[�̃e�N�X�`���n���h�� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_radarTexture;

	// ���[�_�[�̃v���C���[�̃e�N�X�`���n���h�� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_radarPlayerTexture;

	// ���[�_�[�̓G�̃e�N�X�`���n���h�� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_radarEnemyTexture;

	// �v���C���[�ւ̃|�C���^
	Player* m_player;

	// �G�ւ̃|�C���^
	Enemy* m_enemy;


};