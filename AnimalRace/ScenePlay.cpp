#include "pch.h"
#include "ScenePlay.h"
#include <time.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "ModelDate.h"
#include "GameCamera.h"
#include "Game.h"
#include "SceneManager.h"
#include <time.h>
#include <cstdio>
#include "ADX2Le.h"
#include "TextureDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;

const float EFFECT_DUST_LIMIT = 0.3f;

ScenePlay::ScenePlay()
{
	//Effect�̃}�l�[�W���[
	m_eUpManager = nullptr;
	m_eDownManager = nullptr;
	m_eShitManager  = nullptr;
	m_eDustManager = nullptr;
}

ScenePlay::~ScenePlay()
{
}

void ScenePlay::Initialize()
{
	//�J�E���g�_�E���̏�����
	m_count = 0;
	//�~���b�̏�����	
	m_miri = 0;
	m_miriHand = 0;
	//�b�̏�����	
	m_sec = 0;
	//���̏�����	
	m_min = 0;
    //�t���h�~����̏�����	
	m_checkPoint = 0;
    //�������Ԃ̏�����	
	m_second = 0;
	//���U���g�ɏ��������L������\�����邽�߂̃f�[�^�̏�����
	m_winCharacter = 0;
	//�f�o�b�O�J�����̏�����
	m_debugCamera = std::make_unique<DebugCamera>(800, 600);
	//����
	CreateDeviceDependentResources();
	
	m_charaGoal = nullptr;

	m_resultRotation = 0;

	m_countResult = 0;
}

void ScenePlay::Update(const DX::StepTimer& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());
	// �f�o�b�O�J�����̍X�V
	m_debugCamera->Update();
	// �v���C���[�̍X�V
	m_player->Update(timer);
	//m_root->Update(elapsedTime);
	// �A�C�e���̍X�V
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (m_item[i] != nullptr)
		{
			m_item[i]->Update(elapsedTime);
		}
	}
    //�J�E���g�_�E���i�����̓J�E���g�A�b�v�j
	m_count += 1;
	/////�X�V/////////////////////
	//�S�[���̍X�V
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->Update(elapsedTime);
	}
	//�R�[�X�̓����蔻��̍X�V
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_outCose[i]->Update(elapsedTime);
	}
	m_skyCollision->Update(elapsedTime);
	m_courseWaterCollision->Update(elapsedTime);
	///////�����蔻��////////////
	CollisionUpdate();
	Keyboard::State kb = Keyboard::Get().GetState();
	//�J�E���g�_�E�����I�������
	if (m_count > GAME_START_TIME)
	{
		//�v���C���[�̃S�[������
		if (m_player->CharaGoal())
		{
			m_winCharacter = 1;
			m_charaGoal = m_player;
		}
		//CPU�̃S�[������
		if (m_cpu->CharaGoal())
		{
			m_winCharacter = 2;
			m_charaGoal = m_cpu;
		}
		if (m_cpuS->CharaGoal())
		{
			m_winCharacter = 3;
			m_charaGoal = m_cpuS;
		}
		//�S�[��������
		if (m_charaGoal != nullptr)
		{
			m_countResult += elapsedTime;
			if (m_countResult > 3.0f)
			{
				//�V�[���ړ�(���U���g)
				SceneManager* sc = SceneManager::GetInstance();
				sc->ChangeSceneID(SceneManager::SceneID::Result);
			}
		}
		else if (m_charaGoal == nullptr)
		{
			//�������Ԃ̏���
			m_second++;
			m_player->PlayerCommand();
			if (m_player->GetVec().z > EFFECT_DUST_LIMIT)
			{
				m_player->EffectUpdate(timer);
			}
			//CPU�̈ړ�
			m_cpu->MoveFront();
			m_cpuS->MoveFront();
			//CPU�̍X�V
			m_cpu->Update(timer);
			m_cpuS->Update(timer);
		}
		//�L�����̈ړ�
		m_player->PlayerAnimalType();
		
	}
	//�b�̃��Z�b�g
	if (m_sec >= 60) m_sec = 0;
}

