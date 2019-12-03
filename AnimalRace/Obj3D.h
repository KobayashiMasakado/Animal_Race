#pragma once
/// /// <summary>
/// Obj3D
/// 
/// 3D�I�u�W�F�N�g��`�悷�邽�߂̃N���X
/// Day.6/256/25
/// Masakado Kobayashi
#include "pch.h"
class Game;
#include "TaskManager.h"

class Obj3D : public Task
{
protected:
	//�Q�[���I�u�W�F�N�g�ւ̃|�C���^
	Game* m_game;
	//���f���n���h��
	DirectX::Model* m_model;
	ID3D11ShaderResourceView* m_texture;

	// ���x
	DirectX::SimpleMath::Vector3 m_vec;

	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//��]
	DirectX::SimpleMath::Quaternion m_rotation;

	//��]
	DirectX::SimpleMath::Quaternion m_rotationZ;

	//�����x
	DirectX::SimpleMath::Vector3 m_accel;

	//�p�x
	DirectX::SimpleMath::Quaternion m_dirSpeed;
	DirectX::SimpleMath::Vector3 m_dirS;

	//���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

public:
	//�R���X�g���N�^
	Obj3D();
	//�X�V
	virtual bool Update(const float elapsedTime);

	//�`��
	virtual void Render();

	// �Z�b�^�[�֐�
	//�Q�[���I�u�W�F�N�g��ݒ肷��֐�
	void SetGame(Game* game)
	{
		m_game = game;
	}

	//���f���n���h����ݒ肷��֐�
	void SetModel(DirectX::Model* model)
	{
		m_model = model;
	}

	//���f���n���h����ݒ肷��֐�
	void SetTexture(ID3D11ShaderResourceView* texture)
	{
		m_texture = texture;
	}
	
	// ���x��ݒ肷��֐�
	void SetVec(DirectX::SimpleMath::Vector3 vec)
	{
		m_vec = vec;
	}

	// �����x��ݒ肷��֐�
	void SetAccel(DirectX::SimpleMath::Vector3 accel)
	{
		m_accel = accel;
	}

	// �p�x��ݒ肷��֐�
	void SetDir(DirectX::SimpleMath::Quaternion dirS)
	{
		m_dirSpeed = dirS;
	}
	void SetDir(DirectX::SimpleMath::Vector3 dirS)
	{
		m_dirS = dirS;
	}

	//�ʒu�ݒ肷��֐�
	void SetPosition(DirectX::SimpleMath::Vector3 position)
	{
		m_position = position;
	}

	//��]�ݒ肷��֐�
	void SetRotation(DirectX::SimpleMath::Quaternion rotation)
	{
		m_rotation = rotation;
	}

	// �Q�b�^�[
	//�Q�[���I�u�W�F�N�g��ݒ肷��֐�
	Game* GetGame()
	{
		return m_game;
	}

	//���f���n���h����ݒ肷��֐�
	DirectX::Model* GetModel()
	{
		return m_model;
	}

	
	ID3D11ShaderResourceView* GetTexture()
	{
		return m_texture;
	}
	// ���x��ݒ肷��֐�
	const DirectX::SimpleMath::Vector3& GetVec()
	{
		return m_vec;
	}

	// �����x��ݒ肷��֐�
	const DirectX::SimpleMath::Vector3& GetAccel()
	{
		return m_accel;
	}

	// �p�x��ݒ肷��֐�
	const DirectX::SimpleMath::Quaternion& GetDirQ()
	{
		return m_dirSpeed;
	}
	const DirectX::SimpleMath::Vector3& GetDirV()
	{
		return m_dirS;
	}

	//�ʒu�ݒ肷��֐�
	const DirectX::SimpleMath::Vector3& GetPosition()
	{
		return m_position;
	}

	//��]�ݒ肷��֐�
	const DirectX::SimpleMath::Quaternion& GetRotation()
	{
		return m_rotation;
	}
};