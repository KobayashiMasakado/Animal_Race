#pragma once

class Player;

class Command
{
public:
	//コマンドパターンの基盤
	virtual ~Command() {}
	virtual void execute(Player* actor) = 0;
};
