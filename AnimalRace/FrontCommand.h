#pragma once
#include "Command.h"
class Player;

class FrontCommand : public Command
{
public:
	//�O���ړ��̏���������
	virtual void execute(Player* actor)override;
};