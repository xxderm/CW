#include "Scene/MenuScene.h"
#include "Scene/UIDebugScene.h"
#undef main

int main(int argc, char** argv)
{	
	Scene* ApplicationScene = new Scene();
	ApplicationScene->Init();
	ApplicationScene->ChangeScene(UIDebugScene::getInstance());
	try
	{
		while (ApplicationScene->isRunning())
		{
			// TODO: Add request/response interval
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