void ScenePlay::Render()
{
	auto context = m_game->GetContext();

	GameCamera* ganeCamera = GameCamera::GetInstance();
	//�Ǐ]�J����
	// �r���[�s��̍쐬
	Vector3 cameraPos = Vector3(0.0f, 5.0f, -20.0f); //�J�����̌Œ肷��ʒu
	Vector3 target;

	if (m_charaGoal == nullptr)
	{
		ganeCamera->ChaseCamera(m_player->GetPosition(), m_player->GetRotation());
	}
	else
	{
		m_resultRotation += XMConvertToRadians(1.0f);
		ganeCamera->ResultCamera(m_charaGoal->GetPosition(), m_resultRotation);
	}

	// �Ǐ]
	m_game->SetView(ganeCamera->GetViewMatrix());
	// �f�o�b�O�J����
//	m_game->SetView(m_debugCamera->GetCameraMatrix()); 
	/////�`��///////////////////
	//�v���C���[�̕`��
    m_player->Render();
	if (m_player->GetVec().z > EFFECT_DUST_LIMIT)
	{
		m_player->EffectRender();
	}
	//CPU�̕`��
	m_cpu->Render();
	m_cpuS->Render();
	//�A�C�e���̕`��
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (m_item[i] != nullptr)
		{
			m_item[i]->Render();
		}
	}
	//�S�[���̕`��
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->Render();
	}
	//�����蔻��̕`��
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_outCose[i]->Render();
	}
	m_skyCollision->Render();
	m_courseWaterCollision->Render();
	
	//////////////////////////////
	//3D�X�v���C�g 
	Matrix worldGoal;
	worldGoal = Matrix::CreateScale(1.0f) * Matrix::CreateTranslation(Vector3(-103.5f, 0.0f, -12.0f));
	m_goalModel->Draw(context, *m_game->GetState(), worldGoal, m_game->GetView(), m_game->GetProjection());
	//����
	Matrix worldPra;
	worldPra = Matrix::CreateScale(1.0f) * Matrix::CreateTranslation(Vector3(0.0f, 1.99f, 0.0f));
	m_prairie->Draw(context, *m_game->GetState(), worldPra, m_game->GetView(), m_game->GetProjection());
	/////////////////////////////////////////
	// ��
	Matrix worldSky;
	worldSky = Matrix::CreateScale(3.5f) * Matrix::CreateTranslation(Vector3(10.0f, -0.3f, -10.0f));
	m_skydome->Draw(context, *m_game->GetState(), worldSky, m_game->GetView(), m_game->GetProjection());
    /////////////////////////////////////////
	//��
	Matrix worldRoot;
	worldPra = Matrix::CreateTranslation(Vector3(0.0f, -0.0f, 0.0f));
	m_floorModel->Draw(context, *m_game->GetState(), worldRoot, m_game->GetView(), m_game->GetProjection());
	//////////////////////////////
	//�����܂�
	Matrix worldCourseWater;
	worldCourseWater = Matrix::CreateTranslation(Vector3(110.0f, -0.7f, 0.0f));
	m_courseWater->Draw(context, *m_game->GetState(), worldCourseWater, m_game->GetView(), m_game->GetProjection());
	//////////////////////////////
	//���[�_�[
	Vector2 radarPlayerOrigin = Vector2(400.0f, 75.0f);
	Vector2 radarCpuOrigin = Vector2(4.0f, 4.0f);
	float rotation = 0.0f;
	//////////////////////////////
	//2D�X�v���C�g�̕`��
	m_sprites->Begin(SpriteSortMode_Deferred, m_game->GetState()->NonPremultiplied());
	//�^�C��--------------------------------------
	//�J�E���g�_�E��
	//�~���b
	if (m_charaGoal == nullptr)
	{
		m_miri = m_second;
		m_miriHand = m_miri % TIME_MINUTE;
		m_number[2].SetNum(m_miriHand);
		m_number[2].SetPos(Vector2(240, 0));
		m_number[2].Draw(m_sprites.get());
		//�b
		m_sec = m_miri / TIME_MINUTE;
		int sec = m_sec % TIME_MINUTE;
		m_number[1].SetNum(sec);
		m_number[1].SetPos(Vector2(120, 0));
		m_number[1].Draw(m_sprites.get());
		//��
		m_min = m_sec / TIME_MINUTE;
		int min = m_min % TIME_MINUTE;
		m_number[0].SetNum(min);
		m_number[0].SetPos(Vector2(0, 0));
		m_number[0].Draw(m_sprites.get());
		
		//�^�C���\��
		m_sprites->Draw(m_tCComma.Get(), Vector2(80, 0));
		m_sprites->Draw(m_tCComma.Get(), Vector2(200, 0));
		
	}
	//�J�E���g�_�E�����I�������
	if (m_count < 200)
	{
		//��������e�L�X�g
		m_sprites->Draw(m_tOperation.Get(), Vector2(170, 75));
		//�A�C�e���摜
		m_sprites->Draw(m_tLeaf.Get(), Vector2(350, 320));
		m_sprites->Draw(m_tMeat.Get(), Vector2(500, 320));
		m_sprites->Draw(m_tShit.Get(), Vector2(650, 320));
		//�A�C�e���摜�e�L�X�g
		m_sprites->Draw(m_tLeafText.Get(), Vector2(350, 450));
		m_sprites->Draw(m_tMeatText.Get(), Vector2(500, 450));
		m_sprites->Draw(m_tShitText.Get(), Vector2(650, 450));
	}

	for (int i = 3; i > 0; i--)
	{
		if (m_count >  ((i * TIME_MINUTE) - GAME_START_TIME) * -1 &&
			m_count < (((i * TIME_MINUTE) - GAME_START_TIME) * -1) + (TIME_MINUTE - 1))
		{
			//�J�E���g�_�E���\��
			m_sprites->Draw(m_tCountDown[i-1].Get(), Vector2(350, 200));
		}
	}

	if (m_count > GAME_START_TIME && m_count < 200)
	{
		//�J�E���g�_�E���I�����̊|����
		m_sprites->Draw(m_tCGo.Get(), Vector2(280, 200));
	}
	//�S�[������
	if (m_player->CharaGoal() || m_cpu->CharaGoal() || m_cpuS->CharaGoal())
	{
		m_sprites->Draw(m_tGameEnd.Get(), Vector2(150, 150));
	}
	///////////////////////////////////////
	//���[�_�[�̕`��
	m_sprites->Draw(m_tRadar.Get(), Vector2(0, 320));
	//���[�_�[�̃v���C���[�̕`��                                                 �ʒu  
	m_sprites->Draw(m_tRPlayer.Get(), Vector2(m_player->GetPosition().x + 130, m_player->GetPosition().z + 470));
	//���[�_�[�̃v���C���[�̕`��                                                 �ʒu  
	m_sprites->Draw(m_tREnemy.Get(), Vector2(m_cpu->GetPosition().x + 130, m_cpu->GetPosition().z + 470));
	//���[�_�[�̃v���C���[�̕`��                                                 �ʒu  
	m_sprites->Draw(m_tREnemyS.Get(), Vector2(m_cpuS->GetPosition().x + 130, m_cpuS->GetPosition().z + 470));
	///////////////////////////////////////
	m_sprites->End();
}

