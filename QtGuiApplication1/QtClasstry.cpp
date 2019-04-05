#include "QtClasstry.h"
#include "MainScene.h"
#include <qlayout.h>
#include <iostream>
#include <qmessagebox.h>
#include <qaction.h>
QtClasstry::QtClasstry(QWidget *parent)
	: QWidget(parent)
{
	this->grabMouse();
	this->grabKeyboard();
	m_button = new QPushButton("Start", this);
	m_lable = new QLabel("Your Score\n 0", this);
	m_scene = new MainScene(this);
	m_scene->setFixedSize(QSize(600, 700));
	m_lable->setAlignment(Qt::AlignCenter);
	QHBoxLayout *Hlayout = new QHBoxLayout;
	QVBoxLayout *scenelayout = new QVBoxLayout;
	QVBoxLayout *statelayout = new QVBoxLayout;
	scenelayout->addWidget(m_scene);

	statelayout->addStretch();
	statelayout->addWidget(m_lable);
	statelayout->addStretch();
	statelayout->addWidget(m_button);
	statelayout->addStretch();

	Hlayout->addLayout(scenelayout);
	Hlayout->addLayout(statelayout);

	this->setLayout(Hlayout);

	this->setFixedSize(QSize(750, 750));
}

QtClasstry::~QtClasstry()
{
}
