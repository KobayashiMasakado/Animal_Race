#pragma once
#include "Command.h"
class Player;

class FrontCommand : public Command
{
public:
	//前方移動の処理を書く
	virtual void execute(Player* actor)override;
};