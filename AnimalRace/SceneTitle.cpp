#include "pch.h"
#include "SceneTitle.h"
#include <iostream>
#include "SceneManager.h"
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "Game.h"
#include "InputManager.h"
#include "ADX2Le.h"
#include "TextureDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;

SceneTitle::SceneTitle()
{
	//�_�ł̏�����
	m_blink = nullptr;
	m_blinkFlag = false;
	m_blinkTimer = 0;
	//�I���̏�����
	m_select = 1;
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Initialize()
{
	//�^�C�g���̏����ʒu
	m_titleX = 2000;
	m_titleY = 50;
	//�_�ł̐ݒ�
	m_blink->Initialize(30);
	m_blink->Start();

}

void SceneTitle::Update(const DX::StepTimer& timer)
{
	Keyboard::State kb = Keyboard::Get().GetState();
	DirectX::Keyboard::KeyboardStateTracker* tracker = 
		InputManager::GetInstance()->GetKeyTracker();
	//Enter�L�[������
	if (tracker->pressed.Enter)
	{
		//�Z���N�g��ʂֈڍs
		if (m_select == 1)
		{
			SceneManager* sceneManager = SceneManager::GetInstance();
			sceneManager->ChangeSceneID(SceneManager::SceneID::Select);
		}
		if (m_select == 2)
		{
			//WM_QUIT���b�Z�[�W�𑗏o����
			PostQuitMessage(0);
		}	
	}
	//�^�C�g���𓮂���
	m_titleX -= 20;
	if (m_titleX < 100)
	{
		m_titleX = 100;
	}
	//�E����������
	if (tracker->pressed.Right)
	{
		m_select = 1;
	}
	//������������
	if (tracker->pressed.Left)
	{
		m_select = 2;
	}
	//---�_�ł̏���-----
	m_blinkTimer++;
	int a = m_blinkTimer % FLAG_SWITCH;
	if (a >= FLAG_SWITCH / 2)
	{
		m_blinkFlag = true;
	}
	else
	{
		m_blinkFlag = false;
	}
	//------------------
}

void SceneTitle::Render()
{
	auto context = m_game->GetContext();


	//2D�X�v���C�g�̕`��
	m_sprites->Begin(SpriteSortMode_Deferred, m_game->GetState()->NonPremultiplied());
	m_sprites->Draw(m_tBackGround.Get(), Vector2(0, 0));
	m_sprites->Draw(m_tTitleRogo.Get(), Vector2(m_titleX, m_titleY));
	
	if (m_blinkFlag == true)
	{
		//start��I�񂾂�
		if (m_select == 1)
		{
			m_sprites->Draw(m_tPushEnter.Get(), Vector2(500, 450));
		}
		//exit��I�񂾂�
		else if (m_select == 2)
		{
			m_sprites->Draw(m_tExitEnter.Get(), Vector2(100, 450));
		}
		m_sprites->Draw(m_tDescription.Get(), Vector2(200, 550));
	}
	//�I��ł��Ȃ����͏�ɕ\��
	if (m_select == 1)
	{
		m_sprites->Draw(m_tExitEnter.Get(), Vector2(100, 450));

	}
	else if (m_select == 2)
	{
		m_sprites->Draw(m_tPushEnter.Get(), Vector2(500, 450));
	}
	m_sprites->End();
}

void SceneTitle::Finalize()
{
	delete m_blink;
	m_tBackGround.Reset();
	m_tTitleRogo.Reset();
	m_tPushEnter.Reset();
	m_tExitEnter.Reset();
	ADX2Le* adx2le = ADX2Le::GetInstance();
	adx2le->Stop();
}

void SceneTitle::CreateDeviceDependentResources()
{
	m_adx2le = MyLibrary::ADX2Le::GetInstance();
	m_adx2le->LoadAcb(L"SceneTitle.acb", L"SceneTitle.awb");
	m_criAtomExPlaybackId = m_adx2le->Play(0);

	//�X�v���C�g�o�b�`�̍쐬
	ID3D11Device* device = m_game->GetDevice();
	ID3D11DeviceContext* context = m_game->GetContext();
	//�摜�����Ă���
	TextureSet();
	// �X�v���C�g�o�b�`�̍쐬
	m_sprites = std::make_unique<SpriteBatch>(context);
	m_blink = new Blink();
}

void SceneTitle::Reset()
{
	m_blink->Reset(true);
}

//�摜�����Ă���
void SceneTitle::TextureSet()
{
	TextureDate* textureDate = TextureDate::GetInstance();
	m_tBackGround  = textureDate->GetBackGround();
	m_tTitleRogo   = textureDate->GetTitleRogo();
	m_tPushEnter   = textureDate->GetPushEnter();
	m_tExitEnter   = textureDate->GetExitEnter();
	m_tDescription = textureDate->GetTitleDescription();
}

