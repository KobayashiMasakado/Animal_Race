#pragma once
#include "Command.h"

class Player;
class LeftSideCommand : public Command
{
public:
	//左旋回の処理を書く
	virtual void execute(Player* actor)override;
};