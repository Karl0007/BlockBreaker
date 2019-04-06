#pragma once
#include "GameObject.h"
class GameObject;
enum class ComponentType
{
	Collider,
	Speed,
	Render,
	Ball,
	Block,
	Wall,
	Player,
	Buff
};

class Component
{
public:
	ComponentType m_type;
	GameObject *m_gameObject;
	virtual Component* Start() { return nullptr; }
	virtual void Update() {}
	virtual void OnCollider(Component &) {}
	Component();
	virtual ~Component();

protected:
	bool start;
};

