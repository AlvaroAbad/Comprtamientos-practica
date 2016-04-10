#ifndef SCM_MESSAGES_H
#define SCM_MESSAGES_H

#pragma warning(disable:4820)

#include "../include/world.h"

class Image;
class Collision;
class Entity;

struct Message {
	enum MessageType {
		MSG_GRENDERING,
		MSG_REDUCELIFE,
		MSG_REDUCEENERGY,
		MSG_GLIFE,
		MSG_GENERGY,
		MSG_CHECKCOLLISION,
		MSG_CHECKLASERCOLLISION,
		MSG_GCOLLIDER,
		MSG_ALERTCOLLISION,
		MSG_EXPLODE,
		MSG_WEAPONREADY,
		MSG_FIRE,
		MSG_GETCLOSESTENEMY,
		MSG_GETANGULARSPEED,
		MSG_GETLINEARSPEED
	};
	MessageType type;
};

struct MessageGetRendering : public Message {
	MessageGetRendering() { 
		type = MSG_GRENDERING; 
	}
	Image* render;
	int frame;
	int x, y;
	int width, height;
	double rotion;
};

struct MessageReduceLife : public Message {
	MessageReduceLife() {
		type = MSG_REDUCELIFE;
	}
	float damage;
};

struct MessageReduceEnergy : public Message {
	MessageReduceEnergy() {
		type = MSG_REDUCEENERGY;
	}
	float consumption;
};

struct MessageGetLife : public Message {
	MessageGetLife() {
		type = MSG_GLIFE;
	}
	float life;
};

struct MessageGetEnergy : public Message {
	MessageGetEnergy() {
		type = MSG_GENERGY;
	}
	float energy;
};

struct MessageCheckCollision : public Message {
	MessageCheckCollision() {
		type = MSG_CHECKCOLLISION;
	}
	Entity * entity;
};
struct MessageCheckLaserCollision : public Message {
	MessageCheckLaserCollision() {
		type = MSG_CHECKLASERCOLLISION;
	}
	World::Laser * laser;
	bool hit;
	double hitX, hitY;
};
struct MessageGetCollider : public Message {
	MessageGetCollider() {
		type = MSG_GCOLLIDER;
	}
	Collision * collider;
};
struct MessageAllertCollision : public Message {
	MessageAllertCollision() {
		type = MSG_ALERTCOLLISION;
	}
	Entity * entity;
};
struct MessageExplode : public Message {
	MessageExplode() {
		type = MSG_EXPLODE;
	}
	Entity * entity;
};
struct MessageSetWaponReady : public Message {
	MessageSetWaponReady() {
		type = MSG_WEAPONREADY;
	}
};
struct MessageFire : public Message {
	enum Weapon {
		W_MAIN,
		W_SECODARY
	};
	MessageFire() {
		type = MSG_FIRE;
	}
	bool fire;
	Weapon weapon;
	double CurrentEnergy,energyConsumption, range, x, y, width, height, rotation;
	Entity * o_shot;
	
};
struct MessegGetColsestEnemy : public Message {
	MessegGetColsestEnemy(){
		type = MSG_GETCLOSESTENEMY;
	}
	Entity * o_enemie;
	double o_distance;
};

struct MessageGetAngularSpeed : public Message {
	MessageGetAngularSpeed(){
		type = MSG_GETANGULARSPEED;
	}
	double o_speed;
};
struct MessageGetLinearSpeed : public Message {
	MessageGetLinearSpeed() {
		type = MSG_GETLINEARSPEED;
	}
	double o_speed;
};
#endif // !SCM_MESSAGES_H

