#include "ComponentFactory.h"
#include "Speed.h"
#include "Render.h"
#include "Collider.h"
#include "Ball.h"
#include "Wall.h"
#include "Block.h"
#include "Player.h"
int Block::total = 0;
bool Block::totpro = false;
ComponentFactory* ComponentFactory::Instance = nullptr;

ComponentFactory::ComponentFactory()
{
}


ComponentFactory::~ComponentFactory()
{
}


ComponentFactory & ComponentFactory::getInstance()
{
	if (!Instance) {
		Instance = new ComponentFactory();
	}
	return *Instance;
}

Component* ComponentFactory::getComponent(ComponentType type)
{
	switch (type)
	{
	case ComponentType::Speed:
		return new Speed;
	case ComponentType::Render:
		return new Render;
	case ComponentType::Collider:
		return new Collider;
	case ComponentType::Ball:
		return new Ball;
	case ComponentType::Wall:
		return new Wall;
	case ComponentType::Block:
		return new Block;
	case ComponentType::Player:
		return new Player;
	}
	return nullptr;

}