#pragma once
#include "Zero.h"
class TitleScene :
	public ZeroIScene
{
public:
	TitleScene();
	ZeroSprite* p_bg[4],*p_button;
	ZeroSprite* cursor;
	ZeroSprite* city, *clock, *hour, *minute, *ttitle;
	float alpha[4];
	int nowIndex;
	void Update(float eTime);
	void Render();
	virtual ~TitleScene();
};

