#pragma once
#include "SceneBase.h"
#include "DeviceResources.h"
#include "DebugCamera.h"
#include "Blink.h"
#include "ADX2Le.h"

class SceneTitle : public SceneBase
{
public:
	static const int FLAG_SWITCH = 30;

private:
	DX::StepTimer m_timer;

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

	//�_�ŊǗ��I�u�W�F�N�g
	Blink* m_blink;

	// �_��Flag
	bool m_blinkFlag;

	//�_�Ń^�C�}�[
	int m_blinkTimer;
	//�^�C�g���̈ʒu
	int m_titleX;
	int m_titleY;

	//2D�X�v���C�g
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tBackGround;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTitleRogo;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPushEnter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tExitEnter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDescription;
	
	//�J�[�\���ʒu�Ŏ��̍s�����ς��
	int m_select;
	//BGM
	MyLibrary::ADX2Le* m_adx2le;
	CriAtomExPlaybackId m_criAtomExPlaybackId;

public:
	SceneTitle();
	~SceneTitle();

	//������
	void Initialize() override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render() override;
	//�I������
	void Finalize() override;
	
	void CreateDeviceDependentResources();

	void Reset();
	//�摜�����Ă���
	void TextureSet();
};