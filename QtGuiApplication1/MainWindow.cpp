#include "MainWindow.h"
#include "MainScene.h"
#include "MainGame.h"
#include <qlayout.h>
#include <iostream>
#include <qmessagebox.h>
#include <qaction.h>
#include<qtextcodec.h>
MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	//this->grabMouse();
	//this->grabKeyboard();
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	auto author = new QLabel(codec->toUnicode("By ³ÂÊ¢âý \n 181860007 \n github:Karl0007"));
	m_button = new QPushButton("Start",this);
	m_lable = new QLabel("Your Score\n 0",this);
	m_scene = new MainScene(this);
	m_scene->setFixedSize(QSize(600, 700));
	m_lable->setAlignment(Qt::AlignCenter);
	author->setAlignment(Qt::AlignCenter);
	QHBoxLayout *Hlayout = new QHBoxLayout;
	QVBoxLayout *scenelayout = new QVBoxLayout;
	QVBoxLayout *statelayout = new QVBoxLayout;
	scenelayout->addWidget(m_scene);

	
	statelayout->addStretch();
	statelayout->addWidget(m_lable);
	statelayout->addStretch();
	statelayout->addWidget(m_button);
	statelayout->addStretch();
	statelayout->addWidget(author);
	statelayout->addStretch();

	Hlayout->addLayout(scenelayout);
	Hlayout->addLayout(statelayout);

	this->setLayout(Hlayout);

	this->setFixedSize(QSize(770, 770));
	QObject::connect(m_button, &QPushButton::clicked, [&]() {MainGame::getInstance().Play(); m_button->setEnabled(false); });
	//std::cout << m_scene->size().height() << " " << m_scene->size().width();
}


