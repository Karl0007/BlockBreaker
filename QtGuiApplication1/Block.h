#pragma once
#include "Component.h"
#include "Render.h"
#include "Collider.h"
#include "Buff.h"
class Block :
	public Component
{
public:
	static int total;
	static bool totpro;
	int life;
	int protect;
	Block() {
		m_type = ComponentType::Block;
		start = false;
	}
	Block* Start(int l) {
		if (start) return this;
		total++;
		start = true;
		life = l;
		protect = 0;
		m_collider = m_gameObject->addComponent<Collider>()->Start(0, 0, 70, 40, 1, "BLOCK");
		m_render = m_gameObject->addComponent<Render>()->Start(1, 70, 40, 7, 1, 1, 1);
		//m_collider = static_cast<Collider*>(m_gameObject->addComponent(ComponentType::Collider));
		//m_render = static_cast<Render*>(m_gameObject->addComponent(ComponentType::Render));
		//m_collider->Start(0,0,70,40,1,"BLOCK");
		//m_render->Start(1,70,40,7,1,1,1);
		setColorByLife();
		return this;
	}
	void setColorByLife() {
		static default_random_engine e(time(0));
		static uniform_real_distribution<double> R(-5, 1);
		switch (life)
		{
		case 0:
			if (R(e)>0)MainGame::getInstance().creatObject(m_gameObject->m_posx, m_gameObject->m_posy)->addComponent<Buff>()->Start();
			MainGame::getInstance().delObject(m_gameObject);
			return;
		case 5:
			m_render->resetC(0.25, 0, 0.5);
			return;
		case 4:
			m_render->resetC(0, 0, 0.9);
			return;
		case 3:
			m_render->resetC(0, 0.5, 0.5);
			return;
		case 2:
			m_render->resetC(0, 0.9, 0);
			return;
		case 1:
			m_render->resetC(0.8, 0.5, 0);
			return;
		default:
			m_render->resetC(1, 1, 1);
			return;
		}
	}
	void OnCollider(Component &oth) {
		auto& o = static_cast<Collider&>(oth);
		if (o.tag == "BALL" && !protect && !totpro) {
			auto &pow = static_cast<Ball*>(o.m_gameObject->getComponent(ComponentType::Ball))->powerful;
			if (pow) pow--;
			MainGame::getInstance().addScore(100);
			if (life == 6) MainGame::getInstance().creatObject(m_gameObject->m_posx, m_gameObject->m_posy)->addComponent<Buff>()->Start();

			life--;
			setColorByLife();
			protect = 10;
			totpro = true;
		}
	}
	void Update() {
		if (protect) protect--;
		totpro = false;
		
	}
	virtual ~Block() {
		total--;
	}
private:
	Collider *m_collider;
	Render *m_render;
};

