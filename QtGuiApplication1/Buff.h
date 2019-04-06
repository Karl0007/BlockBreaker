#pragma once
#include "Component.h"
#include "Speed.h"
#include "Render.h"
#include "Collider.h"
#include "Player.h"
#include "Ball.h"
#include <random>
using namespace std;
class Buff :
	public Component
{
public:
	Buff() { start = false; m_type = ComponentType::Buff; }
	Buff* Start() {
		if (start) return this;
		start = true;
		m_gameObject->addComponent<Speed>()->Start(0, -0.1);
		m_render = m_gameObject->addComponent<Render>()->Start(0, 16, 0, 7, 0, 0, 0);
		m_gameObject->addComponent<Collider>()->Start(-12, -12, 24, 24, 0, "BUFF");
		return this;
	}
	void Update() {
		if (!start) return;
		static default_random_engine e(time(0));
		static uniform_real_distribution<double> R(0.5, 1);
		m_render->resetC(R(e), R(e), R(e));
	}

	void OnCollider(Component &oth) {
		auto& o = static_cast<Collider&>(oth);
		if (o.tag == "PLAYER") {
			static default_random_engine e(time(0));
			static uniform_int_distribution<int> R(1, 3);
			auto t=R(e);
			switch (t)
			{
			case 1:
				static_cast<Player*>(o.m_gameObject->getComponent(ComponentType::Player))->updateLen(15);
				break;
			case 2:
				MainGame::getInstance().creatObject(m_gameObject->m_posx, m_gameObject->m_posy)->addComponent<Ball>()->Start();
				break;
			case 3:
				for(auto x : Ball::all_balls)
				{
					x->powerful += 10;
				}
				break;
			default:
				break;
			}
			MainGame::getInstance().addScore(666);
			MainGame::getInstance().delObject(m_gameObject);
		}
		if (o.tag == "GAMEOVER") {
			MainGame::getInstance().delObject(m_gameObject);
		}
	}
	virtual ~Buff() {

	}
private:
	Render* m_render;
};



