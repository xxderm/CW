#include "MenuScene.h"

MenuScene MenuScene::mMenuScene;

void MenuScene::Init(Scene* scene)
{
	SDL_GetWindowSize(scene->getWindow(), &mWndWidth, &mWndHeight);
	mGUIRenderer = new GUIRenderer("Resources/UI/menu.ui.json", 30, scene);

	mGUIRenderer->Init(scene->getWindow());

	mCamera = new Camera(glm::vec3(68.72f, 10.83f, 18.34f));
	mCamera->setUp(glm::vec3(-0.0, 0.344642, -0.938734));
	mCamera->setRight(glm::vec3(1.0, 0.0, -0.00));
	mCamera->setFront(glm::vec3(-0.0, -0.938734, -0.344642));
	mMousePicker = new MousePicker(glm::vec2(128, 50), glm::vec2(mWndWidth, mWndHeight));

	mGUIRenderer->setCamera(mCamera);
	mGUIRenderer->setMousePicker(mMousePicker);



	boost::property_tree::ptree pt;
	pt.put("Signal", 0);
	pt.put("User", "Player");
	pt.put("Timestamp", time(NULL));
	std::stringstream ss;
	boost::property_tree::json_parser::write_json(ss, pt);
	auto ClientInput = ss.str();
	scene->getPacket()->len = ClientInput.size() + 1;
	memcpy(scene->getPacket()->data, (Uint8*)ClientInput.c_str(), scene->getPacket()->len);
	SDLNet_UDP_Send(*scene->getSocket(), -1, scene->getPacket());
}

void MenuScene::Clean()
{
}

void MenuScene::Pause()
{
}

void MenuScene::Resume()
{
}

void MenuScene::HandleEvents(Scene* scene)
{
	while (SDL_PollEvent(scene->getEvent()))
	{		
		mGUIRenderer->HandleEvent(scene->getEvent(), scene->getWindow());
	}
}

void MenuScene::Update(Scene* scene)
{
	mGUIRenderer->Update();
}

void MenuScene::Draw(Scene* scene)
{
	glClearColor(0.1, 0.1, 0.1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GetWindowSize(scene->getWindow(), &mWndWidth, &mWndHeight);
	glViewport(0, 0, mWndWidth, mWndHeight);
	mGUIRenderer->Render();
	SDL_GL_SwapWindow(scene->getWindow());
}

void MenuScene::Listen(Scene* scene)
{
	if (SDLNet_UDP_Recv(*scene->getSocket(), scene->getPacket()))
	{
		//std::cout << "Got: " << scene->getPacket()->data << std::endl;		
	}
}

void MenuScene::Response(Scene* scene)
{
	/*auto chrono_clock_now = std::chrono::system_clock::now().time_since_epoch();
	std::chrono::milliseconds chrono_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(chrono_clock_now);
	auto time_sent = chrono_time_ms.count();
	auto ClientInput = "2 " + std::to_string(time_sent);
	scene->getPacket()->len = ClientInput.size() + 1;
	memcpy(scene->getPacket()->data, (Uint8*)ClientInput.c_str(), scene->getPacket()->len);
	SDLNet_UDP_Send(*scene->getSocket(), -1, scene->getPacket());*/

}

MenuScene::~MenuScene()
{
}

MenuScene::MenuScene()
{
}
