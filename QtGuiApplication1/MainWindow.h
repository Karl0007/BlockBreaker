#pragma once

//#include <QtWidgets/QMainWindow>
//#include <qwidget.h>
#include <qwidget.h>
#include <MainScene.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qaction.h>
//#include "ui_MainWindow.h"

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow(){}

public:
	MainScene *m_scene;
	QLabel *m_lable;
	QPushButton *m_button;
};
