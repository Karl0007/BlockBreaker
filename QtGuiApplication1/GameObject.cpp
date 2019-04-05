#include "GameObject.h"
#include <iostream>



Component * GameObject::addComponent(ComponentType type)
{
	auto tmp = ComponentFactory::getInstance().getComponent(type);
	m_components.insert(tmp);
	tmp->m_gameObject = this;
	return tmp;
}

Component * GameObject::getComponent(ComponentType type)
{
	for (auto &x : m_components) {
		if (x->m_type == type) {
			return x;
		}
	}
	return nullptr;
}



vector<Component*> GameObject::getComponents(ComponentType type)
{
	vector<Component*> tmp;
	for (auto &x : m_components) {
		if (x->m_type == type) {
			tmp.push_back(x);
		}
	}
	return tmp;
}

void GameObject::delComponents(Component * com)
{
	if (m_components.count(com)) {
		m_components.erase(com);
		delete com;
	}
}

void GameObject::Update()
{
	for (auto x : m_components) {
		x->Update();
	}
	
}

GameObject::~GameObject()
{
	for (auto &x : m_components) {
		//std::cout << int(x->m_type) << std::endl;
		delete x;
	}
}
