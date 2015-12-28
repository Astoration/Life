#include "stdafx.h"
#include "TitleLoadScene.h"
#include "TitleScene.h"
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;
TitleLoadScene::TitleLoadScene()
	:Checktime(0), ZerosWidth(11), ZerosHeight(35), repeater(1), isAnimation(true), isLoging(false), temp(false), kapese(false), isSceneLoad(false)
{
	srand(time(NULL));
	bg = new ZeroSprite("Texture/loadBg.png");
	cursor = new ZeroSprite("Texture/cursor.png");
	bg->SetScale(10);
	bg->SetColor(0xff000000);
	for (int i = 0; i < ZerosWidth; i++){
		for (int j = 0; j < ZerosHeight; j++){
			Zeros[i][j] = new ZeroFont(30, "0", "Consolas", "Font/consolab.ttf");
			Zeros[i][j]->SetPos(10 + (125 * i), 5 + (20 * j));
			Zeros[i][j]->SetColor(0xf07aaff + ((0xff0000 * rand() % 300 / 300) + (0x00ff00 * rand() % 300 / 300) + (0x0000ff * rand() % 300 / 300)));
		}
	}
}


TitleLoadScene::~TitleLoadScene()
{

}

void TitleLoadScene::Update(float eTime){
	ZeroIScene::Update(eTime);
	cursor->SetPos(ZeroInputMgr->GetClientPoint());
	Checktime -= 0.008;
	repeater += 1.8*0.016;
	if (isAnimation){
		Checktime -= 0.024;
		for (int i = 0; i < ZerosWidth; i++){
			for (int j = 0; j < ZerosHeight; j++){
				if (i<ZerosWidth - 1)Zeros[i][j]->SetString("%d%d%d%d%d%d%d%d%d", rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2);
				else Zeros[i][j]->SetString("%d%d%d%d%d%d%d%d%d%d", rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2);
				float distance =(abs(18-j)/18.0);
				distance *= repeater*repeater;
				if (repeater > 3.2&&!temp){
					Checktime = 1;
					temp = true;
					Logo = new ZeroSprite("Texture/logo.png");
					Logo->SetColor(0xf07aaff);
					Logo->SetColorA(0x00);
					Logo->SetPos(1280 / 2-15, 720 / 2+5);
					Logo->SetScale(40 / 300.0);
				}
				if (repeater > 4.2&&repeater<5.2){
					if (Checktime < 0)Checktime = 0;
					Logo->SetColorA(0xff - (0xff * Checktime));
					Zeros[i][18]->SetColorA(0xff * Checktime);
					Zeros[i][17]->SetColorA(0x0);
					Zeros[i][19]->SetColorA(0x0);
					continue;
				}
				if (repeater > 5.2){
					distance = 1;
					Logo->SetPos(1280 / 2 - 100, 720 / 2 - 75);
					isAnimation = false;
					Logo->SetColorA(0xff);
					Checktime = 1;
					Logo->SetScalingCenter(Logo->Width() / 2.0f, Logo->Height()/2.0);
					repeater = 1;
				}
				Zeros[i][j]->SetColorA(0xff- 0xff * distance);
			}
		}
//		Checktime = 0;
	}
	else{
		if (!isLoging){
			if (Logo->Scale().x<10)
				Logo->AddScale(eTime*2);
			if (Checktime < 0)Checktime = 0;
			Logo->SetColorG((0xff - 0x55 * Checktime));
			Logo->SetColorR((0xff - 0xf8 * Checktime));
			Logo->SetColorB((0xff - 0x00 * Checktime));
			if (Logo->Scale().x >= 1){
				isLoging = true;
				left = new ZeroFont(300, "Zer","Consolas", "Font/consolab.ttf");
				right = new ZeroFont(300, "pen","Consolas", "Font/consolab.ttf");
				temps = new ZeroFont(80, "SUNRIN HIGH SCHOOL DEVELOPMENT");
				temps->SetPos(105, 500);
				Logo->SetColor(0xffffffff);
				PushScene(temps);
				temps->SetColor(0x00ffffff);
				left->SetPos(150, 720 / 2.0 - 150);
				Checktime = 1;
				right->SetPos(700, 720 / 2.0 - 150);
				left->SetColorA(0);
				right->SetColorA(0);
			}
		}
		else{
			Checktime -= 0.008;
			if (repeater > 7){
				bg->SetColor(0xffffd740);
			}
			else if (repeater > 5){
				bg->SetColorR(0xff * (repeater / 7.0));
				bg->SetColorG(0xd7 * (repeater / 7.0));
				bg->SetColorB(0x40 * (repeater / 7.0));
				if (!kapese){
					kapese = true;
				}
			}
			if (Checktime < 0){
				Checktime = 0;
				
			}

			left->SetColorA(0xff - 0xff * (Checktime * 2));
			temps->SetColorA(0xff - 0xff * (Checktime * 2));
			right->SetColorA(0xff - 0xff * (Checktime * 2));
			if (repeater > 8 && !isSceneLoad){
				isSceneLoad = true;
				ZeroSceneMgr->ChangeScene(new TitleScene(), TR::Fade);
			}
		}

	}

}

void TitleLoadScene::Render(){
	bg->Render();
	if (temp)
	Logo->Render();
	if (isAnimation){
		for (int i = 0; i < ZerosWidth; i++){
			for (int j = 0; j < ZerosHeight; j++){
				Zeros[i][j]->Render();
			}
		}
	}
	else{
		if (isLoging){
			left->Render();
			right->Render();

		}
	}
	if (repeater > 6){
		temps->Render();
	}
	cursor->Render();
}