#define GUI
#include "MainWindow.h"
#include "MainScene.h"
#include "MainGame.h"
#include "QtClasstry.h"
#include "ConsoleWindow.h"
#include <iostream>
#include <fstream>
#include <QtWidgets/QApplication>
#include <qaction.h>

//#define CONSOLE

int main(int argc, char *argv[])
{
#ifdef GUI
	QApplication a(argc, argv);
	MainGame::getInstance();
	return a.exec();
#endif // GUI

#ifdef CONSOLE
	MainGame::getInstance().Play();
#endif // CONSOLE



}
