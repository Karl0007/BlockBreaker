#include "MainGame.h"
#include "Component.h"
#include "Render.h"
#include "Speed.h"
#include "Collider.h"
#include "Ball.h"
#include "Wall.h"
#include "Block.h"
#include "Player.h"
#include <qstring.h>
#include <qmessagebox.h>
#include <fstream>
#include <qapplication.h>
#include"ConsoleWindow.h"
#include"Buff.h"
MainGame* MainGame::Instance = nullptr;

MainGame::MainGame()
{
	ifstream is;
	is.open("KARL07");
	KARL07__ = is.is_open();
	Score = 0;
	playing = false;
#ifdef  GUI
	w = new MainWindow;
	w->setWindowTitle("BlockBreaker By Karl07 v0.6");
	w->show();
#endif //  GUI
#ifdef  CONSOLE
	cout << "´ò×©¿é¿ØÖÆÌ¨°æ\n" << endl;
	cout << "By ³ÂÊ¢âý 181860007\n" << endl;
	cout << "github : Karl0007\n\nhttps://github.com/Karl0007/\n" << endl;
	system("pause");
#endif //  CONSOLE

}


MainGame::~MainGame()
{
	//delete w;
	for (auto x : m_objs) {
		delete x;
	}
}

MainGame & MainGame::getInstance()
{
	if (!Instance) {
		Instance = new MainGame();
	}
	return *Instance;
}

void MainGame::Play()
{
	initGame();
#ifdef GUI
	w->m_scene->Updateing = true;
#endif // GUI
	playing = true;
	DeltaTime = 0;
	Score = 0;
	Start();
}

GameObject * MainGame::creatObject(float x, float y)
{
	auto tmp = new GameObject(x, y);
	m_objs.insert(tmp);
	return tmp;
}

void MainGame::delObject(GameObject * del)
{
	if (m_objs.count(del)) {
		Todelete.insert(del);
	}
}

void MainGame::initGame() {
	//GameObject * tmp;
	//tmp = creatObject(350,300);
	creatObject(300, 300)->addComponent<Ball>()->Start();
	creatObject(0, 0)->addComponent<Wall>()->Start();
	creatObject(300, 20)->addComponent<Player>()->Start(0.5, 100);
	//creatObject(500, 500)->addComponent<Buff>()->Start();
	//static_cast<Ball*>(creatObject(350,300)->addComponent(ComponentType::Ball))->Start();
	//static_cast<Wall*>(creatObject(0,0)->addComponent(ComponentType::Wall))->Start();
	//static_cast<Player*>(creatObject(300, 0)->addComponent(ComponentType::Player))->Start(0.5, 100);
#ifdef GUI
	for (int x = 40,c=0; x <= 520; x += 75) {
		for (int y = 600; y >= 450; y -= 50,c++) {
			creatObject(x, y)->addComponent<Block>()->Start(c % 6 + 1);
			//static_cast<Block*>(creatObject(x,y)->addComponent(ComponentType::Block))->Start(c%6+1);
		}
	}
#endif // GUI
#ifdef CONSOLE
	for (int x = 40, c = 0; x <= 520; x += 120) {
		for (int y = 600; y >= 450; y -= 80, c++) {
			creatObject(x, y)->addComponent<Block>()->Start(1);
			//static_cast<Block*>(creatObject(x,y)->addComponent(ComponentType::Block))->Start(c%6+1);
		}
	}
#endif // CONSOLE
}

void MainGame::Start()
{
	//initGame();
	//Update();
#ifdef GUI
	w->m_scene->paintGL();
#endif // GUI
#ifdef CONSOLE
	while (playing) {
		auto t = clock();
		Update();
		//system("pause");
		ConsoleWindow::getInstance().Clear();
		DeltaTime = clock() - t;
		Key = ConsoleWindow::getInstance().GetKey();
		//cout << Key;
		DeltaTime /= 2;
		//cout << DeltaTime << endl;
	}
#endif // CONSOLE

}

void MainGame::Update()
{
	for (auto x : m_objs) {
		x->Update();
	}
	for (auto x : Todelete) {
		m_objs.erase(x);
		delete x;
	}
	Todelete.clear();
	if (Block::total == 0 && Score != 0) {
		End(true);
	}
	if (Ball::total == 0 && playing) {
		End(false);
	}
#ifdef GUI
	w->m_lable->setText(QString("Your Score\n") + QString::number(Score));
#endif // GUI

}

void MainGame::End(bool win)
{
	if (!playing) return;
	playing = false;
	for (auto x : m_objs) {
		delObject(x);
	}
#ifdef CONSOLE
	ConsoleWindow::getInstance().SetColor(11);
	ConsoleWindow::getInstance().Clear();
	if (win) {
		cout << "You Win!"  <<"\nYour Scoure:" <<Score << endl;
	}
	else {
		cout << "You Lose!" << "\nYour Scoure:" << Score << endl;
	}
	system("pause");
#endif // CONSOLE

#ifdef GUI
	w->m_scene->Updateing = false;
	if (win) {
		QMessageBox::about(w, "You Win",QString("Your Score : ") + QString::number(Score));
	}
	else {
		QMessageBox::about(w, "You Lose", QString("Your Score : ") + QString::number(Score));
	}
	w->m_button->setEnabled(1);
#endif // GUI

}

