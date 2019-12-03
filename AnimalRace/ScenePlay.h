#pragma once

#include "SceneBase.h"
#include "Obj3D.h"
#include "CollisionCapsule.h"
#include "CollisionSphere.h"
#include "Player.h"
#include "Enemy.h"
#include "CPU.h"
#include "Item.h"
#include "Meat.h"
#include "Leaf.h"
#include "Fun.h"
#include "Root.h" 
#include "DebugCamera.h"
#include "GameCamera.h"
#include "TaskManager.h"
#include "CollisionMesh.h"
#include "Goal.h"
#include "ObjectCreate.h"
#include "Number.h"
#include "MyEffect.h"
#include "EffectManager.h"
#include "SceneSelect.h"
#include "Radar.h"
#include "ADX2Le.h"

class ScenePlay : public SceneBase
{
public:
	static const int ENEMY_HITCHECK_NUM = 16;
	static const int GOAL_SET_NUM = 6;
	static const int ITEM_SET_NUM = 2;
	static const int ITEM_MAX = 6;
	static const int TIME_SET_NUM = 3;
	static const int TIME_TYPE_NUM = 10;
	static const int GAME_START_TIME = 180;
	static const int TIME_MINUTE = 60;
	static const int TIME_MIRI = 100;
	static const int GOAL_CHARA = 3;
private:
	DX::StepTimer                           m_timer;
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;
	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_debugCamera;
	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	//3D�X�v���C�g///////////////////////////////////////////
	//��
	std::unique_ptr<CollisionMesh> m_skydomeMesh;
	std::unique_ptr<DirectX::Model> m_skydome;
	// ����
	std::unique_ptr<DirectX::Model> m_prairie;
	// ����
	std::unique_ptr<DirectX::Model> m_courseWater;
	//�v���C���[
	Player* m_player;
	//CPU
	Enemy* m_cpu;
	CPU* m_cpuS;
	std::unique_ptr<CollisionCapsule> m_outCose[ENEMY_HITCHECK_NUM];
	std::unique_ptr<CollisionSphere>  m_skyCollision;
	std::unique_ptr<CollisionSphere>  m_courseWaterCollision;
	Root* m_root;
	//���̃��f��
	std::unique_ptr<DirectX::Model> m_rootModel;
	//�S�[���̃��f��
	std::unique_ptr<DirectX::Model> m_goalModel;
	//�S�[��
	std::unique_ptr<Goal> m_goal[GOAL_SET_NUM];
	Character* m_charaGoal;
	//�A�C�e��
	std::unique_ptr<Item> m_item[ITEM_MAX];
	//�A�C�e���`��
	bool m_itemDis;
	//2D�X�v���C�g/////////////////////////////
	//�e�N�X�`���n���h��
	//��������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTime;
	
	//GOAL!!
	//�v���C���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPlayerGoal;
	//CPU
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCPUGoal;
	//CPU
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCPUSGoal;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tFlipGoal;;
	//�J�E���g�_�E��
	//GO!
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCGo;
	//:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCComma;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCCommaS;
	//����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCNum[TIME_TYPE_NUM];
	//����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCountDown[3];
	//�������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOperation;
	//�}�b�v
	
	//���[�_�[�̃e�N�X�`���n���h�� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tRadar;
	//���[�_�[�̃v���C���[�̃e�N�X�`���n���h�� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tRPlayer;
	//���[�_�[�̓G�̃e�N�X�`���n���h�� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tREnemy;
	//���[�_�[�̓G2�̃e�N�X�`���n���h�� 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tREnemyS;
	//�S�[�������㏟������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tGameEnd;
	//�A�C�e�������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tLeaf;
	//�A�C�e�������Text
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tLeafText;
	//�A�C�e�������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tMeat;
	//�A�C�e�������Text
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tMeatText;
	//�A�C�e������t��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tShit;
	//�A�C�e������t��Text
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tShitText;

	Number m_number[TIME_SET_NUM];
	//�^�C��
	int m_second;
	//�J�E���g�_�E��
	int m_count;
	int m_miri;
	int m_miriHand;
	//�b
	int m_sec;
	//��
	int m_min;
	//�S�[���̃`�F�b�N�|�C���g
	int m_checkPoint;
	std::unique_ptr<CollisionMesh> m_floorMesh;
	std::unique_ptr<DirectX::Model> m_floorModel;
	//�G�t�F�N�g
	EffectManager* m_eUpManager;
	EffectManager* m_eDownManager;
	EffectManager* m_eShitManager;
	EffectManager* m_eDustManager;
	int m_winCharacter;
	Radar* m_radar;

	float m_resultRotation;

	float m_countResult;

	MyLibrary::ADX2Le* m_adx2le;
	CriAtomExPlaybackId m_criAtomExPlaybackId;
public:
	ScenePlay();
	~ScenePlay();
	//������
	void Initialize() override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render() override;
	void Finalize() override;
	void CreateDeviceDependentResources();
	// �A�C�e���̍쐬
	void CreateItem();
	void CollisionUpdate();
	//�Q�[����Set
	void GameSeter();
	//Get�֐�
	int GetWinCharacter() const{ return m_winCharacter; }
	Player* GetPlayer() const{ return m_player;  }
	int GetSecond() const{ return m_second; }
	int GetMiri() const{ return m_miri; };
	int GetMiriHand() const{ return m_miriHand; };
	int GetSec() const{ return m_sec; };
	int GetMin() const{ return m_min; };
	//�A�C�e���擾����Effect
	void CreateEffectManager(EffectManager* effectManager,const wchar_t* name ,int count, float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir,
		DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//�摜�����Ă���
	void TextureSet();
};