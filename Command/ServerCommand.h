#pragma once
#ifndef SERVER_COMMAND_HEADER
#define SERVER_COMMAND_HEADER
#include "Command.h"
#include <SDL_net.h>

class GetLobbyListCommand final : public Command
{
public:
	GetLobbyListCommand(UDPpacket* packet, UDPsocket* socket);
	void Execute() override;
private:
	UDPpacket* mPacket_ptr;
	UDPsocket* mSocket_ptr;
};

#endif // !SERVER_COMMAND_HEADER
