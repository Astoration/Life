#pragma once
#include "Zero.h"
#include "Map.h"
#include "Player.h"
#include "Serial.h"
#include "SerialUtil.h"
class InGameScene :
	public ZeroIScene
{
public:
	InGameScene();
	Map *p_mMap;
	int currentLife;
	int score;
	float coolTime;
	bool isMorning;
	Player *p_mPlayer;
	virtual ~InGameScene();
	bool kind;
	bool isWeather;
	char* Weather[4];
	ZeroSprite *cursor;
	ZeroSprite *interfaceOne, *interfaceTwo, *interfaceThree, *interfaceFour;
	ZeroSprite *interfaceHP;
	int hp;
	float hpTime;
	SerialUtil* su;
	int daysCount;
	string str;
	int str2;
	ZeroSprite* message;
	float times;
	bool reConnect;
	int light;
	void Update(float eTime);
	void Render();
	void HpUpdate(int distance);
};

