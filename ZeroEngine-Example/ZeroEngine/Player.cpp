#include "stdafx.h"
#include "Player.h"
#include <iostream>
using namespace std;


Player::Player()
	:MathPlus(ZeroMathMgr->Pi / 120.0), isJumped(false), MathCount(0), count(0)
{
	p_player = new ZeroAnimation(8.0f);
	for (int i = 1; i <= 8; i++)
		p_player->PushSprite("Texture/1/running%d.png", i);
	p_player->SetPos(1280 / 2 - p_player->Width() / 2, 310);
	p_player->SetScalingCenter(p_player->Width() / 2, 0);
	p_player->AddScale(-2.0, 0);
	PushScene(p_player);
	p_Action = new ZeroAnimation(3.0f);
	for (int i = 1; i <= 2; i++)
		p_Action->PushSprite("Texture/1/jump%d.png", i);
	for (int i = 1; i <= 2; i++)
		p_Action->PushSprite("Texture/1/falling%d.png", i);
	p_Action->Stop();
	p_Action->SetScalingCenter(p_Action->Width() / 2, 0);
	PushScene(p_Action);
}


Player::~Player()
{
}

void Player::ResourceReload(int currentfLife){
	ZeroVec tempScale = p_player->Scale();
	ZeroVec temp = p_player->Pos();
	int l = 1, k = 1, j = 1;
	PopScene(p_player, true);
	p_player = new ZeroAnimation(8.0f);
	for (l = 1; l <= 8; l++){
		p_player->PushSprite("Texture/%d/running%d.png", currentfLife, l);
	}
	p_player->SetPos(temp);
	p_player->SetScalingCenter(p_player->Width() / 2, 0);
	PushScene(p_player);
	PopScene(p_Action, true);
	p_Action = new ZeroAnimation(3.0f);
	for (k = 1; k <= 2; k++) p_Action->PushSprite("Texture/%d/jump%d.png", currentfLife, k);
	for (j = 1; j <= 2; j++) p_Action->PushSprite("Texture/%d/falling%d.png", currentfLife, j);
	p_Action->Stop();
	p_Action->SetScalingCenter(p_Action->Width() / 2, 0);
	PushScene(p_Action);
	p_player->SetScale(tempScale);
}

void Player::Update(float eTime){
	if (count > 0){
		p_player->SetColorA(0xff- 100 - ZeroMathMgr->Sin(StartToCurrentTime()*600)*100);
		p_Action->SetColorA(0xff- 100 - ZeroMathMgr->Sin(StartToCurrentTime()*600) * 100);
		//cout << count << endl;

		count--;
	}
	else{
		p_player->SetColorA(0xff);
		p_Action->SetColorA(0xff);
	}
	if (ZeroInputMgr->GetKey(VK_SPACE)==INPUTMGR_KEYDOWN){
		isJumped = true;
		ZeroSoundMgr->Play("jump");
		p_Action->SetCurrentFrame(0);
		p_Action->Start();
	}
	if (isJumped){
		MathCount += MathPlus*2.5;
		p_player->SetPosY(310 - 300*ZeroMathMgr->Sin(MathCount*60));
	}
	p_Action->SetPos(p_player->Pos());
	p_Action->SetScale(p_player->Scale());
	if (MathCount > ZeroMathMgr->Pi){
		isJumped = false;
		MathCount = 0;
		p_Action->SetCurrentFrame(0);
		p_Action->Stop();
		p_player->SetPosY(310); 
	}
	ZeroIScene::Update(eTime);
}

void Player::Render(){
	if(!isJumped)p_player->Render();
	else p_Action->Render();

}