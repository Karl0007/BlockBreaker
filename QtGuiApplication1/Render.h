#pragma once
#include "Component.h"
#include "MainGame.h"
#include <functional>
using std::bind;
class MainGame;
class Render :
	public Component
{
public:
	int type;
	float sizex, sizey, len;
	float r, g, b, rl, gl, bl;
	float px, py;
	Render() { m_type = ComponentType::Render; start = false; }
	void resetS(int t, float x, float y, float l) {
		type = t;
		sizex = x;
		sizey = y;
		len = l;
	}
	void resetC(float R, float G, float B) {
		r = R * 0.8;
		g = G * 0.8;
		b = B * 0.8;
		rl = R;
		gl = G;
		bl = B;
	}
	void reset(int t,float x,float y,float l,float R,float G,float B,float pxx=0,float pyy=0) {
		resetC(R, G, B);
		resetS(t, x, y, l);
		px = pxx;
		py = pyy;
	}
	Render* Start(int t, float x, float y, float l, float R, float G, float B,float pxx=0,float pyy=0) {
		if (start) return this;
		reset(t, x, y, l, R, G, B,pxx,pyy);
		start = true;
		return this;
	}
	void Update(){
		if (!start) return;
		if (type == 0) {
			MainGame::getInstance().DrawC(m_gameObject->m_posx+px,m_gameObject->m_posy+py,sizex,r,g,b,rl,gl,bl,len);
		}
		if (type == 1) {
			MainGame::getInstance().DrawR(m_gameObject->m_posx+px, m_gameObject->m_posy+py, sizex,sizey, r, g, b, rl, gl, bl, len);
		}
	}
	virtual ~Render();
};

