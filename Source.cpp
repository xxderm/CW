#include "Scene/GameScene.h"
#undef main

#include "World/IWorld.h"
#include "World/WorldDecorator/State.h"
#include "World/WorldDecorator/Province.h"

class World : public IWorld
{
public:
	void Create() override 
	{

	}
};

int main(int argc, char** argv)
{	
	IWorld* world = new World();
	world = new Province(world);
	world = new State((Province*)world, world);
	world->Create();

	Scene* ApplicationScene = new Scene();
	ApplicationScene->Init();
	ApplicationScene->ChangeScene(GameScene::getInstance());
	try
	{
		while (ApplicationScene->isRunning())
		{
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