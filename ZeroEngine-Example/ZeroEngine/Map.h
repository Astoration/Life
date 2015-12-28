#pragma once
#include "Zero.h"
class Map :
	public ZeroIScene
{
public:
	ZeroSprite *p_map,*p_sky;
	Map();
	int adr;
	virtual ~Map();
	void Update(float eTime);
	void Render();
};

