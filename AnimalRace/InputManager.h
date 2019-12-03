#pragma once
#include "Utility.h"

class InputManager : public SingletonBase<InputManager>
{
private:
	DirectX::Keyboard::KeyboardStateTracker m_stateTriger;
public:
	InputManager();
	~InputManager();

	DirectX::Keyboard::KeyboardStateTracker* GetKeyTracker()
	{
		return &m_stateTriger;
	}
};