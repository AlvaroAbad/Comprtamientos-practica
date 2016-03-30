#include "..\include\world.h"
#include "../include/entity.h"
#include "../include/componentmessages.h"

#include "../../Ugine/include/scene.h"
#include "../../Ugine/include/renderer.h"
#include "../../Ugine/include/screen.h"
#include "../../Ugine/include/image.h"

World::World()
{
}

void World::Init()
{
	playerOne = factory.CreatePlayerOne();
	playerOne->x = 400;
	playerOne->y = 300;
	entities.Add(playerOne);
	playerTwo = factory.CreatePlayerTwo();
	playerTwo->x = 300;
	playerTwo->y = 400;
	entities.Add(playerTwo);
	entities.Add(factory.CreateDrone(20, 20, 0));
	endGame = false;
}

void World::run()
{
	Array<Entity *> dead;
	MessageCheckCollision msgCCollision;
	for (size_t i = 0; i < entities.Size(); i++)
	{
		entities[i]->Update(Screen::Instance().ElapsedTime());
		if (entities[i]->dead) {
			dead.Add(entities[i]);
		}
	}

	MessageExplode msgExplode;
	for (size_t i = 0; i < dead.Size(); i++)
	{
		msgExplode.entity = nullptr;
		entities.Remove(dead[i]);
		dead[i]->ReciveMessage(&msgExplode);
		if (msgExplode.entity) {
			entities.Add(msgExplode.entity);
			if (dead[i] == playerOne) {
				playerOne = msgExplode.entity;
			}
			else if (dead[i] == playerTwo) {
				playerTwo = msgExplode.entity;
			}
		}		
	}
	if (playerOne && playerOne->dead) {
		endGame = true;
		playerOne = nullptr;
	}
	if (playerTwo && playerTwo->dead) {
		endGame = true;
		playerTwo = nullptr;
	}
	for (size_t i = 0; i < entities.Size()-1; i++)
	{
		for (size_t j = i+1; j < entities.Size(); j++)
		{
			msgCCollision.entity = entities[j];
			entities[i]->ReciveMessage(&msgCCollision);
		}
	}
}

void World::draw()
{
	MessageGetRendering msgRendering;
	for (size_t i = 0; i < entities.Size(); i++)
	{
		entities[i]->ReciveMessage(&msgRendering);
		if (msgRendering.render) {
			msgRendering.render->SetMidHandle();
			Renderer::Instance().DrawImage(msgRendering.render, msgRendering.x, msgRendering.y, msgRendering.frame, msgRendering.width, msgRendering.height, msgRendering.rotion);
			msgRendering.render->SetHandle(0, 0);
		}
		msgRendering.render = nullptr;
	}
}

World::~World()
{
	for (size_t i = 0; i < entities.Size(); i++)
	{
		delete entities[i];
	}
}
