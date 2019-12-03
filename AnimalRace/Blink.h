#pragma once

class Blink
{
private:
	// 点滅フラグ
	bool m_blinkFlag;

	//カウント
	int m_count;

	//間隔
	int m_interval;

	//停止
	bool m_stopFlag;

public:
	//コンストラクタ
	Blink();

	void Initialize(int interval);

	bool Update(float elapsedTime);

	bool GetState();

	void Reset(bool flag);

	void Start();

	void Stop();

};