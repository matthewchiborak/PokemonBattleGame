#include "client.h"
#include <iostream>
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "2000"


Client::Client()
{

}


Client::~Client()
{

}

bool Client::setSocket(string ip, int port)
{
	status = socket.connect(ip, port);
	if (status != sf::Socket::Done)
	{
		std::cout << "Error occurred opening socket.\n";
		return false;
	}
	else
	{
		return true;
	}
}

void Client::sendMessage(string msg)
{
	socket.send(msg.c_str(), msg.size() + 1);
}

string Client::recieveMessage()
{
	char buffer[1024];
	std::size_t recieved = 0;
	socket.receive(buffer, sizeof(buffer), recieved);

	std::string text;

	for (unsigned int i = 0; i < sizeof(buffer); i++)
	{
		if (buffer[i] == '~')
			break;
		else
			text += buffer[i];
	}
	
	return text;
}
