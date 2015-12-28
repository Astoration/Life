#include "stdafx.h"
#include "StoryScene.h"
#include "InGameScene.h"

StoryScene::StoryScene()
{

	ZeroSoundMgr->Stop("ingame");
	ZeroSoundMgr->Stop("gameover");
	ZeroSoundMgr->Play("story");
	bg = new ZeroSprite("Texture/loadBg.png");
	bg->SetScale(10);
	a = new ZeroSprite("Texture/story/a.png");
	a->SetPos(30, 30);
	b = new ZeroSprite("Texture/story/b.png");
	b->SetPos(1280 - 30 - b->Width(), 30);
	c = new ZeroSprite("Texture/story/c.png");
	c->SetPos(30, 720 - 30 - c->Height());
	d = new ZeroSprite("Texture/story/d.png");
	d->SetPos(1280 - 30 - d->Width(), 720 - 30 - d->Height());
	for (int i = 0; i < 5; i++)
		Line[i] = false;
	Line[0] = true;
	times = 0;
	LoadingBg = new ZeroSprite("Texture/loadingBg.png");
	LoadingCircle = new ZeroSprite("Texture/loadingCircle.png");
	LoadingCircle->SetPos(1280 / 2.0 - LoadingCircle->Width() / 2.0, 720 / 2.0 - LoadingCircle->Height() / 2.0);
	LoadingCircle->SetRotCenter(LoadingCircle->Width() / 2.0, LoadingCircle->Height() / 2.0);
	isSponed = false;
}


StoryScene::~StoryScene()
{
}

void StoryScene::Update(float eTime){
	if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN||ZeroInputMgr->GetKey(VK_LBUTTON)==INPUTMGR_KEYDOWN){
		if (Line[1] == false)Line[1] = true;
		else if (Line[2] == false)Line[2] = true;
		else if (Line[3] == false)Line[3] = true;
		else if (Line[4] == false)Line[4] = true;
	}
	LoadingCircle->AddRot(200 * eTime);
	if (Line[4])times += eTime;
	if (times > 6 && !isSponed){
		ZeroSceneMgr->ChangeScene(new InGameScene(), TR::Fade);
		isSponed = true;
	}
}

void StoryScene::Render(){
	bg->Render();
	if (Line[0]) a->Render();
	if (Line[1]) b->Render();
	if (Line[2]) c->Render();
	if (Line[3]) d->Render();
	if (Line[4]){
		LoadingBg->Render();
		LoadingCircle->Render();
	}
}