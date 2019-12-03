#pragma once
#include <list>
#include "Command.h"
#include "FrontCommand.h"
#include "LeftSideCommand.h"
#include "RightSideCommand.h"

#include "Character.h"
class InputHandler : public Character
{
private:
	//�����ŃL�[�̃N���X���擾���܂�
	Command* m_bUp;
	Command* m_bLeft;
	Command* m_bRight;

	std::list<Command*> m_cList;

public:
	InputHandler();
	~InputHandler();
	std::list<Command*>& HandleInput();
};