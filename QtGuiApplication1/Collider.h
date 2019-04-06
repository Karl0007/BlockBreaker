#pragma once
#include "Component.h"
#include <unordered_set>
#include <iostream>
#include <string>
using namespace std;
using std::unordered_set;

class Collider :
	public Component
{
public:
	float m_stx, m_sty, m_lx, m_ly;
	int sta;
	bool start;
	string tag;
	Collider() { m_type = ComponentType::Collider; sta = -1; start = false; }
	Collider* Start(float x, float y, float lx, float ly,bool s,string t = "") {
		if (start) return this;
		m_stx = x, m_sty = y, m_lx = lx, m_ly = ly;
		sta = s;
		m_all.insert(this);
		if (!s) m_mov.insert(this);
		tag = t;
		start = true;
		return this;
	}
	void Update() {
		if (!start) return;
		if (sta) return;
		float locx = this->m_gameObject->m_posx + this->m_stx;
		float locy = this->m_gameObject->m_posy + this->m_sty;

		for (auto co : m_all) {
			float othx = co->m_gameObject->m_posx + co->m_stx;
			float othy = co->m_gameObject->m_posy + co->m_sty;
			if (co == this) continue;
			if ((abs(locx * 2 + m_lx - othx * 2 - co->m_lx) <= m_lx + co->m_lx) &&
				(abs(locy * 2 + m_ly - othy * 2 - co->m_ly) <= m_ly + co->m_ly)) {
				for (auto each : this->m_gameObject->m_components) {
					each->OnCollider(*co);
				}
				if (m_all.count(co) && co->sta) {
					for (auto each : co->m_gameObject->m_components) {
						each->OnCollider(*this);
					}
				}

			}

		}
	}
	virtual ~Collider() {
		if (!start) return;
		if (!sta) m_mov.erase(this);
		m_all.erase(this);
		//cout << "erase" << endl;
	}

private:
	static unordered_set<Collider*> m_mov;
	static unordered_set<Collider*> m_all;
};
