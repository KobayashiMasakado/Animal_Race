#pragma once
#include <sys/timeb.h>
#include "DeviceResources.h"
#include "CollisionCapsule.h"
#include "DebugCapsule.h"

#include "Character.h"
#include "Item.h"
class EnemyBoss : public Character
{
public:
	//�A�C�e���̐ݒu��
	static const int ITEM_SET_NUM = 2;
	//AI�̍ŏ��̈ʒu
	static const int WARP_ZERO = 0;
	//AI�̍ŏI�ʒu
	static const int WARP_MAX = 26;


	//�G�̌��݈ʒu
	DirectX::SimpleMath::Vector3 m_startPos;
	//�G�̎��̈ʒu
	DirectX::SimpleMath::Vector3 m_targetPos;
	//AI�|�W�e�B�u�̐ݒ�ϐ�
	DirectX::SimpleMath::Vector3 m_CPUPoint[WARP_MAX];

	//�A�C�e�����擾������
	bool m_itemCPUCheck;
	bool m_itemCPUBadCheck;
	bool m_itemCPUFunCheck;

	//CPU�����[�v����ꏊ
	DirectX::SimpleMath::Vector3 m_cpuSetPos[WARP_MAX];
	//CPU�����[�v�����ꏊ�̓����蔻��Flag
	int m_targetElem;

	//���̕ϐ�
	Collision::Sphere m_sphere;
	std::unique_ptr<DebugCapsule> m_debug;

	//�L�����N�^�[�̑��̃��f��
	DirectX::Model* m_modelLegL;
	DirectX::Model* m_modelLegR;
	//�L�����N�^�[�̉e�̃��f��
	DirectX::Model* m_shadow;

public:
	//�R���X�g���N�^
	EnemyBoss();
	//�f�X�g���N�^
	~EnemyBoss();
	//�X�V
	 bool Update(const DX::StepTimer& stepTimer);
	//�`��
	void Render();
	//CPU�쐬

	void Finalize();

	bool GetItemCPU() const { return m_itemCPUCheck; }
	bool GetItemCPUBad() const { return m_itemCPUBadCheck; }
	bool GetItemCPUFun() const { return m_itemCPUFunCheck; }

	//�G�t�F�N�g�̐ݒ�֐�
	void SetUpEffect();

	// �A�C�e���̌���
	void SetItemEffect(ItemEffect* itemEffect)
	{
		if (m_itemEffect != nullptr)
		{
			delete m_itemEffect;
		}
		m_itemEffect = itemEffect;
	}

	//�����񂷂�
	void Left();
	//�E���񂷂�
	void Right();
	//���̃��f���̕`��
	void LegModelRender(DirectX::SimpleMath::Matrix& world, float r, DirectX::SimpleMath::Vector3 posdif);

};