void ScenePlay::Finalize()
{ 
	delete m_player;
	delete m_cpu;
	delete m_cpuS;
	m_skydome.reset();
	m_goalModel.reset();
	m_skyCollision.reset();
	m_courseWaterCollision.reset();
	m_prairie.reset();
	m_floorModel.reset();
	m_floorMesh.reset();
	m_courseWater.reset();
	m_sprites.reset();
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i].reset();
	}
	for (int i = 0; i < ITEM_MAX; i++)
	{
		m_item[i].reset();
	}
	m_tTime.Reset();
	m_tPlayerGoal.Reset();
	m_tCPUGoal.Reset();
	m_tRadar.Reset();
	m_tRPlayer.Reset();
	m_tREnemy.Reset();
	m_tREnemyS.Reset();
	for (int i = 0; i < 10; i++)
	{
		m_tCNum[i].Reset();
	}
	for (int i = 0; i < 3; i++)
	{
		m_tCountDown[i].Reset();
	}
	m_tCComma.Reset();
	m_tCCommaS.Reset();
	
	m_tCGo.Reset();
	m_tFlipGoal.Reset();
	m_tOperation.Reset();
	m_tGameEnd.Reset();
	m_tLeaf.Reset();
	m_tLeafText.Reset();
	m_tMeat.Reset();
	m_tMeatText.Reset();
	m_tShit.Reset();
	m_tShitText.Reset();
	/*for (int i = 0; i < TIME_SET_NUM; i++)
	{
		delete &m_number[i];
	}*/
	if (m_eShitManager)
	{
		m_eShitManager->Lost();
		delete m_eShitManager;
	}
	if (m_eUpManager)
	{
		m_eUpManager->Lost();
		delete m_eUpManager;
	}
	if (m_eDownManager)
	{
		m_eDownManager->Lost();
		delete m_eDownManager;
	}
	if (m_eDustManager)
	{
		m_eDustManager->Lost();
		delete m_eDustManager;
	}
	ADX2Le* adx2le = ADX2Le::GetInstance();
	adx2le->Stop();
}

