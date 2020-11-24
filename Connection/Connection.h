#pragma once
#ifndef CONNECTION_HEADER
#define CONNECTION_HEADER
#include <SDL_net.h>
#include "easylogging++.h"

enum SIGNAL : int
{
	CONNECT,
	DISCONNECT,
	PING,
	ADD_LOBBY,
	DELETE_LOBBY,
	GET_LOBBY_LIST,
	CONNECT_TO_LOBBY,
	LEAVE_FROM_LOBBY,
};

class Connection abstract
{
public:
	virtual void Connect() = 0;
};

#endif // !CONNECTION_HEADER
