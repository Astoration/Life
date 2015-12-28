#include "stdafx.h"
#include "Map.h"


Map::Map()
	:adr(30)
{
	p_sky = new ZeroSprite("Texture/sky.png");
	PushScene(p_sky);
	p_map = new ZeroSprite("Texture/map.png");
	p_map->AddScale(1.5f);
	p_map->SetRotCenter(p_map->Width()*2.5 / 2, p_map->Height()*2.5 / 2);
	p_map->SetPos(-(p_map->Width()*2.5 / 2 - 1280 / 2), -100);
	PushScene(p_map);
}


Map::~Map()
{
}

void Map::Update(float eTime){
	p_sky->Update(eTime);
	p_map->Update(eTime);
	p_map->AddRot(adr * eTime);
}

void Map::Render(){
	p_sky->Render();
	p_map->Render();
}