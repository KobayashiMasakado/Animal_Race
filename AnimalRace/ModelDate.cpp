#include "pch.h"
#include "ModelDate.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

ModelDate::ModelDate()
{
}

ModelDate::~ModelDate()
{
	m_playerModel.reset();
	m_playerLegLModel.reset();
	m_playerLegRModel.reset();
	m_cpuModel.reset();
	m_cpuBodyModel.reset();
	m_cpuLegLModel.reset();
	m_cpuLegRModel.reset();
	m_itemHERBIVOREModel.reset();
	m_itemCARNIVOREModel.reset();
	m_itemFunModel.reset();
	m_courseWaterModel.release();
	m_cpu2BodyModel.reset();
	m_cpu2LegLModel.reset();
	m_cpu2LegRModel.reset();
	m_shadowModel.reset();
}

void ModelDate::Create(ID3D11Device* device)
{
	// モデルを読み込み
	// エフェクトファクトリー 
	EffectFactory fx(device);
	// モデルのテクスチャの入っているフォルダを指定する 
	fx.SetDirectory(L"Resources\\Models");      //テクスチャ付きのcmoがある場合上に持ってくる
	m_playerModel     = Model::CreateFromCMO(device, L"Resources\\Models\\O&Hbody.cmo", fx);
	m_playerLegLModel = Model::CreateFromCMO(device, L"Resources\\Models\\O&HlegL.cmo", fx);
	m_playerLegRModel = Model::CreateFromCMO(device, L"Resources\\Models\\O&HlegR.cmo", fx);
	m_cpuModel        = Model::CreateFromCMO(device, L"Resources\\Models\\Tiger.cmo", fx);
	m_cpuBodyModel = Model::CreateFromCMO(device, L"Resources\\Models\\TigerB.cmo", fx);
	m_cpuLegLModel = Model::CreateFromCMO(device, L"Resources\\Models\\TigerL.cmo", fx);
	m_cpuLegRModel = Model::CreateFromCMO(device, L"Resources\\Models\\TigerR.cmo", fx);
	m_itemHERBIVOREModel = Model::CreateFromCMO(device, L"Resources\\Models\\Item.cmo", fx);
	m_itemCARNIVOREModel = Model::CreateFromCMO(device, L"Resources\\Models\\esaC.cmo", fx);
	m_itemFunModel = Model::CreateFromCMO(device, L"Resources\\Models\\Fun.cmo", fx);
	m_courseWaterModel = Model::CreateFromCMO(device, L"Resources\\Models\\puddle.cmo", fx);
	m_cpu2BodyModel = Model::CreateFromCMO(device, L"Resources\\Models\\RakudaB.cmo", fx);
	m_cpu2LegLModel = Model::CreateFromCMO(device, L"Resources\\Models\\RakudaL.cmo", fx);
	m_cpu2LegRModel = Model::CreateFromCMO(device, L"Resources\\Models\\RakudaR.cmo", fx);
	m_shadowModel = Model::CreateFromCMO(device, L"Resources\\Models\\shadow.cmo", fx);
}
