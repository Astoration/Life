#pragma once
#include "Zero.h"
class TitleLoadScene :
	public ZeroIScene
{
public:
	ZeroSprite* bg,*Logo;
	float Checktime;
	bool isSceneLoad;
	ZeroSprite *cursor;
	bool isAnimation, isLoging, temp,kapese;
	ZeroFont* temps;
	float repeater;
	int ZerosWidth, ZerosHeight;
	ZeroFont* Zeros[11][35], *left, *right;
	TitleLoadScene();
	virtual ~TitleLoadScene();
	void Update(float eTime);
	void Render();
};

