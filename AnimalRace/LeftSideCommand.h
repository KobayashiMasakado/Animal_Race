#pragma once
#include "Command.h"

class Player;
class LeftSideCommand : public Command
{
public:
	//¶ù‰ñ‚Ìˆ—‚ğ‘‚­
	virtual void execute(Player* actor)override;
};