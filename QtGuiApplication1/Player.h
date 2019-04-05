#pragma once
#include "Component.h"
#include "Render.h"
#include "Collider.h"
class Player :
	public Component
{
public:
	float m_speed;
	float m_lenth;
	float m_ylen;
	float m_yspd;
	Player() {
		m_type = ComponentType::Player;
		start = false;
	}
	Player* Start(float spd,float len,float ys=0,float yl=0) {
		if (start) return this;
		start = true;
		m_speed = spd;
		m_lenth = len;
		m_ylen = yl;
		m_yspd = ys;
		m_render = m_gameObject->addComponent<Render>()->Start(1, m_lenth, 30, 10, 0.2, 0.6, 1);
		m_collider = m_gameObject->addComponent<Collider>()->Start(0, 0, m_lenth, 30, 0, "PLAYER");

		//m_render = static_cast<Render*>(m_gameObject->addComponent(ComponentType::Render));
		//m_collider = static_cast<Collider*>(m_gameObject->addComponent(ComponentType::Collider));
		//m_render->Start(1, m_lenth, 30, 10, 0.2, 0.6, 1);
		//m_collider->Start(0, 0, m_lenth, 30, 0, "PLAYER");
		return this;
	}
	void Update() {
		if (MainGame::getInstance().getKey() == string("LEFT")) {
			m_gameObject->m_posx -= m_speed;
			m_gameObject->m_posx = max(m_gameObject->m_posx,.0f );

		}
		if (MainGame::getInstance().getKey() == string("RIGHT")) {
			m_gameObject->m_posx += m_speed;
			m_gameObject->m_posx = min(m_gameObject->m_posx, 600 - m_lenth);
		}
	}
	virtual ~Player() {
	}
private:
	Render *m_render;
	Collider *m_collider;
};

