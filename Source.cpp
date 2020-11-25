#include "Scene/MenuScene.h"
#undef main
#include "World/World.h"
int main(int argc, char** argv)
{	
	World* w = new World();
	w->Create();
	Scene* ApplicationScene = new Scene();
	ApplicationScene->Init();
	ApplicationScene->ChangeScene(MenuScene::getInstance());
	try
	{
		while (ApplicationScene->isRunning())
		{
			ApplicationScene->Response();
			ApplicationScene->Listen();
			ApplicationScene->HandleEvents();
			ApplicationScene->Update();
			ApplicationScene->Draw();
		}
		ApplicationScene->Clean();
	}
	catch (const std::exception& ex)
	{
		LOG(ERROR) << ex.what();
	}
	catch (const std::string& ex)
	{
		LOG(ERROR) << ex.c_str();
	}
	catch (...)
	{
		LOG(ERROR) << "Unknown exception";
	}
	delete ApplicationScene;
	return 0;
}