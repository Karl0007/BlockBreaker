#pragma once
#include <set>
#include <unordered_set>
#include <memory>
#include <vector>
#include "Component.h"
#include "ComponentFactory.h"
using namespace std;
class Component;
enum class ComponentType;
class GameObject
{
	friend class Collider;
private:
	unordered_set<Component*> m_components;
public:
	float m_posx, m_posy;
	template<typename T>
	T* addComponent() {
		auto tmp = new T;
		m_components.insert(tmp);
		tmp->m_gameObject = this;
		return tmp;
	}
	Component* addComponent(ComponentType type);
	Component* getComponent(ComponentType type);
	vector<Component*> getComponents(ComponentType type);
	void delComponents(Component* com);
	void Update();
	GameObject(float x = 0, float y = 0) : m_posx(x), m_posy(y) {}
	virtual ~GameObject();
};

