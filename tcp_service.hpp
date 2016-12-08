//
// asynchronous tcp DAQ service for microcontrollers
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// July 2015 
// Juan Pablo Cordova E. (jpcordovae@gmail.com)
//
// Orignal file asynchronous tcp service example 
// from Christopher M. Kohlhoff (chris@kohlhoff.com)
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

class session
  : public std::enable_shared_from_this<session>
{
public:

  void set_query_begin(std::string _qbegin) { query_begin = _qbegin; }
  void set_query_end(std::string _qend){ query_end = _qend; }
  std::string get_query_begin() { return query_begin; }
  std::string get_query_end() { return query_end; }

  session(tcp::socket socket)
    : socket_(std::move(socket))
  {
  }
     
  void start()
  {
    do_read();
  }

private:
  void do_read()
  {
    auto self(shared_from_this());
    boost::asio::async_read_until(socket_,input_buffer_,'\n',
				  [this, self](boost::system::error_code ec, std::size_t length) // uncomment commented
				  {
				    if (!ec)
				      {
					try
					  {
					  	std::cout << std::string(boost::asio::buffer_cast<const char*>(input_buffer_.data()),length);
						input_buffer_.consume(length);
					  }catch(std::exception &e)
					  {
					    std::cerr << "exception: " << e.what() << std::endl;
					  }
					do_read();
				      }
				  });
  }

  void do_write(std::size_t length)
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
			     [this, self](boost::system::error_code ec, std::size_t)
			     {
			       if (!ec)
				 {
				   do_read();
				 }
			     });
  }

  void parse_string(std::string _message)
  {
    
  }

  boost::asio::streambuf input_buffer_;
  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
  std::string query_begin;
  std::string query_end;
  
};

/*************************************************/

class server
{
public:
  server(boost::asio::io_service& io_service, short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      socket_(io_service)
  {
    do_accept();
  }
   
  void set_query_begin(std::string _qbegin) { query_begin = _qbegin; }
  void set_query_end(std::string _qend){ query_end = _qend; }
  std::string get_query_begin() { return query_begin; }
  std::string get_query_end() { return query_end; }

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
				 		my_session->set_query_begin(query_begin);
				 		my_session->set_query_end(query_end);
				 		my_session->start();
			       		}
					do_accept();
				});
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
  std::string query_begin;
  std::string query_end;

};

#endif