void ScenePlay::CreateDeviceDependentResources()
{
	//��
	m_adx2le = MyLibrary::ADX2Le::GetInstance();
	m_adx2le->LoadAcb(L"FightRace.acb", L"FightRace.awb");
	m_criAtomExPlaybackId = m_adx2le->Play(0);

	//�X�v���C�g�o�b�`�̍쐬
	ID3D11Device* device = m_game->GetDevice();
	ID3D11DeviceContext* context = m_game->GetContext();
	// �X�v���C�g�o�b�`�̍쐬
	m_sprites = std::make_unique<SpriteBatch>(context);
	//�摜�����Ă���
	TextureSet();
	//�����̕`��--------------------------------
	for (int i = 0; i < TIME_SET_NUM; i++)
	{
		for (int j = 0; j < TIME_TYPE_NUM; j++)
		{
			m_number[i].SetTexture(j, m_tCNum[j].Get());
		}
	}
	//-------------------------------------------
	// ���f���̓ǂݍ���
	ModelDate* modelDate = ModelDate::GetInstance();
	SceneManager* sceneManager = SceneManager::GetInstance();
	// �v���C���[�̍쐬
	m_player = new Player();
	m_player->SetGame(m_game);
	m_player->SetAnimalType(sceneManager->GetSceneSelect()->GetPlayerAnimalType());
	m_player->PlayerCreate();
	// CPU�̍쐬
	m_cpu = new Enemy();
	m_cpu->SetGame(m_game);
	m_cpu->SetAnimalType(sceneManager->GetSceneSelect()->GetCPUAnimalType());
	m_cpu->CPUCreate();
	m_cpuS = new CPU();
	m_cpuS->SetGame(m_game);
	m_cpuS->SetAnimalType(sceneManager->GetSceneSelect()->GetCPUSAnimalType());
	m_cpuS->CPUCreate();

	//-------------�G�t�F�N�g-------------
	RECT outputSize = m_game->GetDeviceResources()->GetOutputSize();
	UINT backBufferWidth = std::max<UINT>(outputSize.right - outputSize.left, 1);
	UINT backBufferHeight = std::max<UINT>(outputSize.bottom - outputSize.top, 1);
	Vector3 camera = Vector3(0, 0, -5);
	Matrix view = Matrix::CreateLookAt(camera,
		Vector3::Zero, Vector3::UnitY);
	Matrix proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(backBufferWidth) / float(backBufferHeight), 0.1f, 1000.f);
	//�A�C�e��(UP)
	m_eUpManager = new EffectManager();
	m_eUpManager->Create(m_game->GetDeviceResources(), L"Textures\\gameW.png", 5);
	m_eUpManager->InitializeBut(0.05f, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	m_eUpManager->SetRenderState(camera, view, proj);
	//�A�C�e��(DOWN)
	m_eDownManager = new EffectManager();
    m_eDownManager->Create(m_game->GetDeviceResources(), L"Textures\\gameB.png", 4);
	m_eDownManager->InitializeBut(0.03f, Vector3(0.0f, 0.9f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
	m_eDownManager->SetRenderState(camera, view, proj);
	//�A�C�e��(Shit)
	m_eShitManager = new EffectManager();
	m_eShitManager->Create(m_game->GetDeviceResources(), L"Textures\\gameB.png", 4);
	m_eShitManager->InitializeBut(0.03f, Vector3(0.0f, 0.9f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
	m_eShitManager->SetRenderState(camera, view, proj);
	//dust
	m_eDustManager = new EffectManager();
	m_eDustManager->Create(m_game->GetDeviceResources(), L"Textures\\gameF.png", 4);
	m_eDustManager->InitializeBut(0.2f, Vector3(0.0f, -0.1f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
	m_eDustManager->SetRenderState(camera, view, proj);

	// ���f����ǂݍ���
	// �G�t�F�N�g�t�@�N�g���[ 
	EffectFactory fx(device);
	// ���f���̃e�N�X�`���̓����Ă���t�H���_���w�肷�� 
	fx.SetDirectory(L"Resources\\Models");      //�e�N�X�`���t����cmo������ꍇ��Ɏ����Ă���
	//�A�C�e���̐���
	CreateItem();
	
	m_player->SetEffectManager(m_eDustManager);
	//�S�[���쐬
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i] = std::make_unique<Goal>();
		m_goal[i]->GoalCreate(i);
	}
	//�X�J�C�h�[���R���W�����쐬
	m_skyCollision = std::make_unique<CollisionSphere>();
	m_skyCollision->SetGame(m_game);
	Collision::Sphere sphereSky;
	ModelDate* modelDateSky = ModelDate::GetInstance();
	sphereSky.center = Vector3(10.0f, -0.3f, -10.0f);
	sphereSky.r = 170.0f;
	m_skyCollision->SetCollision(sphereSky);
	//�����܂�R���W�����쐬
	m_courseWaterCollision = std::make_unique<CollisionSphere>();
	m_courseWaterCollision->SetGame(m_game);
	Collision::Sphere sphereCourseWater;
	ModelDate* modelDateCourseWater = ModelDate::GetInstance();
	sphereCourseWater.center = Vector3(110.0f, 0.0f, 0.0f);
	sphereCourseWater.r = 8.0f;
	m_courseWaterCollision->SetCollision(sphereCourseWater);
	//�R�̊O�ɏo�Ȃ��悤�ɂ���
	 for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_outCose[i] = std::make_unique<CollisionCapsule>();
		m_outCose[i]->SetGame(m_game);
		Collision::Capsule capsule[ENEMY_HITCHECK_NUM];
		ModelDate* modelDate = ModelDate::GetInstance();
		capsule[i].r = 1.0f;
		switch (i)
		{
			//��ڂ̎R
		case 0:
			m_outCose[i]->SetPosition(Vector3(-4.0f, 12.0f, 88.0f));
			capsule[i].start = Vector3(  0.0f,  0.0f, 0.0f);
			capsule[i].end   = Vector3(-65.0f, -12.0f, 0.0f);
			break;
		case 1:
			m_outCose[i]->SetPosition(Vector3(6.0f, 12.0f, 88.0f));
			capsule[i].start = Vector3( 10.0f, 0.0f, 0.0f);
			capsule[i].end   = Vector3(-10.0f, 0.0f, 0.0f);
			break;
		case 2:
			m_outCose[i]->SetPosition(Vector3(16.0f, 12.0f, 88.0f));
			capsule[i].start = Vector3( 0.0f,   0.0f, 0.0f);
			capsule[i].end   = Vector3(65.0f, -12.0f, 0.0f);
			break;
		case 3:
			m_outCose[i]->SetPosition(Vector3(-4.0f, 12.0f, 112.0f));
			capsule[i].start = Vector3( 0.0f,   0.0f, 0.0f);
			capsule[i].end   = Vector3(-65.0f, -12.0f, 0.0f);
			break;
		case 4:
			m_outCose[i]->SetPosition(Vector3(6.0f, 12.0f, 112.0f));
			capsule[i].start = Vector3( 10.0f, 0.0f, 0.0f);
			capsule[i].end   = Vector3(-10.0f, 0.0f, 0.0f);
			break;
		case 5:
			m_outCose[i]->SetPosition(Vector3(16.0f, 12.0f, 112.0f));
			capsule[i].start = Vector3( 0.0f,   0.0f, 0.0f);
			capsule[i].end   = Vector3(65.0f, -12.0f, 0.0f);
			break;
		case 6:
			m_outCose[i]->SetPosition(Vector3(0.0f, 0.0f, 88.0f));
			capsule[i].start = Vector3( 65.0f, 0.0f, 0.0f);
			capsule[i].end   = Vector3(-65.0f, 0.0f, 0.0f);
			break;
		case 7:
			m_outCose[i]->SetPosition(Vector3(0.0f, 0.0f, 112.0f));
			capsule[i].start = Vector3( 65.0f, 0.0f, 0.0f);
			capsule[i].end   = Vector3(-65.0f, 0.0f, 0.0f);
			break;
			//��ڂ̎R
		case 8:
			m_outCose[i]->SetPosition(Vector3(-20.0f, 0.0f, 30.0f));
			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[i].end = Vector3(0.0f, 10.0f, -49.0f);
			break;
		case 9:
			m_outCose[i]->SetPosition(Vector3(-20.0f, 10.0f, -29.0f));
			capsule[i].end = Vector3(0.0f, 0.0f, 10.0f);
			capsule[i].start = Vector3(0.0f, 0.0f, -10.0f);
			break;
		case 10:
			m_outCose[i]->SetPosition(Vector3(-20.0f, 0.0f, -90.0f));
			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[i].end = Vector3(0.0f, 10.0f, 49.0f);
			break;
		case 11:
			m_outCose[i]->SetPosition(Vector3(-43.0f, 0.0f, 30.0f));
			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[i].end = Vector3(0.0f, 10.0f, -49.0f);
			break;
		case 12:
			m_outCose[i]->SetPosition(Vector3(-43.0f, 10.0f, -29.0f));
			capsule[i].end   = Vector3(0.0f, 0.0f,  10.0f);
			capsule[i].start = Vector3(0.0f, 0.0f, -10.0f);
			break;
		case 13:
			m_outCose[i]->SetPosition(Vector3(-43.0f, 0.0f, -90.0f));
			capsule[i].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[i].end = Vector3(0.0f, 10.0f, 49.0f);
			break;
		case 14:
			m_outCose[i]->SetPosition(Vector3(-20.0f, 0.0f, -30.0f));
			capsule[i].end   = Vector3(0.0f, 0.0f,  50.0f);
			capsule[i].start = Vector3(0.0f, 0.0f, -50.0f);
			break;
		case 15:
			m_outCose[i]->SetPosition(Vector3(-45.0f, 0.0f, -30.0f));
			capsule[i].end   = Vector3(0.0f, 0.0f,  50.0f);
			capsule[i].start = Vector3(0.0f, 0.0f, -50.0f);
			break;
		}
		m_outCose[i]->SetCollision(capsule[i]);
	}
	
	m_goalModel = Model::CreateFromCMO(device, L"Resources\\Models\\RaceGoal.cmo", fx);
	//��
	m_skydome = Model::CreateFromCMO(device, L"Resources\\Models\\savanna.cmo", fx);
	m_skydome->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ���C�g�̉e�����Ȃ���
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false); lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// �G�~�b�V�����F�𔒂ɐݒ肷�� 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
	//�n��
	m_prairie = Model::CreateFromCMO(device, L"Resources\\Models\\newSavanna.cmo", fx);
	m_prairie->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ���C�g�̉e�����Ȃ���
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false); 
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// �G�~�b�V�����F�𔒂ɐݒ肷�� 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
	
	m_floorModel = Model::CreateFromCMO(device, L"Resources\\Models\\Root.cmo", fx);
	m_floorModel->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ���C�g�̉e�����Ȃ���
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false); 
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// �G�~�b�V�����F�𔒂ɐݒ肷�� 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
	//�n��
	m_courseWater = Model::CreateFromCMO(device, L"Resources\\Models\\puddle.cmo", fx);
	m_courseWater->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ���C�g�̉e�����Ȃ���
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false);
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// �G�~�b�V�����F�𔒂ɐݒ肷�� 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});

	//���̃R���W�������b�V�����쐬
	m_floorMesh = std::make_unique<CollisionMesh>(device, L"FBX\\Root.obj");
	m_floorMesh->SetGame(m_game);

}

