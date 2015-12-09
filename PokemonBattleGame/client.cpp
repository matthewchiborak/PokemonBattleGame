#include "client.h"
#include <iostream>

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

void Client::sendMessage(string msg)					// Send message from the client
{
	socket.send(msg.c_str(), msg.size() + 1);
}

string Client::recieveMessage()							// Recieve Message from the client
{
	char buffer[1024];
	std::size_t recieved = 0;
	socket.receive(buffer, sizeof(buffer), recieved);

	std::string text;

	for (unsigned int i = 0; i < sizeof(buffer); i++)
	{
		if (buffer[i] == '~')
			break;
		else if (buffer[i] == '?')
			break;
		else
			text += buffer[i];
	}
	std::cout << "Server sends: " << text << std::endl;
	//if (text == "Server is closing")					// If server is closing then it will show an error 
	//{
	//	// Figure out some way to signal both threads to stop execution
	//}
	return text;
}
