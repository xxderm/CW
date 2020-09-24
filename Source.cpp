#include "Scene/GameScene.h"
#undef main

int main(int argc, char** argv)
{
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
		// log
	}
	delete ApplicationScene;
	return 0;
}