/// <summary>
/// �A�C�e���̍쐬
/// </summary>
void ScenePlay::CreateItem()
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	//�A�C�e���쐬(��)
	m_item[0] = std::make_unique<Leaf>();
	//�A�C�e���̈ʒu
	m_item[0]->SetPosition(Vector3(-80.0f, 0, 97.0f));
	//�Q�[���I�u�W�F�g�̐ݒ�
	m_item[0]->SetGame(m_game);
	//�v���C���[�������������̃G�t�F�N�g
	m_item[0]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//�A�C�e���̏�����
	m_item[0]->Initialize();
	//----------------------------
	//�A�C�e���쐬(��)
	m_item[1] = std::make_unique<Leaf>();
	//�A�C�e���̈ʒu
	m_item[1]->SetPosition(Vector3(-33.0f, 0.0f, 50.0f));
	//�Q�[���I�u�W�F�g�̐ݒ�
	m_item[1]->SetGame(m_game);
	//�v���C���[�������������̃G�t�F�N�g
	m_item[1]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//�A�C�e���̏�����
	m_item[1]->Initialize();
	//-------------------------------------------------------------------------------
	//�A�C�e���쐬(��)
	m_item[2] = std::make_unique<Meat>();
	//�A�C�e���̈ʒu
	m_item[2]->SetPosition(Vector3(-80.0f, 0, 103.0f));
	//�Q�[���I�u�W�F�g�̐ݒ�
	m_item[2]->SetGame(m_game);
	//�v���C���[�������������̃G�t�F�N�g
	m_item[2]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//�A�C�e���̏�����
	m_item[2]->Initialize();
	//----------------------------
	//�A�C�e���쐬(��)
	m_item[3] = std::make_unique<Meat>();
	//�A�C�e���̈ʒu
	m_item[3]->SetPosition(Vector3(-27.0f, 0.0f, 50.0f));
	//�Q�[���I�u�W�F�g�̐ݒ�
	m_item[3]->SetGame(m_game);
	//�v���C���[�������������̃G�t�F�N�g
	m_item[3]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//�A�C�e���̏�����
	m_item[3]->Initialize();
	//-------------------------------------------------------------------------------
	//�A�C�e���쐬(Fun)
	m_item[4] = std::make_unique<Fun>();
	//�A�C�e���̈ʒu
	m_item[4]->SetPosition(Vector3(0, 0, -8));
	//�Q�[���I�u�W�F�g�̐ݒ�
	m_item[4]->SetGame(m_game);	   
	//�v���C���[�������������̃G�t�F�N�g
	m_item[4]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//�A�C�e���̏�����
	m_item[4]->Initialize();
	//----------------------------
	//�A�C�e���쐬(Fun)
	m_item[5] = std::make_unique<Fun>();
	//�A�C�e���̈ʒu
	m_item[5]->SetPosition(Vector3(-10, 0, 67));
	//�Q�[���I�u�W�F�g�̐ݒ�
	m_item[5]->SetGame(m_game);
	//�v���C���[�������������̃G�t�F�N�g
	m_item[5]->SetEffectManager(m_eUpManager, m_eDownManager, m_eShitManager);
	//�A�C�e���̏�����
	m_item[5]->Initialize();
}

