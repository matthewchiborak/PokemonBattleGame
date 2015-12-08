#pragma once
#include <SFML/Network.hpp>
#include <string>

using std::string;

class ByteArray
{
public:
	std::vector<char> v;
	std::string ToString(void) const
	{
		std::string returnValue;
		for (int i = 0; i<v.size(); i++)
			returnValue.push_back(v[i]);
		return returnValue;
	}
	ByteArray(void) {}
	ByteArray(std::string const & in)
	{
		for (int i = 0; i<in.size(); i++)
			v.push_back(in[i]);
	}
	ByteArray(void * p, int s)
	{
		char * temp = (char*)p;
		for (int i = 0; i<s; i++)
			v.push_back(temp[i]);
	}
};

class Client
{
private:
	sf::TcpSocket socket;
	sf::Socket::Status status;
public:
	Client();
	~Client();
	bool setSocket(string ip, int port);
	void sendMessage(string msg);
	string recieveMessage();
};