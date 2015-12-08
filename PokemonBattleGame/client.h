#pragma once
#include <SFML/Network.hpp>
#include <string>

using std::string;

class Client
{
private:
	sf::TcpSocket socket;
	sf::Socket::Status status;
public:
	Client();
	~Client();
	void setSocket(string ip, int port);
};