/// <summary>
/// �����蔻��
/// </summary>
void ScenePlay::CollisionUpdate()
{
	///�����蔻��////////////
	//�v���C���[�ƃR�[�X�̓����蔻��
	static int id;
	Vector3 s;
	Vector3 playerPos = m_player->GetPosition();
	Vector3 cpuPos = m_cpu->GetPosition();
	Vector3 cpuSPos = m_cpuS->GetPosition();
	Vector3 pV[2] = { Vector3(playerPos.x,100,playerPos.z),Vector3(playerPos.x,-1,playerPos.z) };
	Vector3 cV[2] = { Vector3(cpuPos.x,100,cpuPos.z),Vector3(cpuPos.x,-1,cpuPos.z) };
	Vector3 cSV[2] = { Vector3(cpuSPos.x,100,cpuSPos.z),Vector3(cpuSPos.x,-1,cpuSPos.z) };

	if (m_floorMesh->HitCheck_Segment(pV[0], pV[1], &id, &s))
	{
		// �d��
		s.y -= 0.1f;
		m_player->SetPosition(s);
	}
	else
	{
		// ���x��������(�R�[�X�O)
		Vector3 vec = m_player->GetVec();
		vec.z *= -0.01f;
		m_player->SetVec(vec);
	}
	//�X�J�C�h�[������o�悤�Ƃ�����	
	if (Collision::HitCheck_Sphere2Capsule(m_skyCollision->GetCollision(),
		m_player->GetCollision()) == true)
	{
		//--�o�Ȃ�--
		//�R�[�X�i�R�j����o�悤�Ƃ�����
		for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
		{
			if (Collision::HitCheck_Capsule2Capsule(m_outCose[i]->GetCollision()
				, m_player->GetCollision()) == true)
			{
				//�o�Ȃ��悤�ɂ���
				m_player->OutCose();
			}
		}
		if (Collision::HitCheck_Sphere2Capsule(m_courseWaterCollision->GetCollision(),
			m_player->GetCollision()) == true)
		{
			Vector3 vec = m_player->GetVec();
			vec.z *= 0.1f;
			m_player->SetVec(vec);
		}
		//CPU
		if (m_floorMesh->HitCheck_Segment(cV[0], cV[1], &id, &s))
		{
			// �d��
			s.y -= 0.1f;
			m_cpu->SetPosition(s);
		}
		else
		{
			// ���x��������(�R�[�X�O)
			Vector3 vec = m_cpu->GetVec();
			vec.z *= 0.5f;
			m_cpu->SetVec(vec);
		}
		if (m_floorMesh->HitCheck_Segment(cSV[0], cSV[1], &id, &s))
		{
			// �d��
			s.y -= 0.1f;
			m_cpuS->SetPosition(s);
		}
		else
		{
			// ���x��������(�R�[�X�O)
			Vector3 vec = m_cpuS->GetVec();
			vec.z *= 0.5f;
			m_cpuS->SetVec(vec);
		}
		for (int i = 0; i < ITEM_MAX; i++)
		{
			// �|�C���^���Ȃ��ꍇ�͔�΂��Ď��ɐi��
			if (m_item[i] == nullptr)
			{
				continue;
			}
			// �A�C�e���̓����蔻��(player)
			if (Collision::HitCheck_Capsule2Capsule(m_item[i]->GetCollision(), m_player->GetCollision()))
			{
				ItemEffect* itemEffect = m_item[i]->CreateItemEffect();
				m_player->SetItemEffect(itemEffect);
			}
		}
		for (int i = 0; i < GOAL_SET_NUM; i++)
		{
			//�S�[���ƃv���C���[�̓����蔻�������
			if (Collision::HitCheck_Capsule2Capsule(m_goal[i]->GetCollision()
				, m_player->GetCollision()) == true)
			{
				if (m_checkPoint == i)
				{
					m_player->CheckPoint(i);
					m_checkPoint = i + 1;
				}
			}
			//�S�[����CPU�̓����蔻�������
			if (Collision::HitCheck_Capsule2Capsule
			    (m_goal[i]->GetCollision(),m_cpu->GetCollision()) == true)
			{
				m_cpu->CheckPoint(i);
			}

			if (Collision::HitCheck_Capsule2Capsule
			(m_goal[i]->GetCollision(), m_cpuS->GetCollision()) == true)
			{
				m_cpuS->CheckPoint(i);
			}
		}
	}
	else
	{
		//--�o��--
		//�o�Ȃ��悤�ɂ���
		Vector3 vec = m_player->GetVec();
		vec.z -= 1.3f;
		m_player->SetVec(vec);
	}
}

