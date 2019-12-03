#pragma once
#include "DeviceResources.h"

class Game;

class SceneBase
{
protected:
	Game* m_game;

public:
	SceneBase():m_game(nullptr) {};
	~SceneBase() {};
	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update(const DX::StepTimer& timer) = 0;
	//�`��
	virtual void Render() = 0;
	//�I������
	virtual void Finalize() = 0;
	//�Q�[���ł�����̂����
	virtual void CreateDeviceDependentResources() = 0;

	//�Q�[���I�u�W�F�N�g��ݒ肷��֐�
	void SetGame(Game* game)
	{
		m_game = game;
	}
};