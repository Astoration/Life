#pragma once
#include "Zero.h"
class Player :
	public ZeroIScene
{
public:
	Player();
	ZeroAnimation *p_player;
	ZeroAnimation *p_Action;
	float MathPlus;
	bool isJumped;
	int count;
	float MathCount;
	float test;
	virtual ~Player();
	void Update(float eTime);
	void Render();
	void ResourceReload(int currentLife);
};

