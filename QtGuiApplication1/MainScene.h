#pragma once

#include <qwidget.h>
#include <qgl.h>
#include <qmessagebox.h>
#include <vector>
#include <functional>
#include <mutex>
#include <qevent.h>
using namespace std;

class MainScene : public QGLWidget
{
	Q_OBJECT

public:	
	bool Updateing;

	MainScene(QWidget *parent = Q_NULLPTR);
	~MainScene();
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);
	void addFun(function<void(void)> fun);
	void DrawCircle0(float x, float y, float size, float r, float g, float b,int ts=16);
	void DrawCircle(float x, float y, float size, float r, float g, float b, float rl, float gl, float bl, float len,int ts=16);
	void DrawRect0(float x, float y, float lx, float ly, float r, float g, float b);
	void DrawRect(float x,float y, float lx, float ly, float r, float g, float b, float rl, float gl, float bl,float len);
private:
	vector <function<void(void)>> list;
};