void ScenePlay::GameSeter()
{
	//�A�C�e���̃Q�[���I�u�W�F�N�g��ݒ�
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_item[i]->SetGame(m_game);
	}
	//�S�[���̃Q�[���I�u�W�F�N�g��ݒ�
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->SetGame(m_game);
	}
	//AI���[�g�̃Q�[���I�u�W�F�N�g��ݒ�
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_outCose[i]->SetGame(m_game);
	}
	//��̃Q�[���I�u�W�F�N�g��ݒ�
	m_skyCollision->SetGame(m_game);
	//�v���C���[�̃Q�[���I�u�W�F�N�g��ݒ�
	m_player->SetGame(m_game);
	//CPU�̃Q�[���I�u�W�F�N�g��ݒ�
	m_cpu->SetGame(m_game);
	m_cpuS->SetGame(m_game);
}
//�A�C�e���擾����Effect
void ScenePlay::CreateEffectManager(EffectManager * effectManager, 
	const wchar_t * name, int count, float life, Vector3 pos, 
	Vector3 dir ,Vector3 camera, Matrix view, Matrix proj)
{
	effectManager = new EffectManager();
	effectManager->Create(m_game->GetDeviceResources(), name, count);
	effectManager->InitializeBut(life, pos, dir);
	effectManager->SetRenderState(camera, view, proj);
}
//�摜�����Ă���
void ScenePlay::TextureSet()
{
	TextureDate* textureDate = TextureDate::GetInstance();
	m_tTime = textureDate->GetTime();
	m_tPlayerGoal = textureDate->GetPlayerGoal();
	m_tCPUGoal = textureDate->GetCPUGoal();
	m_tCPUSGoal = textureDate->GetCPUSGoal();
	m_tFlipGoal = textureDate->GetFlipGoal();
	m_tCGo = textureDate->GetCGo();
	for (int i = 0; i < 3; i++)
	{
		m_tCountDown[i] = textureDate->GetCountDown(i);
	}
	m_tOperation = textureDate->GetOperation();
	m_tRadar = textureDate->GetRadar();
	m_tRPlayer = textureDate->GetRPlayer();
	m_tREnemy = textureDate->GetREnemy();
	m_tREnemyS = textureDate->GetREnemyS();
	m_tGameEnd = textureDate->GetGameEnd();
	m_tLeaf = textureDate->GetLeaf();
	m_tLeafText = textureDate->GetLeafText();
	m_tMeat = textureDate->GetMeat();
	m_tMeatText = textureDate->GetMeatText();
	m_tShit = textureDate->GetShit();
	m_tShitText = textureDate->GetShitText();
	m_tCComma = textureDate->GetCComma();
	m_tCCommaS = textureDate->GetCComma();
	for (int i = 0; i < 10; i++)
	{
		m_tCNum[i] = textureDate->GetCNum(i);
	}
}

