#pragma once
#include "Command.h"
class Player;

class FrontCommand : public Command
{
public:
	//‘O•ûˆÚ“®‚Ìˆ—‚ğ‘‚­
	virtual void execute(Player* actor)override;
};