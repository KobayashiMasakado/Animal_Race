#pragma once
#include "Command.h"

class RightSideCommand : public Command
{
public:
	//�E����̏���������
	virtual void execute(Player* actor) override;
};