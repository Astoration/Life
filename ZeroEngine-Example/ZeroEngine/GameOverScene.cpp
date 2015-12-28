#include "stdafx.h"
#include "GameOverScene.h"
#include "TitleScene.h"


GameOverScene::GameOverScene(int score, float currentTime)
{
	ZeroSoundMgr->Stop("story");
	ZeroSoundMgr->Stop("ingame");
	ZeroSoundMgr->Play("gameover");
	bg = new ZeroSprite("Texture/sky.png");
	PushScene(bg);
	map = new ZeroSprite("Texture/map.png");
	map->AddScale(1.5f);
	window = new ZeroSprite("Texture/gameover.png");
	//window->SetPos(1280 / 2 - window->Width() / 2, 720 / 2 - window->Height() / 2);
	map->SetPos(-(map->Width()*2.5 / 2 - 1280 / 2), -100);
	PushScene(map);
	message = new ZeroFont(70, "","나눔손글씨 펜", "Texture/NanumPen.ttf");
	message->SetString("당신은\n%d일 동안\n살아왔습니다.\n당신의\n행복지수는\n%d였습니다.", (int)currentTime, score);
	message->SetPos(450, 200);
	message->SetColor(0xff545454);
	cursor = new ZeroSprite("Texture/cursor.png");

}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update(float eTime){
	ZeroIScene::Update(eTime);
	if (map->Pos().y<-500 && ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN){
		ZeroSceneMgr->ChangeScene(new TitleScene(), TR::Fade);
	}
	if(map->Pos().y>-500)map->AddPosY(-300 * eTime);
	cursor->SetPos(ZeroInputMgr->GetClientPoint());

}

void GameOverScene::Render(){
	bg->Render();
	map->Render();
	if (map->Pos().y < -500)window->Render();
	if (map->Pos().y < -500)message->Render();
	cursor->Render();
}