#pragma once

#include "SceneBase.h"
#include "DeviceResources.h"
#include "DebugCamera.h"
#include "Character.h"
#include "Item.h"
#include "Blink.h"

class Player;
class SceneSelect : public SceneBase
{
private:
	//�J�[�\���̈ړ���
	static const int CURSOR_MOVE = 273;
	//�J�[�\���̈ړ����E
	static const int CURSOR_MAX = 90;
	static const int CURSOR_MIX = 440;
private:
	DX::StepTimer                           m_timer;

	// Device resources.
	DX::DeviceResources* m_deviceResources;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;

	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_debugCamera;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;

	//�J�[�\���ړ�
	int m_x;
	int m_y;

	//�L�����I��
	int m_charaNum;

	//�_�ł̊Ԋu
	int m_blinkInterval;

	//������I��
	int m_charaSerect;
	//�I�񂾓������v���C���[�ɂ���
	ANIMAL_TYPE m_playerType;
	ANIMAL_TYPE m_cpuType;
	ANIMAL_TYPE m_cpuSType;

	//�e�N�X�`��
	//�w�i
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tBackGround;
	//���N�_�̊G
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCamel;
	//�g���̊G
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTiger;
	//�_�`���E�̊G
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOstrich;
	//���N�_�̃p�����[�^
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCamelParameter;
	//�g���̃p�����[�^
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTigerParameter;
	//�_�`���E�̃p�����[�^
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOstrichParameter;
	//�I���̃J�b�R
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tSelectPointer;
	//�������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDescription;
	
	//�_�ŊǗ��I�u�W�F�N�g
	Blink* m_blink;
	// �_��Flag
	bool m_blinkFlag;

	//�_�Ń^�C�}�[
	int m_blinkTimer;

public:
	SceneSelect();
	~SceneSelect();

	//������
	void Initialize() override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render() override;
	void CreateDeviceDependentResources();
	//�I������
	void Finalize() override;

	void Reset();
	int GetCharaSelect(){ return m_charaSerect;}

	//Set�֐�
	//�Q�b�^�[�֐�
	ANIMAL_TYPE GetPlayerAnimalType() const
	{
		return m_playerType;
	}
	ANIMAL_TYPE GetCPUAnimalType() const
	{
		return m_cpuType;
	}
	ANIMAL_TYPE GetCPUSAnimalType() const
	{
		return m_cpuSType;
	}

	void TextureSet();

	//�f�o�C�X���擾����֐�
	ID3D11Device* GetDevice() const
	{
		return m_deviceResources->GetD3DDevice();
	}

	//�R���e�L�X�g���擾����֐�
	ID3D11DeviceContext* GetContext() const
	{
		return m_deviceResources->GetD3DDeviceContext();
	}
	//�R�����X�e�[�g���擾����֐�
	DirectX::CommonStates* GetState() const
	{
		return m_states.get();
	}
	//�r���[�s����擾����֐� 
	const DirectX::SimpleMath::Matrix& GetView() const
	{
		return m_view;
	}
	//�ˉe�s����擾����֐�
	const DirectX::SimpleMath::Matrix& GetProjection() const
	{
		return m_projection;
	}
	//Set�֐�
	void SetDeviceResources(DX::DeviceResources* deviceResources)
	{
		this->m_deviceResources = deviceResources;
	}

	void SetProjection(const DirectX::SimpleMath::Matrix& projection)
	{
		this->m_projection = projection;
	}

	
};