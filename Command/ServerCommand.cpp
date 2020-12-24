#include "ServerCommand.h"

GetLobbyListCommand::GetLobbyListCommand(UDPpacket* packet, UDPsocket* socket)
	: mPacket_ptr(packet), mSocket_ptr(socket)
{
}

void GetLobbyListCommand::Execute()
{
	std::string ClientInput = "{ \"Signal\": 5 }";
	mPacket_ptr->len = ClientInput.size() + 1;
	memcpy(mPacket_ptr->data, (Uint8*)ClientInput.c_str(), mPacket_ptr->len);
	SDLNet_UDP_Send(*mSocket_ptr, -1, mPacket_ptr);
	SDLNet_UDP_Send(*mSocket_ptr, -1, mPacket_ptr);
}
