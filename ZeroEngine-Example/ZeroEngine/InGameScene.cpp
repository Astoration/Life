#include "stdafx.h"
#include "GameOverScene.h"
#include "Monster.h"
#include "InGameScene.h"
#include "Serial.h"
#include "SerialUtil.h"
#include <iostream>
#include "Items.h"
using namespace std;

InGameScene::InGameScene()
	:kind(true), light(0), reConnect(false), times(0), currentLife(1), hpTime(0), isMorning(true), hp(8), daysCount(0), coolTime(0), score(0)
{
	ZeroSoundMgr->PushSound("Sound/brick.wav","brick");
	ZeroSoundMgr->PushSound("Sound/get.wav", "get");
	ZeroSoundMgr->PushSound("Sound/jump.mp3", "jump");
	p_mMap = new Map();
	ZeroSoundMgr->Stop("gameover");
	ZeroSoundMgr->Stop("story");
	ZeroSoundMgr->Play("ingame");
	cursor = new ZeroSprite("Texture/cursor.png");
	p_mPlayer = new Player();
	message = new ZeroSprite("Texture/loading.png");
	message->SetPos(1280 / 2 - message->Width() / 2, 720 / 2 - message->Height() / 2);
	PushScene(p_mMap,false);
	PushScene(p_mPlayer,false);
	PushScene(message);
	interfaceOne  = new ZeroSprite("Texture/morningItem/1_0.png");
	interfaceTwo  = new ZeroSprite("Texture/morningItem/1_1.png");
	interfaceThree = new ZeroSprite("Texture/nightItem/1_0.png");
	interfaceFour = new ZeroSprite("Texture/nightItem/1_1.png");
	  interfaceOne->SetScale(0.5);
	  interfaceTwo->SetScale(0.5);
	interfaceThree->SetScale(0.5);
	 interfaceFour->SetScale(0.5);
	 interfaceOne->SetColor(0xff222222);
	 interfaceTwo->SetColor(0xff222222);
	 interfaceThree->SetColor(0xff222222);
	 interfaceFour->SetColor(0xff222222);
	 interfaceOne->SetPos(1280/2-90-100, 720 - 150);
	interfaceTwo->SetPos(1280/2-90-210, 720 - 150);
	interfaceThree->SetPos(1280/2+10+100, 720 - 150);
	interfaceFour->SetPos(1280/2+10+210, 720 - 150);
	interfaceHP = new ZeroSprite("Texture/HP_bar/8.png");
	interfaceHP->SetPos(1280 / 2 - interfaceHP->Width()/2, 720 - 180);
	PushScene(interfaceHP);
	Weather[0] = "sakura";
	Weather[1] = "rain";
	Weather[2] = "maple";
	Weather[3] = "snow";
	try{
		su = new SerialUtil();
	}
	catch (string s)
	{
		cout << "..ERROR OCCURED::" << s << " :( \n";
	}
	if (su->SP->IsConnected()){
		reConnect = false;
	}
	else{
		reConnect = true;
	}
}


InGameScene::~InGameScene()
{
}

void InGameScene::HpUpdate(int distance){
	hp += distance;
	if (hp > 8)hp = 8;
	if (hp < 1){
		ZeroSceneMgr->ChangeScene(new GameOverScene(score, this->StartToCurrentTime()), TR::Fade);
		return;
	}
	hpTime = 0;
	PopScene(interfaceHP, true);
	interfaceHP = new ZeroSprite("Texture/HP_bar/%d.png", hp);
	interfaceHP->SetPos(1280 / 2 - interfaceHP->Width() / 2, 720 - 180);
	PushScene(interfaceHP);
}

