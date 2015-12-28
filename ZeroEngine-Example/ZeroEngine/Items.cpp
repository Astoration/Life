#include "stdafx.h"
#include "Items.h"
#include "InGameScene.h"
#include<math.h>
#include <iostream>
#include <time.h>
using namespace std;

Items::Items(bool kind, int currentLife, bool times)
	:adr(530)
{
	srand(time(NULL));
	randomKind = rand() % 2;
	this->times = times;
	p_item = new ZeroSprite("Texture/%s/%d_%d.png", times ? "morningItem" : "nightItem", currentLife, randomKind);
	p_item->SetScale(0.8, 0.8);
	p_item->SetRotCenter(p_item->Width() / 2, p_item->Height());

	if (kind){
		p_item->SetPosX(-200);
		p_item->SetRot(-40);
		addPlus = 30;
	}
	else{
		p_item->SetPosX(1280);
		p_item->SetScalingCenter(p_item->Width() / 2, 0);
		p_item->SetScale(-0.8, 0.8);
		adr = -530;
		p_item->SetRot(40);
		addPlus = -30;
	}
	p_item->SetPosY(720 - 150);

}

Items::~Items()
{
}

void Items::Update(float eTime){
	if (this->IsErase())return;
	p_item->AddPosX(adr*eTime);
	p_item->AddRot(addPlus*eTime);
	InGameScene* temp = (InGameScene*)this->Parent();
	if (temp->kind){
		adr = 530;
		addPlus = 30;
	}
	else{
		adr = -530;
		addPlus = -30;
	}
	bool result = 100>sqrt(pow(abs(p_item->Pos().x - temp->p_mPlayer->p_player->Pos().x), 2) + pow(abs(p_item->Pos().y - temp->p_mPlayer->p_player->Pos().y), 2));
	if (result){
		InGameScene* temps = (InGameScene*)this->Parent();
		switch (times){
		case true:
			switch (randomKind){
			case 0:
				temps->interfaceOne->SetColor(0xffffffff);
				break;
			case 1:
				temps->interfaceTwo->SetColor(0xffffffff);
				break;
			}
			break;
		case false:
			switch (randomKind){
			case 0:
				temps->interfaceThree->SetColor(0xffffffff);
				break;
			case 1:
				temps->interfaceFour->SetColor(0xffffffff);
				break;
			}
			break;
		}
		temps->HpUpdate(1);
		ZeroSoundMgr->Play("get");
		temps->score += 100;
		this->SetErase(true);
		return;
	}
	p_item->SetPosY(720 - 500 - (ZeroMathMgr->Sin((ZeroMathMgr->Pi*((p_item->Pos().x + 100) / (1280))) * 60) * 170));
	if (p_item->Pos().x < -200 || p_item->Pos().x>1280) {
		this->SetErase(true);
		return;
	}
}

void Items::Render(){
	if (this->IsErase())return;
	p_item->Render();
}