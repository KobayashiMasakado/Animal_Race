#pragma once
#include "Command.h"

class RightSideCommand : public Command
{
public:
	//右旋回の処理を書く
	virtual void execute(Player* actor) override;
};