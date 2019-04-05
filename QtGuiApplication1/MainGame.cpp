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
MainGame* MainGame::Instance = nullptr;

MainGame::MainGame()
{
	ifstream is;
	is.open("KARL07");
	KARL07__ = is.is_open();
	w = new MainWindow;
	w->show();
	Score = 0;
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
	playing = true;
	w->m_scene->Updateing = true;
	Score = 0;
	Start();
	//thread t(&MainGame::Work,this);
	//t.detach();
}

void MainGame::Work()
{
	Start();

	//auto t = clock();
	//while (playing) {
	//	Update();
	//	DeltaTime = clock() - t;
	//	t = clock();
	//	w->m_scene->paintGL();
	//	//std::cout << DeltaTime << endl;
	//}
	//End();
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
	GameObject * tmp;
	//tmp = creatObject(350,300);
	creatObject(350, 300)->addComponent<Ball>()->Start();
	creatObject(0, 0)->addComponent<Wall>()->Start();
	creatObject(300, 0)->addComponent<Player>()->Start(0.5, 100);
	
	//static_cast<Ball*>(creatObject(350,300)->addComponent(ComponentType::Ball))->Start();
	//static_cast<Wall*>(creatObject(0,0)->addComponent(ComponentType::Wall))->Start();
	//static_cast<Player*>(creatObject(300, 0)->addComponent(ComponentType::Player))->Start(0.5, 100);
	for (int x = 40,c=0; x <= 520; x += 75) {
		for (int y = 600; y >= 450; y -= 50,c++) {
			creatObject(x, y)->addComponent<Block>()->Start(c%6+1);
			//static_cast<Block*>(creatObject(x,y)->addComponent(ComponentType::Block))->Start(c%6+1);
		}
	}
}

void MainGame::Start()
{
	playing = 1;
	DeltaTime = 0;
	initGame();
	w->m_scene->paintGL();
	//auto obj = creatObject(200, 200);
	//static_cast<Render*>(obj->addComponent(ComponentType::Render))->Start(1,50,50,10,1,0,0);
	//static_cast<Speed*>(obj->addComponent(ComponentType::Speed))->Start(0.1, 0.1);
	//static_cast<Collider*>(obj->addComponent(ComponentType::Collider))->Start(0,0,50,50,0);
	//auto obj2 = creatObject(500, 500);
	//static_cast<Render*>(obj2->addComponent(ComponentType::Render))->Start(0, 25, 0, 10, 0, 1, 0);
	//static_cast<Collider*>(obj2->addComponent(ComponentType::Collider))->Start(-25, -25, 50, 50, 1);
	//auto obj3 = creatObject(100, 100);
	//static_cast<Ball*>(obj3->addComponent(ComponentType::Ball))->Start();
	//auto obj4 = creatObject(0, 0);
	//static_cast<Wall*>(obj4->addComponent(ComponentType::Wall))->Start();
	//auto obj5 = creatObject(300, 300);
	//static_cast<Block*>(obj5->addComponent(ComponentType::Block))->Start(3);
	//obj5 = creatObject(400, 300);
	//static_cast<Block*>(obj5->addComponent(ComponentType::Block))->Start(3);
	//auto obj6 = creatObject(300, 30);
	//<Player*>(obj6->addComponent(ComponentType::Player))->Start(0.5,100);



}

void MainGame::Update()
{
	//cout << getKey() << endl;
	for (auto x : m_objs) {
		//cout << x->m_posx << " " << x->m_posy << endl;
		x->Update();
	}
	for (auto x : Todelete) {
		m_objs.erase(x);
		delete x;
	}
	Todelete.clear();
	w->m_lable->setText(QString("Your Score\n") +QString::number(Score));
	if (Block::total == 0 && Score!=0) {
		End(true);
	}
}

void MainGame::End(bool win)
{
	if (!playing) return;
	//cout << "You Lose" << endl;
	playing = false;
	w->m_scene->Updateing = false;
	for (auto x : m_objs) {
		delObject(x);
	}
	if (win) {
		QMessageBox::about(w, "You Win",QString("Your Score : ") + QString::number(Score));
	}
	else {
		QMessageBox::about(w, "You Lose", QString("Your Score : ") + QString::number(Score));
	}
	w->m_button->setEnabled(1);

}

