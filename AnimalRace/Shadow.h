#pragma once
#include "CollisionCapsule.h"
class Shadow : public CollisionCapsule
{
private:

	// �\���t���O
	bool m_active;
	// �u�����h�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;

public:
	// �R���X�g���N�^
	Shadow();

	// �������֐�
	void Initialize();

	bool Update();

	// �`��֐�
	void Render();

	// �\����ON/OFF����֐�
	void Active(bool flag) { m_active = flag; }
};
