#include "../include/entityfactory.h"
#include "../include/entity.h"
#include "../include/resourcestore.h"
#include "../include/lvlManager.h"
#include "../include/rapidjson/document.h"
#include "../include/gamecomponents.h"

#include "../../Ugine/include/string.h"
#include "../../Ugine/include/image.h"

using namespace rapidjson;

Entity * EntityFactory::CreatePlayerOne()
{
	Entity * entity;
	Image * ship = nullptr;
	Document document;
	String string;
	const char * json;
	float life, energy, eneryRegeneration;

	/*Retive spaceshipdata*/
	switch (LevelManager::Instance().GetPLayerOneSpaceShip())
	{
		
	case LevelManager::AVATAR:
		string = String::Read("../data/spaceships/avatar/data.cfg");
		json = string.ToCString();
		document.Parse(json);
		ship = ResourceStore::Instance().GetAvatarImage();
		break;
	case  LevelManager::DREADNOUGH:
		string = String::Read("../data/spaceships/dreadnought/data.cfg");
		json = string.ToCString();
		document.Parse(json);
		ship = ResourceStore::Instance().GetDreadnoughtImage();
		break;
	}
	entity = new Entity(0, 0, ship->GetWidth(), ship->GetHeight(), 0);//create entity
	/*Set spaceship control*/
	switch (LevelManager::Instance().GetPLayerOneType())
	{
		float linearVel, angularVel;
	case LevelManager::HUMAN:
	{
		string = String::Read("../data/config/keybindings.cfg");
		json = string.ToCString();

		Document keybindings;
		keybindings.Parse(json);

		assert(keybindings.HasMember("Player1"));
		assert(keybindings["Player1"].IsObject());

		assert(document.HasMember("LinearVelocity"));
		assert(document["LinearVelocity"].IsNumber());
		assert(document["LinearVelocity"].IsFloat());
		linearVel = document["LinearVelocity"].GetFloat();

		assert(document.HasMember("AngularVelocity"));
		assert(document["AngularVelocity"].IsNumber());
		assert(document["AngularVelocity"].IsFloat());
		angularVel = document["AngularVelocity"].GetFloat();

		ComponentPlayerController * playerController = new ComponentPlayerController(linearVel, angularVel);
		playerController->BinKeys(static_cast<inputs>(keybindings["Player1"]["UP"].GetInt()), static_cast<inputs>(keybindings["Player1"]["DOWN"].GetInt()), static_cast<inputs>(keybindings["Player1"]["RLEFT"].GetInt()), static_cast<inputs>(keybindings["Player1"]["RRIGHT"].GetInt()));
		entity->AddComponent(playerController);
	}
	break;
	case  LevelManager::EASY:
		//addIAcomponent
		break;
	}

	assert(document.HasMember("Life"));
	assert(document["Life"].IsNumber());
	assert(document["Life"].IsFloat());
	life = document["Life"].GetFloat();

	assert(document.HasMember("Energy"));
	assert(document["Energy"].IsNumber());
	assert(document["Energy"].IsFloat());
	energy = document["Energy"].GetFloat();

	assert(document.HasMember("EnergyRegeneration"));
	assert(document["EnergyRegeneration"].IsNumber());
	assert(document["EnergyRegeneration"].IsFloat());
	eneryRegeneration = document["EnergyRegeneration"].GetFloat();

	ComponentStats * stats = new ComponentStats(life, energy, eneryRegeneration);
	entity->AddComponent(stats);

	ComponentRenderer * renderer = new ComponentRenderer(ship);
	entity->AddComponent(renderer);

	ComponentCircleCollision * collider = new ComponentCircleCollision(1000, false);
	entity->AddComponent(collider);

	ComponentShipExplosion * explosion = new ComponentShipExplosion(this);
	entity->AddComponent(explosion);

	entityStore.Add(entity);
	return entity;
}

