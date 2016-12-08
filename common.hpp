#ifndef __GPS_BASE_HPP__
#define __GPS_BASE_HPP__

#include <iostream>
#include <ctime>
#include <vector>

#include <boost/date_time.hpp>
#include <boost/shared_ptr.hpp>

//std::string timestamp_sql();

typedef std::vector<boost::uint8_t> buffertype;
typedef boost::shared_ptr<buffertype> buffertype_ptr;

#endif

