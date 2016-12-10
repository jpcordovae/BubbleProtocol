//
// asynchronous tcp service 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// July 2016 
// Juan Pablo Cordova E. (jpcordovae@gmail.com)
//

#ifndef TCP_DB_SERVICE_HPP
#define TCP_DB_SERVICE_HPP

#include <cstdlib>
#include <iostream>
#include <list>
#include <deque>
#include <memory>
#include <utility>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include "common.hpp"

using boost::asio::ip::tcp;
using boost::asio::deadline_timer;


class session
  : public std::enable_shared_from_this<session>
{
public:
  
  session(tcp::socket socket) : m_socket(std::move(socket))
  {
  }
     
  void start()
  {
    do_read();
    do_write(std::string("BUUBLE PROTOCOL V0.1\n"));
  }

private:
  void do_read()
  {
    auto self(shared_from_this());
    boost::asio::async_read_until(m_socket,input_buffer_,'\n',
				  [this, self](boost::system::error_code ec, std::size_t length) 
				  {
				    if (!ec)
				      {
					try
					  {
					    //say hello to client
					    std::string sData = std::string(boost::asio::buffer_cast<const char*>(input_buffer_.data()),length);
					    std::cout << sData;
					    input_buffer_.consume(length);
					    
					  }catch(std::exception &e)
					  {
					    std::cerr << "exception: " << e.what() << std::endl;
					  }
					do_read();
				      }
				  });
  }

  void do_write(std::string _msg)
  {
    auto self(shared_from_this());
    boost::asio::async_write(m_socket, boost::asio::buffer(_msg.c_str(), _msg.size()),
			     [this, self](boost::system::error_code ec, std::size_t)
			     {
			       if (!ec)
				 {
				   //do_read();
				 }
			     });
  }
  
  boost::asio::streambuf input_buffer_;
  boost::asio::streambuf m_output_buffer;
  tcp::socket m_socket;
  //deadline_timer m_timer;
  int m_timed_out;
};

/*************************************************/

class server
{
public:
  server(boost::asio::io_service& io_service, short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      socket_(io_service)
  {
    m_io_service = &io_service;
    do_accept();
  }
   
private:
  void do_accept()
  {
	acceptor_.async_accept(	socket_,
				[this](boost::system::error_code ec)
			   	{
			     		if (!ec)
			       		{
						#ifdef DEBUG
				 		std::cout << "new session from IP (TODO)" << std::endl; //TODO: make this debug line
						#endif
				 		std::shared_ptr<session> my_session = std::make_shared<session>(std::move(socket_));
				 		my_session->start();
			       		}
					do_accept();
				});
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
  boost::asio::io_service *m_io_service;
};

#endif
