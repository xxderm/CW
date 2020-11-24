#include "UDPConnection.h"

ConnectedUDP::ConnectedUDP()
{
}

UDPsocket* ConnectedUDP::getSocket()
{
	return &this->mSocket;
}

UDPpacket* ConnectedUDP::getPacket()
{
	return this->mPacket;
}

bool ConnectedUDP::hasReceived()
{
	if (SDLNet_UDP_Recv(mSocket, mPacket))
		return true;
	return false;
}

UDPConnection::UDPConnection()
	: mSize(0)
{
}

void UDPConnection::Connect()
{
	if (SDLNet_Init() == -1)
		LOG(ERROR) << "UDPConnection: " << SDLNet_GetError();
	mSocket = SDLNet_UDP_Open(NULL);
	if (mSocket == nullptr)
		LOG(ERROR) << "UDPConnection: Failed to open UDP Socket";
	if (SDLNet_ResolveHost(&mIp, mIPv4.c_str(), mPort) == -1)
		LOG(ERROR) << "UDPConnection: Failed to resolve host";
	mPacket = SDLNet_AllocPacket(0xffff);
	mPacket->address.host = mIp.host;
	mPacket->address.port = mIp.port;
	if (SDLNet_UDP_Bind(mSocket, 0, &mIp) == -1)
		LOG(ERROR) << "UDPConnection: Failed to bind socket";
	mClientIP = SDLNet_UDP_GetPeerAddress(mSocket, -1);
}
