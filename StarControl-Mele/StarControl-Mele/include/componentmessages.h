#ifndef SCM_MESSAGES_H
#define SCM_MESSAGES_H

#pragma warning(disable:4820)

class Image;
class Collision;

struct Message {
	enum MessageType {
		MSG_GRENDERING,
		MSG_REDUCELIFE,
		MSG_REDUCEENERGY,
		MSG_GLIFE,
		MSG_GENERGY,
		MSG_GTRANSFORM,
		MSG_CHECKCOLLISION,
		MSG_GCOLLIDER,
		MSG_ALERTCOLLISION,
		MSG_EXPLODE
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

struct MessageGetTransform : public Message {
	MessageGetTransform() {
		type = MSG_GTRANSFORM;
	}
	double x,y,width,height;
};

struct MessageCheckCollision : public Message {
	MessageCheckCollision() {
		type = MSG_CHECKCOLLISION;
	}
	Entity * entity;
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
#endif // !SCM_MESSAGES_H

