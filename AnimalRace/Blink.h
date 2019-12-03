#pragma once

class Blink
{
private:
	// �_�Ńt���O
	bool m_blinkFlag;

	//�J�E���g
	int m_count;

	//�Ԋu
	int m_interval;

	//��~
	bool m_stopFlag;

public:
	//�R���X�g���N�^
	Blink();

	void Initialize(int interval);

	bool Update(float elapsedTime);

	bool GetState();

	void Reset(bool flag);

	void Start();

	void Stop();

};