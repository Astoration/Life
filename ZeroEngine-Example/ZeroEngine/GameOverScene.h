#pragma once
#include "Zero.h"
class GameOverScene :
	public ZeroIScene
{
public:
	GameOverScene(int score, float currentTime);
	ZeroFont* message;
	virtual ~GameOverScene();
	void Update(float eTime);
	void Render();
	ZeroSprite *bg, *map,*window;
	ZeroSprite *cursor;
};