void InGameScene::Update(float eTime){
	if (SerialUtil::SP->IsConnected())
	{
		str = su->read();
		int str2 = atoi(str.c_str());
		if (str2 > 100){
			light = str2;
			reConnect = false;
			times = 0;
		}
		//cout << str2 << endl;
	}
	
	if (ZeroInputMgr->GetKey('Z') == INPUTMGR_KEYDOWN){
		if(light!=500)light = 500;
		else light = 50;
	}

	if (!reConnect){
		times += eTime;
		coolTime += eTime;
		hpTime += eTime;
		if (hpTime > 2){
			hpTime = 0;
			hp--;
			if (hp < 1){
				ZeroSceneMgr->ChangeScene(new GameOverScene(score, this->StartToCurrentTime()), TR::Fade,1.0f);
				return;
			}
			PopScene(interfaceHP, true);
			interfaceHP = new ZeroSprite("Texture/HP_bar/%d.png", hp);
			interfaceHP->SetPos(1280 / 2 - interfaceHP->Width() / 2, 720 - 180);
			PushScene(interfaceHP);
		}
		if (times > 5){
			reConnect = true;
		}
		cout << light << endl;
		
		if (light < 450 && isMorning){
			daysCount++;
			if (ZeroMathMgr->RandInt(0, 100) < 30){
				isWeather = true;
			}
			else{
				isWeather = false;
			}
			isMorning = false;
			hpTime = 0;
			hp++;
			if (hp > 8)hp = 8;
			PopScene(interfaceHP, true);
			interfaceHP = new ZeroSprite("Texture/HP_bar/%d.png", hp);
			interfaceHP->SetPos(1280 / 2 - interfaceHP->Width() / 2, 720 - 180);
			PushScene(interfaceHP);
		}
		else if (light>450&&!isMorning){
			isMorning = true;
			hpTime = 0;
			hp++;
			if (hp > 8)hp = 8;

			PopScene(interfaceHP, true);
			interfaceHP = new ZeroSprite("Texture/HP_bar/%d.png", hp);
			interfaceHP->SetPos(1280 / 2 - interfaceHP->Width() / 2, 720 - 180);
			PushScene(interfaceHP);
		}
		if (!isMorning){
			p_mMap->p_sky->SetColorR(0xFF -150);
			p_mMap->p_sky->SetColorG(0xFF -150);
			p_mMap->p_sky->SetColorB(0xFF -150);
		}
		else{
			p_mMap->p_sky->SetColorR(0xFF);
			p_mMap->p_sky->SetColorG(0xFF);
			p_mMap->p_sky->SetColorB(0xFF);
		}
		if (daysCount > 9&&currentLife<6){
			daysCount = 0;
			if (!(interfaceOne->Color() == 0xffffffff && interfaceTwo->Color() == 0xffffffff && interfaceThree->Color() == 0xffffffff && interfaceFour->Color() == 0xffffffff)){
				hp -= 5;
				score -= 1000;
			}
			currentLife++;
			PopScene(interfaceOne, true);
			PopScene(interfaceTwo, true);
			PopScene(interfaceThree, true);
			PopScene(interfaceFour, true);
			interfaceOne = new ZeroSprite("Texture/morningItem/%d_0.png",currentLife);
			interfaceTwo = new ZeroSprite("Texture/morningItem/%d_1.png",currentLife);
			interfaceThree = new ZeroSprite("Texture/nightItem/%d_0.png",currentLife);
			interfaceFour = new ZeroSprite("Texture/nightItem/%d_1.png",currentLife);
			interfaceOne->SetScale(0.5);
			interfaceTwo->SetScale(0.5);
			interfaceThree->SetScale(0.5);
			interfaceFour->SetScale(0.5);
			interfaceOne->SetColor(0xff222222);
			interfaceTwo->SetColor(0xff222222);
			interfaceThree->SetColor(0xff222222);
			interfaceFour->SetColor(0xff222222);
			interfaceOne->SetPos(1280 / 2 - 90 - 100, 720 - 150);
			interfaceTwo->SetPos(1280 / 2 - 90 - 210, 720 - 150);
			interfaceThree->SetPos(1280 / 2 + 10 + 100, 720 - 150);
			interfaceFour->SetPos(1280 / 2 + 10 + 210, 720 - 150);
			p_mPlayer->ResourceReload(currentLife);
		}
		if (ZeroInputMgr->GetKey('A') == INPUTMGR_KEYDOWN){
			p_mMap->adr = 30;
			p_mPlayer->p_player->SetScale(-1, 1);
			kind = true;

		}
		else if (ZeroInputMgr->GetKey('D') == INPUTMGR_KEYDOWN){
			p_mMap->adr = -30;
			p_mPlayer->p_player->SetScale(1, 1);
			kind = false;
			
		}
		p_mMap->Update(eTime);
		p_mPlayer->Update(eTime);
		int rand = ZeroMathMgr->RandInt(0, 10000);
		if (rand > 9900&&coolTime>1){
			Items *tempItems = new Items(kind, currentLife, isMorning);
			coolTime = 0;
			PushScene(tempItems);
		}
		if (rand > 9600&&!(isMorning&&currentLife==1)&&coolTime>1){
			Monster* tempMT = new Monster(kind, currentLife,isMorning);
			coolTime = 0;
			PushScene(tempMT);
		}
		if (isWeather){
			char tempChar[100];
			sprintf(tempChar, "Texture/weather/%s.png", Weather[(daysCount / 2) % 4]);
			ZeroParticleSprite* p = new ZeroParticleSprite(tempChar, 5);
			p->SetPos(ZeroMathMgr->RandInt(-100,1280), -200);
			p->SetScalingCenter(p->Width() / 2, p->Height() / 2);
			p->SetParticleSpread(180);
			p->SetParticleLifeTime(8, 11);
			p->SetParticleScale(0.8, 1.1);
			p->SetParticleSpeed(0, 300);
			p->SetRenderPage(1);
			PushScene(p);
			p->Start();
		}
		ZeroIScene::Update(eTime);
	}
	else {
			try{
				SAFE_DELETE(su->SP);
				su->SP = new Serial(su->port);
				if (su->SP->IsConnected()){
					reConnect = false;
				}
				times = 0;
				Sleep(1000);
			}
			catch (string s)
			{
				cout << "..ERROR OCCURED::" << s << " :( \n";
			}
		}
	cursor->SetPos(ZeroInputMgr->GetClientPoint());
}

void InGameScene::Render(){
		p_mMap->Render();
		for (NODE::iterator iter = ZeroIScene::m_Node.begin(); iter != ZeroIScene::m_Node.end(); ++iter) {
			if ((*iter) != p_mMap && (*iter) != p_mPlayer && (*iter) != message){
				(*iter)->Render();
			}

			if ((*iter)->IsErase()) {
				SAFE_DELETE(*iter);
				iter = ZeroIScene::m_Node.erase(iter);
				if (iter == ZeroIScene::m_Node.end()) break;
			}
		}
		p_mPlayer->Render();
		ZeroRTMgr("Particle")->Begin();
		ZeroEffectMgr->RenderPage(1);
		ZeroRTMgr("Particle")->End();
		ZeroRTMgr("Particle")->Render();
		interfaceOne->Render();
		interfaceTwo->Render();
		interfaceThree->Render();
		interfaceFour->Render();
		interfaceHP->Render();
		if (reConnect)
			message->Render();
		cursor->Render();
}