#pragma once
#include "Component.h"
#include"Collider.h"
#include "Render.h"
class Wall :
	public Component
{
public:
	Wall() {
		m_type = ComponentType::Wall;
		start = false;
	}
	Wall* Start() {
		if (start) return this;
		start = true;
		m_gameObject->addComponent<Render>()->Start(1, 20, 700, 0, 0.8, 0.8, 0.8);
		m_gameObject->addComponent<Collider>()->Start(0, 0, 20, 700, 1, "WALLSIDE");
		m_gameObject->addComponent<Render>()->Start(1, 20, 700, 0, 0.8, 0.8, 0.8, 580, 0);
		m_gameObject->addComponent<Collider>()->Start(580, 0, 20, 700, 1, "WALLSIDE");
		m_gameObject->addComponent<Render>()->Start(1, 600, 20, 0, 1, 0, 0);
		m_gameObject->addComponent<Collider>()->Start(0, 0, 600, 20, 1, "GAMEOVER");
		m_gameObject->addComponent<Render>()->Start(1, 600, 20, 0, 0.8, 0.8, 0.8, 0, 680);
		m_gameObject->addComponent<Collider>()->Start(0, 680, 600, 20, 1, "WALLTOP");

		//static_cast<Render*>(m_gameObject->addComponent(ComponentType::Render))->Start(1, 20, 700, 0, 0.8, 0.8, 0.8);
		//static_cast<Collider*>(m_gameObject->addComponent(ComponentType::Collider))->Start(0, 0, 20, 700, 1,"WALLSIDE");
		//static_cast<Render*>(m_gameObject->addComponent(ComponentType::Render))->Start(1,20, 700, 0, 0.8, 0.8, 0.8,580,0);
		//static_cast<Collider*>(m_gameObject->addComponent(ComponentType::Collider))->Start(580, 0, 20, 700, 1,"WALLSIDE");
		//static_cast<Render*>(m_gameObject->addComponent(ComponentType::Render))->Start(1, 600, 20, 0, 1, 0, 0);
		//static_cast<Collider*>(m_gameObject->addComponent(ComponentType::Collider))->Start(0, 0, 600, 20, 1,"GAMEOVER");
		//static_cast<Render*>(m_gameObject->addComponent(ComponentType::Render))->Start(1, 600, 20, 0, 0.8, 0.8, 0.8,0,680);
		//static_cast<Collider*>(m_gameObject->addComponent(ComponentType::Collider))->Start(0, 680, 600, 20, 1,"WALLTOP");
		return this;
	}
	virtual ~Wall() {

	}
private:
	
};