Entity * EntityFactory::CreatePlayerTwo()
{
	Entity * entity;
	Image * ship = nullptr;
	Document document;
	String string;
	const char * json;
	float life, energy, eneryRegeneration;

	switch (LevelManager::Instance().GetPLayerTwoSpaceShip())
	{

	case LevelManager::AVATAR:
		string = String::Read("../data/spaceships/avatar/data.cfg");
		json = string.ToCString();
		document.Parse(json);
		ship = ResourceStore::Instance().GetAvatarImage();
		break;
	case  LevelManager::DREADNOUGH:
		string = String::Read("../data/spaceships/dreadnought/data.cfg");
		json = string.ToCString();
		document.Parse(json);
		ship = ResourceStore::Instance().GetDreadnoughtImage();
		break;
	}
	entity = new Entity(0, 0, ship->GetWidth(), ship->GetHeight(), 0);
	switch (LevelManager::Instance().GetPLayerTwoType())
	{
		float linearVel, angularVel;
	case LevelManager::HUMAN:
	{
		string = String::Read("../data/config/keybindings.cfg");
		json = string.ToCString();

		Document keybindings;

		keybindings.Parse(json);

		assert(keybindings.HasMember("Player2"));
		assert(keybindings["Player2"].IsObject());

		assert(document.HasMember("LinearVelocity"));
		assert(document["LinearVelocity"].IsNumber());
		assert(document["LinearVelocity"].IsFloat());
		linearVel = document["LinearVelocity"].GetFloat();

		assert(document.HasMember("AngularVelocity"));
		assert(document["AngularVelocity"].IsNumber());
		assert(document["AngularVelocity"].IsFloat());
		angularVel = document["AngularVelocity"].GetFloat();

		ComponentPlayerController * playerController = new ComponentPlayerController(linearVel, angularVel);
		playerController->BinKeys(static_cast<inputs>(keybindings["Player2"]["UP"].GetInt()), static_cast<inputs>(keybindings["Player2"]["DOWN"].GetInt()), static_cast<inputs>(keybindings["Player2"]["RLEFT"].GetInt()), static_cast<inputs>(keybindings["Player2"]["RRIGHT"].GetInt()));
		entity->AddComponent(playerController);

	}
	break;
	case  LevelManager::EASY:
		//addIAcomponent
		break;
	}

	assert(document.HasMember("Life"));
	assert(document["Life"].IsNumber());
	assert(document["Life"].IsFloat());
	life = document["Life"].GetFloat();

	assert(document.HasMember("Energy"));
	assert(document["Energy"].IsNumber());
	assert(document["Energy"].IsFloat());
	energy = document["Energy"].GetFloat();

	assert(document.HasMember("EnergyRegeneration"));
	assert(document["EnergyRegeneration"].IsNumber());
	assert(document["EnergyRegeneration"].IsFloat());
	eneryRegeneration = document["EnergyRegeneration"].GetFloat();

	ComponentStats * stats = new ComponentStats(life, energy, eneryRegeneration);
	entity->AddComponent(stats);

	ComponentRenderer * renderer = new ComponentRenderer(ship);
	entity->AddComponent(renderer);

	ComponentCircleCollision * collider = new ComponentCircleCollision(1000, false);
	entity->AddComponent(collider);

	ComponentShipExplosion * explosion = new ComponentShipExplosion(this);
	entity->AddComponent(explosion);

	entityStore.Add(entity);
	return entity;
}
Entity * EntityFactory::CreateDrone(double x, double y, double rotation)
{
	Entity * entity;
	Image * drone = nullptr;
	Document document;
	String string;
	drone = ResourceStore::Instance().GetDroneImage(63, 1);
	entity = new Entity(x, y, drone->GetWidth(), drone->GetHeight(), rotation);
	ComponentRenderer * renderer = new ComponentRenderer(drone, 63, 30);
	entity->AddComponent(renderer);
	entityStore.Add(entity);
	return entity;
}
Entity * EntityFactory::CreateShipExplosion(double x, double y)
{
	Entity * entity;
	Image * explosion = nullptr;
	Document document;
	String string;
	explosion = ResourceStore::Instance().GetExplosionImage(20, 1, rand()%2);
	entity = new Entity(x, y, explosion->GetWidth(), explosion->GetHeight(), 0);
	ComponentRenderer * renderer = new ComponentRenderer(explosion, 20, 30,false);
	entity->AddComponent(renderer);
	entityStore.Add(entity);
	return entity;
}
