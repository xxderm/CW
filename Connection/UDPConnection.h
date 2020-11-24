#pragma once
#ifndef UDP_CONNECTION_HEADER
#define UDP_CONNECTION_HEADER
#include "Connection.h"

class UDPConnection : public Connection
{
public:
	UDPConnection();
	void Connect() override;	
protected:
	UDPsocket mSocket;
	IPaddress mIp;
	IPaddress* mClientIP;
	Uint32 mIpAddr;
	Uint16 mPort;
	Uint16 mSize;
	UDPpacket* mPacket;
	std::string mIPv4;
};

class ConnectedUDP : public UDPConnection
{
public:
	ConnectedUDP();
	UDPsocket* getSocket();
	UDPpacket* getPacket();
protected:
	virtual void Listen() = 0;
	virtual void Response() = 0;
	bool hasReceived();
};

#endif // !UDP_CONNECTION_HEADER
