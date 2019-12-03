#pragma once

#include <Model.h>
#include "Utility.h"

#include "SceneSelect.h"

class ModelDate : public SingletonBase<ModelDate>
{
private:
	std::unique_ptr<DirectX::Model> m_playerModel;
	std::unique_ptr<DirectX::Model> m_playerLegLModel;
	std::unique_ptr<DirectX::Model> m_playerLegRModel;
	std::unique_ptr<DirectX::Model> m_cpuModel;
	std::unique_ptr<DirectX::Model> m_cpuBodyModel;
	std::unique_ptr<DirectX::Model> m_cpuLegLModel;
	std::unique_ptr<DirectX::Model> m_cpuLegRModel;
	std::unique_ptr<DirectX::Model> m_itemHERBIVOREModel;
	std::unique_ptr<DirectX::Model> m_itemCARNIVOREModel;
	std::unique_ptr<DirectX::Model> m_itemFunModel;
	std::unique_ptr<DirectX::Model> m_courseWaterModel;
	std::unique_ptr<DirectX::Model> m_cpu2BodyModel;
	std::unique_ptr<DirectX::Model> m_cpu2LegLModel;
	std::unique_ptr<DirectX::Model> m_cpu2LegRModel;
	std::unique_ptr<DirectX::Model> m_shadowModel;

public:
	ModelDate();
	~ModelDate();

	void Create(ID3D11Device* device);

	DirectX::Model* GetPlayer() { return m_playerModel.get(); }
	DirectX::Model* GetLegLPlayer() { return m_playerLegLModel.get(); }
	DirectX::Model* GetLegRPlayer() { return m_playerLegRModel.get(); }

	DirectX::Model* GetCPU() { return m_cpuModel.get(); }
	DirectX::Model* GetBodyCPU() { return m_cpuBodyModel.get(); }
	DirectX::Model* GetLegLCPU() { return m_cpuLegLModel.get(); }
	DirectX::Model* GetLegRCPU() { return m_cpuLegRModel.get(); }
	DirectX::Model* GetItemHerbivore() { return m_itemHERBIVOREModel.get(); }
	DirectX::Model* GetItemCarnivore() { return m_itemCARNIVOREModel.get(); }
	DirectX::Model* GetItemFun() { return m_itemFunModel.get(); }
	DirectX::Model* GetCourseWater() { return m_courseWaterModel.get(); }
	DirectX::Model* GetBodyCPU2() { return m_cpu2BodyModel.get(); }
	DirectX::Model* GetLegLCPU2() { return m_cpu2LegLModel.get(); }
	DirectX::Model* GetLegRCPU2() { return m_cpu2LegRModel.get(); }
	DirectX::Model* GetShadow() { return m_shadowModel.get(); }
};