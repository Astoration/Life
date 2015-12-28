#pragma once
#include "Zero.h"
class Items :
	public ZeroIScene
{
public:
	ZeroSprite *p_item;
	Items(bool kind, int currentLife, bool times);
	virtual ~Items();
	void Update(float eTime);
	void Render();
	int adr;
	bool times;
	float addPlus;
	int randomKind;
};

