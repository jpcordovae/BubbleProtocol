#ifndef BUBBLE_HPP
#define BUBBLE_HPP

#include "bubble.h"
#include "tcp_client.hpp"
#include "tcp_service.hpp"

switch(m_handshake)
  {
  case NONE:
    std::cerr << "should not be here " << __LINE__ << " " << __FILE__ << std::endl; 
    break;
  case WELCOME:
    //TODO: trim sData
    if(sData.compare(std::string("V1.0\n"))!=0)
      {
	std::cout << "CLIENT VERSION NOT COMPATIBLE.\n";
	do_write(std::string("CONNECTION REJECTED BY PROTOCOL VERSION\n"));
      }else{
      do_write(std::string("CONNECTION ACCEPTED\n"));
      m_handshake = REJECTED;
    }
    m_handshake = ACCEPTED;
    break;
  case VERSION_CHECK:
    break;
  case ACCEPTED:
    break;
  case REJECTED:
    break;
  }


#endif
