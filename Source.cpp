#include "Scene/GameScene.h"
#undef main

#include "World/WorldDecorator/State.h"
#include "World/WorldDecorator/Province.h"
int main(int argc, char** argv)
{	
	Province* prov = new Province(nullptr);
	prov->Init();
	State* st = new State(nullptr);
	st->Init(prov);
	Scene* ApplicationScene = new Scene();
	ApplicationScene->ChangeScene(GameScene::getInstance());
	try
	{
		ApplicationScene->Init();
		while (ApplicationScene->isRunning())
		{
			ApplicationScene->HandleEvents();
			ApplicationScene->Update();
			ApplicationScene->Draw();
		}
		ApplicationScene->Clean();
	}
	catch (const std::exception& e)
	{
		LOG(ERROR) << e.what();
	}
	delete ApplicationScene;
	return 0;
}