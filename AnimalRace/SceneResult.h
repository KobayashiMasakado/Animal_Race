#pragma once

#include "SceneBase.h"
#include "DeviceResources.h"
#include "DebugCamera.h"
#include "ScenePlay.h"
#include "Number.h"

class SceneResult : public SceneBase
{
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
	//�e�N�X�`��
	//�w�i
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tBackGround;
	//�����������H
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tHerbivore;
	//�����������H
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCarnivore;
	//���������G�H
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOmnivorous;
	//�s�k�������H
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDHerbivore;
	//�s�k�������H
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDCarnivore;
	//�s�k�����G�H
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDOmnivorous;
	//playerwin�Əo��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPlayerWin;
	//cpuwin�Əo��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCpuWin;
	//youwin�Əo��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tYouWin;
	//youlose�Əo��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tYouLose;
	//�������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDecision;
	//:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCComma;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCCommaS;
	//����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCNum[10];
	//�������o��
	Number m_number[3];

	//�_�ŊǗ��I�u�W�F�N�g
	Blink* m_blink;

	// �_��Flag
	bool m_blinkFlag;

	//�_�Ń^�C�}�[
	int m_blinkTimer;

	//��
	MyLibrary::ADX2Le* m_adx2le;
	CriAtomExPlaybackId m_criAtomExPlaybackId;
public:
	SceneResult();
	~SceneResult();

	//������
	void Initialize() override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��;
	void Render() override;

	void CreateDeviceDependentResources();

	//�I������
	void Finalize() override;

	void Reset();
	//�摜�����Ă���
	void TextureSet();

	//Set�֐�
	//�Q�b�^�[�֐�
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