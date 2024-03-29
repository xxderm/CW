#pragma once
#ifndef UI_COMMAND_HEADER
#define UI_COMMAND_HEADER
#include "Command.h"

class ExitCommand final : public Command
{
public:
	ExitCommand(Scene* scene);
	void Execute() override;
private:
	Scene* mScene_ptr;
};

class ChangeSceneCommand final : public Command
{
public:
	ChangeSceneCommand(Scene* src, SceneMachine* dst);
	void Execute() override;
private:
	Scene* mScene_ptr;
	SceneMachine* mSceneMachine_ptr;
};

class ClearLobbyListCommand final : public Command
{
public:
	ClearLobbyListCommand(std::vector<Lobby>* lobbies);
	void Execute() override;
private:
	std::vector<Lobby>* mLobbies;
};

class SelectCountryCommand final : public Command
{
public:
	SelectCountryCommand(Scene* scene, CountryFormat* country);
	void Execute() override;
private:
	Scene* mScene_ptr;
	CountryFormat* mCountry_ptr;
};

class AddFormCommand final : public Command
{
public:
	AddFormCommand(GUITexture* Gui_ptr);
	void Execute() override;
private:
	GUITexture* mGui_ptr;
};

class GetFormCommand final : public Command
{
public:
	GetFormCommand(GUITexture* Gui_ptr, std::string* FormName);
	void Execute() override;
private:
	GUITexture* mGui_ptr;
	std::string* mFormName_ptr;
};

class SaveFormCommand final : public Command
{
public:
	SaveFormCommand(GUITexture* Gui_ptr, std::string* GuiSavePath);
	void Execute() override;
private:
	GUITexture* mGui_ptr;
	std::string* mGuiSavePath;
};

class ApplyFormSettingsCommand final : public Command
{
public:
	ApplyFormSettingsCommand(GUITexture* Gui_ptr, std::string* FormName);
	void Execute() override;
private:
	GUITexture* mGui_ptr;
	std::string* mFormName_ptr;
};

#endif // !UI_COMMAND_HEADER