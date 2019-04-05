#include "MainScene.h"
#include <iostream>
#include "MainGame.h"
#include <time.h>
using namespace std;
MainScene::MainScene(QWidget *parent)
	: QGLWidget(parent)
{
	this->grabKeyboard();
	//this->grabMouse();
}

MainScene::~MainScene()
{
}

void MainScene::initializeGL()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_DEPTH);
}


void MainScene::paintGL()
{
	auto t = clock();
	if (Updateing) MainGame::getInstance().Update();
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	for (auto &f : list) {
		f();
	}
	list.clear();
	glPopMatrix();
	MainGame::getInstance().DeltaTime = clock() - t;
	if (Updateing) {
		update();
	}
}

void MainScene::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	//glMatrixMode(GL_MODELVIEW);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
}


void MainScene::addFun(function<void(void)> fun)
{
	list.push_back(fun);
}

void MainScene::DrawRect0(float x, float y, float lx, float ly, float r, float g, float b)
{
	glColor3f(r, g, b);
	glRectf(x, y, x+lx, y+ly);
}

void MainScene::DrawCircle0(float x, float y, float size, float r, float g, float b,int ts)
{
	const static float pi = 3.1415926536;
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	for (int i = 0; i < ts; i++)
	{
		glVertex2f(x + size*cos(2 * pi / ts * i),y + size*sin(2 * pi / ts * i));
	}
	glEnd();

}

void MainScene::DrawCircle(float x, float y, float size, float r, float g, float b, float rl, float gl, float bl, float len, int ts)
{
	DrawCircle0(x, y, size, rl, gl, bl,ts);
	DrawCircle0(x, y, size-len, r, g, b,ts);
}

void MainScene::DrawRect(float x, float y, float lx, float ly, float r, float g, float b, float rl, float gl, float bl, float len)
{
	DrawRect0(x, y, lx, ly, rl, gl, bl);
	DrawRect0(x+len/2, y+len/2, lx-len, ly-len, r, g, b);
}

void MainScene::keyPressEvent(QKeyEvent * e)
{
	if (e->key() == Qt::Key::Key_Left) 
		MainGame::getInstance().Key = "LEFT";
	if (e->key() == Qt::Key::Key_Right)
		MainGame::getInstance().Key = "RIGHT";
}

void MainScene::keyReleaseEvent(QKeyEvent * e)
{
	if (e->key() == Qt::Key::Key_Left)
		MainGame::getInstance().Key = "NULL";
	if (e->key() == Qt::Key::Key_Right)
		MainGame::getInstance().Key = "NULL";
}
