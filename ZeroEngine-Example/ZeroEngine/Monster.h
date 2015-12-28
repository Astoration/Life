#pragma once
#include "Zero.h"
class Monster :
	public ZeroIScene
{
public:
	ZeroSprite *p_mt;
	Monster(bool kind, int currentLife, bool time);
	virtual ~Monster();
	void Update(float eTime);
	void Render();
	int adr;
	float addPlus;
};

