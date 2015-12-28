#include "stdafx.h"
#include "Monster.h"
#include "InGameScene.h"
#include<math.h>
#include <iostream>
using namespace std;

Monster::Monster(bool kind, int currentLife, bool time)
	:adr(550)
{
	p_mt = new ZeroSprite("Texture/%s/%d.png",time?"morningMT":"nightMT",currentLife);
	p_mt->SetScale(0.8, 0.8);
	p_mt->SetRotCenter(p_mt->Width() / 2, p_mt->Height());

	if (kind){
		p_mt->SetPosX(-200);
		p_mt->SetRot(-40);
		addPlus = 28;
	}
	else{
		p_mt->SetPosX(1280);
		p_mt->SetScalingCenter(p_mt->Width() / 2, 0);
		p_mt->SetScale(-0.8, 0.8);
		adr = -550;
		p_mt->SetRot(40);
		addPlus = -28;
	}
	p_mt->SetPosY(720 - 150);
	
}

Monster::~Monster()
{
}

void Monster::Update(float eTime){
	if (this->IsErase()) return;
	InGameScene* temp = (InGameScene*)this->Parent();
	if (temp->kind){
		adr = 550;
		addPlus = 28;
	}
	else{
		adr = -550;
		addPlus = -28;
	}
	p_mt->AddPosX(adr*eTime);
	p_mt->AddRot(addPlus*eTime);
	bool result = 100>sqrt(pow(abs(p_mt->Pos().x - temp->p_mPlayer->p_player->Pos().x), 2) + pow(abs(p_mt->Pos().y - temp->p_mPlayer->p_player->Pos().y), 2));
	if (result&&temp->p_mPlayer->count==0){
		temp->p_mPlayer->count = 200;
		temp->score -= 150;
		ZeroSoundMgr->Play("brick");
		temp->HpUpdate(-1);
	}
	p_mt->SetPosY(720 - 200 - (ZeroMathMgr->Sin((ZeroMathMgr->Pi*((p_mt->Pos().x + 100) / (1280)))*60 )*170));
	if (p_mt->Pos().x < -200 || p_mt->Pos().x>1280) {	
		this->SetErase(true);
		return;
	}
}

void Monster::Render(){
	if (this->IsErase()) return;
	p_mt->Render();
}