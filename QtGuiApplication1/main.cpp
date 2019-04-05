#include "MainWindow.h"
#include "MainScene.h"
#include "MainGame.h"
#include "QtClasstry.h"
#include <iostream>
#include <fstream>
#include <QtWidgets/QApplication>
#include <qaction.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainGame::getInstance();
	return a.exec();
}
