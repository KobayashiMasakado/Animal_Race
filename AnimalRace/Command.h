#pragma once

class Player;

class Command
{
public:
	//�R�}���h�p�^�[���̊��
	virtual ~Command() {}
	virtual void execute(Player* actor) = 0;
};
