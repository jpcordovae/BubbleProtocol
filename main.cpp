#include "bubble.h"
#include "tcp_client.hpp"
#include "tcp_service.hpp"

#define DEBUG

int main(int argc, char *argv[])
{
	boost::asio::io_service io_service;
	server s(io_service,5409);
	try
	{
		io_service.run();
	}catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

