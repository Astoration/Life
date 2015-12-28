#include "stdafx.h"
#include "TitleScene.h"
#include "StoryScene.h"
#include "InGameScene.h"


TitleScene::TitleScene()
{
	ZeroSoundMgr->PushSound("Sound/story.mp3", "story");
	ZeroSoundMgr->PushSound("Sound/gameover.mp3","gameover");
	ZeroSoundMgr->PushSound("Sound/backgroundIn.mp3","ingame");
	ZeroSoundMgr->Play("gameover");
	ZeroSoundMgr->Stop("story");
	ZeroSoundMgr->Stop("ingame");
	p_bg[0] = new ZeroSprite("Texture/scene1.jpg");
	p_bg[0]->SetScale(2);
	PushScene(p_bg[0]);
	p_bg[1] = new ZeroSprite("Texture/scene2.jpg");
	PushScene(p_bg[1]);
	p_bg[1]->SetScale(2);
	p_bg[2] = new ZeroSprite("Texture/scene3.jpg");
	PushScene(p_bg[2]);
	p_bg[2]->SetScale(2);
	p_bg[3] = new ZeroSprite("Texture/scene4.jpg");
	PushScene(p_bg[3]);
	p_bg[3]->SetScale(2);
	p_button = new ZeroSprite("Texture/start.png");
	p_button->SetPos(100, 450);
	PushScene(p_button);
	cursor = new ZeroSprite("Texture/cursor.png");
	for (int i = 0; i < 4; i++){
		p_bg[i]->AddPosX(300);
	}
	alpha[0] = 100;
	alpha[1] = 0;
	nowIndex = 0;
	alpha[2] = 0;
	alpha[3] = 0;
	city = new ZeroSprite("Texture/city.png");
	city->SetScale(2);
	clock = new ZeroSprite("Texture/clock.png");
	clock->SetScale(2);
	hour = new ZeroSprite("Texture/hour.png");
	hour->SetScale(2);
	minute = new ZeroSprite("Texture/min.png");
	minute->SetScale(2);
	city->AddPosX(-500);
	city->AddPosY(-400);
	clock->AddPosX(-500);
	clock->AddPosY(-400);
	hour->AddPosX(-500);
	hour->AddPosY(-400);
	minute->AddPosX(-500);
	minute->AddPosY(-400);
	city->SetRotCenter(750, 750);
	clock->SetRotCenter(750, 750);
	hour->SetRotCenter(750, 750);
	minute->SetRotCenter(750, 750);
	ttitle = new ZeroSprite("Texture/ttitle.png");
	ttitle->SetPos(1050, 10);

}


TitleScene::~TitleScene()
{
}

void TitleScene::Update(float eTime){
	ZeroIScene::Update(eTime);
	if (p_button->IsOverlapped(ZeroInputMgr->GetClientPoint())){
		p_button->SetColorA(150);
		if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN){
			ZeroSceneMgr->ChangeScene(new StoryScene(), TR::Fade);
			return;
		}
	}
	else p_button->SetColorA(255);

	if (nowIndex < 3){
		alpha[nowIndex] -= eTime*50;
		alpha[nowIndex + 1] += eTime*50;
		if (alpha[nowIndex] < 0){
			nowIndex++;
			alpha[nowIndex - 1] = 0;
		}
	}else{
		alpha[3] -= eTime*50;
		alpha[0] += eTime*50;
		if (alpha[3] < 0){
			nowIndex = 0;
			alpha[3] = 0;
		}
	}

	city->AddRot(-eTime * 50);
	hour->AddRot(eTime * 25);
	cursor->SetPos(ZeroInputMgr->GetClientPoint());
	minute->AddRot(eTime * 150);
}

void TitleScene::Render(){
	for (int i = 0; i < 4; i++){
		p_bg[i]->SetColorA(0xff * (alpha[i]/100.0));
		p_bg[i]->Render();
	}
	clock->Render();
	city->Render();
	p_button->Render();

	hour->Render();
	minute->Render();
	ttitle->Render();
	cursor->Render();
}	