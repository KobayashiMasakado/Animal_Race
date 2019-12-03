#pragma once
#include <Model.h>
#include "Utility.h"

#include "SceneBase.h"

class TextureDate : public SingletonBase<TextureDate>
{
private:
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;
	//---Title用-----------------
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tBackGround;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTitleRogo;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPushEnter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tExitEnter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTitleDescription;
	//---Select用----------------
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCamel;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTiger;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOstrich;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tSelectPointer;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tSelectDescription;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTigerParameter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCamelParameter;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOstrichParameter;
	//---Result用----------------
	//勝利した草食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tHerbivore;
	//勝利した肉食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCarnivore;
	//勝利した雑食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOmnivorous;
	//敗北した草食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDHerbivore;
	//敗北した肉食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDCarnivore;
	//敗北した雑食
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDOmnivorous;
	//playerwinと出す
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPlayerWin;
	//cpuwinと出す
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCpuWin;
	//youwinと出す
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tYouWin;
	//youloseと出す
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tYouLose;
	//操作説明
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tDecision;
	//:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCComma;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCCommaS;
	//数字
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCNum[10];
	//---Play用----------------
	//制限時間
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTime;
	//GOAL!!
	//プレイヤー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPlayerGoal;
	//CPU
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCPUGoal;
	//CPU
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCPUSGoal;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tFlipGoal;;
	//カウントダウン
	//GO!
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCGo;
	//数字
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCountDown[3];
	//操作説明
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tOperation;
	//マップ
	//レーダーのテクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tRadar;
	//レーダーのプレイヤーのテクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tRPlayer;
	//レーダーの敵のテクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tREnemy;
	//レーダーの敵2のテクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tREnemyS;
	//ゴールした後勝負あり
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tGameEnd;
	//アイテム解説草
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tLeaf;
	//アイテム解説草Text
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tLeafText;
	//アイテム解説肉
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tMeat;
	//アイテム解説肉Text
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tMeatText;
	//アイテム解説フン
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tShit;
	//アイテム解説フンText
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tShitText;
public:
	TextureDate();
	~TextureDate();

	void Create(ID3D11Device* device,ID3D11DeviceContext* context);
	//Title用
	ID3D11ShaderResourceView* GetBackGround()        { return m_tBackGround.Get();  }
	ID3D11ShaderResourceView* GetTitleRogo()         { return m_tTitleRogo.Get();   }
	ID3D11ShaderResourceView* GetPushEnter()         { return m_tPushEnter.Get();   }
	ID3D11ShaderResourceView* GetExitEnter()         { return m_tExitEnter.Get();   }
	ID3D11ShaderResourceView* GetTitleDescription()  { return m_tTitleDescription.Get(); }
	//Select用
	ID3D11ShaderResourceView* GetCamel()             { return m_tCamel.Get(); }
	ID3D11ShaderResourceView* GetTiger()             { return m_tTiger.Get(); }
	ID3D11ShaderResourceView* GetTigerParameter()    { return m_tTigerParameter.Get(); }
	ID3D11ShaderResourceView* GetCamelParameter()    { return m_tCamelParameter.Get(); }
	ID3D11ShaderResourceView* GetOstrichParameter()  { return m_tOstrichParameter.Get(); }
	ID3D11ShaderResourceView* GetOstrich()           { return m_tOstrich.Get(); }
	ID3D11ShaderResourceView* GetSelectPointer()     { return m_tSelectPointer.Get(); }
	ID3D11ShaderResourceView* GetSelectDescription() { return m_tSelectDescription.Get(); }
	//Result用
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
	//Play用
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