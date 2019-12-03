#include "pch.h"
#include "TextureDate.h"

#include "Game.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

TextureDate::TextureDate()
{
}

TextureDate::~TextureDate()
{
	//Title用
	m_tBackGround.Reset();
	m_tTitleRogo.Reset();
	m_tPushEnter.Reset();
	m_tExitEnter.Reset();
	m_tTitleDescription.Reset();
	//Select用
	m_tCamel.Reset();
	m_tTiger.Reset();
	m_tOstrich.Reset();
	m_tSelectPointer.Reset();
	m_tSelectDescription.Reset();
	m_tTigerParameter.Reset();
	m_tCamelParameter.Reset();
	m_tOstrichParameter.Reset();

	//Result用
	m_tHerbivore.Reset();
	m_tCarnivore.Reset();
	m_tOmnivorous.Reset();
	m_tDHerbivore.Reset();
	m_tDCarnivore.Reset();
	m_tDOmnivorous.Reset();
	m_tPlayerWin.Reset();
	m_tCpuWin.Reset();
	m_tYouWin.Reset();
	m_tYouLose.Reset();
	m_tDecision.Reset();
	m_tCComma.Reset();
	for (int i = 0; i < 10; i++)
	{
		m_tCNum[i].Reset();
	}
}

void TextureDate::Create(ID3D11Device* device,ID3D11DeviceContext* context)
{
	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);
	//Title用
	CreateWICTextureFromFile(device, L"Textures\\BackGround.png",     nullptr, m_tBackGround.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\animlrasetitle.png", nullptr, m_tTitleRogo.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\start.png",          nullptr, m_tPushEnter.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\exit.png",           nullptr, m_tExitEnter.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Description.png",    nullptr, m_tTitleDescription.GetAddressOf());
	//Select用
	CreateWICTextureFromFile(device, L"Textures\\BackGround.png",     nullptr, m_tBackGround.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Rakuda.png",         nullptr, m_tCamel.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Tiger.png",          nullptr, m_tTiger.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Datyou.png",         nullptr, m_tOstrich.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\kakko.png",          nullptr, m_tSelectPointer.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Description.png",    nullptr, m_tSelectDescription.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\TigerP.png",         nullptr, m_tTigerParameter.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\RakudaP.png",        nullptr, m_tCamelParameter.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\DatyouP.png",        nullptr, m_tOstrichParameter.GetAddressOf());
	//Result用
	CreateWICTextureFromFile(device, L"Textures\\Datyou.png",    nullptr, m_tOmnivorous.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Tiger.png",     nullptr, m_tCarnivore.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Rakuda.png",    nullptr, m_tHerbivore.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Ddown.png",     nullptr, m_tDOmnivorous.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Tdown.png",     nullptr, m_tDCarnivore.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Rdown.png",     nullptr, m_tDHerbivore.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\playerwin.png", nullptr, m_tPlayerWin.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\cpuwin.png",    nullptr, m_tCpuWin.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\YouWin.png",    nullptr, m_tYouWin.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\YouLose.png",   nullptr, m_tYouLose.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Decision.png",  nullptr, m_tDecision.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Comma_red.png", nullptr, m_tCComma.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\0_red.png",     nullptr, m_tCNum[0].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\1_red.png",     nullptr, m_tCNum[1].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\2_red.png",     nullptr, m_tCNum[2].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\3_red.png",     nullptr, m_tCNum[3].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\4_red.png",     nullptr, m_tCNum[4].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\5_red.png",     nullptr, m_tCNum[5].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\6_red.png",     nullptr, m_tCNum[6].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\7_red.png",     nullptr, m_tCNum[7].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\8_red.png",     nullptr, m_tCNum[8].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\9_red.png",     nullptr, m_tCNum[9].GetAddressOf());
	//Play用
	CreateWICTextureFromFile(device, L"Textures\\savanna_time.png", nullptr, m_tTime.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\GO.png", nullptr, m_tCGo.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Waening.png", nullptr, m_tFlipGoal.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Operation.png", nullptr, m_tOperation.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\uoCorse.PNG", nullptr, m_tRadar.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\mapPlayer.png", nullptr, m_tRPlayer.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\mapCpu.png", nullptr, m_tREnemy.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\mapCpu.png", nullptr, m_tREnemyS.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\count1.png", nullptr, m_tCountDown[0].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\count2.png", nullptr, m_tCountDown[1].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\count3.png", nullptr, m_tCountDown[2].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\gameEnd.png", nullptr, m_tGameEnd.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\LeafEat.png", nullptr, m_tLeaf.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\LeafEatText.png", nullptr, m_tLeafText.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\MeatEat.png", nullptr, m_tMeat.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\MeatEatText.png", nullptr, m_tMeatText.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Shit.png", nullptr, m_tShit.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\ShitText.png", nullptr, m_tShitText.GetAddressOf());

}

