#pragma once
#include "Zero.h"
class StoryScene :
	public ZeroIScene
{
public:
	StoryScene();
	virtual ~StoryScene();
	bool Line[5];
	float times;
	ZeroSprite *bg, *a, *b, *c, *d, *LoadingBg, *LoadingCircle;
	void Update(float eTime);
	void Render();
	bool isSponed;
};

