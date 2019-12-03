#pragma once
#include <Model.h>
#include "Utility.h"

#include "SceneBase.h"

class TextureDate : public SingletonBase<TextureDate>
{
private:
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;
	//---Title�p-----------------
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tBackGround;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTitleRogo;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPushEnter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tExitEnter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTitleDescription;
	//---Select�p----------------
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCamel;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTiger;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOstrich;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tSelectPointer;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tSelectDescription;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTigerParameter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCamelParameter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOstrichParameter;
	//---Result�p----------------
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
	//---Play�p----------------
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
public:
	TextureDate();
	~TextureDate();

	void Create(ID3D11Device* device,ID3D11DeviceContext* context);
	//Title�p
	ID3D11ShaderResourceView* GetBackGround()        { return m_tBackGround.Get();  }
	ID3D11ShaderResourceView* GetTitleRogo()         { return m_tTitleRogo.Get();   }
	ID3D11ShaderResourceView* GetPushEnter()         { return m_tPushEnter.Get();   }
	ID3D11ShaderResourceView* GetExitEnter()         { return m_tExitEnter.Get();   }
	ID3D11ShaderResourceView* GetTitleDescription()  { return m_tTitleDescription.Get(); }
	//Select�p
	ID3D11ShaderResourceView* GetCamel()             { return m_tCamel.Get(); }
	ID3D11ShaderResourceView* GetTiger()             { return m_tTiger.Get(); }
	ID3D11ShaderResourceView* GetTigerParameter()    { return m_tTigerParameter.Get(); }
	ID3D11ShaderResourceView* GetCamelParameter()    { return m_tCamelParameter.Get(); }
	ID3D11ShaderResourceView* GetOstrichParameter()  { return m_tOstrichParameter.Get(); }
	ID3D11ShaderResourceView* GetOstrich()           { return m_tOstrich.Get(); }
	ID3D11ShaderResourceView* GetSelectPointer()     { return m_tSelectPointer.Get(); }
	ID3D11ShaderResourceView* GetSelectDescription() { return m_tSelectDescription.Get(); }
	//Result�p
	ID3D11ShaderResourceView* GetHerbivore()         { return m_tHerbivore.Get(); }
	ID3D11ShaderResourceView* GetCarnivore()         { return m_tCarnivore.Get(); }
	ID3D11ShaderResourceView* GetOmnivorous()        { return m_tOmnivorous.Get(); }
	ID3D11ShaderResourceView* GetDHerbivore()        { return m_tDHerbivore.Get(); }
	ID3D11ShaderResourceView* GetDCarnivore()        { return m_tDCarnivore.Get(); }
	ID3D11ShaderResourceView* GetDOmnivorous()       { return m_tDOmnivorous.Get(); }
	ID3D11ShaderResourceView* GetPlayerWin()         { return m_tPlayerWin.Get(); }
	ID3D11ShaderResourceView* GetCpuWin()            { return m_tCpuWin.Get(); }
	ID3D11ShaderResourceView* GetYouWin()            { return m_tYouWin.Get(); }
	ID3D11ShaderResourceView* GetYouLose()           { return m_tYouLose.Get(); }
	ID3D11ShaderResourceView* GetDecision()          { return m_tDecision.Get(); }
	ID3D11ShaderResourceView* GetCComma()            { return m_tCComma.Get(); }
	ID3D11ShaderResourceView* GetCNum(int i)         { return m_tCNum[i].Get(); }
	//Play�p
	ID3D11ShaderResourceView* GetTime()              { return m_tTime.Get(); }
	ID3D11ShaderResourceView* GetPlayerGoal()        { return m_tPlayerGoal.Get(); }
	ID3D11ShaderResourceView* GetCPUGoal()           { return m_tCPUGoal.Get(); }
	ID3D11ShaderResourceView* GetCPUSGoal()          { return m_tCPUSGoal.Get(); }
	ID3D11ShaderResourceView* GetFlipGoal()          { return m_tFlipGoal.Get(); }
	ID3D11ShaderResourceView* GetCGo()               { return m_tCGo.Get(); }
	ID3D11ShaderResourceView* GetCountDown(int i)    { return m_tCountDown[i].Get(); }
	ID3D11ShaderResourceView* GetOperation()         { return m_tOperation.Get(); }
	ID3D11ShaderResourceView* GetRadar()             { return m_tRadar.Get(); }
	ID3D11ShaderResourceView* GetRPlayer()           { return m_tRPlayer.Get(); }
	ID3D11ShaderResourceView* GetREnemy()            { return m_tREnemy.Get(); }
	ID3D11ShaderResourceView* GetREnemyS()           { return m_tREnemyS.Get(); }
	ID3D11ShaderResourceView* GetGameEnd()           { return m_tGameEnd.Get(); }
	ID3D11ShaderResourceView* GetLeaf()              { return m_tLeaf.Get(); }
	ID3D11ShaderResourceView* GetLeafText()          { return m_tLeafText.Get(); }
	ID3D11ShaderResourceView* GetMeat()              { return m_tMeat.Get(); }
	ID3D11ShaderResourceView* GetMeatText()          { return m_tMeatText.Get(); }
	ID3D11ShaderResourceView* GetShit()              { return m_tShit.Get(); }
	ID3D11ShaderResourceView* GetShitText()          { return m_tShitText.Get(); }
	                                              
};