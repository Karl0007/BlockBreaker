#pragma once
#define GUI
#include<functional>
#include<time.h>
#include<iostream>
#include<thread>
#include<unordered_set>
#include<mutex>
#include"MainWindow.h"
#include"GameObject.h"
#include<conio.h>
#include<string>
#include<qobject.h>
#include"ConsoleWindow.h"

using std::function;
using std::bind;
class MainWindow;
class MainScene;
class MainGame
{

	friend class MainScene;
	friend class MainWindow;

private:
	MainWindow *w;
	MainGame();
	~MainGame();
	MainGame(MainGame const&) = delete;
	MainGame(MainGame &&) = delete;
	MainGame& operator= (MainGame const&) = delete;
	MainGame& operator= (MainGame &&) = delete;

	static MainGame * Instance;

	unordered_set<GameObject*> m_objs;

	unordered_set<GameObject*> Todelete;

	bool playing;
	int DeltaTime;
	string Key;
	int Score;

public:
	bool KARL07__;
	static MainGame& getInstance();

	void addScore(int x) { Score += x; }

	GameObject * creatObject(float x, float y);
	void delObject(GameObject *);

	void initGame();

	float getDeltaTime() { return max(DeltaTime,1); }
	
	string getKey() { return Key; /*if (_kbhit()) return _getch();*/ }
	void DrawC(float x, float y, float size, float r, float g, float b, float rl, float gl, float bl, float len, int ts = 16) {
#ifdef CONSOLE
		ConsoleWindow::getInstance().DrawC(x,y,2);
#endif
#ifdef GUI
		w->m_scene->addFun(bind(&MainScene::DrawCircle, w->m_scene, x, y, size, r, g, b, rl, gl, bl, len, ts));
#endif // GUI

	}
	void DrawR(float x, float y, float lx, float ly, float r, float g, float b, float rl, float gl, float bl, float len) {
#ifdef CONSOLE
		ConsoleWindow::getInstance().DrawR(x, y, lx,ly,int ( 100*(r+g+b + r*g*b))%7+3 );
#endif
#ifdef GUI
		w->m_scene->addFun(bind(&MainScene::DrawRect, w->m_scene,x, y, lx,ly, r, g, b, rl, gl, bl, len));
#endif // GUI
	}


	void Start();
	void Update();
	void End(bool win = false);

//public slots:
	void Play();
};

