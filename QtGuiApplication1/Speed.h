#pragma once
#include "Component.h"
#include "MainGame.h"
#include "Collider.h"
#include <iostream>
class MainGame;
class Speed :
	public Component
{
public:
	float vx, vy;
	Speed() { m_type = ComponentType::Speed; start = false; }
	void Update(){
		if (!start) return;
		m_gameObject->m_posx += vx * MainGame::getInstance().getDeltaTime();
		m_gameObject->m_posy += vy * MainGame::getInstance().getDeltaTime();
	}
	Speed* Start(float x, float y) {
		if (start) return this;
		setSpeed(x, y);
		start = true;
		return this;
	}
	void normal(float len) {
		float tmp = sqrt(vx*vx + vy * vy);
		vx /= tmp;
		vx *= len;
		vy /= tmp;
		vy *= len;
	}
	void setSpeed(float x, float y) { vx = x, vy = y; }
	virtual ~Speed();
};

