#pragma once
#include "Component.h"
#include <random>
#include <time.h>
#include <stdlib.h>
#include <unordered_set>
using std::default_random_engine;
using std::uniform_real_distribution;
using std::unordered_set;

class Ball :
	public Component
{
public:
	static int total;
	static unordered_set<Ball*> all_balls;
	bool rev;
	int powerful;
	Ball() {
		m_type = ComponentType::Ball;
		start = false;
	}
	Ball* Start() {
		if (start) return this;
		start = true;
		powerful = 0;
		all_balls.insert(this);
		total++;
		m_staticSpeed = 0.3;
		m_speed = m_gameObject->addComponent<Speed>()->Start(1, 1);
		m_render = m_gameObject->addComponent<Render>()->Start(0, 16, 0, 7, 0, 1, 1);
		m_collider = m_gameObject->addComponent<Collider>()->Start(-12, -12, 24, 24, 0, "BALL");
		m_speed->normal(m_staticSpeed);

		//m_speed = static_cast<Speed*>(m_gameObject->addComponent(ComponentType::Speed));
		//m_render = static_cast<Render*>(m_gameObject->addComponent(ComponentType::Render));
		//m_collider = static_cast<Collider*>(m_gameObject->addComponent(ComponentType::Collider));
		//m_speed->Start(0,1);
		//m_speed->normal(m_staticSpeed);
		//m_render->Start(0,16,0,7,0,1,1);
		//m_collider->Start(-12,-12,24,24,0,"BALL");
		return this;
	}
	virtual void OnCollider(Component &oth) {
		if (!rev) return;
		rev = false;
		auto & o = static_cast<Collider&>(oth);
		//cout << "ball on" << oth.m_gameObject->m_posx << "??" << oth.m_gameObject->m_posy<<endl;

		static default_random_engine e(time(0));
		static uniform_real_distribution<double> R(5, 10);
		static uniform_int_distribution<int> u(0, 1);
		//e.seed(123);
		if (o.tag == "WALLSIDE") {
			m_gameObject->m_posx -= m_speed->vx * 1 * MainGame::getInstance().getDeltaTime();
			m_speed->vx = -m_speed->vx;
			m_speed->vy = m_speed->vy;
		}
		if (o.tag == "WALLTOP"  || o.tag == "GAMEOVER") {
			m_gameObject->m_posy -= m_speed->vy * 1 * MainGame::getInstance().getDeltaTime();
			m_speed->vx = m_speed->vx;
			m_speed->vy = -m_speed->vy;
		}
		if (o.tag == "PLAYER") {
			m_gameObject->m_posy += abs(m_speed->vy) * 1 * MainGame::getInstance().getDeltaTime();
			m_speed->vx = m_speed->vx;
			m_speed->vy = abs(m_speed->vy);
		}

		
		if (o.tag == "BLOCK") {
			if (powerful) {
			}
			else {
				m_gameObject->m_posx -= m_speed->vx * 1 * MainGame::getInstance().getDeltaTime();
				m_gameObject->m_posy -= m_speed->vy * 1 * MainGame::getInstance().getDeltaTime();
				m_speed->vx = R(e) * (u(e) ? -1 : 1);
				m_speed->vy = R(e) * (u(e) ? -1 : 1);
			}
		}
		if (o.tag == "GAMEOVER" && !MainGame::getInstance().KARL07__) {
			MainGame::getInstance().delObject(m_gameObject);
			//MainGame::getInstance().End();
		}
		//cout << static_cast<Collider&>(oth).tag << endl;
		m_speed->normal(m_staticSpeed);

	}
	void Update() {
		rev = true;
		if (powerful) m_render->resetC(1, 0, 0); else m_render->resetC(0, 1, 1);
	}
	virtual ~Ball() {
		if (start) {
			all_balls.erase(this);
			total--;
		}
	}

private:

	float m_staticSpeed;
	Speed * m_speed;
	Render * m_render;
	Collider * m_collider;

};

