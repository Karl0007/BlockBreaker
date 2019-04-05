#pragma once

#include <QWidget>
#include <qwidget.h>
#include <MainScene.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qaction.h>
class QtClasstry : public QWidget
{
	Q_OBJECT

public:
	QtClasstry(QWidget *parent);
	~QtClasstry();
public:
	MainScene *m_scene;
	QLabel *m_lable;
	QPushButton *m_button;
};
