//
// This software is derivated from third_party_lib.cpp at http://www.boost.org/doc/libs/1_53_0/doc/html/boost_asio/example/nonblocking/third_party_lib.cpp
// ~~~~~~~~~~~~~~~~~~~
// 
// This file: Copyright (c) 2013 Gustavo Gomes (github at guvux dot com dot br)
// Original file: Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "boost-server.h"

int main(int argc, char* argv[])
{
  try
  {
    // Initialize
	boost::asio::io_service io_service;
    boostServer::server s(io_service, SERVER_PORT);

    // Start server
	boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
	boost::this_thread::sleep(boost::posix_time::seconds(5));
	std::cout << "load\n";

	// Close server
	// boost::this_thread::interruption_point();
	// t.interrupt();
	std::cout << "interrupt\n";
	t.join();
	std::cout << "close\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}